//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_ITERATOR_HPP
#define SL_ITERATOR_ITERATOR_HPP

#pragma once

#include <iterator>
#include <type_traits>
#include <functional>
#include <concepts>

namespace sl::itr::detail
{
	template <class T,
			class TIterator,
			class TDescriptor,
			std::signed_integral TDifference,
			auto VAdvance,
			auto VDereference,
			class TIteratorCategory
	>
	class base_iterator
	{
	public:
		// typedefs to keep the stl happy
		using value_type = T;
		using difference_type = TDifference;
		using iterator_concept = TIteratorCategory;

		constexpr TIterator& operator ++() noexcept
		{
			m_Descriptor = std::invoke(VAdvance, m_Descriptor, 1);
			return static_cast<TIterator&>(*this);
		}

		[[nodiscard]]
		constexpr TIterator operator ++(int) noexcept
		{
			auto tmp{ static_cast<TIterator&>(*this) };
			++(*this);
			return tmp;
		}

		[[nodiscard]]
		constexpr decltype(auto) operator *() const noexcept
		{
			return std::invoke(VDereference, m_Descriptor);
		}

	protected:
		TDescriptor m_Descriptor{};

		constexpr base_iterator() noexcept = default;

		constexpr explicit base_iterator(TDescriptor descriptor) noexcept :
			m_Descriptor{ descriptor }
		{
		}

		constexpr ~base_iterator() noexcept = default;

		constexpr base_iterator(const base_iterator&) noexcept = default;
		constexpr base_iterator& operator =(const base_iterator&) noexcept = default;
		constexpr base_iterator(base_iterator&&) noexcept = default;
		constexpr base_iterator& operator =(base_iterator&&) noexcept = default;

		[[nodiscard]]
		friend constexpr auto operator <=>(const base_iterator& lhs, const base_iterator& rhs) noexcept = default;
	};
}

#endif
