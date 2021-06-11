//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <catch2/catch.hpp>

#include "Simple-Iterator/iterator_interface.hpp"

using namespace sl::itr;

namespace
{
	struct TestInputIterator : public iterator_interface<std::input_iterator_tag, TestInputIterator>
	{
	private:
		using super = iterator_interface<std::input_iterator_tag, TestInputIterator>;

	public:
		using element_type = int;
		using difference_type = std::ptrdiff_t;

		TestInputIterator() = default;

		TestInputIterator(const TestInputIterator&) = delete;
		TestInputIterator& operator =(const TestInputIterator&) = delete;
		TestInputIterator(TestInputIterator&&) = default;
		TestInputIterator& operator =(TestInputIterator&&) = default;

		int dummyValue = 0;

		mutable int dereferenceCounter_const = 0;
		mutable int preIncrementCounter = 0;

		[[nodiscard]]
		constexpr const int& operator *() const
		{
			++dereferenceCounter_const;
			return dummyValue;
		}

		constexpr TestInputIterator& operator ++()
		{
			++preIncrementCounter;
			return *this;
		}

		using super::operator++;
	};

	struct TestForwardIterator : public iterator_interface<std::forward_iterator_tag, TestForwardIterator>
	{
	private:
		using super = iterator_interface<std::forward_iterator_tag, TestForwardIterator>;

	public:
		using element_type = int;
		using difference_type = std::ptrdiff_t;

		bool operator ==(const TestForwardIterator&) const = default;

		int dummyValue = 0;

		mutable int dereferenceCounter_const = 0;
		mutable int preIncrementCounter = 0;

		[[nodiscard]]
		constexpr const int& operator *() const
		{
			++dereferenceCounter_const;
			return dummyValue;
		}

		constexpr TestForwardIterator& operator ++()
		{
			++preIncrementCounter;
			return *this;
		}

		using super::operator++;
	};

	struct TestBidirectionalIterator : public iterator_interface<std::bidirectional_iterator_tag, TestBidirectionalIterator>
	{
	private:
		using super = iterator_interface<std::bidirectional_iterator_tag, TestBidirectionalIterator>;

	public:
		using element_type = int;
		using difference_type = std::ptrdiff_t;

		bool operator ==(const TestBidirectionalIterator&) const = default;

		int dummyValue = 0;

		mutable int dereferenceCounter_const = 0;
		mutable int preIncrementCounter = 0;
		mutable int preDecrementCounter = 0;

		[[nodiscard]]
		constexpr const int& operator *() const
		{
			++dereferenceCounter_const;
			return dummyValue;
		}

		constexpr TestBidirectionalIterator& operator ++()
		{
			++preIncrementCounter;
			return *this;
		}

		constexpr TestBidirectionalIterator& operator --()
		{
			++preDecrementCounter;
			return *this;
		}

		using super::operator++;
		using super::operator--;
	};

	struct TestRandomAccessIterator : public iterator_interface<std::random_access_iterator_tag, TestRandomAccessIterator>
	{
	private:
		using super = iterator_interface<std::random_access_iterator_tag, TestRandomAccessIterator>;

	public:
		using element_type = int;
		using difference_type = std::ptrdiff_t;

		auto operator <=>(const TestRandomAccessIterator&) const = default;

		int dummyValue = 0;

		mutable int dereferenceCounter_const = 0;
		mutable int preIncrementCounter = 0;
		mutable int preDecrementCounter = 0;
		mutable int advanceCounter = 0;
		mutable int distanceCounter = 0;

		[[nodiscard]]
		constexpr const int& operator *() const
		{
			++dereferenceCounter_const;
			return dummyValue;
		}

		constexpr TestRandomAccessIterator& operator ++()
		{
			++preIncrementCounter;
			return *this;
		}

		constexpr TestRandomAccessIterator& operator --()
		{
			++preDecrementCounter;
			return *this;
		}

		constexpr TestRandomAccessIterator& operator +=(std::ptrdiff_t diff)
		{
			++advanceCounter;
			return *this;
		}

		[[nodiscard]]
		constexpr std::ptrdiff_t operator -(const TestRandomAccessIterator& rhs) const
		{
			++distanceCounter;
			return 0;
		}

		using super::operator++;
		using super::operator--;
	};
}

TEST_CASE
(
	"input_iterator_tag iterator_interface should invoke pre-increment operator when post-incrementing.",
	"[iterator_interface][input_iterator]"
)
{
	TestInputIterator itr;
	// ReSharper disable once CppDiscardedPostfixOperatorResult
	itr++;

	REQUIRE(itr.preIncrementCounter == 1);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"Using test iterator types, iterator_interface should fulfill std::input_iterator concepts.",
	"[iterator_interface][input_iterator]",
	TestInputIterator,
	TestForwardIterator,
	TestBidirectionalIterator,
	TestRandomAccessIterator
)
#pragma warning(default: 26444)
{
	using Itr_t = TestType;

	REQUIRE(std::default_initializable<Itr_t>);
	REQUIRE(std::movable<Itr_t>);
	REQUIRE(std::weakly_incrementable<Itr_t>);
	REQUIRE(std::input_or_output_iterator<Itr_t>);

	REQUIRE(std::indirectly_readable<Itr_t>);

	REQUIRE(std::input_iterator<Itr_t>);
}

TEST_CASE
(
	"TestForwardIterator iterator_interface should invoke pre-increment operator when post-incrementing and receive a valid copy.",
	"[iterator_interface][forward_iterator]"
)
{
	TestForwardIterator itr;
	const auto tmp = itr++;

	REQUIRE(tmp.preIncrementCounter == 0);
	REQUIRE(itr.preIncrementCounter == 1);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"Using test iterator types, iterator_interface should fulfill std::forward_iterator concepts.",
	"[iterator_interface][forward_iterator]",
	TestForwardIterator,
	TestBidirectionalIterator,
	TestRandomAccessIterator
)
#pragma warning(default: 26444)
{
	using Itr_t = TestType;

	REQUIRE(std::equality_comparable<Itr_t>);
	REQUIRE(std::copyable<Itr_t>);
	REQUIRE(std::semiregular<Itr_t>);
	REQUIRE(std::regular<Itr_t>);

	REQUIRE(std::sentinel_for<Itr_t, Itr_t>);

	REQUIRE(std::forward_iterator<Itr_t>);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"Using test iterator types, iterator_interface should fulfill std::bidirectional_iterator concepts.",
	"[iterator_interface][bidirectional_iterator]",
	TestBidirectionalIterator,
	TestRandomAccessIterator
)
#pragma warning(default: 26444)
{
	using Itr_t = TestType;

	REQUIRE(std::bidirectional_iterator<Itr_t>);
}

TEST_CASE
(
	"TestBidirectionalIterator iterator_interface should invoke pre-decrement operator when post-decrementing and receive a valid copy.",
	"[iterator_interface][forward_iterator]"
)
{
	TestBidirectionalIterator itr;
	const auto tmp = itr--;

	REQUIRE(tmp.preDecrementCounter == 0);
	REQUIRE(itr.preDecrementCounter == 1);
}

TEST_CASE
(
	"TestRandomAccesslIterator iterator_interface should invoke operator += when using random access operations.",
	"[iterator_interface][forward_iterator]"
)
{
	TestRandomAccessIterator itr;

	SECTION("operator +=")
	{
		itr += 1;

		REQUIRE(itr.advanceCounter == 1);
	}

	SECTION("operator +")
	{
		const auto secItr = itr + 1;

		REQUIRE(itr.advanceCounter == 0);
		REQUIRE(secItr.advanceCounter == 1);
	}

	SECTION("commutative operator +")
	{
		const auto secItr = 1 + itr;

		REQUIRE(itr.advanceCounter == 0);
		REQUIRE(secItr.advanceCounter == 1);
	}

	SECTION("operator -=")
	{
		itr -= 1;

		REQUIRE(itr.advanceCounter == 1);
	}

	SECTION("operator -")
	{
		const auto secItr = itr - 1;

		REQUIRE(itr.advanceCounter == 0);
		REQUIRE(secItr.advanceCounter == 1);
	}

	SECTION("operator - with iterator")
	{
		const auto diff = itr - itr;

		REQUIRE(itr.distanceCounter == 1);
	}

	SECTION("operator []")
	{
		const auto val = itr[1];

		REQUIRE(itr.advanceCounter == 0);
	}
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"Using test iterator types, iterator_interface should fulfill std::random_access_iterator concepts.",
	"[iterator_interface][random_access_iterator]",
	TestRandomAccessIterator
)
#pragma warning(default: 26444)
{
	using Itr_t = TestType;

	REQUIRE(std::totally_ordered<Itr_t>);
	REQUIRE(std::sized_sentinel_for<Itr_t, Itr_t>);

	REQUIRE(std::random_access_iterator<Itr_t>);
}
