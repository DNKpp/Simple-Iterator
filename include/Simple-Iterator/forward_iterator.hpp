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
	template <class TValueType,
			class TMostDerivedIteratorType,
			class TStateType = std::add_pointer_t<TValueType>,
			std::signed_integral TDifferenceType = int,
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{},
			iterator_category_tag TIteratorCategory = std::forward_iterator_tag>
		requires advance_for<decltype(VAdvance), TStateType, TDifferenceType> &&
				dereference_for<decltype(VDereference), TStateType>
	class base_forward_iterator :
		public base_input_iterator<TValueType,
									TMostDerivedIteratorType,
									TStateType,
									TDifferenceType,
									VAdvance,
									VDereference,
									TIteratorCategory
		>
	{
		using super = base_input_iterator<TValueType,
										TMostDerivedIteratorType,
										TStateType,
										TDifferenceType,
										VAdvance,
										VDereference,
										TIteratorCategory
		>;

	public:
		using typename super::value_type;

	protected:
		constexpr base_forward_iterator() noexcept = default;

		constexpr explicit base_forward_iterator(TStateType descriptor) noexcept :
			super{ descriptor }
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
			class TStateType = std::add_pointer_t<TValueType>,
			std::signed_integral TDifferenceType = int,
			auto VAdvance = std::plus<>{},
			auto VDereference = dereference{}
	>
		requires advance_for<decltype(VAdvance), TStateType, TDifferenceType> &&
				dereference_for<decltype(VDereference), TStateType>
	class forward_iterator :
		public detail::base_forward_iterator<TValueType,
											forward_iterator<TValueType,
															TStateType,
															TDifferenceType,
															VAdvance,
															VDereference
											>,
											TStateType,
											TDifferenceType,
											VAdvance,
											VDereference,
											std::forward_iterator_tag
		>
	{
		using super = detail::base_forward_iterator<TValueType,
													forward_iterator<TValueType,
																	TStateType,
																	TDifferenceType,
																	VAdvance,
																	VDereference
													>,
													TStateType,
													TDifferenceType,
													VAdvance,
													VDereference,
													std::forward_iterator_tag
		>;

	public:
		constexpr forward_iterator() noexcept = default;

		constexpr explicit forward_iterator(TStateType descriptor) noexcept :
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
