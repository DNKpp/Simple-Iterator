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
			class TDescriptor = std::add_pointer_t<T>,
			std::signed_integral TDifferenceType = int,
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{},
			class TIteratorCategory = std::random_access_iterator_tag>
	class base_random_access_iterator :
		public base_bidirectional_iterator<T,
											TIterator,
											TDescriptor,
											TDifferenceType,
											VAdvance,
											VDereference,
											TIteratorCategory
		>
	{
		using super = base_bidirectional_iterator<T,
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

		[[nodiscard]]
		friend constexpr auto operator <=>(
			const base_random_access_iterator& lhs,
			const base_random_access_iterator& rhs
		) noexcept = default;

		TIterator& operator +=(difference_type value) noexcept
		{
			this->m_Descriptor = std::invoke(VAdvance, this->m_Descriptor, value);
			return static_cast<TIterator&>(*this);
		}

		TIterator& operator -=(difference_type value) noexcept
		{
			this->m_Descriptor = std::invoke(VAdvance, this->m_Descriptor, -value);
			return static_cast<TIterator&>(*this);
		}

		[[nodiscard]]
		value_type& operator [](difference_type dist) const noexcept
		{
			return *(this->m_Descriptor + dist);
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
			return lhs.m_Descriptor - rhs.m_Descriptor;
		}

	protected:
		constexpr base_random_access_iterator() noexcept = default;

		constexpr explicit base_random_access_iterator(TDescriptor descriptor) noexcept :
			super{ descriptor }
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
			class TDescriptorType = std::add_pointer_t<TValueType>,
			std::signed_integral TDifferenceType = int,
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{}
	>
	class random_access_iterator :
		public detail::base_random_access_iterator<TValueType,
													random_access_iterator<TValueType,
																			TDescriptorType,
																			TDifferenceType,
																			VAdvance,
																			VDereference
													>,
													TDescriptorType,
													TDifferenceType,
													VAdvance,
													VDereference,
													std::random_access_iterator_tag
		>
	{
		using super = detail::base_random_access_iterator<TValueType,
														random_access_iterator<TValueType,
																				TDescriptorType,
																				TDifferenceType,
																				VAdvance,
																				VDereference
														>,
														TDescriptorType,
														TDifferenceType,
														VAdvance,
														VDereference,
														std::random_access_iterator_tag
		>;

	public:
		constexpr random_access_iterator() noexcept = default;

		constexpr explicit random_access_iterator(TDescriptorType descriptor) noexcept :
			super{ descriptor }
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
