//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_BIDIRECTIONAL_ITERATOR_HPP
#define SL_ITERATOR_BIDIRECTIONAL_ITERATOR_HPP

#pragma once

#include "forward_iterator.hpp"

namespace sl::itr::detail
{
	template <class T,
			class TIterator,
			class TDescriptor = std::add_pointer_t<T>,
			std::signed_integral TDifferenceType = int,
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{},
			class TIteratorCategory = std::bidirectional_iterator_tag>
	class base_bidirectional_iterator :
		public base_forward_iterator<T,
									TIterator,
									TDescriptor,
									TDifferenceType,
									VAdvance,
									VDereference,
									TIteratorCategory
		>
	{
		using super = base_forward_iterator<T,
											TIterator,
											TDescriptor,
											TDifferenceType,
											VAdvance,
											VDereference,
											TIteratorCategory
		>;

	public:
		using typename super::value_type;

		TIterator& operator --() noexcept
		{
			this->m_Descriptor = std::invoke(VAdvance, this->m_Descriptor, -1);
			return static_cast<TIterator&>(*this);
		}

		[[nodiscard]]
		TIterator operator --(int) noexcept
		{
			auto tmp{ static_cast<TIterator&>(*this) };
			--(*this);
			return tmp;
		}

	protected:
		constexpr base_bidirectional_iterator() noexcept = default;

		constexpr explicit base_bidirectional_iterator(TDescriptor descriptor) noexcept :
			super{ descriptor }
		{
		}

		constexpr ~base_bidirectional_iterator() noexcept = default;

		constexpr base_bidirectional_iterator(const base_bidirectional_iterator&) noexcept = default;
		constexpr base_bidirectional_iterator& operator =(const base_bidirectional_iterator&) noexcept = default;
		constexpr base_bidirectional_iterator(base_bidirectional_iterator&&) noexcept = default;
		constexpr base_bidirectional_iterator& operator =(base_bidirectional_iterator&&) noexcept = default;

		[[nodiscard]]
		friend constexpr auto operator <=>(
			const base_bidirectional_iterator& lhs,
			const base_bidirectional_iterator& rhs
		) noexcept = default;
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
	class bidirectional_iterator :
		public detail::base_bidirectional_iterator<TValueType,
													bidirectional_iterator<TValueType,
																			TDescriptorType,
																			TDifferenceType,
																			VAdvance,
																			VDereference
													>,
													TDescriptorType,
													TDifferenceType,
													VAdvance,
													VDereference,
													std::bidirectional_iterator_tag
		>
	{
		using super = detail::base_bidirectional_iterator<TValueType,
														bidirectional_iterator<TValueType,
																				TDescriptorType,
																				TDifferenceType,
																				VAdvance,
																				VDereference
														>,
														TDescriptorType,
														TDifferenceType,
														VAdvance,
														VDereference,
														std::bidirectional_iterator_tag
		>;

	public:
		constexpr bidirectional_iterator() noexcept = default;

		constexpr explicit bidirectional_iterator(TDescriptorType descriptor) noexcept :
			super{ descriptor }
		{
		}

		constexpr ~bidirectional_iterator() noexcept = default;

		constexpr bidirectional_iterator(const bidirectional_iterator&) noexcept = default;
		constexpr bidirectional_iterator& operator =(const bidirectional_iterator&) noexcept = default;
		constexpr bidirectional_iterator(bidirectional_iterator&&) noexcept = default;
		constexpr bidirectional_iterator& operator =(bidirectional_iterator&&) noexcept = default;
	};
}

#endif
