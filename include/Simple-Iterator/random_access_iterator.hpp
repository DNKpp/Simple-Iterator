//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP
#define SL_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP

#pragma once

#include "bidirectional_iterator.hpp"

namespace sl::itr::detail
{
	template <class T,
			class TIterator,
			class TStateType = std::add_pointer_t<T>,
			std::signed_integral TDifferenceType = int,
			auto VDistance = std::minus<>{},
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{},
			class TIteratorCategory = std::random_access_iterator_tag>
		requires distance_for<decltype(VDistance), TStateType, TDifferenceType> &&
				advance_for<decltype(VAdvance), TStateType, TDifferenceType> &&
				dereference_for<decltype(VDereference), TStateType>
	class base_random_access_iterator :
		public base_bidirectional_iterator<T,
											TIterator,
											TStateType,
											TDifferenceType,
											VAdvance,
											VDereference,
											TIteratorCategory
		>
	{
		using super = base_bidirectional_iterator<T,
												TIterator,
												TStateType,
												TDifferenceType,
												VAdvance,
												VDereference,
												TIteratorCategory
		>;

	public:
		using typename super::value_type;
		using typename super::difference_type;

		[[nodiscard]]
		friend constexpr auto operator <=>(
			const base_random_access_iterator& lhs,
			const base_random_access_iterator& rhs
		) noexcept = default;

		TIterator& operator +=(difference_type value) noexcept
		{
			this->m_State = std::invoke(VAdvance, this->m_State, value);
			return static_cast<TIterator&>(*this);
		}

		TIterator& operator -=(difference_type value) noexcept
		{
			this->m_State = std::invoke(VAdvance, this->m_State, -value);
			return static_cast<TIterator&>(*this);
		}

		[[nodiscard]]
		value_type& operator [](difference_type dist) const noexcept
		{
			return std::invoke(VDereference, std::invoke(VAdvance, this->m_State, dist));
		}

		[[nodiscard]]
		friend constexpr TIterator operator +(TIterator itr, difference_type value) noexcept
		{
			return itr += value;
		}

		[[nodiscard]]
		friend constexpr TIterator operator +(difference_type value, TIterator itr) noexcept
		{
			return itr += value;
		}

		[[nodiscard]]
		friend constexpr TIterator operator -(TIterator itr, difference_type value) noexcept
		{
			return itr -= value;
		}

		[[nodiscard]]
		friend constexpr difference_type operator -(const TIterator& lhs, const TIterator& rhs) noexcept
		{
			return std::invoke(VDistance, lhs.m_State, rhs.m_State);
		}

	protected:
		constexpr base_random_access_iterator() noexcept = default;

		constexpr explicit base_random_access_iterator(TStateType state) noexcept :
			super{ std::move(state) }
		{
		}

		constexpr ~base_random_access_iterator() noexcept = default;

		constexpr base_random_access_iterator(const base_random_access_iterator&) noexcept = default;
		constexpr base_random_access_iterator& operator =(const base_random_access_iterator&) noexcept = default;
		constexpr base_random_access_iterator(base_random_access_iterator&&) noexcept = default;
		constexpr base_random_access_iterator& operator =(base_random_access_iterator&&) noexcept = default;
	};
}

namespace sl::itr
{
	template <class TValueType,
			class TStateType = std::add_pointer_t<TValueType>,
			std::signed_integral TDifferenceType = int,
			auto VDistance = std::minus<>{},
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{}
	>
		requires distance_for<decltype(VDistance), TStateType, TDifferenceType> &&
				advance_for<decltype(VAdvance), TStateType, TDifferenceType> &&
				dereference_for<decltype(VDereference), TStateType>
	class random_access_iterator :
		public detail::base_random_access_iterator<TValueType,
													random_access_iterator<TValueType,
																			TStateType,
																			TDifferenceType,
																			VDistance,
																			VAdvance,
																			VDereference
													>,
													TStateType,
													TDifferenceType,
													VDistance,
													VAdvance,
													VDereference,
													std::random_access_iterator_tag
		>
	{
		using super = detail::base_random_access_iterator<TValueType,
														random_access_iterator<TValueType,
																				TStateType,
																				TDifferenceType,
																				VDistance,
																				VAdvance,
																				VDereference
														>,
														TStateType,
														TDifferenceType,
														VDistance,
														VAdvance,
														VDereference,
														std::random_access_iterator_tag
		>;

	public:
		constexpr random_access_iterator() noexcept = default;

		constexpr explicit random_access_iterator(TStateType state) noexcept :
			super{ std::move(state) }
		{
		}

		constexpr ~random_access_iterator() noexcept = default;

		constexpr random_access_iterator(const random_access_iterator&) noexcept = default;
		constexpr random_access_iterator& operator =(const random_access_iterator&) noexcept = default;
		constexpr random_access_iterator(random_access_iterator&&) noexcept = default;
		constexpr random_access_iterator& operator =(random_access_iterator&&) noexcept = default;
	};
}

#endif
