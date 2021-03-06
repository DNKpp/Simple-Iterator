//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <catch2/catch.hpp>

#include "TestTypes.hpp"

#include "Simple-Iterator/concepts.hpp"

using namespace sl::itr;

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"contiguous_iterator_category_tag concept should detect valid iterator tags",
	"[concept]",
	((class TTagType, bool VExpected), TTagType, VExpected),
	(int, false),
	(std::random_access_iterator_tag, false),
	(std::contiguous_iterator_tag, true)
)
#pragma warning(default: 26444)
{
	REQUIRE(contiguous_iterator_category_tag<TTagType> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"random_access_iterator_category_tag concept should detect valid iterator tags",
	"[concept]",
	((class TTagType, bool VExpected), TTagType, VExpected),
	(int, false),
	(std::bidirectional_iterator_tag, false),
	(std::random_access_iterator_tag, true),
	(std::contiguous_iterator_tag, true)
)
#pragma warning(default: 26444)
{
	REQUIRE(random_access_iterator_category_tag<TTagType> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"bidirectional_iterator_category_tag concept should detect valid iterator tags",
	"[concept]",
	((class TTagType, bool VExpected), TTagType, VExpected),
	(int, false),
	(std::forward_iterator_tag, false),
	(std::bidirectional_iterator_tag, true),
	(std::random_access_iterator_tag, true),
	(std::contiguous_iterator_tag, true)
)
#pragma warning(default: 26444)
{
	REQUIRE(bidirectional_iterator_category_tag<TTagType> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"forward_iterator_category_tag concept should detect valid iterator tags",
	"[concept]",
	((class TTagType, bool VExpected), TTagType, VExpected),
	(int, false),
	(std::input_iterator_tag, false),
	(std::output_iterator_tag, false),
	(std::forward_iterator_tag, true),
	(std::bidirectional_iterator_tag, true),
	(std::random_access_iterator_tag, true),
	(std::contiguous_iterator_tag, true)
)
#pragma warning(default: 26444)
{
	REQUIRE(forward_iterator_category_tag<TTagType> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"input_iterator_category_tag concept should detect valid iterator tags",
	"[concept]",
	((class TTagType, bool VExpected), TTagType, VExpected),
	(int, false),
	(std::output_iterator_tag, false),
	(std::input_iterator_tag, true),
	(std::forward_iterator_tag, true),
	(std::bidirectional_iterator_tag, true),
	(std::random_access_iterator_tag, true),
	(std::contiguous_iterator_tag, true)
)
#pragma warning(default: 26444)
{
	REQUIRE(input_iterator_category_tag<TTagType> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"output_iterator_category_tag concept should detect valid iterator tags",
	"[concept]",
	((class TTagType, bool VExpected), TTagType, VExpected),
	(int, false),
	(std::input_iterator_tag, false),
	(std::output_iterator_tag, true),
	(std::forward_iterator_tag, true),
	(std::bidirectional_iterator_tag, true),
	(std::random_access_iterator_tag, true),
	(std::contiguous_iterator_tag, true)
)
#pragma warning(default: 26444)
{
	REQUIRE(output_iterator_category_tag<TTagType> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"iterator_category_tag concept should detect valid iterator tags",
	"[concept]",
	((class TTagType, bool VExpected), TTagType, VExpected),
	(int, false),
	(std::input_iterator_tag, true),
	(std::output_iterator_tag, true),
	(std::forward_iterator_tag, true),
	(std::bidirectional_iterator_tag, true),
	(std::random_access_iterator_tag, true),
	(std::contiguous_iterator_tag, true)
)
#pragma warning(default: 26444)
{
	REQUIRE(iterator_category_tag<TTagType> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"dereferencable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(TestInputIterator, true),
	(TestForwardIterator, true),
	(TestBidirectionalIterator, true),
	(TestRandomAccessIterator, true),
	(TestReducedRandomAccessIterator, true),
	(int*, false),
	(int, false),
	(void*, false),
	(void, false)
)
#pragma warning(default: 26444)
{
	REQUIRE(dereferencable<T> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"incrementable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(int*, false),
	(int, false),
	(void, false),
	(TestIncrement, true)
)
#pragma warning(default: 26444)
{
	REQUIRE(incrementable<T> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"decrementable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(int*, false),
	(int, false),
	(void, false),
	(TestDecrement, true)
)
#pragma warning(default: 26444)
{
	REQUIRE(decrementable<T> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"input_iterator_suitable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(TestInputIterator, true),
	(TestForwardIterator, true),
	(TestBidirectionalIterator, true),
	(TestRandomAccessIterator, true),
	(int, false),
	(void, false)
)
#pragma warning(default: 26444)
{
	REQUIRE(input_iterator_suitable<T> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"forward_iterator_suitable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(TestForwardIterator, true),
	(TestBidirectionalIterator, true),
	(TestRandomAccessIterator, true),
	(int, false),
	(void, false)
)
#pragma warning(default: 26444)
{
	REQUIRE(forward_iterator_suitable<T> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"bidirectional_iterator_suitable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(TestBidirectionalIterator, true),
	(TestRandomAccessIterator, true),
	(int, false),
	(void, false)
)
#pragma warning(default: 26444)
{
	REQUIRE(bidirectional_iterator_suitable<T> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"random_access_iterator_suitable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(TestRandomAccessIterator, true),
	(int, false),
	(void, false)
)
#pragma warning(default: 26444)
{
	REQUIRE(random_access_iterator_suitable<T> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"contiguous_iterator_suitable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(TestGetContiguousIterator, true),
	(int, false),
	(void, false)
)
#pragma warning(default: 26444)
{
	REQUIRE(contiguous_iterator_suitable<T> == VExpected);
}
