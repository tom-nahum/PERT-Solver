cmake_minimum_required(VERSION 3.14)
project(PertSolver)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(PertSolver_run ${SOURCE_FILES})

set(Boost_INCLUDE_DIR C:/local/boost_1_74_0)

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


include_directories(PertSolver_lib)
add_subdirectory(PertSolver_lib)

target_link_libraries(PertSolver_run PertSolver_lib)

add_subdirectory(Google_tests)

