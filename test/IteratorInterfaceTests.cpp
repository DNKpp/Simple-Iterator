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
	(TestInputIterator)
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
