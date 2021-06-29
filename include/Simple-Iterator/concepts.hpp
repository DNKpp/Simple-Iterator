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

	template <class T>
	concept non_void = !std::same_as<T, void>;

	template <class T>
	concept pointer_type = std::is_pointer_v<T>;

	template <class T>
	concept dereferencable = requires(T& t)
	{
		{ t.get() } -> non_void;
	};

	template <class T, class TDifferenceType>
	concept advanceable_with = requires(T t, const TDifferenceType diff)
	{
		t.advance(diff);
	};

	template <class T>
	concept incrementable = requires(T t) { t.increment(); } ||
							advanceable_with<T, int>;

	template <class T>
	concept decrementable = requires(T t) { t.decrement(); } ||
							advanceable_with<T, int>;

	template <class T>
	concept distanceable = requires(const T t)
	{
		{ t.distance(t) } -> std::same_as<std::iter_difference_t<T>>;
	};

	template <class T>
	concept input_iterator_suitable = std::default_initializable<T> &&
									std::movable<T> &&
									dereferencable<const T> &&
									incrementable<T>;

	template <class T>
	concept forward_iterator_suitable = input_iterator_suitable<T> &&
										std::regular<T>;

	template <class T>
	concept bidirectional_iterator_suitable = forward_iterator_suitable<T> &&
											decrementable<T>;

	template <class T>
	concept random_access_iterator_suitable = bidirectional_iterator_suitable<T> &&
											advanceable_with<T, std::iter_difference_t<T>> &&
											distanceable<T>;
}

#endif
