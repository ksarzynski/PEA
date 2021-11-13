cmake_minimum_required(VERSION 3.19)
project(PEA_1)

set(CMAKE_CXX_STANDARD 14)

set(APP_SOLVERS ./solvers)
set(APP_GRAPH ./graph)
set(APP_TESTER ./tester)
set(APP_HELPERS ./helpers)

include_directories(${APP_SOLVERS})
include_directories(${APP_GRAPH})
include_directories(${APP_TESTER})
include_directories(${APP_HELPERS})

set(
        SOURCE_FILES
            main.cpp
            ${APP_SOLVERS}/solvers_h/Solver.h
            ${APP_SOLVERS}/solvers_cpp/Solver.cpp
            ${APP_SOLVERS}/solvers_h/BruteForceSolver.h
            ${APP_SOLVERS}/solvers_cpp/BruteForceSolver.cpp
            ${APP_SOLVERS}/solvers_h/DynamicSolver.h
            ${APP_SOLVERS}/solvers_cpp/DynamicSolver.cpp
            ${APP_SOLVERS}/solvers_h/BestFirstBranchAndBoundSolver.h
            ${APP_SOLVERS}/solvers_cpp/BestFirstBranchAndBoundSolver.cpp
            ${APP_SOLVERS}/solvers_h/DepthFirstBranchAndBoundSolver.h
            ${APP_SOLVERS}/solvers_cpp/DepthFirstBranchAndBoundSolver.cpp
            ${APP_GRAPH}/Graph.h
            ${APP_GRAPH}/Graph.cpp
            ${APP_TESTER}/Tester.h
            ${APP_TESTER}/Tester.cpp
            ${APP_HELPERS}/Node.h
            ${APP_HELPERS}/Node.cpp
)

add_executable(untitled ${SOURCE_FILES})