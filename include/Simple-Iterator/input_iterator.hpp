//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_INPUT_ITERATOR_HPP
#define SL_ITERATOR_INPUT_ITERATOR_HPP

#pragma once

#include "iterator.hpp"
#include "utility.hpp"

#include <functional>

namespace sl::itr::detail
{
	template <class TValueType,
			class TMostDerivedIteratorType,
			class TDescriptorType = std::add_pointer_t<TValueType>,
			std::signed_integral TDifferenceType = int,
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{},
			iterator_category_tag TIteratorCategory = std::input_iterator_tag>
		requires advance_for<decltype(VAdvance), TDescriptorType, TDifferenceType> &&
				dereference_for<decltype(VDereference), TDescriptorType>
	class base_input_iterator :
		public base_iterator<TValueType,
							TMostDerivedIteratorType,
							TDescriptorType,
							TDifferenceType,
							VAdvance,
							VDereference,
							TIteratorCategory
		>
	{
		using super = base_iterator<TValueType,
									TMostDerivedIteratorType,
									TDescriptorType,
									TDifferenceType,
									VAdvance,
									VDereference,
									TIteratorCategory
		>;

	public:
		using typename super::value_type;

		[[nodiscard]]
		constexpr value_type* operator ->() const noexcept
		{
			return &**this;
		}

		[[nodiscard]]
		friend constexpr bool operator ==(const base_input_iterator& lhs, const base_input_iterator& rhs) noexcept = default;

	protected:
		constexpr base_input_iterator() noexcept = default;

		constexpr explicit base_input_iterator(TDescriptorType descriptor) noexcept :
			super{ descriptor }
		{
		}

		constexpr ~base_input_iterator() noexcept = default;

		constexpr base_input_iterator(const base_input_iterator&) noexcept = default;
		constexpr base_input_iterator& operator =(const base_input_iterator&) noexcept = default;
		constexpr base_input_iterator(base_input_iterator&&) noexcept = default;
		constexpr base_input_iterator& operator =(base_input_iterator&&) noexcept = default;

		[[nodiscard]]
		friend constexpr auto operator <=>(
			const base_input_iterator& lhs,
			const base_input_iterator& rhs
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
		requires advance_for<decltype(VAdvance), TDescriptorType, TDifferenceType> &&
				dereference_for<decltype(VDereference), TDescriptorType>
	class input_iterator :
		public detail::base_input_iterator<TValueType,
											input_iterator<TValueType,
															TDescriptorType,
															TDifferenceType,
															VAdvance,
															VDereference
											>,
											TDescriptorType,
											TDifferenceType,
											VAdvance,
											VDereference,
											std::input_iterator_tag
		>
	{
		using super = detail::base_input_iterator<TValueType,
												input_iterator<TValueType,
																TDescriptorType,
																TDifferenceType,
																VAdvance,
																VDereference
												>,
												TDescriptorType,
												TDifferenceType,
												VAdvance,
												VDereference,
												std::input_iterator_tag
		>;

	public:
		constexpr input_iterator() noexcept = default;

		constexpr explicit input_iterator(TDescriptorType descriptor) noexcept :
			super{ descriptor }
		{
		}

		constexpr ~input_iterator() noexcept = default;

		constexpr input_iterator(const input_iterator&) noexcept = default;
		constexpr input_iterator& operator =(const input_iterator&) noexcept = default;
		constexpr input_iterator(input_iterator&&) noexcept = default;
		constexpr input_iterator& operator =(input_iterator&&) noexcept = default;
	};
}

#endif
