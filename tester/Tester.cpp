//
// Created by kacpe on 08.11.2021.
//

#include <Graph.h>
#include <solvers_h/BruteForceSolver.h>
#include <solvers_h/DynamicSolver.h>
#include <solvers_h/BranchAndBoundSolver.h>
#include "Tester.h"

void Tester::testWithDataFromFiles(std::vector<std::vector<std::string>> fileNamesForEachAlgorithm) {
    if(fileNamesForEachAlgorithm.size() > 3){
        std::cout << "Wrong data input!";
        return;
    }
    // brute force
    for(const std::string& fileName: fileNamesForEachAlgorithm[0]){
        auto graph = new Graph(fileName);
        auto bruteForceSolver = new BruteForceSolver(graph);
        bruteForceSolver->solve();
        bruteForceSolver->getResult("brute force");
        delete bruteForceSolver;
    }
    // dynamic
    for(const std::string& fileName: fileNamesForEachAlgorithm[1]){
        auto graph = new Graph(fileName);
        auto dynamicSolver = new DynamicSolver(graph);
        dynamicSolver->solve();
        dynamicSolver->getResult("dynamic");
        delete dynamicSolver;
    }
    // branch and bound
    for(const std::string& fileName: fileNamesForEachAlgorithm[2]){
        auto graph = new Graph(fileName);
        auto branchAndBoundSolver = new BranchAndBoundSolver(graph);
        branchAndBoundSolver->solve();
        branchAndBoundSolver->getResult("branch and bound");
        delete branchAndBoundSolver;
    }
}
