cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(Simple_Iterator
	LANGUAGES CXX
)

set(TestsDir "${CMAKE_CURRENT_SOURCE_DIR}/test/")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
	${PROJECT_NAME}
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(
	${PROJECT_NAME}
	INTERFACE
	cxx_std_20
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

	include(CTest)

	if (BUILD_TESTING)
		add_subdirectory(${TestsDir})
	endif()

endif()
