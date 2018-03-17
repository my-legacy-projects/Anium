cmake_minimum_required(VERSION 2.6)
project(Anium)

option(CPP20 "Enable experimental support for C++20 (C++2a) - requires a compiler that supports it" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./bin)

file(GLOB_RECURSE SRC src/*.cpp src/*.hpp)

if (NOT CMAKE_BUILD_TYPE)
    message(WARNING "No build type has been selected, defaulting to Release.")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(SHARED_FLAGS "-O3 -Wall -fPIC")

if(CPP20)
    set(SHARED_FLAGS "${SHARED_FLAGS} -std=c++2a")
else()
    set(SHARED_FLAGS "${SHARED_FLAGS} -std=c++17")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${SHARED_FLAGS} -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${SHARED_FLAGS}")

if (WIN32)
    set(CMAKE_DL_LIBS)
elseif (APPLE)
    set(CMAKE_DL_LIBS dl pthread c stdc++)
elseif (UNIX) # Linux
    set(CMAKE_DL_LIBS dl pthread c stdc++ stdc++fs)
endif()

add_library(Anium SHARED ${SRC})

target_link_libraries(Anium ${CMAKE_DL_LIBS})
