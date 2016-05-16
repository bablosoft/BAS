// -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*-
// vim:tabstop=4:shiftwidth=4:expandtab:

/*
 * Copyright (C) 2004-2013 Wu Yongwei <adah at users dot sourceforge dot net>
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
 * @file  static_mem_pool.h
 *
 * Header file for the `static' memory pool.
 *
 * @date  2013-10-06
 */

#ifndef NVWA_STATIC_MEM_POOL_H
#define NVWA_STATIC_MEM_POOL_H

#include <new>                  // std::bad_alloc
#include <stdexcept>            // std::runtime_error
#include <string>               // std::string
#include <vector>               // std::vector
#include <assert.h>             // assert
#include <stddef.h>             // size_t/NULL
#include "_nvwa.h"              // NVWA/NVWA_NAMESPACE_*
#include "c++11.h"              // _NOEXCEPT
#include "class_level_lock.h"   // nvwa::class_level_lock
#include "mem_pool_base.h"      // nvwa::mem_pool_base

/* Defines the macro for debugging output */
# ifdef _STATIC_MEM_POOL_DEBUG
#   include <iostream>
#   define _STATIC_MEM_POOL_TRACE(_Lck, _Msg) \
        { \
            if (_Lck) { \
                static_mem_pool_set::lock guard; \
                std::cerr << "static_mem_pool: " << _Msg << std::endl; \
            } else { \
                std::cerr << "static_mem_pool: " << _Msg << std::endl; \
            } \
        }
# else
#   define _STATIC_MEM_POOL_TRACE(_Lck, _Msg) \
        ((void)0)
# endif

NVWA_NAMESPACE_BEGIN

/**
 * Singleton class to maintain a set of existing instantiations of
 * static_mem_pool.
 */
class static_mem_pool_set
{
public:
    typedef class_level_lock<static_mem_pool_set>::lock lock;
    static static_mem_pool_set& instance();
    void recycle();
    void add(mem_pool_base* memory_pool_p);

private:
    static_mem_pool_set();
    ~static_mem_pool_set();

    typedef std::vector<mem_pool_base*> container_type;
    container_type _M_memory_pool_set;

    /* Forbid their use */
    static_mem_pool_set(const static_mem_pool_set&);
    const static_mem_pool_set& operator=(const static_mem_pool_set&);
};

/**
 * Singleton class template to manage the allocation/deallocation of
 * memory blocks of one specific size.
 *
 * @param _Sz   size of elements in the static_mem_pool
 * @param _Gid  group ID of a static_mem_pool: if it is negative,
 *              simultaneous accesses to this static_mem_pool will be
 *              protected from each other; otherwise no protection is
 *              given
 */
template <size_t _Sz, int _Gid = -1>
class static_mem_pool : public mem_pool_base
{
    typedef typename class_level_lock<static_mem_pool<_Sz, _Gid>, (_Gid < 0)>
            ::lock lock;
public:
    /**
     * Gets the instance of the static memory pool.  It will create the
     * instance if it does not already exist.  Generally this function
     * is now not needed.
     *
     * @return  reference to the instance of the static memory pool
     * @see     instance_known
     */
    static static_mem_pool& instance()
    {
        lock guard;
        if (!_S_instance_p)
        {
            _S_instance_p = _S_create_instance();
        }
        return *_S_instance_p;
    }
    /**
     * Gets the known instance of the static memory pool.  The instance
     * must already exist.  Generally the static initializer of the
     * template guarantees it.
     *
     * @return  reference to the instance of the static memory pool
     */
    static static_mem_pool& instance_known()
    {
        assert(_S_instance_p != NULL);
        return *_S_instance_p;
    }
    /**
     * Allocates memory and returns its pointer.  The template will try
     * to get it from the memory pool first, and request memory from the
     * system if there is no free memory in the pool.
     *
     * @return  pointer to allocated memory if successful; \c NULL
     *          otherwise
     */
    void* allocate()
    {
        {
            lock guard;
            if (_S_memory_block_p)
            {
                void* result = _S_memory_block_p;
                _S_memory_block_p = _S_memory_block_p->_M_next;
                return result;
            }
        }
        return _S_alloc_sys(_S_align(_Sz));
    }
    /**
     * Deallocates memory by putting the memory block into the pool.
     *
     * @param ptr  pointer to memory to be deallocated
     */
    void deallocate(void* ptr)
    {
        assert(ptr != NULL);
        lock guard;
        _Block_list* block = reinterpret_cast<_Block_list*>(ptr);
        block->_M_next = _S_memory_block_p;
        _S_memory_block_p = block;
    }
    virtual void recycle();

private:
    static_mem_pool()
    {
        _STATIC_MEM_POOL_TRACE(true, "static_mem_pool<" << _Sz << ','
                                     << _Gid << "> is created");
    }
    ~static_mem_pool()
    {
#   ifdef _DEBUG
        // Empty the pool to avoid false memory leakage alarms.  This is
        // generally not necessary for release binaries.
        _Block_list* block = _S_memory_block_p;
        while (block)
        {
            _Block_list* next = block->_M_next;
            dealloc_sys(block);
            block = next;
        }
        _S_memory_block_p = NULL;
#   endif
        _S_instance_p = NULL;
        _S_destroyed = true;
        _STATIC_MEM_POOL_TRACE(false, "static_mem_pool<" << _Sz << ','
                                      << _Gid << "> is destroyed");
    }
    static size_t _S_align(size_t size)
    {
        return size >= sizeof(_Block_list) ? size : sizeof(_Block_list);
    }
    static void* _S_alloc_sys(size_t size);
    static static_mem_pool* _S_create_instance();

    static bool _S_destroyed;
    static static_mem_pool* _S_instance_p;
    static mem_pool_base::_Block_list* _S_memory_block_p;

    /* Forbid their use */
    static_mem_pool(const static_mem_pool&);
    const static_mem_pool& operator=(const static_mem_pool&);
};

template <size_t _Sz, int _Gid> bool
        static_mem_pool<_Sz, _Gid>::_S_destroyed = false;
template <size_t _Sz, int _Gid> mem_pool_base::_Block_list*
        static_mem_pool<_Sz, _Gid>::_S_memory_block_p = NULL;
template <size_t _Sz, int _Gid> static_mem_pool<_Sz, _Gid>*
        static_mem_pool<_Sz, _Gid>::_S_instance_p = _S_create_instance();

/**
 * Recycles half of the free memory blocks in the memory pool to the
 * system.  It is called when a memory request to the system (in other
 * instances of the static memory pool) fails.
 */
template <size_t _Sz, int _Gid>
void static_mem_pool<_Sz, _Gid>::recycle()
{
    // Only here the global lock in static_mem_pool_set is obtained
    // before the pool-specific lock.  However, no race conditions are
    // found so far.
    lock guard;
    _Block_list* block = _S_memory_block_p;
    while (block)
    {
        if (_Block_list* temp = block->_M_next)
        {
            _Block_list* next = temp->_M_next;
            block->_M_next = next;
            dealloc_sys(temp);
            block = next;
        }
        else
        {
            break;
        }
    }
    _STATIC_MEM_POOL_TRACE(false, "static_mem_pool<" << _Sz << ','
                                  << _Gid << "> is recycled");
}

template <size_t _Sz, int _Gid>
void* static_mem_pool<_Sz, _Gid>::_S_alloc_sys(size_t size)
{
    static_mem_pool_set::lock guard;
    void* result = mem_pool_base::alloc_sys(size);
    if (!result)
    {
        static_mem_pool_set::instance().recycle();
        result = mem_pool_base::alloc_sys(size);
    }
    return result;
}

template <size_t _Sz, int _Gid>
static_mem_pool<_Sz, _Gid>* static_mem_pool<_Sz, _Gid>::_S_create_instance()
{
    if (_S_destroyed)
        throw std::runtime_error("dead reference detected");

    static_mem_pool_set::instance();  // Force its creation
    static_mem_pool* inst_p = new static_mem_pool();
    try
    {
        static_mem_pool_set::instance().add(inst_p);
    }
    catch (...)
    {
        _STATIC_MEM_POOL_TRACE(true,
                "Exception occurs in static_mem_pool_set::add");
        // The strange cast below is to work around a bug in GCC 2.95.3
        delete static_cast<mem_pool_base*>(inst_p);
        throw;
    }
    return inst_p;
}

NVWA_NAMESPACE_END

/**
 * Declares the normal (throwing) allocation and deallocation functions.
 * This macro uses the default group.
 *
 * @param _Cls  class to use the static_mem_pool
 * @see   DECLARE_STATIC_MEM_POOL__NOTHROW
 * @see   DECLARE_STATIC_MEM_POOL_GROUPED
 * @see   DECLARE_STATIC_MEM_POOL_GROUPED__NOTHROW
 */
#define DECLARE_STATIC_MEM_POOL(_Cls) \
public: \
    static void* operator new(size_t size) \
    { \
        assert(size == sizeof(_Cls)); \
        void* ptr; \
        ptr = NVWA::static_mem_pool<sizeof(_Cls)>:: \
                               instance_known().allocate(); \
        if (ptr == NULL) \
            throw std::bad_alloc(); \
        return ptr; \
    } \
    static void operator delete(void* ptr) \
    { \
        if (ptr) \
            NVWA::static_mem_pool<sizeof(_Cls)>:: \
                           instance_known().deallocate(ptr); \
    }

/**
 * Declares the nothrow allocation and deallocation functions.  This macro
 * uses the default group.
 *
 * @param _Cls  class to use the static_mem_pool
 * @see   DECLARE_STATIC_MEM_POOL
 * @see   DECLARE_STATIC_MEM_POOL_GROUPED
 * @see   DECLARE_STATIC_MEM_POOL_GROUPED__NOTHROW
 */
#define DECLARE_STATIC_MEM_POOL__NOTHROW(_Cls) \
public: \
    static void* operator new(size_t size) _NOEXCEPT \
    { \
        assert(size == sizeof(_Cls)); \
        return NVWA::static_mem_pool<sizeof(_Cls)>:: \
                              instance_known().allocate(); \
    } \
    static void operator delete(void* ptr) \
    { \
        if (ptr) \
            NVWA::static_mem_pool<sizeof(_Cls)>:: \
                           instance_known().deallocate(ptr); \
    }

/**
 * Declares the normal (throwing) allocation and deallocation functions.
 * Users need to specify a group ID.
 *
 * @param _Cls  class to use the static_mem_pool
 * @param _Gid  group ID (negative to protect multi-threaded access)
 * @see   DECLARE_STATIC_MEM_POOL
 * @see   DECLARE_STATIC_MEM_POOL__NOTHROW
 * @see   DECLARE_STATIC_MEM_POOL_GROUPED__NOTHROW
 */
#define DECLARE_STATIC_MEM_POOL_GROUPED(_Cls, _Gid) \
public: \
    static void* operator new(size_t size) \
    { \
        assert(size == sizeof(_Cls)); \
        void* ptr; \
        ptr = NVWA::static_mem_pool<sizeof(_Cls), (_Gid)>:: \
                               instance_known().allocate(); \
        if (ptr == NULL) \
            throw std::bad_alloc(); \
        return ptr; \
    } \
    static void operator delete(void* ptr) \
    { \
        if (ptr) \
            NVWA::static_mem_pool<sizeof(_Cls), (_Gid)>:: \
                           instance_known().deallocate(ptr); \
    }

/**
 * Declares the nothrow allocation and deallocation functions.  Users need
 * to specify a group ID.
 *
 * @param _Cls  class to use the static_mem_pool
 * @param _Gid  group ID (negative to protect multi-threaded access)
 * @see   DECLARE_STATIC_MEM_POOL
 * @see   DECLARE_STATIC_MEM_POOL__NOTHROW
 * @see   DECLARE_STATIC_MEM_POOL_GROUPED
 */
#define DECLARE_STATIC_MEM_POOL_GROUPED__NOTHROW(_Cls, _Gid) \
public: \
    static void* operator new(size_t size) _NOEXCEPT \
    { \
        assert(size == sizeof(_Cls)); \
        return NVWA::static_mem_pool<sizeof(_Cls), (_Gid)>:: \
                              instance_known().allocate(); \
    } \
    static void operator delete(void* ptr) \
    { \
        if (ptr) \
            NVWA::static_mem_pool<sizeof(_Cls), (_Gid)>:: \
                           instance_known().deallocate(ptr); \
    }

#endif // NVWA_STATIC_MEM_POOL_H
