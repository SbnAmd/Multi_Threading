cmake_minimum_required(VERSION 3.25)
project(Multi_Threading)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        Examples/Common
                    Examples/Simple/Large_Array_Summation
                    )

add_executable(Multi_Threading
                main.cpp main.h
                Examples/Simple/Large_Array_Summation/large_array_summation.cpp
        Examples/Common/common.cpp)
