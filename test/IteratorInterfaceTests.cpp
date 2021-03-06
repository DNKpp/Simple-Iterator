//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <catch2/catch.hpp>

#include "TestTypes.hpp"

#include "Simple-Iterator/iterator_interface.hpp"

using namespace sl::itr;

TEST_CASE
(
	"input_iterator_tag iterator_interface should invoke pre-increment operator when post-incrementing.",
	"[iterator_interface][input_iterator]"
)
{
	TestInputIterator itr;
	// ReSharper disable once CppDiscardedPostfixOperatorResult
	itr++;

	REQUIRE(itr.incrementCounter == 1);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"Using test iterator types, iterator_interface should fulfill std::input_iterator concepts.",
	"[iterator_interface][input_iterator]",
	TestInputIterator,
	TestForwardIterator,
	TestBidirectionalIterator,
	TestRandomAccessIterator,
	TestReducedRandomAccessIterator,
	TestGetPtrContiguousIterator,
	TestGetContiguousIterator
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

	REQUIRE(tmp.incrementCounter == 0);
	REQUIRE(itr.incrementCounter == 1);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"Using test iterator types, iterator_interface should fulfill std::forward_iterator concepts.",
	"[iterator_interface][forward_iterator]",
	TestForwardIterator,
	TestBidirectionalIterator,
	TestRandomAccessIterator,
	TestReducedRandomAccessIterator,
	TestGetPtrContiguousIterator,
	TestGetContiguousIterator
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
	TestRandomAccessIterator,
	TestReducedRandomAccessIterator,
	TestGetPtrContiguousIterator,
	TestGetContiguousIterator
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

	REQUIRE(tmp.decrementCounter == 0);
	REQUIRE(itr.decrementCounter == 1);
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
	TestRandomAccessIterator,
	TestReducedRandomAccessIterator,
	TestGetPtrContiguousIterator,
	TestGetContiguousIterator
)
#pragma warning(default: 26444)
{
	using Itr_t = TestType;

	REQUIRE(std::totally_ordered<Itr_t>);
	REQUIRE(std::sized_sentinel_for<Itr_t, Itr_t>);

	REQUIRE(std::random_access_iterator<Itr_t>);
}

TEST_CASE
(
	"TestReducedRandomAccessIterator iterator_interface should invoke advance with 1 when incrementing.",
	"[iterator_interface][input_iterator]"
)
{
	TestReducedRandomAccessIterator itr;

	SECTION("pre-increment")
	{
		++itr;

		REQUIRE(itr.incrementCounter == 1);
		REQUIRE(itr.lastAdvanceDist == 1);
	}

	SECTION("post-increment")
	{
		const auto secItr = itr++;

		REQUIRE(itr.incrementCounter == 1);
		REQUIRE(itr.lastAdvanceDist == 1);

		REQUIRE(secItr.incrementCounter == 0);
		REQUIRE(secItr.lastAdvanceDist == 0);
	}
}

TEST_CASE
(
	"TestReducedRandomAccessIterator iterator_interface should invoke advance with -1 when decrementing.",
	"[iterator_interface][input_iterator]"
)
{
	TestReducedRandomAccessIterator itr;

	SECTION("pre-decrement")
	{
		--itr;

		REQUIRE(itr.decrementCounter == 1);
		REQUIRE(itr.lastAdvanceDist == -1);
	}

	SECTION("post-decrement")
	{
		const auto secItr = itr--;

		REQUIRE(itr.decrementCounter == 1);
		REQUIRE(itr.lastAdvanceDist == -1);

		REQUIRE(secItr.decrementCounter == 0);
		REQUIRE(secItr.lastAdvanceDist == 0);
	}
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"Using test iterator types, iterator_interface should fulfill std::contiguous_iterator concepts.",
	"[iterator_interface][contiguous_access_iterator]",
	TestGetPtrContiguousIterator,
	TestGetContiguousIterator
)
#pragma warning(default: 26444)
{
	using Itr_t = TestType;

	REQUIRE(std::contiguous_iterator<Itr_t>);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"TestGetContiguousIterator iterator_interface should call the expected get(_ptr) function when using arrow operator.",
	"[iterator_interface][contiguous_access_iterator]",
	TestGetPtrContiguousIterator,
	TestGetContiguousIterator
)
#pragma warning(default: 26444)
{
	using Itr_t = TestType;

	Itr_t itr;

	itr.operator->();

	REQUIRE(itr.ptrDereferenceCounter_const == 1);
}
