cmake_minimum_required(VERSION 3.30)
project(Employee_Record_Sorter)

set(CMAKE_CXX_STANDARD 23)

add_executable(Employee_Record_Sorter
                src/main.cpp
                src/merge_sort.cpp
                src/sort_data.cpp)
