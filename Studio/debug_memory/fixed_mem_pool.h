// -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*-
// vim:tabstop=4:shiftwidth=4:expandtab:

/*
 * Copyright (C) 2005-2013 Wu Yongwei <adah at users dot sourceforge dot net>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must
 *    not claim that you wrote the original software.  If you use this
 *    software in a product, an acknowledgement in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must
 *    not be misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 *
 * This file is part of Stones of Nvwa:
 *      http://sourceforge.net/projects/nvwa
 *
 */

/**
 * @file  fixed_mem_pool.h
 *
 * Definition of a fixed-size memory pool template for structs/classes.
 * This is a easy-to-use class template for pre-allocated memory pools.
 * The client side needs to do the following things:
 * - Use one of the macros
 *   - #DECLARE_FIXED_MEM_POOL,
 *   - #DECLARE_FIXED_MEM_POOL__NOTHROW, or
 *   - #DECLARE_FIXED_MEM_POOL__THROW_NOCHECK
 *   .
 *   at the end of the class (say, \c class \e _Cls) definitions.
 * - Optionally, specialize fixed_mem_pool::alignment to change the
 *   alignment value for this specific type.
 * - Optionally, specialize fixed_mem_pool::bad_alloc_handler to change
 *   the behaviour when all memory blocks are allocated.
 * - Call fixed_mem_pool<_Cls>::initialize at the beginning of the
 *   program.
 * - Optionally, call fixed_mem_pool<_Cls>::deinitialize at exit of the
 *   program to check for memory leaks.
 * - Optionally, call fixed_mem_pool<_Cls>::get_alloc_count to check
 *   memory usage when the program is running.
 *
 * @date  2013-10-06
 */

#ifndef NVWA_FIXED_MEM_POOL_H
#define NVWA_FIXED_MEM_POOL_H

#include <new>                  // std::bad_alloc
#include <assert.h>             // assert
#include <stdlib.h>             // size_t/NULL
#include "_nvwa.h"              // NVWA/NVWA_NAMESPACE_*
#include "c++11.h"              // _NOEXCEPT
#include "class_level_lock.h"   // nvwa::class_level_lock
#include "mem_pool_base.h"      // nvwa::mem_pool_base
#include "static_assert.h"      // STATIC_ASSERT

NVWA_NAMESPACE_BEGIN

/**
 * Defines the alignment of memory blocks.
 */
#ifndef MEM_POOL_ALIGNMENT
#define MEM_POOL_ALIGNMENT sizeof(void*)
#endif

/**
 * Class template to manipulate a fixed-size memory pool.  Please notice
 * that only allocate and deallocate are protected by a lock.
 *
 * @param _Tp  class to use the fixed_mem_pool
 */
template <class _Tp>
class fixed_mem_pool
{
public:
    typedef typename class_level_lock<fixed_mem_pool<_Tp> >::lock lock;
    /**
     * Specializable struct to define the alignment of an object in the
     * fixed_mem_pool.
     */
    struct alignment
    {
        static const size_t value = MEM_POOL_ALIGNMENT;
    };
    /**
     * Struct to calculate the block size based on the (specializable)
     * alignment value.
     */
    struct block_size
    {
        static const size_t value =
            (sizeof(_Tp) + fixed_mem_pool<_Tp>::alignment::value - 1)
                       & ~(fixed_mem_pool<_Tp>::alignment::value - 1);
    };
    static void*  allocate();
    static void   deallocate(void*);
    static bool   initialize(size_t size);
    static int    deinitialize();
    static int    get_alloc_count();
    static bool   is_initialized();
protected:
    static bool   bad_alloc_handler();
private:
    static void*  _S_mem_pool_ptr;
    static void*  _S_first_avail_ptr;
    static int    _S_alloc_cnt;
};

/** Pointer to the allocated chunk of memory. */
template <class _Tp>
void* fixed_mem_pool<_Tp>::_S_mem_pool_ptr = NULL;

/** Pointer to the first available memory block. */
template <class _Tp>
void* fixed_mem_pool<_Tp>::_S_first_avail_ptr = NULL;

/** Count of allocations. */
template <class _Tp>
int   fixed_mem_pool<_Tp>::_S_alloc_cnt = 0;

/**
 * Allocates a memory block from the memory pool.
 *
 * @return  pointer to the allocated memory block
 */
template <class _Tp>
inline void* fixed_mem_pool<_Tp>::allocate()
{
    lock guard;
    for (;;)
    {
        if (void* result = _S_first_avail_ptr)
        {
            _S_first_avail_ptr = *(void**)_S_first_avail_ptr;
            ++_S_alloc_cnt;
            return result;
        }
        else
            if (!bad_alloc_handler())
                return NULL;
    }
}

/**
 * Deallocates a memory block and returns it to the memory pool.
 *
 * @param block_ptr  pointer to the memory block to return
 */
template <class _Tp>
inline void fixed_mem_pool<_Tp>::deallocate(void* block_ptr)
{
    if (block_ptr == NULL)
        return;
    lock guard;
    assert(_S_alloc_cnt != 0);
    --_S_alloc_cnt;
    *(void**)block_ptr = _S_first_avail_ptr;
    _S_first_avail_ptr = block_ptr;
}

/**
 * Initializes the memory pool.
 *
 * @param size  number of memory blocks to put in the memory pool
 * @return      \c true if successful; \c false if memory insufficient
 */
template <class _Tp>
bool fixed_mem_pool<_Tp>::initialize(size_t size)
{
    STATIC_ASSERT(alignment::value > 0 && alignment::value <= 8192,
                  Bad_alignment);
    STATIC_ASSERT((alignment::value & (alignment::value - 1)) == 0,
                  Alignment_must_be_power_of_two);
    STATIC_ASSERT(block_size::value >= sizeof(void*),
                  Alignment_too_small);
    assert(!is_initialized());
    assert(size > 0);
    _S_mem_pool_ptr = mem_pool_base::alloc_sys(size * block_size::value);
    _S_first_avail_ptr = _S_mem_pool_ptr;
    if (_S_mem_pool_ptr == NULL)
        return false;
    char* block = (char*)_S_mem_pool_ptr;
    while (--size != 0)
    {
        char* next = block + block_size::value;
        *(void**)block = next;
        block = next;
    }
    *(void**)block = NULL;
    return true;
}

/**
 * Deinitializes the memory pool.
 *
 * @return  \c 0 if all memory blocks are returned and the memory pool
 *          successfully freed; or a non-zero value indicating number of
 *          memory blocks still in allocation
 */
template <class _Tp>
int fixed_mem_pool<_Tp>::deinitialize()
{
    if (_S_alloc_cnt != 0)
        return _S_alloc_cnt;
    assert(is_initialized());
    mem_pool_base::dealloc_sys(_S_mem_pool_ptr);
    _S_mem_pool_ptr = NULL;
    _S_first_avail_ptr = NULL;
    return 0;
}

/**
 * Gets the allocation count.
 *
 * @return  the number of memory blocks still in allocation
 */
template <class _Tp>
inline int fixed_mem_pool<_Tp>::get_alloc_count()
{
    return _S_alloc_cnt;
}

/**
 * Is the memory pool initialized?
 *
 * @return  \c true if it is successfully initialized; \c false otherwise
 */
template <class _Tp>
inline bool fixed_mem_pool<_Tp>::is_initialized()
{
    return _S_mem_pool_ptr != NULL;;
}

/**
 * Bad allocation handler.  Called when there are no memory blocks
 * available in the memory pool.  If this function returns \c false
 * (default behaviour if not explicitly specialized), it indicates that
 * it can do nothing and allocate() should return \c NULL; if this
 * function returns \c true, it indicates that it has freed some memory
 * blocks and allocate() should try allocating again.
 */
template <class _Tp>
bool fixed_mem_pool<_Tp>::bad_alloc_handler()
{
    return false;
}

NVWA_NAMESPACE_END

/**
 * Declares the normal (throwing) allocation and deallocation functions.
 *
 * @param _Cls  class to use the fixed_mem_pool
 * @see         DECLARE_FIXED_MEM_POOL__THROW_NOCHECK, which, too,
 *              defines an <b>operator new</b> that will never return
 *              \c NULL, but requires more discipline on the
 *              programmer's side.
 */
#define DECLARE_FIXED_MEM_POOL(_Cls) \
public: \
    static void* operator new(size_t size) \
    { \
        assert(size == sizeof(_Cls)); \
        if (void* ptr = NVWA::fixed_mem_pool<_Cls>::allocate()) \
            return ptr; \
        else \
            throw std::bad_alloc(); \
    } \
    static void  operator delete(void* ptr) \
    { \
        if (ptr != NULL) \
            NVWA::fixed_mem_pool<_Cls>::deallocate(ptr); \
    }

/**
 * Declares the nothrow allocation and deallocation functions.
 *
 * @param _Cls  class to use the fixed_mem_pool
 */
#define DECLARE_FIXED_MEM_POOL__NOTHROW(_Cls) \
public: \
    static void* operator new(size_t size) _NOEXCEPT \
    { \
        assert(size == sizeof(_Cls)); \
        return NVWA::fixed_mem_pool<_Cls>::allocate(); \
    } \
    static void  operator delete(void* ptr) \
    { \
        if (ptr != NULL) \
            NVWA::fixed_mem_pool<_Cls>::deallocate(ptr); \
    }

/**
 * Declares the throwing, non-checking allocation and deallocation
 * functions.
 *
 * N.B.  Using this macro \e requires users to explicitly specialize
 * fixed_mem_pool::bad_alloc_handler so that it shall never return
 * \c false (it may throw exceptions, say, \c std::bad_alloc, or simply
 * abort).  Otherwise a segmentation fault might occur (instead of
 * returning a \c NULL pointer).
 *
 * @param _Cls  class to use the fixed_mem_pool
 */
#define DECLARE_FIXED_MEM_POOL__THROW_NOCHECK(_Cls) \
public: \
    static void* operator new(size_t size) \
    { \
        assert(size == sizeof(_Cls)); \
        return NVWA::fixed_mem_pool<_Cls>::allocate(); \
    } \
    static void  operator delete(void* ptr) \
    { \
        if (ptr != NULL) \
            NVWA::fixed_mem_pool<_Cls>::deallocate(ptr); \
    }

#endif // NVWA_FIXED_MEM_POOL_H
