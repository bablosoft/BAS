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
 * @file  cont_ptr_utils.h
 *
 * Utility functors for containers of pointers (adapted from Scott
 * Meyers' <em>Effective STL</em>).
 *
 * @date  2013-10-06
 */

#ifndef NVWA_CONT_PTR_UTILS_H
#define NVWA_CONT_PTR_UTILS_H

#include "_nvwa.h"              // NVWA_NAMESPACE_*

NVWA_NAMESPACE_BEGIN

/**
 * Functor to return objects pointed by a container of pointers.
 *
 * A typical usage might be like:
 * @code
 * vector<Object*> v;
 * ...
 * transform(v.begin(), v.end(),
 *           ostream_iterator<Object>(cout, " "),
 *           dereference());
 * @endcode
 */
struct dereference
{
    template <typename _Tp>
    const _Tp& operator()(const _Tp* ptr) const
    {
        return *ptr;
    }
};

/**
 * Functor to compare objects pointed by a container of pointers.
 *
 * @code
 * vector<Object*> v;
 * ...
 * sort(v.begin(), v.end(), dereference_less());
 * @endcode
 * or
 * @code
 * set<Object*, dereference_less> s;
 * @endcode
 */
struct dereference_less
{
    template <typename _Pointer>
    bool operator()(const _Pointer& ptr1, const _Pointer& ptr2) const
    {
        return *ptr1 < *ptr2;
    }
};

/**
 * Functor to delete objects pointed by a container of pointers.
 *
 * A typical usage might be like:
 * @code
 * list<Object*> l;
 * ...
 * for_each(l.begin(), l.end(), delete_object());
 * @endcode
 */
struct delete_object
{
    template <typename _Tp>
    void operator()(_Tp* ptr) const
    {
        delete ptr;
    }
};

/**
 * Functor to output objects pointed by a container of pointers.
 *
 * A typical usage might be like:
 * @code
 * list<Object*> l;
 * ...
 * for_each(l.begin(), l.end(), output_object<ostream>(cout, " "));
 * @endcode
 */
template <typename _OutputStrm, typename _StringType = const char*>
struct output_object
{
    output_object(_OutputStrm& outs, const _StringType& sep)
        : _M_outs(outs), _M_sep(sep)
    {}

    template <typename _Pointer>
    void operator()(const _Pointer& ptr) const
    {
        _M_outs << *ptr << _M_sep;
    }

private:
    _OutputStrm& _M_outs;
    _StringType  _M_sep;
};

NVWA_NAMESPACE_END

#endif // NVWA_CONT_PTR_UTILS_H
