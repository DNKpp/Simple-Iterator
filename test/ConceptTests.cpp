//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <catch2/catch.hpp>

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
	"non_void concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(int, true),
	(void*, true),
	(const void*, true),
	(void, false)
)
#pragma warning(default: 26444)
{
	REQUIRE(non_void<T> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"dereferencable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(int*, true),
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
	"arrow_dereferencable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(int*, false),
	(int, false),
	(void, false),
	(std::string, false),
	(std::string&, false),
	(std::string*, true),
	(const std::string*, true)
)
#pragma warning(default: 26444)
{
	REQUIRE(arrow_dereferencable<T> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"pre_incrementable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(int*, true),
	(int, true),
	(void, false)
)
#pragma warning(default: 26444)
{
	REQUIRE(pre_incrementable<T> == VExpected);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE_SIG
(
	"input_iterator_suitable concept should detect valid types",
	"[concept]",
	((class T, bool VExpected), T, VExpected),
	(int*, true),
	(const int*, true),
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
	(int*, true),
	(const int*, true),
	(int, false),
	(void, false)
)
#pragma warning(default: 26444)
{
	REQUIRE(forward_iterator_suitable<T> == VExpected);
}
