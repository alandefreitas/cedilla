// Copyright (c) 2016, Tom Honermann
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef TEXT_VIEW_ADVANCE_TO_HPP // {
#define TEXT_VIEW_ADVANCE_TO_HPP


#include <range/v3/utility/iterator_concepts.hpp>


namespace std {
namespace experimental {
inline namespace text {
namespace text_detail {

template<typename IT,
CONCEPT_REQUIRES_(ranges::InputIterator<IT>())>
IT advance_to(IT i, IT s) {
    return s;
}

template<typename IT, typename ST,
CONCEPT_REQUIRES_(
    ranges::InputIterator<IT>(),
    ranges::Sentinel<ST,IT>())>
IT advance_to(IT i, ST s) {
    while(i != s) {
        ++i;
    }
    return i;
}

} // namespace text_detail
} // inline namespace text
} // namespace experimental
} // namespace std


#endif // } TEXT_VIEW_ADVANCE_TO_HPP
