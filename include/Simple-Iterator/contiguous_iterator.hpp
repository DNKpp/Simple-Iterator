//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_CONTIGUOUS_ITERATOR_HPP
#define SL_ITERATOR_CONTIGUOUS_ITERATOR_HPP

#pragma once

#include "random_access_iterator.hpp"

#include <type_traits>

namespace sl::itr::detail
{
	template <class TValueType,
			class TMostDerivedIteratorType,
			class TStateType = std::add_pointer_t<TValueType>,
			std::signed_integral TDifferenceType = int,
			auto VDistance = std::minus<>{},
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{},
			iterator_category_tag TIteratorCategory = std::contiguous_iterator_tag>
		requires distance_for<decltype(VDistance), TStateType, TDifferenceType> &&
				advance_for<decltype(VAdvance), TStateType, TDifferenceType> &&
				dereference_for<decltype(VDereference), TStateType>
	class base_contiguous_iterator :
		public base_random_access_iterator<TValueType,
											TMostDerivedIteratorType,
											TStateType,
											TDifferenceType,
											VDistance,
											VAdvance,
											VDereference,
											TIteratorCategory
		>
	{
		using super = base_random_access_iterator<TValueType,
												TMostDerivedIteratorType,
												TStateType,
												TDifferenceType,
												VDistance,
												VAdvance,
												VDereference,
												TIteratorCategory
		>;

	public:
		using typename super::value_type;
		using typename super::difference_type;
		using element_type = std::add_const_t<value_type>;

	protected:
		constexpr base_contiguous_iterator() noexcept = default;

		constexpr explicit base_contiguous_iterator(TStateType state) noexcept :
			super{ std::move(state) }
		{
		}

		constexpr ~base_contiguous_iterator() noexcept = default;

		constexpr base_contiguous_iterator(const base_contiguous_iterator&) noexcept = default;
		constexpr base_contiguous_iterator& operator =(const base_contiguous_iterator&) noexcept = default;
		constexpr base_contiguous_iterator(base_contiguous_iterator&&) noexcept = default;
		constexpr base_contiguous_iterator& operator =(base_contiguous_iterator&&) noexcept = default;
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
	class contiguous_iterator :
		public detail::base_contiguous_iterator<TValueType,
												contiguous_iterator<TValueType,
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
												std::contiguous_iterator_tag
		>
	{
		using super = detail::base_contiguous_iterator<TValueType,
														contiguous_iterator<TValueType,
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
														std::contiguous_iterator_tag
		>;

	public:
		constexpr contiguous_iterator() noexcept = default;

		constexpr explicit contiguous_iterator(TStateType state) noexcept :
			super{ std::move(state) }
		{
		}

		constexpr ~contiguous_iterator() noexcept = default;

		constexpr contiguous_iterator(const contiguous_iterator&) noexcept = default;
		constexpr contiguous_iterator& operator =(const contiguous_iterator&) noexcept = default;
		constexpr contiguous_iterator(contiguous_iterator&&) noexcept = default;
		constexpr contiguous_iterator& operator =(contiguous_iterator&&) noexcept = default;
	};
}

#endif
