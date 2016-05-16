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
 * @file  bool_array.cpp
 *
 * Code for class bool_array (packed boolean array).
 *
 * @date  2013-03-01
 */

#include <limits.h>             // UINT_MAX, ULONG_MAX
#include <string.h>             // memset/memcpy
#include <algorithm>            // std::swap
#include "_nvwa.h"              // NVWA_NAMESPACE_*
#include "bool_array.h"         // bool_array
#include "static_assert.h"      // STATIC_ASSERT

NVWA_NAMESPACE_BEGIN

/**
 * Array that contains pre-calculated values how many 1-bits there are
 * in a given byte.
 */
bool_array::byte bool_array::_S_bit_count[256] =
{
    0, /*   0 */ 1, /*   1 */ 1, /*   2 */ 2, /*   3 */ 1, /*   4 */
    2, /*   5 */ 2, /*   6 */ 3, /*   7 */ 1, /*   8 */ 2, /*   9 */
    2, /*  10 */ 3, /*  11 */ 2, /*  12 */ 3, /*  13 */ 3, /*  14 */
    4, /*  15 */ 1, /*  16 */ 2, /*  17 */ 2, /*  18 */ 3, /*  19 */
    2, /*  20 */ 3, /*  21 */ 3, /*  22 */ 4, /*  23 */ 2, /*  24 */
    3, /*  25 */ 3, /*  26 */ 4, /*  27 */ 3, /*  28 */ 4, /*  29 */
    4, /*  30 */ 5, /*  31 */ 1, /*  32 */ 2, /*  33 */ 2, /*  34 */
    3, /*  35 */ 2, /*  36 */ 3, /*  37 */ 3, /*  38 */ 4, /*  39 */
    2, /*  40 */ 3, /*  41 */ 3, /*  42 */ 4, /*  43 */ 3, /*  44 */
    4, /*  45 */ 4, /*  46 */ 5, /*  47 */ 2, /*  48 */ 3, /*  49 */
    3, /*  50 */ 4, /*  51 */ 3, /*  52 */ 4, /*  53 */ 4, /*  54 */
    5, /*  55 */ 3, /*  56 */ 4, /*  57 */ 4, /*  58 */ 5, /*  59 */
    4, /*  60 */ 5, /*  61 */ 5, /*  62 */ 6, /*  63 */ 1, /*  64 */
    2, /*  65 */ 2, /*  66 */ 3, /*  67 */ 2, /*  68 */ 3, /*  69 */
    3, /*  70 */ 4, /*  71 */ 2, /*  72 */ 3, /*  73 */ 3, /*  74 */
    4, /*  75 */ 3, /*  76 */ 4, /*  77 */ 4, /*  78 */ 5, /*  79 */
    2, /*  80 */ 3, /*  81 */ 3, /*  82 */ 4, /*  83 */ 3, /*  84 */
    4, /*  85 */ 4, /*  86 */ 5, /*  87 */ 3, /*  88 */ 4, /*  89 */
    4, /*  90 */ 5, /*  91 */ 4, /*  92 */ 5, /*  93 */ 5, /*  94 */
    6, /*  95 */ 2, /*  96 */ 3, /*  97 */ 3, /*  98 */ 4, /*  99 */
    3, /* 100 */ 4, /* 101 */ 4, /* 102 */ 5, /* 103 */ 3, /* 104 */
    4, /* 105 */ 4, /* 106 */ 5, /* 107 */ 4, /* 108 */ 5, /* 109 */
    5, /* 110 */ 6, /* 111 */ 3, /* 112 */ 4, /* 113 */ 4, /* 114 */
    5, /* 115 */ 4, /* 116 */ 5, /* 117 */ 5, /* 118 */ 6, /* 119 */
    4, /* 120 */ 5, /* 121 */ 5, /* 122 */ 6, /* 123 */ 5, /* 124 */
    6, /* 125 */ 6, /* 126 */ 7, /* 127 */ 1, /* 128 */ 2, /* 129 */
    2, /* 130 */ 3, /* 131 */ 2, /* 132 */ 3, /* 133 */ 3, /* 134 */
    4, /* 135 */ 2, /* 136 */ 3, /* 137 */ 3, /* 138 */ 4, /* 139 */
    3, /* 140 */ 4, /* 141 */ 4, /* 142 */ 5, /* 143 */ 2, /* 144 */
    3, /* 145 */ 3, /* 146 */ 4, /* 147 */ 3, /* 148 */ 4, /* 149 */
    4, /* 150 */ 5, /* 151 */ 3, /* 152 */ 4, /* 153 */ 4, /* 154 */
    5, /* 155 */ 4, /* 156 */ 5, /* 157 */ 5, /* 158 */ 6, /* 159 */
    2, /* 160 */ 3, /* 161 */ 3, /* 162 */ 4, /* 163 */ 3, /* 164 */
    4, /* 165 */ 4, /* 166 */ 5, /* 167 */ 3, /* 168 */ 4, /* 169 */
    4, /* 170 */ 5, /* 171 */ 4, /* 172 */ 5, /* 173 */ 5, /* 174 */
    6, /* 175 */ 3, /* 176 */ 4, /* 177 */ 4, /* 178 */ 5, /* 179 */
    4, /* 180 */ 5, /* 181 */ 5, /* 182 */ 6, /* 183 */ 4, /* 184 */
    5, /* 185 */ 5, /* 186 */ 6, /* 187 */ 5, /* 188 */ 6, /* 189 */
    6, /* 190 */ 7, /* 191 */ 2, /* 192 */ 3, /* 193 */ 3, /* 194 */
    4, /* 195 */ 3, /* 196 */ 4, /* 197 */ 4, /* 198 */ 5, /* 199 */
    3, /* 200 */ 4, /* 201 */ 4, /* 202 */ 5, /* 203 */ 4, /* 204 */
    5, /* 205 */ 5, /* 206 */ 6, /* 207 */ 3, /* 208 */ 4, /* 209 */
    4, /* 210 */ 5, /* 211 */ 4, /* 212 */ 5, /* 213 */ 5, /* 214 */
    6, /* 215 */ 4, /* 216 */ 5, /* 217 */ 5, /* 218 */ 6, /* 219 */
    5, /* 220 */ 6, /* 221 */ 6, /* 222 */ 7, /* 223 */ 3, /* 224 */
    4, /* 225 */ 4, /* 226 */ 5, /* 227 */ 4, /* 228 */ 5, /* 229 */
    5, /* 230 */ 6, /* 231 */ 4, /* 232 */ 5, /* 233 */ 5, /* 234 */
    6, /* 235 */ 5, /* 236 */ 6, /* 237 */ 6, /* 238 */ 7, /* 239 */
    4, /* 240 */ 5, /* 241 */ 5, /* 242 */ 6, /* 243 */ 5, /* 244 */
    6, /* 245 */ 6, /* 246 */ 7, /* 247 */ 5, /* 248 */ 6, /* 249 */
    6, /* 250 */ 7, /* 251 */ 6, /* 252 */ 7, /* 253 */ 7, /* 254 */
    8  /* 255 */
}; // End _S_bit_count

/**
 * Array that contains pre-calculated values which the first 1-bit is
 * for a given byte.  The first element indicates an invalid value
 * (there are only 0-bits).
 */
bool_array::byte bool_array::_S_bit_ordinal[256] =
{
    9, /*   0 */
    0, /*   1 */ 1, /*   2 */ 0, /*   3 */ 2, /*   4 */ 0, /*   5 */
    1, /*   6 */ 0, /*   7 */ 3, /*   8 */ 0, /*   9 */ 1, /*  10 */
    0, /*  11 */ 2, /*  12 */ 0, /*  13 */ 1, /*  14 */ 0, /*  15 */
    4, /*  16 */ 0, /*  17 */ 1, /*  18 */ 0, /*  19 */ 2, /*  20 */
    0, /*  21 */ 1, /*  22 */ 0, /*  23 */ 3, /*  24 */ 0, /*  25 */
    1, /*  26 */ 0, /*  27 */ 2, /*  28 */ 0, /*  29 */ 1, /*  30 */
    0, /*  31 */ 5, /*  32 */ 0, /*  33 */ 1, /*  34 */ 0, /*  35 */
    2, /*  36 */ 0, /*  37 */ 1, /*  38 */ 0, /*  39 */ 3, /*  40 */
    0, /*  41 */ 1, /*  42 */ 0, /*  43 */ 2, /*  44 */ 0, /*  45 */
    1, /*  46 */ 0, /*  47 */ 4, /*  48 */ 0, /*  49 */ 1, /*  50 */
    0, /*  51 */ 2, /*  52 */ 0, /*  53 */ 1, /*  54 */ 0, /*  55 */
    3, /*  56 */ 0, /*  57 */ 1, /*  58 */ 0, /*  59 */ 2, /*  60 */
    0, /*  61 */ 1, /*  62 */ 0, /*  63 */ 6, /*  64 */ 0, /*  65 */
    1, /*  66 */ 0, /*  67 */ 2, /*  68 */ 0, /*  69 */ 1, /*  70 */
    0, /*  71 */ 3, /*  72 */ 0, /*  73 */ 1, /*  74 */ 0, /*  75 */
    2, /*  76 */ 0, /*  77 */ 1, /*  78 */ 0, /*  79 */ 4, /*  80 */
    0, /*  81 */ 1, /*  82 */ 0, /*  83 */ 2, /*  84 */ 0, /*  85 */
    1, /*  86 */ 0, /*  87 */ 3, /*  88 */ 0, /*  89 */ 1, /*  90 */
    0, /*  91 */ 2, /*  92 */ 0, /*  93 */ 1, /*  94 */ 0, /*  95 */
    5, /*  96 */ 0, /*  97 */ 1, /*  98 */ 0, /*  99 */ 2, /* 100 */
    0, /* 101 */ 1, /* 102 */ 0, /* 103 */ 3, /* 104 */ 0, /* 105 */
    1, /* 106 */ 0, /* 107 */ 2, /* 108 */ 0, /* 109 */ 1, /* 110 */
    0, /* 111 */ 4, /* 112 */ 0, /* 113 */ 1, /* 114 */ 0, /* 115 */
    2, /* 116 */ 0, /* 117 */ 1, /* 118 */ 0, /* 119 */ 3, /* 120 */
    0, /* 121 */ 1, /* 122 */ 0, /* 123 */ 2, /* 124 */ 0, /* 125 */
    1, /* 126 */ 0, /* 127 */ 7, /* 128 */ 0, /* 129 */ 1, /* 130 */
    0, /* 131 */ 2, /* 132 */ 0, /* 133 */ 1, /* 134 */ 0, /* 135 */
    3, /* 136 */ 0, /* 137 */ 1, /* 138 */ 0, /* 139 */ 2, /* 140 */
    0, /* 141 */ 1, /* 142 */ 0, /* 143 */ 4, /* 144 */ 0, /* 145 */
    1, /* 146 */ 0, /* 147 */ 2, /* 148 */ 0, /* 149 */ 1, /* 150 */
    0, /* 151 */ 3, /* 152 */ 0, /* 153 */ 1, /* 154 */ 0, /* 155 */
    2, /* 156 */ 0, /* 157 */ 1, /* 158 */ 0, /* 159 */ 5, /* 160 */
    0, /* 161 */ 1, /* 162 */ 0, /* 163 */ 2, /* 164 */ 0, /* 165 */
    1, /* 166 */ 0, /* 167 */ 3, /* 168 */ 0, /* 169 */ 1, /* 170 */
    0, /* 171 */ 2, /* 172 */ 0, /* 173 */ 1, /* 174 */ 0, /* 175 */
    4, /* 176 */ 0, /* 177 */ 1, /* 178 */ 0, /* 179 */ 2, /* 180 */
    0, /* 181 */ 1, /* 182 */ 0, /* 183 */ 3, /* 184 */ 0, /* 185 */
    1, /* 186 */ 0, /* 187 */ 2, /* 188 */ 0, /* 189 */ 1, /* 190 */
    0, /* 191 */ 6, /* 192 */ 0, /* 193 */ 1, /* 194 */ 0, /* 195 */
    2, /* 196 */ 0, /* 197 */ 1, /* 198 */ 0, /* 199 */ 3, /* 200 */
    0, /* 201 */ 1, /* 202 */ 0, /* 203 */ 2, /* 204 */ 0, /* 205 */
    1, /* 206 */ 0, /* 207 */ 4, /* 208 */ 0, /* 209 */ 1, /* 210 */
    0, /* 211 */ 2, /* 212 */ 0, /* 213 */ 1, /* 214 */ 0, /* 215 */
    3, /* 216 */ 0, /* 217 */ 1, /* 218 */ 0, /* 219 */ 2, /* 220 */
    0, /* 221 */ 1, /* 222 */ 0, /* 223 */ 5, /* 224 */ 0, /* 225 */
    1, /* 226 */ 0, /* 227 */ 2, /* 228 */ 0, /* 229 */ 1, /* 230 */
    0, /* 231 */ 3, /* 232 */ 0, /* 233 */ 1, /* 234 */ 0, /* 235 */
    2, /* 236 */ 0, /* 237 */ 1, /* 238 */ 0, /* 239 */ 4, /* 240 */
    0, /* 241 */ 1, /* 242 */ 0, /* 243 */ 2, /* 244 */ 0, /* 245 */
    1, /* 246 */ 0, /* 247 */ 3, /* 248 */ 0, /* 249 */ 1, /* 250 */
    0, /* 251 */ 2, /* 252 */ 0, /* 253 */ 1, /* 254 */ 0  /* 255 */
}; // End _S_bit_ordinal

/**
 * Constructs a bool_array with a specific size.
 *
 * @param size          size of the array
 * @throw out_of_range  \a size equals \c 0
 * @throw bad_alloc     memory is insufficient
 */
bool_array::bool_array(size_type size)
    : _M_byte_ptr(NULL), _M_length(0)
{
    if (size == 0)
        throw std::out_of_range("invalid bool_array size");
    if (!create(size))
        throw std::bad_alloc();
}

/**
 * Constructs a bool_array from a given bitmap.
 *
 * @param ptr           pointer to a bitmap
 * @param size          size of the array
 * @throw out_of_range  \a size equals \c 0
 * @throw bad_alloc     memory is insufficient
 */
bool_array::bool_array(const void* ptr, size_type size)
    : _M_byte_ptr(NULL), _M_length(0)
{
    if (size == 0)
        throw std::out_of_range("invalid bool_array size");
    if (!create(size))
        throw std::bad_alloc();

    size_t byte_cnt = get_num_bytes_from_bits(_M_length);
    memcpy(_M_byte_ptr, ptr, byte_cnt);
    int valid_bits_in_last_byte = (_M_length - 1) % 8 + 1;
    _M_byte_ptr[byte_cnt - 1] &= ~(~0 << valid_bits_in_last_byte);
}

/**
 * Copy-constructor.
 *
 * @param rhs        the bool_array to copy from
 * @throw bad_alloc  memory is insufficient
 */
bool_array::bool_array(const bool_array& rhs)
{
    if (rhs.size() == 0)
    {
        _M_byte_ptr = NULL;
        _M_length = 0;
        return;
    }
    if (!create(rhs.size()))
        throw std::bad_alloc();
    memcpy(_M_byte_ptr, rhs._M_byte_ptr, (size_t)((_M_length - 1) / 8) + 1);
}

/**
 * Assignment operator.
 *
 * @param rhs        the bool_array to copy from
 * @throw bad_alloc  memory is insufficient
 */
bool_array& bool_array::operator=(const bool_array& rhs)
{
    bool_array temp(rhs);
    swap(temp);
    return *this;
}

/**
 * Creates the packed boolean array with a specific size.
 *
 * @param size  size of the array
 * @return      \c false if \a size equals \c 0 or is too big, or if
 *              memory is insufficient; \c true if \a size has a
 *              suitable value and memory allocation is successful.
 */
bool bool_array::create(size_type size) _NOEXCEPT
{
    if (size == 0)
        return false;

#if defined(__x86_64) || defined(__ia64) || defined(__ppc64__) || \
    defined(_WIN64) || defined(_M_IA64) || \
    defined(__lp64) || defined(_LP64)
    STATIC_ASSERT(sizeof(size_t) == sizeof(size_type),  Wrong_size_type);
#else
    STATIC_ASSERT(sizeof(size_t) <= sizeof(size_type),  Wrong_size_type);
    STATIC_ASSERT(sizeof(size_t)==sizeof(unsigned int), Wrong_size_assumption);
    // Will be optimized away by a decent compiler if ULONG_MAX == UINT_MAX
    if (ULONG_MAX > UINT_MAX && ((size - 1) / 8 + 1) > UINT_MAX)
        return false;
#endif

    size_t byte_cnt = get_num_bytes_from_bits(size);
    byte* byte_ptr = (byte*)malloc(byte_cnt);
    if (byte_ptr == NULL)
        return false;

    if (_M_byte_ptr)
        free(_M_byte_ptr);

    _M_byte_ptr = byte_ptr;
    _M_length = size;
    return true;
}

/**
 * Initializes all array elements to a specific value optimally.
 *
 * @param value  the boolean value to assign to all elements
 */
void bool_array::initialize(bool value) _NOEXCEPT
{
    assert(_M_byte_ptr);
    size_t byte_cnt = get_num_bytes_from_bits(_M_length);
    memset(_M_byte_ptr, value ? ~0 : 0, byte_cnt);
    if (value)
    {
        int valid_bits_in_last_byte = (_M_length - 1) % 8 + 1;
        _M_byte_ptr[byte_cnt - 1] &= ~(~0 << valid_bits_in_last_byte);
    }
}

/**
 * Counts elements with a \c true value.
 *
 * @return  the count of \c true elements
 */
bool_array::size_type bool_array::count() const _NOEXCEPT
{
    assert(_M_byte_ptr);
    size_type true_cnt = 0;
    size_t byte_cnt = get_num_bytes_from_bits(_M_length);
    for (size_t i = 0; i < byte_cnt; ++i)
        true_cnt += _S_bit_count[_M_byte_ptr[i]];
    return true_cnt;
}

/**
 * Counts elements with a \c true value in a specified range.
 *
 * @param begin         beginning of the range
 * @param end           end of the range (exclusive)
 * @return              the count of \c true elements
 * @throw out_of_range  the range [begin, end) is invalid
 */
bool_array::size_type bool_array::count(size_type begin, size_type end) const
{
    assert(_M_byte_ptr);
    if (begin == end)
        return 0;
    if (end == npos)
        end = _M_length;
    if (begin > end || end > _M_length)
        throw std::out_of_range("invalid bool_array range");
    --end;

    size_type true_cnt = 0;
    size_t byte_pos_beg, byte_pos_end;
    byte byte_val;

    byte_pos_beg = (size_t)(begin / 8);
    byte_val = _M_byte_ptr[byte_pos_beg];
    byte_val &= ~0 << (begin % 8);

    byte_pos_end = (size_t)(end / 8);
    if (byte_pos_beg < byte_pos_end)
    {
        true_cnt = _S_bit_count[byte_val];
        byte_val = _M_byte_ptr[byte_pos_end];
    }
    byte_val &= ~(~0 << (end % 8 + 1));
    true_cnt += _S_bit_count[byte_val];

    for (++byte_pos_beg; byte_pos_beg < byte_pos_end; ++byte_pos_beg)
        true_cnt += _S_bit_count[_M_byte_ptr[byte_pos_beg]];
    return true_cnt;
}

/**
 * Searches for the specified boolean value.  This function accepts a
 * range expressed in [begin, end).
 *
 * @param begin         the position at which the search is to begin
 * @param end           the end position (exclusive) to stop searching
 * @param value         the boolean value to find
 * @return              position of the first value found if successful;
 *                      \c #npos otherwise
 * @throw out_of_range  the range [begin, end) is invalid
 */
bool_array::size_type bool_array::find_until(
        bool value,
        size_type begin,
        size_type end) const
{
    assert(_M_byte_ptr);
    if (begin == end)
        return npos;
    if (end == npos)
        end = _M_length;
    if (begin > end || end > _M_length)
        throw std::out_of_range("invalid bool_array range");
    --end;

    size_t byte_pos_beg = (size_t)(begin / 8);
    size_t byte_pos_end = (size_t)(end / 8);
    byte byte_val = _M_byte_ptr[byte_pos_beg];

    if (value)
    {
        byte_val &= ~0 << (begin % 8);
        for (size_t i = byte_pos_beg; i < byte_pos_end;)
        {
            if (byte_val != 0)
                return i * 8 + _S_bit_ordinal[byte_val];
            byte_val = _M_byte_ptr[++i];
        }
        byte_val &= ~(~0 << (end % 8 + 1));
        if (byte_val != 0)
            return byte_pos_end * 8 + _S_bit_ordinal[byte_val];
    }
    else
    {
        byte_val |= ~(~0 << (begin % 8));
        for (size_t i = byte_pos_beg; i < byte_pos_end;)
        {
            if (byte_val != 0xFF)
                return i * 8 + _S_bit_ordinal[(byte)~byte_val];
            byte_val = _M_byte_ptr[++i];
        }
        byte_val |= ~0 << (end % 8 + 1);
        if (byte_val != 0xFF)
            return byte_pos_end * 8 + _S_bit_ordinal[(byte)~byte_val];
    }

    return npos;
}

/**
 * Changes all \c true elements to \c false, and \c false ones to \c true.
 */
void bool_array::flip() _NOEXCEPT
{
    assert(_M_byte_ptr);
    size_t byte_cnt = get_num_bytes_from_bits(_M_length);
    for (size_t i = 0; i < byte_cnt; ++i)
        _M_byte_ptr[i] = ~_M_byte_ptr[i];
    int valid_bits_in_last_byte = (_M_length - 1) % 8 + 1;
    _M_byte_ptr[byte_cnt - 1] &= ~(~0 << valid_bits_in_last_byte);
}

/**
 * Exchanges the content of this bool_array with another.
 *
 * @param rhs  another bool_array to exchange content with
 */
void bool_array::swap(bool_array& rhs) _NOEXCEPT
{
    std::swap(_M_byte_ptr, rhs._M_byte_ptr);
    std::swap(_M_length,   rhs._M_length);
}

/**
 * Merges elements of another bool_array with a logical AND.
 *
 * @param rhs           another bool_array to merge
 * @param begin         beginning of the range in \a rhs
 * @param end           end of the range (exclusive) in \a rhs
 * @param offset        position to merge in this bool_array
 * @throw out_of_range  bad range for the source or the destination
 */
void bool_array::merge_and(
        const bool_array& rhs,
        size_type begin,
        size_type end,
        size_type offset)
{
    assert(_M_byte_ptr);
    if (begin == end)
        return;
    if (end == npos)
        end = rhs._M_length;
    if (begin > end || end > rhs._M_length)
        throw std::out_of_range("invalid bool_array range");
    if (offset + (end - begin) > _M_length)
        throw std::out_of_range("destination overflown");

    size_t byte_offset = (size_t)(offset / 8);
    size_t bit_offset = (size_t)(offset % 8);
    byte value;
    if (bit_offset != 0 && begin + 8 - bit_offset <= end)
    {   // Merge the first byte (in destination), if it is partial and
        // there are remaining bits
        value = rhs.get_8bits(begin, end);
        value = ~(~value << bit_offset);
        _M_byte_ptr[byte_offset] &= value;
        begin += 8 - bit_offset;
        byte_offset++;
        bit_offset = 0;
    }
    while (begin + 8 <= end)
    {   // Merge all the full bytes
        value = rhs.get_8bits(begin, end);
        _M_byte_ptr[byte_offset++] &= value;
        begin += 8;
    }
    if (begin < end)
    {   // Merge the remaining bits
        assert(end - begin < 8);
        value = rhs.get_8bits(begin, end);
        value |= ~0 << (end - begin);
        if (bit_offset != 0)
            value = ~(~value << bit_offset);
        _M_byte_ptr[byte_offset] &= value;
    }
}

/**
 * Merges elements of another bool_array with a logical OR.
 *
 * @param rhs           another bool_array to merge
 * @param begin         beginning of the range in \a rhs
 * @param end           end of the range (exclusive) in \a rhs
 * @param offset        position to merge in this bool_array
 * @throw out_of_range  bad range for the source or the destination
 */
void bool_array::merge_or(
        const bool_array& rhs,
        size_type begin,
        size_type end,
        size_type offset)
{
    assert(_M_byte_ptr);
    if (begin == end)
        return;
    if (end == npos)
        end = rhs._M_length;
    if (begin > end || end > rhs._M_length)
        throw std::out_of_range("invalid bool_array range");
    if (offset + (end - begin) > _M_length)
        throw std::out_of_range("destination overflown");

    size_t byte_offset = (size_t)(offset / 8);
    size_t bit_offset = (size_t)(offset % 8);
    byte value;
    if (bit_offset != 0 && begin + 8 - bit_offset <= end)
    {   // Merge the first byte (in destination), if it is partial and
        // there are remaining bits
        value = rhs.get_8bits(begin, end);
        value = value << bit_offset;
        _M_byte_ptr[byte_offset] |= value;
        begin += 8 - bit_offset;
        byte_offset++;
        bit_offset = 0;
    }
    while (begin + 8 <= end)
    {   // Merge all the full bytes
        value = rhs.get_8bits(begin, end);
        _M_byte_ptr[byte_offset++] |= value;
        begin += 8;
    }
    if (begin < end)
    {   // Merge the remaining bits
        assert(end - begin < 8);
        value = rhs.get_8bits(begin, end);
        value &= ~(~0 << (end - begin));
        if (bit_offset != 0)
            value = value << bit_offset;
        _M_byte_ptr[byte_offset] |= value;
    }
}

/**
 * Copies the bool_array content as bitmap to a specified buffer.  The
 * caller needs to ensure the destination buffer is big enough.
 *
 * @param dest          address of the destination buffer
 * @param begin         beginning of the range
 * @param end           end of the range (exclusive)
 * @throw out_of_range  bad range for the source or the destination
 */
void bool_array::copy_to_bitmap(void* dest, size_type begin, size_type end)
{
    assert(_M_byte_ptr);
    if (begin == end)
        return;
    if (end == npos)
        end = _M_length;
    if (begin > end || end > _M_length)
        throw std::out_of_range("invalid bool_array range");


    if (begin % 8 == 0)
        memcpy(dest, _M_byte_ptr + begin / 8,
               get_num_bytes_from_bits(end - begin));
    else
    {
        byte* byte_ptr = (byte*)dest;
        size_type offset = begin;
        while (offset < end)
        {
            *byte_ptr++ = get_8bits(offset, end);
            offset += 8;
        }
    }

    if (int extra_bits = (end - begin) % 8)
    {
        byte* last_byte_ptr = (byte*)dest +
                              get_num_bytes_from_bits(end - begin) - 1;
        *last_byte_ptr &= ~(~0 << extra_bits);
    }
}

/**
 * Retreive contiguous 8 bits from the bool_array.  If fewer than 8 bits
 * are available, the extra bits are undefined.
 *
 * @param offset  beginning position to retrieve the bits
 * @param end     end position beyond whose byte no bits will be taken
 */
bool_array::byte bool_array::get_8bits(size_type offset, size_type end) const
{
    size_t byte_offset = offset / 8;
    size_t bit_offset = offset % 8;
    byte retval = _M_byte_ptr[byte_offset] >> bit_offset;
    if (bit_offset != 0 && byte_offset < (end - 1) / 8)
        retval |= _M_byte_ptr[byte_offset + 1] << (8 - bit_offset);
    return retval;
}

NVWA_NAMESPACE_END

