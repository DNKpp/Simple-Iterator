//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_CONCEPTS_HPP
#define SL_ITERATOR_CONCEPTS_HPP

#pragma once

#include <iterator>
#include <type_traits>
#include <concepts>

namespace sl::itr
{
	template <class T>
	concept non_void = !std::is_same_v<T, void>;

	template <class T>
	concept derefencable = requires(T& t)
	{
		{ *t } -> non_void;
	};

	struct dereference
	{
		template <derefencable T>
		[[nodiscard]]
		constexpr decltype(auto) operator()(T&& p) const noexcept
		{
			return *p;
		}
	};

	template <class T, class TReturn, class... TArgs>
	concept invokable_r = std::invocable<T, TArgs...> && std::convertible_to<std::invoke_result_t<T, TArgs...>, TReturn>;

	template <class T, class TDescriptorType, class TDifferenceType>
	concept advance_for = std::signed_integral<TDifferenceType> && invokable_r<
							T, TDescriptorType, TDescriptorType, TDifferenceType>;

	template <class T, class TDescriptorType>
	concept dereference_for = std::invocable<T, TDescriptorType> && non_void<std::invoke_result_t<T, TDescriptorType>>;

	template <class T, class... TOthers>
	concept same_as_any = (std::same_as<T, TOthers> || ...);

	template <class T>
	concept iterator_category_tag = same_as_any<T, std::input_iterator_tag,
												std::forward_iterator_tag,
												std::bidirectional_iterator_tag,
												std::random_access_iterator_tag,
												std::contiguous_iterator_tag>;
}

#endif
