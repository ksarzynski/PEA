//
// Created by kacpe on 08.11.2021.
//

#include <Graph.h>
#include <solvers_h/BruteForceSolver.h>
#include <solvers_h/DynamicSolver.h>
#include <solvers_h/BestFirstBranchAndBoundSolver.h>
#include <solvers_h/DepthFirstBranchAndBoundSolver.h>
#include "Tester.h"

void Tester::testWithDataFromFiles(std::vector<std::vector<std::string>> fileNamesForEachAlgorithm, bool output) {
    if(fileNamesForEachAlgorithm.size() > 4){
        std::cout << "Wrong data input!";
        return;
    }
    // brute force
    for(const std::string& fileName: fileNamesForEachAlgorithm[0]){
        auto graph = new Graph(fileName);
        auto bruteForceSolver = new BruteForceSolver(graph);
        if (output)
            bruteForceSolver->solveWithOutput();
        else
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
    // best first branch and bound
    for(const std::string& fileName: fileNamesForEachAlgorithm[2]){
        auto graph = new Graph(fileName);
        auto bestFirstbranchAndBoundSolver = new BestFirstBranchAndBoundSolver(graph);
        if (output)
            bestFirstbranchAndBoundSolver->solveWithOutput();
        else
            bestFirstbranchAndBoundSolver->solve();
        bestFirstbranchAndBoundSolver->getResult("best first branch and bound");
        delete bestFirstbranchAndBoundSolver;
    }
    // depth first branch and bound
    for (const std::string& fileName : fileNamesForEachAlgorithm[3]) {
        auto graph = new Graph(fileName);
        auto depthFirstbranchAndBoundSolver = new DepthFirstBranchAndBoundSolver(graph);
        if (output)
            depthFirstbranchAndBoundSolver->solveWithOutput();
        else
            depthFirstbranchAndBoundSolver->solve();
        depthFirstbranchAndBoundSolver->getResult("depth first branch and bound");
        delete depthFirstbranchAndBoundSolver;
    }
}

void Tester::testWithRandomData(int bruteForceTests, int dynamicTests, int branchAndBoundTests)
{
}
