project(PertSolver)

set(HEADER_FILES PertProblem.h)
set(SOURCE_FILES PertProblem.cpp)


add_library(PertSolver_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})