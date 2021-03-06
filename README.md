# Simple-Iterator C++20 library

|windows msvc | windows clang-cl | ubuntu clang | ubuntu gcc|
-------------|------------------|--------------|--------------
| ![Build & Test - MSVC](https://github.com/DNKpp/Simple-Iterator/workflows/Build%20&%20Test%20-%20MSVC/badge.svg) | ![Build & Test - Clang-Cl](https://github.com/DNKpp/Simple-Iterator/workflows/Build%20&%20Test%20-%20Clang-Cl/badge.svg) | ![Build & Test - Clang-10](https://github.com/DNKpp/Simple-Iterator/workflows/Build%20&%20Test%20-%20Clang-10/badge.svg) | ![Build & Test - GCC-10](https://github.com/DNKpp/Simple-Iterator/workflows/Build%20&%20Test%20-%20GCC-10/badge.svg) |
|			|					| ![Build & Test - Clang-11](https://github.com/DNKpp/Simple-Iterator/actions/workflows/build_and_test-Clang-11.yml/badge.svg) | ![Build & Test - GCC-11](https://github.com/DNKpp/Simple-Iterator/actions/workflows/build_and_test-GCC-11.yml/badge.svg) |
|			|					| ![Build & Test - Clang-12](https://github.com/DNKpp/Simple-Iterator/actions/workflows/build_and_test-Clang-12.yml/badge.svg) |	|

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/f6464e1b3fce49f193baeaf2acfd0b58)](https://www.codacy.com/gh/DNKpp/Simple-Iterator/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=DNKpp/Simple-Iterator&amp;utm_campaign=Badge_Grade)

## Author
Dominic Koepke  
Mail: [DNKpp2011@gmail.com](mailto:dnkpp2011@gmail.com)

## License

[BSL-1.0](https://github.com/DNKpp/Simple-Log/blob/master/LICENSE_1_0.txt) (free, open source)

```text
          Copyright Dominic Koepke 2021 - 2021.
 Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
          https://www.boost.org/LICENSE_1_0.txt)
```

## Description
This library provides an iterator_interface class, which aims to reduce the boilerplate needed for ``c++20`` iterator like classes. Users must simply inherit from that class,
provide some minimal template arguments and implement a minimal amount of methods (depending on the aimed category) until the custom iterator is ready for use.
Everything is checked via concepts, thus it should be quite easy to find the missing or wrong parts in your definition. Have a look into the wiki, if you need a more in depth
explanation or simply some examples.

I took the new std::ranges::view_interface as an inspiration how to design such a class.

Be aware that many clang and gcc versions doesn't finally support all used ``c++20`` features. Have a look at the badges on top, to get an idea which one might fit.


## Installation with CMake
This library can easily be integrated into your project via CMake target_link_libraries command.

```cmake
target_link_libraries(
	<your_target_name>
	PRIVATE
	simple_iterator
)
```
This will add the the include path "<simple_iterator_install_dir>/include", thus you are able to include the headers via
```cpp
#include <Simple-Iterator/iterator_interface.hpp>
```

### FetchContent
It is possible fetching this library via CMakes FetchContent module.

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(<your_project_name>)

include(FetchContent)

FetchContent_Declare(
	simple_iterator
	GIT_REPOSITORY	https://github.com/DNKpp/Simple-Iterator
	GIT_TAG		origin/v1.x
)
FetchContent_MakeAvailable(simple_iterator)

target_link_libraries(
	<your_target_name>
	PRIVATE simple_iterator
)
```
