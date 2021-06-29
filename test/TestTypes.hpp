//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef SL_ITERATOR_TEST_TEST_TYPES_HPP
#define SL_ITERATOR_TEST_TEST_TYPES_HPP

#pragma once

#include "Simple-Iterator/iterator_interface.hpp"

namespace sl::itr
{
	struct TestInputIterator : public iterator_interface<TestInputIterator>
	{
		using element_type = int;
		using difference_type = std::ptrdiff_t;
		using iterator_concept = std::input_iterator_tag;

		TestInputIterator() = default;

		TestInputIterator(const TestInputIterator&) = delete;
		TestInputIterator& operator =(const TestInputIterator&) = delete;
		TestInputIterator(TestInputIterator&&) = default;
		TestInputIterator& operator =(TestInputIterator&&) = default;

		int dummyValue = 0;

		mutable int dereferenceCounter_const = 0;
		int incrementCounter = 0;

		[[nodiscard]]
		constexpr const int& get() const
		{
			++dereferenceCounter_const;
			return dummyValue;
		}

		constexpr void increment()
		{
			++incrementCounter;
		}
	};

	struct TestForwardIterator : public iterator_interface<TestForwardIterator>
	{
		using element_type = int;
		using difference_type = std::ptrdiff_t;
		using iterator_concept = std::forward_iterator_tag;

		TestForwardIterator() = default;

		bool operator ==(const TestForwardIterator&) const = default;

		int dummyValue = 0;

		mutable int dereferenceCounter_const = 0;
		int incrementCounter = 0;

		[[nodiscard]]
		constexpr const int& get() const
		{
			++dereferenceCounter_const;
			return dummyValue;
		}

		constexpr void increment()
		{
			++incrementCounter;
		}
	};

	struct TestBidirectionalIterator : public iterator_interface<TestBidirectionalIterator>
	{
		using element_type = int;
		using difference_type = std::ptrdiff_t;
		using iterator_concept = std::bidirectional_iterator_tag;

		TestBidirectionalIterator() = default;

		bool operator ==(const TestBidirectionalIterator&) const = default;

		int dummyValue = 0;

		mutable int dereferenceCounter_const = 0;
		int incrementCounter = 0;
		int decrementCounter = 0;

		[[nodiscard]]
		constexpr const int& get() const
		{
			++dereferenceCounter_const;
			return dummyValue;
		}

		constexpr void increment()
		{
			++incrementCounter;
		}

		constexpr void decrement()
		{
			++decrementCounter;
		}
	};

	struct TestRandomAccessIterator : public iterator_interface<TestRandomAccessIterator>
	{
		using element_type = int;
		using difference_type = std::ptrdiff_t;
		using iterator_concept = std::random_access_iterator_tag;

		TestRandomAccessIterator() = default;

		auto operator <=>(const TestRandomAccessIterator&) const = default;

		int dummyValue = 0;

		mutable int dereferenceCounter_const = 0;
		int incrementCounter = 0;
		int decrementCounter = 0;
		int advanceCounter = 0;
		mutable int distanceCounter = 0;

		[[nodiscard]]
		constexpr const int& get() const
		{
			++dereferenceCounter_const;
			return dummyValue;
		}

		constexpr void increment()
		{
			++incrementCounter;
		}

		constexpr void decrement()
		{
			++decrementCounter;
		}

		constexpr void advance(std::ptrdiff_t diff)
		{
			++advanceCounter;
		}

		[[nodiscard]]
		constexpr std::ptrdiff_t distance(const TestRandomAccessIterator& rhs) const
		{
			++distanceCounter;
			return 0;
		}
	};

	struct TestReducedRandomAccessIterator : public iterator_interface<TestReducedRandomAccessIterator>
	{
		using element_type = int;
		using difference_type = std::ptrdiff_t;
		using iterator_concept = std::random_access_iterator_tag;

		TestReducedRandomAccessIterator() = default;

		auto operator <=>(const TestReducedRandomAccessIterator&) const = default;

		int dummyValue = 0;
		int lastAdvanceDist = 0;

		mutable int dereferenceCounter_const = 0;
		int incrementCounter = 0;
		int decrementCounter = 0;
		int advanceCounter = 0;
		mutable int distanceCounter = 0;

		[[nodiscard]]
		constexpr const int& get() const
		{
			++dereferenceCounter_const;
			return dummyValue;
		}

		constexpr void advance(std::ptrdiff_t dist)
		{
			++incrementCounter;
			++decrementCounter;
			++advanceCounter;

			lastAdvanceDist += static_cast<int>(dist);
		}

		[[nodiscard]]
		constexpr std::ptrdiff_t distance(const TestReducedRandomAccessIterator& rhs) const
		{
			++distanceCounter;
			return 0;
		}
	};

	struct TestIncrement
	{
		void increment()
		{
		}
	};

	struct TestDecrement
	{
		void decrement()
		{
		}
	};
}

#endif
