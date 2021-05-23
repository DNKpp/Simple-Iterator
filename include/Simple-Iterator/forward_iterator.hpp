//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_FORWARD_ITERATOR_HPP
#define SL_ITERATOR_FORWARD_ITERATOR_HPP

#pragma once

#include "input_iterator.hpp"

namespace sl::itr::detail
{
	template <class T,
			class TIterator,
			class TDescriptor = std::add_pointer_t<T>,
			std::signed_integral TDifferenceType = int,
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{},
			class TIteratorCategory = std::forward_iterator_tag
	>
	class base_forward_iterator :
		public base_input_iterator<T,
									TIterator,
									TDescriptor,
									TDifferenceType,
									VAdvance,
									VDereference,
									TIteratorCategory
		>
	{
		using super = base_input_iterator<T,
										TIterator,
										TDescriptor,
										TDifferenceType,
										VAdvance,
										VDereference,
										TIteratorCategory
		>;

	public:
		using typename super::value_type;

	protected:
		constexpr base_forward_iterator() noexcept = default;

		constexpr base_forward_iterator(value_type* ptr) noexcept :
			super{ ptr }
		{
		}

		constexpr ~base_forward_iterator() noexcept = default;

		constexpr base_forward_iterator(const base_forward_iterator&) noexcept = default;
		constexpr base_forward_iterator& operator =(const base_forward_iterator&) noexcept = default;
		constexpr base_forward_iterator(base_forward_iterator&&) noexcept = default;
		constexpr base_forward_iterator& operator =(base_forward_iterator&&) noexcept = default;

	protected:
		[[nodiscard]]
		friend constexpr auto operator <=>(
			const base_forward_iterator& lhs,
			const base_forward_iterator& rhs
		) noexcept = default;
	};
}

namespace sl::itr
{
	template <class TValueType,
			class TDescriptorType = std::add_pointer_t<TValueType>,
			std::signed_integral TDifferenceType = int,
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{}>
	class forward_iterator :
		public detail::base_forward_iterator<TValueType,
											forward_iterator<TValueType,
															TDescriptorType,
															TDifferenceType,
															VAdvance,
															VDereference
											>,
											TDescriptorType,
											TDifferenceType,
											VAdvance,
											VDereference,
											std::forward_iterator_tag
		>
	{
		using super = detail::base_forward_iterator<TValueType,
													forward_iterator<TValueType,
																	TDescriptorType,
																	TDifferenceType,
																	VAdvance,
																	VDereference
													>,
													TDescriptorType,
													TDifferenceType,
													VAdvance,
													VDereference,
													std::forward_iterator_tag
		>;

	public:
		constexpr forward_iterator() noexcept = default;

		constexpr forward_iterator(TDescriptorType descriptor) noexcept :
			super{ descriptor }
		{
		}

		constexpr ~forward_iterator() noexcept = default;

		constexpr forward_iterator(const forward_iterator&) noexcept = default;
		constexpr forward_iterator& operator =(const forward_iterator&) noexcept = default;
		constexpr forward_iterator(forward_iterator&&) noexcept = default;
		constexpr forward_iterator& operator =(forward_iterator&&) noexcept = default;
	};
}

#endif
