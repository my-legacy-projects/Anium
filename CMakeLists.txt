cmake_minimum_required(VERSION 2.6)
project(Anium)

# Prefered compilers on each platform:
# * Windows: Microsoft Visual C++ Compiler
# * Mac OS: GCC
# * Linux: Clang

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./bin)

file(GLOB_RECURSE SRC src/*.cpp src/*.hpp)

if (NOT CMAKE_BUILD_TYPE)
    message(WARNING "No build type has been selected, defaulting to Release.")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(SHARED_FLAGS "-O3 -std=c++17 -Wall -fPIC -shared")
set(CMAKE_CXX_FLAGS_DEBUG "${SHARED_FLAGS} -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${SHARED_FLAGS}")

add_library(Anium SHARED ${SRC})

if (WIN32)
    # Windows link targets
    target_link_libraries(Anium c stdc++)
else()
    # *nix link targets
    target_link_libraries(Anium c stdc++ SDL2 GL dl)
endif()
