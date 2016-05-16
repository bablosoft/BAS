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
 * @file  pctimer.h
 *
 * Function to get a high-resolution timer for Win32/Cygwin/Unix.
 *
 * @date  2013-03-01
 */

#ifndef NVWA_PCTIMER_H
#define NVWA_PCTIMER_H

#if defined(_WIN32) || defined(__CYGWIN__)

#ifndef _WIN32
#define _PCTIMER_NO_WIN32
#endif /* _WIN32 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif /* WIN32_LEAN_AND_MEAN */
#include <windows.h>            // QueryPerformance*

#ifdef _PCTIMER_NO_WIN32
#undef _PCTIMER_NO_WIN32
#undef _WIN32
#endif /* _PCTIMER_NO_WIN32 */

#include "_nvwa.h"              // NVWA_NAMESPACE_*

NVWA_NAMESPACE_BEGIN

typedef double pctimer_t;

__inline pctimer_t pctimer(void)
{
    static LARGE_INTEGER pcount, pcfreq;
    static int initflag;

    if (!initflag)
    {
        QueryPerformanceFrequency(&pcfreq);
        initflag++;
    }

    QueryPerformanceCounter(&pcount);
    return (double)pcount.QuadPart / (double)pcfreq.QuadPart;
}

NVWA_NAMESPACE_END

#else /* Not Win32/Cygwin */

#include <sys/time.h>

NVWA_NAMESPACE_BEGIN

typedef double pctimer_t;

__inline pctimer_t pctimer(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
}

NVWA_NAMESPACE_END

#endif /* Win32/Cygwin */

#endif /* NVWA_PCTIMER_H */
