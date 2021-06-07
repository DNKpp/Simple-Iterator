//          Copyright Dominic Koepke 2021 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <catch2/catch.hpp>

#include "Simple-Iterator/iterator_interface.hpp"

using namespace sl::itr;

namespace
{
	template <class TIteratorTag>
	struct TestIterator : public iterator_interface<TIteratorTag, TestIterator<TIteratorTag>>
	{
	private:
		using super = iterator_interface<TIteratorTag, TestIterator<TIteratorTag>>;

	public:
		using element_type = int;
		using difference_type = std::ptrdiff_t;

		int dummyValue = 0;

		mutable int dereferenceCounter_const = 0;
		mutable int preIncrementCounter = 0;

		[[nodiscard]]
		constexpr const int& operator *() const
		{
			++dereferenceCounter_const;
			return dummyValue;
		}

		constexpr TestIterator& operator ++()
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
	TestIterator<std::input_iterator_tag> itr;
	// ReSharper disable once CppDiscardedPostfixOperatorResult
	itr++;

	REQUIRE(itr.preIncrementCounter == 1);
}

#pragma warning(disable: 26444)
TEMPLATE_TEST_CASE
(
	"Using TestIterator, iterator_interface should fulfill std::input_iterator concepts.",
	"[iterator_interface][input_iterator]",
	(std::input_iterator_tag)
)
#pragma warning(default: 26444)
{
	using Itr_t = TestIterator<TestType>;

	REQUIRE(std::default_initializable<Itr_t>);
	REQUIRE(std::movable<Itr_t>);
	REQUIRE(std::weakly_incrementable<Itr_t>);
	REQUIRE(std::input_or_output_iterator<Itr_t>);

	REQUIRE(std::indirectly_readable<Itr_t>);

	REQUIRE(std::input_iterator<Itr_t>);
}
