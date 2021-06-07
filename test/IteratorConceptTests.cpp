//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <catch2/catch.hpp>

#include "Simple-Iterator/bidirectional_iterator.hpp"
#include "Simple-Iterator/contiguous_iterator.hpp"
#include "Simple-Iterator/forward_iterator.hpp"
#include "Simple-Iterator/input_iterator.hpp"
#include "Simple-Iterator/iterator.hpp"
#include "Simple-Iterator/random_access_iterator.hpp"

using namespace sl::itr;

namespace
{
	struct TestValueType
	{
		int m = 0;
	};

	// there is no general iterator concept, thus I have to gather all requirements myself.
	// https://en.cppreference.com/w/cpp/named_req/Iterator
	template <class TItr>
	concept legacy_iterator = requires(TItr i)
	{
		typename TItr::value_type;
		{ *i } -> non_void;
		{ ++i } -> std::same_as<TItr&>;
		{ *i++ } -> non_void;
	};

	class TestIterator :
		public detail::base_iterator<TestValueType, TestIterator, TestValueType*, int, std::plus<>{}, dereference{},
									std::input_iterator_tag>
	{
	public:
		TestIterator() noexcept = default;
	};

	class TestInputIterator :
		public detail::base_input_iterator<TestValueType, TestInputIterator>
	{
	public:
		TestInputIterator() noexcept = default;
	};

	class TestForwardIterator :
		public detail::base_forward_iterator<TestValueType, TestForwardIterator>
	{
	public:
		TestForwardIterator() noexcept = default;
	};

	class TestBidirectionalIterator :
		public detail::base_bidirectional_iterator<TestValueType, TestBidirectionalIterator>
	{
	public:
		TestBidirectionalIterator() noexcept = default;
	};

	class TestRandomAccessIterator :
		public detail::base_random_access_iterator<TestValueType, TestRandomAccessIterator>
	{
	public:
		TestRandomAccessIterator() noexcept = default;
	};

	class TestContiguousIterator :
		public detail::base_contiguous_iterator<TestValueType, TestContiguousIterator>
	{
	public:
		TestContiguousIterator() noexcept = default;
	};
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"iterators should match all concepts of LegacyIterator",
	"[iterator]",
	TestIterator,
	TestInputIterator,
	TestForwardIterator,
	TestBidirectionalIterator,
	TestRandomAccessIterator,
	TestContiguousIterator,

	input_iterator<int>,
	forward_iterator<int>,
	bidirectional_iterator<int>,
	random_access_iterator<int>,
	contiguous_iterator<int>
)
#pragma warning(default: 26444)
{
	using Iterator_t = TestType;

	REQUIRE(std::copyable<Iterator_t>);
	REQUIRE(std::destructible<Iterator_t>);
	REQUIRE(std::swappable<Iterator_t>);
	REQUIRE(legacy_iterator<Iterator_t>);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"iterators should match all concepts of std::input_iterator",
	"[iterator][input_iterator]",
	TestInputIterator,
	TestForwardIterator,
	TestBidirectionalIterator,
	TestRandomAccessIterator,
	TestContiguousIterator,

	input_iterator<int>,
	forward_iterator<int>,
	bidirectional_iterator<int>,
	random_access_iterator<int>,
	contiguous_iterator<int>
)
#pragma warning(default: 26444)
{
	using Iterator_t = TestType;

	// unroll nested concepts here, thus we are able to determine potential issues more easily
	REQUIRE(std::equality_comparable<Iterator_t>);

	REQUIRE(std::default_initializable<Iterator_t>);
	REQUIRE(std::movable<Iterator_t>);
	REQUIRE(std::weakly_incrementable<Iterator_t>);

	REQUIRE(std::indirectly_readable<Iterator_t>);
	REQUIRE(std::input_or_output_iterator<Iterator_t>);
	REQUIRE(std::input_iterator<Iterator_t>);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"iterators should match all concepts of std::forward_iterator",
	"[iterator][input_iterator][forward_iterator]",
	TestForwardIterator,
	TestBidirectionalIterator,
	TestRandomAccessIterator,
	TestContiguousIterator,

	forward_iterator<int>,
	bidirectional_iterator<int>,
	random_access_iterator<int>,
	contiguous_iterator<int>
)
#pragma warning(default: 26444)
{
	using Iterator_t = TestType;

	// unroll nested concepts here, thus we are able to determine potential issues more easily
	REQUIRE(std::regular<Iterator_t>);
	REQUIRE(std::incrementable<Iterator_t>);
	REQUIRE(std::sentinel_for<Iterator_t, Iterator_t>);
	REQUIRE(std::forward_iterator<Iterator_t>);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"iterators should match all concepts of std::bidirectional_iterator",
	"[iterator][input_iterator][forward_iterator][bidirectional_iterator]",
	TestBidirectionalIterator,
	TestRandomAccessIterator,
	TestContiguousIterator,

	bidirectional_iterator<int>,
	random_access_iterator<int>,
	contiguous_iterator<int>
)
#pragma warning(default: 26444)
{
	using Iterator_t = TestType;

	// unroll nested concepts here, thus we are able to determine potential issues more easily
	REQUIRE(std::bidirectional_iterator<Iterator_t>);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"iterators should match all concepts of std::random_access_iterator",
	"[iterator][input_iterator][forward_iterator][bidirectional_iterator][random_access_iterator]",
	TestRandomAccessIterator,
	TestContiguousIterator,

	random_access_iterator<int>,
	contiguous_iterator<int>
)
#pragma warning(default: 26444)
{
	using Iterator_t = TestType;

	// unroll nested concepts here, thus we are able to determine potential issues more easily
	REQUIRE(std::totally_ordered<Iterator_t>);
	REQUIRE(std::sentinel_for<Iterator_t, Iterator_t>);
	REQUIRE(std::sized_sentinel_for<Iterator_t, Iterator_t>);
	REQUIRE(std::random_access_iterator<Iterator_t>);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"iterators should match all concepts of std::contiguous_iterator",
	"[iterator][input_iterator][forward_iterator][bidirectional_iterator][random_access_iterator][contiguous_iterator]",
	TestContiguousIterator,

	contiguous_iterator<int>
)
#pragma warning(default: 26444)
{
	using Iterator_t = TestType;

	// unroll nested concepts here, thus we are able to determine potential issues more easily
	REQUIRE(std::is_lvalue_reference_v<std::iter_reference_t<Iterator_t>>);
	REQUIRE(std::same_as<std::iter_value_t<Iterator_t>, std::remove_cvref_t<std::iter_reference_t<Iterator_t>>>);
	REQUIRE(std::contiguous_iterator<Iterator_t>);
}
