cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(Simple_Iterator_Test)

include(FetchContent)

FetchContent_Declare(
	catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        origin/v2.x
)
FetchContent_MakeAvailable(catch2)

add_executable(
	${PROJECT_NAME}
	"main.cpp"
	"ConceptTests.cpp"
	"IteratorInterfaceTests.cpp"
 )

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	Simple_Iterator
	Catch2::Catch2
)

add_test(SimpleIteratorTestSuite ${PROJECT_NAME})
