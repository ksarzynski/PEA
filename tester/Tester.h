//
// Created by kacpe on 08.11.2021.
//

#ifndef PEA_1_TESTER_H
#define PEA_1_TESTER_H


#include <string>
#include <vector>

class Tester {

public:
    static void testWithRandomData(int bruteForceTests, int dynamicTests, int branchAndBoundTests);
    static void testWithDataFromFiles(std::vector<std::vector<std::string>> fileNamesForEachAlgorithm, bool output);
};


#endif //PEA_1_TESTER_H
