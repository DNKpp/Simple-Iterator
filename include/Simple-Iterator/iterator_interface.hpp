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

namespace sl::itr::detail
{
	template <class TIterator>
		requires requires(TIterator d) { d.increment(); }
	constexpr TIterator& increment(TIterator& itr) noexcept(noexcept(itr.increment()))
	{
		itr.increment();
		return itr;
	}

	template <class TIterator>
		requires (!requires(TIterator d) { d.increment(); })
	constexpr TIterator& increment(TIterator& itr) noexcept(noexcept(itr.advance(1)))
	{
		itr.advance(1);
		return itr;
	}

	template <class TIterator>
		requires requires(TIterator d) { d.decrement(); }
	constexpr TIterator& decrement(TIterator& itr) noexcept(noexcept(itr.decrement()))
	{
		itr.decrement();
		return itr;
	}

	template <class TIterator>
		requires (!requires(TIterator d) { d.decrement(); })
	constexpr TIterator& decrement(TIterator& itr) noexcept(noexcept(itr.advance(-1)))
	{
		itr.advance(-1);
		return itr;
	}

	template <class TInterface, class TDerived>
	void static_itr_checks()
	{
		static_assert
		(
			std::derived_from<TDerived, TInterface>,
			"iterator_interface's template argument TDerived must derive from iterator_interface."
		);

		using itr_concept_t = typename TDerived::iterator_concept;
		static_assert
		(
			!input_iterator_category_tag<itr_concept_t> || input_iterator_suitable<TDerived>,
			"iterator_interface's template argument TDerived must fulfill all constraints of input_iterator_suitable when using this iterator category."
		);

		static_assert
		(
			!forward_iterator_category_tag<itr_concept_t> || forward_iterator_suitable<TDerived>,
			"iterator_interface's template argument TDerived must fulfill all constraints of forward_iterator_suitable when using this iterator category."
		);

		static_assert
		(
			!bidirectional_iterator_category_tag<itr_concept_t> || bidirectional_iterator_suitable<TDerived>,
			"iterator_interface's template argument TDerived must fulfill all constraints of bidirectional_iterator_suitable when using this iterator category."
		);

		static_assert
		(
			!random_access_iterator_category_tag<itr_concept_t> || random_access_iterator_suitable<TDerived>,
			"iterator_interface's template argument TDerived must fulfill all constraints of random_access_iterator_suitable when using this iterator category."
		);
	}
}

namespace sl::itr
{
	template <class TDerived>
		requires std::is_class_v<TDerived> && std::same_as<TDerived, std::remove_cv_t<TDerived>>
	class iterator_interface
	{
	private:
		[[nodiscard]]
		constexpr TDerived& cast() noexcept
		{
			detail::static_itr_checks<iterator_interface, TDerived>();
			return static_cast<TDerived&>(*this);
		}

		[[nodiscard]]
		constexpr const TDerived& cast() const noexcept
		{
			detail::static_itr_checks<iterator_interface, TDerived>();
			return static_cast<const TDerived&>(*this);
		}

	public:
		constexpr iterator_interface() noexcept = default;

		constexpr auto operator<=>(const iterator_interface&) const noexcept = default;

		[[nodiscard]]
		constexpr decltype(auto) operator *() const noexcept(noexcept(cast().get()))
		{
			return cast().get();
		}

		constexpr TDerived& operator ++() noexcept(noexcept(detail::increment(std::declval<TDerived&>())))
		{
			return detail::increment(cast());
		}

		constexpr void operator ++(int) noexcept(noexcept(detail::increment(std::declval<TDerived&>())))
			requires (!std::copy_constructible<TDerived>)
		{
			detail::increment(cast());
		}

		[[nodiscard]]
		constexpr TDerived operator ++
		(
			int
		) noexcept(noexcept(detail::increment(std::declval<TDerived&>())) &&
					std::is_nothrow_copy_constructible_v<TDerived>)
			requires std::copy_constructible<TDerived>
		{
			auto& self = cast();
			auto tmp{ self };
			detail::increment(self);
			return tmp;
		}

		constexpr TDerived& operator --() noexcept(noexcept(detail::decrement(std::declval<TDerived&>())))
			requires decrementable<TDerived>
		{
			return detail::decrement(cast());
		}

		[[nodiscard]]
		constexpr TDerived operator --
		(
			int
		) noexcept(noexcept(detail::decrement(std::declval<TDerived&>())) && std::is_nothrow_copy_constructible_v<TDerived>)
			requires decrementable<TDerived>
		{
			auto& self = cast();
			auto tmp{ self };
			detail::decrement(self);
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
			noexcept(cast().get())
		)
			requires advanceable_with<TDerived, TDifference>
		{
			auto tmp{ cast() };
			tmp.advance(std::forward<TDifference>(value));
			return tmp.get();
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
		constexpr iterator_interface(const iterator_interface&) = default;
		constexpr iterator_interface& operator =(const iterator_interface&) = default;
		constexpr iterator_interface(iterator_interface&&) = default;
		constexpr iterator_interface& operator =(iterator_interface&&) = default;
	};
}

#endif
