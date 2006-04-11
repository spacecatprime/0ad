/**
 * =========================================================================
 * File        : string_s.h
 * Project     : 0 A.D.
 * Description : implementation of proposed CRT safe string functions
 *
 * @author Jan.Wassenberg@stud.uni-karlsruhe.de
 * =========================================================================
 */

/*
 * Copyright (c) 2005 Jan Wassenberg
 *
 * Redistribution and/or modification are also permitted under the
 * terms of the GNU General Public License as published by the
 * Free Software Foundation (version 2 or later, at your option).
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef STRING_S_H__
#define STRING_S_H__

#include "posix_types.h"	// size_t
#include "config.h"

// only declare these functions if using our implementation
// (otherwise, we risk incompatibilities)
#if !HAVE_STRING_S

// (conflicts with glibc definitions)
#if !OS_UNIX
// return length [in characters] of a string, not including the trailing
// null character. to protect against access violations, only the
// first <max_len> characters are examined; if the null character is
// not encountered by then, <max_len> is returned.
extern size_t strnlen(const char* str, size_t max_len);
extern size_t wcsnlen(const wchar_t* str, size_t max_len);
#endif

// copy at most <max_src_chars> (not including trailing null) from
// <src> into <dst>, which must not overlap.
// if thereby <max_dst_chars> (including null) would be exceeded,
// <dst> is set to the empty string and ERANGE returned; otherwise,
// 0 is returned to indicate success and that <dst> is null-terminated.
//
// note: padding with zeroes is not called for by NG1031.
extern int strncpy_s(char* dst, size_t max_dst_chars, const char* src, size_t max_src_chars);
extern int wcsncpy_s(wchar_t* dst, size_t max_dst_chars, const wchar_t* src, size_t max_src_chars);

// copy <src> (including trailing null) into <dst>, which must not overlap.
// if thereby <max_dst_chars> (including null) would be exceeded,
// <dst> is set to the empty string and ERANGE returned; otherwise,
// 0 is returned to indicate success and that <dst> is null-terminated.
//
// note: implemented as tncpy_s(dst, max_dst_chars, src, SIZE_MAX)
extern int strcpy_s(char* dst, size_t max_dst_chars, const char* src);
extern int wcscpy_s(wchar_t* dst, size_t max_dst_chars, const wchar_t* src);

// append at most <max_src_chars> (not including trailing null) from
// <src> to <dst>, which must not overlap.
// if thereby <max_dst_chars> (including null) would be exceeded,
// <dst> is set to the empty string and ERANGE returned; otherwise,
// 0 is returned to indicate success and that <dst> is null-terminated.
extern int strncat_s(char* dst, size_t max_dst_chars, const char* src, size_t max_src_chars);
extern int wcsncat_s(wchar_t* dst, size_t max_dst_chars, const wchar_t* src, size_t max_src_chars);

// append <src> to <dst>, which must not overlap.
// if thereby <max_dst_chars> (including null) would be exceeded,
// <dst> is set to the empty string and ERANGE returned; otherwise,
// 0 is returned to indicate success and that <dst> is null-terminated.
//
// note: implemented as tncat_s(dst, max_dst_chars, src, SIZE_MAX)
extern int strcat_s(char* dst, size_t max_dst_chars, const char* src);
extern int wcscat_s(wchar_t* dst, size_t max_dst_chars, const wchar_t* src);

#endif	// #if !HAVE_STRING_S

#endif	// #ifndef STRING_S_H__
