#pragma once
#include <vector>
#include <string>
#include "Graph.h"
#include "BruteForceSolver.h"
#include "DynamicSolver.h"
#include "BranchAndBoundSolver.h"
#include "MultiThreadedBFSolver.h"
#include "TestCase.h"

class Tester
{

public:

    static void testWithRandomData(int bruteForceTests, int dynamicTests, int branchAndBoundTests);

    static void testWithDataFromFiles(std::vector<std::vector<std::string>> fileNamesForEachAlgorithm, bool output);

    static void test(std::string fileName);
    
private:

    static void test(std::vector<TestCase*> testCases);

    static std::vector<TestCase*> sort(std::vector<TestCase*> testCases, int algorithm);

    static void test(TestCase* testCase);

    static std::vector<TestCase*> getTestCasesFromFile(std::string fileName);

    static void saveResult(std::string fileName, std::string instance, std::vector<float> timeResults);
};

