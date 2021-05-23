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
}

#endif
