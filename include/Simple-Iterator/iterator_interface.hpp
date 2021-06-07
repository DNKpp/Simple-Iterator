//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_ITERATOR_HPP
#define SL_ITERATOR_ITERATOR_HPP

#pragma once

#include "concepts.hpp"

#include <concepts>
#include <type_traits>

namespace sl::itr
{
	template
	<
		iterator_category_tag TIteratorCategory,
		class TDerived
	>
		requires std::is_class_v<TDerived> && std::same_as<TDerived, std::remove_cv_t<TDerived>>
	class iterator_interface
	{
		[[nodiscard]]
		constexpr TDerived& cast() noexcept
		{
			static_assert
			(
				std::derived_from<TDerived, iterator_interface>,
				"iterator_interface's template argument TDerived must derive from iterator_interface."
			);
			return static_cast<TDerived&>(*this);
		}

		[[nodiscard]]
		constexpr const TDerived& cast() const noexcept
		{
			static_assert
			(
				std::derived_from<TDerived, iterator_interface>,
				"iterator_interface's template argument TDerived must derive from iterator_interface."
			);
			return static_cast<TDerived&>(*this);
		}

	public:
		using iterator_concept = TIteratorCategory;

		constexpr iterator_interface() noexcept
		{
			static_assert
			(
				!input_iterator_category_tag<TIteratorCategory> || input_iterator_suitable<TDerived>,
				"iterator_interface's template argument TDerived must fulfill all constraints of input_iterator_suitable when using this iterator category."
			);
		}

		constexpr void operator ++(int) noexcept(noexcept(++cast()))
			requires (!std::copy_constructible<TDerived>)
		{
			auto& self = cast();
			++self;
		}

		[[nodiscard]]
		constexpr TDerived operator ++(int) noexcept(noexcept(++cast()) && std::is_nothrow_copy_constructible_v<TDerived>)
			requires std::copy_constructible<TDerived>
		{
			auto& self = cast();
			auto tmp{ self };
			++self;
			return tmp;
		}
	};
}

#endif
