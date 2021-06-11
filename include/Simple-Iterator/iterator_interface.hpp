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
			return static_cast<const TDerived&>(*this);
		}

	public:
		using iterator_concept = TIteratorCategory;

		constexpr auto operator<=>(const iterator_interface&) const noexcept = default;

		constexpr iterator_interface() noexcept
		{
			static_assert
			(
				!input_iterator_category_tag<TIteratorCategory> || input_iterator_suitable<TDerived>,
				"iterator_interface's template argument TDerived must fulfill all constraints of input_iterator_suitable when using this iterator category."
			);

			static_assert
			(
				!forward_iterator_category_tag<TIteratorCategory> || forward_iterator_suitable<TDerived>,
				"iterator_interface's template argument TDerived must fulfill all constraints of forward_iterator_suitable when using this iterator category."
			);

			static_assert
			(
				!bidirectional_iterator_category_tag<TIteratorCategory> || bidirectional_iterator_suitable<TDerived>,
				"iterator_interface's template argument TDerived must fulfill all constraints of bidirectional_iterator_suitable when using this iterator category."
			);

			static_assert
			(
				!random_access_iterator_category_tag<TIteratorCategory> || random_access_iterator_suitable<TDerived>,
				"iterator_interface's template argument TDerived must fulfill all constraints of random_access_iterator_suitable when using this iterator category."
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

		[[nodiscard]]
		constexpr TDerived& operator --() noexcept(noexcept(cast().decrement()))
			requires decrementable<TDerived>
		{
			auto& self = cast();
			self.decrement();
			return self;
		}

		[[nodiscard]]
		constexpr TDerived operator --(int) noexcept(noexcept(cast().decrement()) && std::is_nothrow_copy_constructible_v<TDerived>)
			requires decrementable<TDerived>
		{
			auto& self = cast();
			auto tmp{ self };
			self.decrement();
			return tmp;
		}

		template <class TDifference>
		constexpr decltype(auto) operator []
		(
			TDifference&& value
		) const noexcept
		(
			std::is_nothrow_copy_constructible_v<TDerived> &&
			noexcept(std::declval<TDerived>().advance(std::forward<TDifference>(value))) &&
			noexcept(*cast())
		)
			requires (random_access_iterator_category_tag<TIteratorCategory> || advanceable_with<TDerived, TDifference>)
		{
			auto tmp{ cast() };
			tmp.advance(std::forward<TDifference>(value));
			return *tmp;
		}

		template <class TDifference>
		constexpr TDerived& operator +=(TDifference&& value) noexcept(noexcept(cast().advance(std::forward<TDifference>(value))))
			requires advanceable_with<TDerived, TDifference>
		{
			auto& self = cast();
			self.advance(std::forward<TDifference>(value));
			return self;
		}

		template <class TDifference>
		constexpr TDerived& operator -=(TDifference&& value) noexcept(noexcept(cast() += std::forward<TDifference>(value)))
			requires advanceable_with<TDerived, TDifference>
		{
			value *= -1;
			auto& self = cast();
			self.advance(std::forward<TDifference>(value));
			return self;
		}

		template <class TDifference>
		[[nodiscard]]
		friend constexpr TDerived operator +
		(
			TDerived itr,
			TDifference&& value
		) noexcept(noexcept(itr += std::forward<TDifference>(value)))
			requires advanceable_with<TDerived, TDifference>
		{
			itr += std::forward<TDifference>(value);
			return itr;
		}

		template <class TDifference>
		[[nodiscard]]
		friend constexpr TDerived operator +
		(
			TDifference&& value,
			TDerived itr
		) noexcept(noexcept(itr += std::forward<TDifference>(value)))
			requires advanceable_with<TDerived, TDifference>
		{
			itr += std::forward<TDifference>(value);
			return itr;
		}

		template <class TDifference>
		[[nodiscard]]
		friend constexpr TDerived operator -
		(
			TDerived itr,
			TDifference&& value
		) noexcept(noexcept(itr -= std::forward<TDifference>(value)))
			requires advanceable_with<TDerived, TDifference>
		{
			itr -= std::forward<TDifference>(value);
			return itr;
		}

		[[nodiscard]]
		friend constexpr auto operator -
		(
			const TDerived& lhs,
			const TDerived& rhs
		)
		noexcept(noexcept(lhs.distance(rhs)))
			requires requires { lhs.distance(rhs); }
		{
			return lhs.distance(rhs);
		}

	protected:
		constexpr ~iterator_interface() noexcept = default;
		constexpr iterator_interface(const iterator_interface&) noexcept = default;
		constexpr iterator_interface& operator =(const iterator_interface&) noexcept = default;
		constexpr iterator_interface(iterator_interface&&) noexcept = default;
		constexpr iterator_interface& operator =(iterator_interface&&) noexcept = default;
	};
}

#endif
