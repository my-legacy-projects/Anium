cmake_minimum_required(VERSION 3.9)
project(Anium)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./bin)

file(GLOB_RECURSE SRC src/*.cpp src/*.hpp)

if (NOT CMAKE_BUILD_TYPE)
    message(WARNING "No build type has been selected, defaulting to Release.")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(CMAKE_CXX_FLAGS "-O3 -Wall -fPIC -std=c++17")

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wno-unused-parameter")
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
    # Prevents generation of STB_GNU_UNIQUE symbols which prevent unloading using dlclose
    # https://stackoverflow.com/a/39123106/7360990
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --no-gnu-unique")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -D_DEBUG -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -s")

if (WIN32)
    set(CMAKE_DL_LIBS)
elseif (APPLE)
    set(CMAKE_DL_LIBS dl pthread c stdc++)
elseif (UNIX) # Linux
    set(CMAKE_DL_LIBS dl pthread c stdc++ stdc++fs)
endif()

add_library(Anium SHARED ${SRC})

target_link_libraries(Anium ${CMAKE_DL_LIBS})
