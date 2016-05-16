// -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*-
// vim:tabstop=4:shiftwidth=4:expandtab:

/*
 * Copyright (C) 2013 Wu Yongwei <adah at users dot sourceforge dot net>
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
 * @file  type_traits.h
 *
 * Type traits in the C++11 style but usable across main compilers.
 *
 * @date  2013-04-22
 */

#ifndef NVWA_TYPE_TRAITS_H
#define NVWA_TYPE_TRAITS_H

#include "_nvwa.h"              // NVWA_NAMESPACE_*
#include "c++11.h"              // HAVE_CXX11_TYPE_TRAITS

// For modern compilers that switch on C++11 support.  It, however,
// does not guarantee that it is fully standard-conformant.  Thus the
// version detection.
#if HAVE_CXX11_TYPE_TRAITS

# include <type_traits>

NVWA_NAMESPACE_BEGIN

using std::true_type;
using std::false_type;

# if defined(__GNUC__) && __GNUC__ * 100 + __GNUC_MINOR__ >= 408
using std::is_trivially_destructible;
# elif __has_extension(has_trivial_destructor)
// Treat Clang specially since I know no reliable way to detect its
// version or the library version
template <typename _Tp>
struct is_trivially_destructible
    : public std::integral_constant<bool, __has_trivial_destructor(_Tp)> {};
# else  // the compiler only has std::has_trivial_destructor
template <typename _Tp>
struct is_trivially_destructible
    : public std::has_trivial_destructor<_Tp> {};
# endif

NVWA_NAMESPACE_END

// Boost is the next option
#elif defined(BOOST_CONFIG_HPP) && !defined(NVWA_NO_BOOST_TYPETRAITS)

# include <boost/type_traits.hpp>

NVWA_NAMESPACE_BEGIN

using boost::true_type;
using boost::false_type;

template <typename _Tp>
struct is_trivially_destructible
    : public boost::has_trivial_destructor<_Tp> {};

NVWA_NAMESPACE_END

// GCC 4 has good TR1 support.
#elif defined(__GNUC__) && (__GNUC__ >= 4)

# include <tr1/type_traits>

NVWA_NAMESPACE_BEGIN

using std::tr1::true_type;
using std::tr1::false_type;

template <typename _Tp>
struct is_trivially_destructible
    : public std::tr1::has_trivial_destructor<_Tp> {};

NVWA_NAMESPACE_END

// GCC 3
#elif defined(__GNUC__) && (__GNUC__ == 3)

# include <bits/type_traits.h>

NVWA_NAMESPACE_BEGIN

typedef __true_type  true_type;
typedef __false_type false_type;

template <typename _Tp>
struct is_trivially_destructible
    : __type_traits<_Tp>::has_trivial_destructor {};

NVWA_NAMESPACE_END

#else

# error "Unrecognized platform for type traits!"

#endif

#endif // NVWA_TYPE_TRAITS_H
