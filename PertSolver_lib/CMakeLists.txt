cmake_minimum_required(VERSION 3.14)
project(PertSolver)

set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES PertProblem.h Parser.h)
set(SOURCE_FILES PertProblem.cpp Parser.cpp)

set(Boost_INCLUDE_DIR C:/local/boost_1_74_0)
find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_library(PertSolver_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

