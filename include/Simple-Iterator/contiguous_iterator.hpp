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
	template <class T,
			class TIterator,
			class TDescriptor = std::add_pointer_t<T>,
			std::signed_integral TDifferenceType = int,
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{},
			class TIteratorCategory = std::contiguous_iterator_tag>
	class base_contiguous_iterator :
		public base_random_access_iterator<T,
											TIterator,
											TDescriptor,
											TDifferenceType,
											VAdvance,
											VDereference,
											TIteratorCategory
		>
	{
		using super = base_random_access_iterator<T,
												TIterator,
												TDescriptor,
												TDifferenceType,
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

		constexpr base_contiguous_iterator(value_type* ptr) noexcept :
			super{ ptr }
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
			class TDescriptorType = std::add_pointer_t<TValueType>,
			std::signed_integral TDifferenceType = int,
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{}
	>
	class contiguous_iterator :
		public detail::base_contiguous_iterator<TValueType,
												contiguous_iterator<TValueType,
																	TDescriptorType,
																	TDifferenceType,
																	VAdvance,
																	VDereference
												>,
												TDescriptorType,
												TDifferenceType,
												VAdvance,
												VDereference,
												std::contiguous_iterator_tag
		>
	{
		using super = detail::base_contiguous_iterator<TValueType,
														contiguous_iterator<TValueType,
																			TDescriptorType,
																			TDifferenceType,
																			VAdvance,
																			VDereference
														>,
														TDescriptorType,
														TDifferenceType,
														VAdvance,
														VDereference,
														std::contiguous_iterator_tag
		>;

	public:
		constexpr contiguous_iterator() noexcept = default;

		constexpr contiguous_iterator(TDescriptorType descriptor) noexcept :
			super{ descriptor }
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
