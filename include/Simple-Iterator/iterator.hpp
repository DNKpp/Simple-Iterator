//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_ITERATOR_HPP
#define SL_ITERATOR_ITERATOR_HPP

#pragma once

#include "utility.hpp"

#include <iterator>
#include <type_traits>
#include <functional>
#include <concepts>

namespace sl::itr::detail
{
	template <class TValueType,
			class TMostDerivedIteratorType,
			class TStateType,
			std::signed_integral TDifferenceType,
			auto VAdvance,
			auto VDereference,
			iterator_category_tag TIteratorCategory
	>
		requires advance_for<decltype(VAdvance), TStateType, TDifferenceType> &&
				dereference_for<decltype(VDereference), TStateType>
	class base_iterator
	{
	public:
		// typedefs to keep the stl happy
		using value_type = TValueType;
		using difference_type = TDifferenceType;
		using iterator_concept = TIteratorCategory;

		constexpr TMostDerivedIteratorType& operator ++() noexcept
		{
			m_State = std::invoke(VAdvance, m_State, 1);
			return static_cast<TMostDerivedIteratorType&>(*this);
		}

		[[nodiscard]]
		constexpr TMostDerivedIteratorType operator ++(int) noexcept
		{
			auto tmp{ static_cast<TMostDerivedIteratorType&>(*this) };
			++(*this);
			return tmp;
		}

		[[nodiscard]]
		constexpr decltype(auto) operator *() const noexcept
		{
			return std::invoke(VDereference, m_State);
		}

	protected:
		TStateType m_State{};

		constexpr base_iterator() noexcept = default;

		constexpr explicit base_iterator(TStateType descriptor) noexcept :
			m_State{ descriptor }
		{
		}

		constexpr ~base_iterator() noexcept = default;

		constexpr base_iterator(const base_iterator&) noexcept = default;
		constexpr base_iterator& operator =(const base_iterator&) noexcept = default;
		constexpr base_iterator(base_iterator&&) noexcept = default;
		constexpr base_iterator& operator =(base_iterator&&) noexcept = default;

		[[nodiscard]]
		friend constexpr auto operator <=>(const base_iterator& lhs, const base_iterator& rhs) noexcept = default;
	};
}

#endif
