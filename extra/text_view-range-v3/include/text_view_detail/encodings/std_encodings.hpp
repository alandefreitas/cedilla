// Copyright (c) 2015, Tom Honermann
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef TEXT_VIEW_STD_ENCODINGS_HPP // {
#define TEXT_VIEW_STD_ENCODINGS_HPP


#include <text_view_detail/encodings/basic_encodings.hpp>
#include <text_view_detail/encodings/unicode_encodings.hpp>


#if !defined(TEXT_VIEW_EXECUTION_CHARACTER_ENCODING)
#define TEXT_VIEW_EXECUTION_CHARACTER_ENCODING \
        ::std::experimental::basic_execution_character_encoding
#endif
#if !defined(TEXT_VIEW_EXECUTION_WIDE_CHARACTER_ENCODING)
#define TEXT_VIEW_EXECUTION_WIDE_CHARACTER_ENCODING \
        ::std::experimental::basic_execution_wide_character_encoding
#endif
#if !defined(TEXT_VIEW_CHAR8_CHARACTER_ENCODING)
#define TEXT_VIEW_CHAR8_CHARACTER_ENCODING \
        ::std::experimental::utf8_encoding
#endif
#if !defined(TEXT_VIEW_CHAR16_CHARACTER_ENCODING)
#define TEXT_VIEW_CHAR16_CHARACTER_ENCODING \
        ::std::experimental::utf16_encoding
#endif
#if !defined(TEXT_VIEW_CHAR32_CHARACTER_ENCODING)
#define TEXT_VIEW_CHAR32_CHARACTER_ENCODING \
        ::std::experimental::utf32_encoding
#endif


namespace std {
namespace experimental {
inline namespace text {


/*
 * C++ execution character encoding
 * ISO/IEC 14882:2011(E) 2.14.5 [lex.string]
 */
using execution_character_encoding = TEXT_VIEW_EXECUTION_CHARACTER_ENCODING;


/*
 * C++ execution wide character encoding
 * ISO/IEC 14882:2011(E) 2.14.5 [lex.string]
 */
using execution_wide_character_encoding = TEXT_VIEW_EXECUTION_WIDE_CHARACTER_ENCODING;


/*
 * C++ char (u8) character encoding
 * ISO/IEC 14882:2011(E) 2.14.5 [lex.string]
 */
using char8_character_encoding = TEXT_VIEW_CHAR8_CHARACTER_ENCODING;


/*
 * C++ char16_t (u) character encoding
 * ISO/IEC 14882:2011(E) 2.14.5 [lex.string]
 */
using char16_character_encoding = TEXT_VIEW_CHAR16_CHARACTER_ENCODING;


/*
 * C++ char32_t (U) character encoding
 * ISO/IEC 14882:2011(E) 2.14.5 [lex.string]
 */
using char32_character_encoding = TEXT_VIEW_CHAR32_CHARACTER_ENCODING;


} // inline namespace text
} // namespace experimental
} // namespace std


#endif // } TEXT_VIEW_STD_ENCODINGS_HPP
