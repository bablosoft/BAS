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
 * @file  set_assign.h
 *
 * Definition of template functions set_assign_union and set_assign_difference.
 *
 * @date  2013-03-01
 */

#ifndef NVWA_SET_ASSIGN_H
#define NVWA_SET_ASSIGN_H

#include <algorithm>            // std::copy
#include "_nvwa.h"              // NVWA_NAMESPACE_*

NVWA_NAMESPACE_BEGIN

template <class _Container, class _InputIter>
_Container& set_assign_union(_Container& dest,
                             _InputIter first,
                             _InputIter last)
{
    typename _Container::iterator first_dest = dest.begin();
    typename _Container::iterator  last_dest = dest.end();
    while (first_dest != last_dest && first != last)
    {
        if (*first_dest < *first)
            ++first_dest;
        else if (*first < *first_dest)
        {
            dest.insert(first_dest, *first);
            ++first;
        }
        else    // *first_dest == *first
        {
            ++first_dest;
            ++first;
        }
    }
    if (first != last)
        std::copy(first, last, inserter(dest, last_dest));
    return dest;
}

template <class _Container, class _InputIter, class _Compare>
_Container& set_assign_union(_Container& dest,
                             _InputIter first,
                             _InputIter last,
                             _Compare comp)
{
    typename _Container::iterator first_dest = dest.begin();
    typename _Container::iterator  last_dest = dest.end();
    while (first_dest != last_dest && first != last)
    {
        if (comp(*first_dest, *first))
            ++first_dest;
        else if (comp(*first, *first_dest))
        {
            dest.insert(first_dest, *first);
            ++first;
        }
        else    // *first_dest is equivalent to *first
        {
            ++first_dest;
            ++first;
        }
    }
    if (first != last)
        std::copy(first, last, inserter(dest, last_dest));
    return dest;
}

template <class _Container, class _InputIter>
_Container& set_assign_difference(_Container& dest,
                                  _InputIter first,
                                  _InputIter last)
{
    typename _Container::iterator first_dest = dest.begin();
    typename _Container::iterator  last_dest = dest.end();
    while (first_dest != last_dest && first != last)
    {
        if (*first_dest < *first)
            ++first_dest;
        else if (*first < *first_dest)
            ++first;
        else  // *first == *first_dest
        {
            dest.erase(first_dest++);
            ++first;
        }
    }
    return dest;
}

template <class _Container, class _InputIter, class _Compare>
_Container& set_assign_difference(_Container& dest,
                                  _InputIter first,
                                  _InputIter last,
                                  _Compare comp)
{
    typename _Container::iterator first_dest = dest.begin();
    typename _Container::iterator  last_dest = dest.end();
    while (first_dest != last_dest && first != last)
    {
        if (comp(*first_dest, *first))
            ++first_dest;
        else if (comp(*first, *first_dest))
            ++first;
        else    // *first_dest is equivalent to *first
        {
            dest.erase(first_dest++);
            ++first;
        }
    }
    return dest;
}

NVWA_NAMESPACE_END

#endif // NVWA_SET_ASSIGN_H
