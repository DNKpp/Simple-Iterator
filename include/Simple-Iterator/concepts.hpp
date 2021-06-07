//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_CONCEPTS_HPP
#define SL_ITERATOR_CONCEPTS_HPP

#pragma once

#include <concepts>
#include <iterator>

namespace sl::itr
{
	template <class T>
	concept contiguous_iterator_category_tag = std::same_as<T, std::contiguous_iterator_tag>;

	template <class T>
	concept random_access_iterator_category_tag = std::same_as<T, std::random_access_iterator_tag> ||
												contiguous_iterator_category_tag<T>;

	template <class T>
	concept bidirectional_iterator_category_tag = std::same_as<T, std::bidirectional_iterator_tag> ||
												random_access_iterator_category_tag<T>;

	template <class T>
	concept forward_iterator_category_tag = std::same_as<T, std::forward_iterator_tag> ||
											bidirectional_iterator_category_tag<T>;

	template <class T>
	concept input_iterator_category_tag = std::same_as<T, std::input_iterator_tag> ||
										forward_iterator_category_tag<T>;

	template <class T>
	concept output_iterator_category_tag = std::same_as<T, std::output_iterator_tag> ||
											forward_iterator_category_tag<T>;

	template <class T>
	concept iterator_category_tag = output_iterator_category_tag<T> || input_iterator_category_tag<T>;
}

#endif
