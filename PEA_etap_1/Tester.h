#pragma once
#include <vector>
#include <string>
#include "Graph.h"
#include "BruteForceSolver.h"
#include "DynamicSolver.h"
#include "BranchAndBoundSolver.h"
#include "SimulatedAnnealingSolver.h"
#include "TabuSearchSolver.h"
#include "TestCase.h"

class Tester
{

public:


    static void testWithDataFromFiles(std::vector<std::vector<std::string>> fileNamesForEachAlgorithm, bool output);

    static void test(std::string fileName, firstSolutionMethod fsm, nextSolutionMethod nsm, coolingMethod cm, int maxTime);
    
private:

    static void test(std::vector<TestCase*> testCases, firstSolutionMethod fsm, nextSolutionMethod nsm, coolingMethod cm, int maxTime);

    static std::vector<TestCase*> sort(std::vector<TestCase*> testCases, algorithmEnum algorithm);

    static void test(TestCase* testCase);

    static void test(TestCase* testCase, firstSolutionMethod fsm, nextSolutionMethod nsm, coolingMethod cm, int maxTime);

    static std::vector<TestCase*> getTestCasesFromFile(std::string fileName);

    static void saveResult(std::string fileName, std::string instance, std::vector<float> timeResults);
};

