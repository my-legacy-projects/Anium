cmake_minimum_required(VERSION 2.6)
project(Anium)

# Prefered compilers on each platform:
# * Windows: Microsoft Visual C++ Compiler
# * *nix: Clang

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./bin)

file(GLOB_RECURSE SRC src/*.cpp src/*.hpp)

if (NOT CMAKE_BUILD_TYPE)
    message(WARNING "No build type has been selected, defaulting to Release.")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(SHARED_FLAGS "-O3 -std=c++17 -Wall -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${SHARED_FLAGS} -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${SHARED_FLAGS}")

if (WIN32)
    set(CMAKE_DL_LIBS dlfcn-win32::dl psapi)
elseif (APPLE)
    set(CMAKE_DL_LIBS dl pthread)
elseif (UNIX) # Linux
    set(CMAKE_DL_LIBS dl pthread)
endif()

set(CMAKE_DL_LIBS ${CMAKE_DL_LIBS} c stdc++)

add_library(Anium SHARED ${SRC})

target_link_libraries(Anium ${CMAKE_DL_LIBS})
