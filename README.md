# Simple-Log C++20 library
![Build & Test - MSVC](https://github.com/DNKpp/Simple-Iterator/workflows/Build%20&%20Test%20-%20MSVC/badge.svg)
![Build & Test - Clang-Cl](https://github.com/DNKpp/Simple-Iterator/workflows/Build%20&%20Test%20-%20Clang-Cl/badge.svg)
![Build & Test - Clang-10](https://github.com/DNKpp/Simple-Iterator/workflows/Build%20&%20Test%20-%20Clang-10/badge.svg)
![Build & Test - GCC-10](https://github.com/DNKpp/Simple-Iterator/workflows/Build%20&%20Test%20-%20GCC-10/badge.svg)

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
This library provides easy to use iterator like classes, one for most of the std iterator categories (currently excluding output_iterator). Even with c++20 it is rather tedious to write custom iterator classes,
thus this library aims to take over the boilerplate, but opens up various customization points for the users.


## Installation with CMake
This library can easily be integrated into your project via CMake target_link_libraries command.

```cmake
target_link_libraries(
	<your_target_name>
	PRIVATE
	simple_iterator
)
```
This will add the the include path "<simple_iterator_install_dir>/include", thus you are able to include all headers via
```cpp
#include <Simple-Iterator/input_iterator.hpp>
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
	GIT_TAG		origin/master
)
FetchContent_MakeAvailable(simple_iterator)

target_link_libraries(
	<your_target_name>
	PRIVATE simple_iterator
)
```