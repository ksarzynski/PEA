#include "Tester.h"

void Tester::testWithDataFromFiles(std::vector<std::vector<std::string>> fileNamesForEachAlgorithm, bool output) {
    if (fileNamesForEachAlgorithm.size() != 6) {
        std::cout << "Wrong data input!";
        return;
    }
    // brute force
    for (const std::string& fileName : fileNamesForEachAlgorithm[0]) {
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
    for (const std::string& fileName : fileNamesForEachAlgorithm[1]) {
        auto graph = new Graph(fileName);
        auto dynamicSolver = new DynamicSolver(graph);
        dynamicSolver->solve();
        dynamicSolver->getResult("dynamic");
        delete dynamicSolver;
    }
    // branch and bound
    for (const std::string& fileName : fileNamesForEachAlgorithm[2]) {
        auto graph = new Graph(fileName);
        auto branchAndBoundSolver = new BranchAndBoundSolver(graph);
        if (output)
            branchAndBoundSolver->solveWithOutput();
        else
            branchAndBoundSolver->solve();
        branchAndBoundSolver->getResult("branch and bound");
        delete branchAndBoundSolver;
    }
    // multi threaded brute force
    for (const std::string& fileName : fileNamesForEachAlgorithm[3]) {
        auto graph = new Graph(fileName);
        auto multiThreadedBFSolver = new MultiThreadedBFSolver(graph);
        if (output)
            multiThreadedBFSolver->solveWithOutput();
        else
            multiThreadedBFSolver->solve();
        multiThreadedBFSolver->getResult("multi threaded bf");
        delete multiThreadedBFSolver;
    }
    // simulated annealing
    for (const std::string& fileName : fileNamesForEachAlgorithm[4]) {
        auto graph = new Graph(fileName);
        auto simulatedAnnealingSolver = new MultiThreadedBFSolver(graph);
        if (output)
            simulatedAnnealingSolver->solveWithOutput();
        else
            simulatedAnnealingSolver->solve();
        simulatedAnnealingSolver->getResult("simulated annealing");
        delete simulatedAnnealingSolver;
    }
    // multi threaded simulated annealing
    for (const std::string& fileName : fileNamesForEachAlgorithm[5]) {
        auto graph = new Graph(fileName);
        auto simulatedAnnealingSolver = new SimulatedAnnealingSolver(graph);
        if (output)
            simulatedAnnealingSolver->solveWithOutput();
        else
            simulatedAnnealingSolver->solve();
        simulatedAnnealingSolver->getResult("simulated annealing");
        delete simulatedAnnealingSolver;
    }
}

void Tester::testWithRandomData(int bruteForceTests, int dynamicTests, int branchAndBoundTests){

}

void Tester::test(std::string fileName) {
    std::ofstream ofs;
    ofs.open("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/brute_force_results.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/dynamic_results.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/branch_and_bound_results.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/multi_threaded_bf_results.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/simulated_annealing.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/multi_threaded_simulated_annealing.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    test(getTestCasesFromFile(fileName));
}

void Tester::test(std::vector<TestCase*> testCases) {
    // sorting test cases by algorithm so console output is more understandable
    std::vector<TestCase*> bruteForceTestCases = sort(testCases, 0);
    std::vector<TestCase*> dynamicTestCases = sort(testCases, 1);
    std::vector<TestCase*> branchAndBoundTestCases = sort(testCases, 2);
    std::vector<TestCase*> multiThreadedBFTestCases = sort(testCases, 3);
    std::vector<TestCase*> simulatedAnnealingTestCases = sort(testCases, 4);
    std::vector<TestCase*> multiThreadedSATestCases = sort(testCases, 5);
    // running tests
    for (TestCase* testCase : bruteForceTestCases)
        test(testCase);
    for (TestCase* testCase : dynamicTestCases)
        test(testCase);
    for (TestCase* testCase : branchAndBoundTestCases)
        test(testCase);
    for (TestCase* testCase : multiThreadedBFTestCases)
        test(testCase);
    for (TestCase* testCase : simulatedAnnealingTestCases)
        test(testCase);
    for (TestCase* testCase : multiThreadedSATestCases)
        test(testCase);
}

void Tester::test(TestCase* testCase){
    std::vector<float> timeResults;
    // if test case includes file name
    Graph* graph;
    if (testCase->getIsFromFile()) 
        graph = new Graph(testCase->getFileName());
    // if test case doesnt include file name
    else
        graph = new Graph(testCase->getSize(), testCase->getSize() * 10, false);
    switch (testCase->getAlgorithm()) {
    
    // brute force
    case 0: {
        auto solver = new BruteForceSolver(graph);
        for (int i = 0; i < testCase->getHowManyTests(); i++) {
            solver->solve();
            solver->getResult("brute force");
            timeResults.push_back((float)solver->getTime() / 1000000);
        }
        saveResult("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/brute_force_results.txt", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults);
        timeResults.clear();
        delete solver;
    }
          break;
    
    // dynamic
    case 1: {
        auto solver = new DynamicSolver(graph);
        for (int i = 0; i < testCase->getHowManyTests(); i++) {
            solver->solve();
            solver->getResult("dynamic");
            timeResults.push_back((float)solver->getTime() / 1000000);
        }
        saveResult("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/dynamic_results.txt", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults);
        timeResults.clear();
        delete solver;
    }
          break;
    
    // branch and bound
    case 2: {
        auto solver = new BranchAndBoundSolver(graph);
        for (int i = 0; i < testCase->getHowManyTests(); i++) {
            solver->solve();
            solver->getResult("branch and bound");
            timeResults.push_back((float)solver->getTime() / 1000000);
        }
        saveResult("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/branch_and_bound_results.txt", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults);
        timeResults.clear();
        delete solver;
    }
          break;

    // multi threaded bf
    case 3: {
        auto solver = new MultiThreadedBFSolver(graph);
        for (int i = 0; i < testCase->getHowManyTests(); i++) {
            solver->solve();
            solver->getResult("multi threaded bf");
            timeResults.push_back((float)solver->getTime() / 1000000);
        }
        saveResult("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/multi_threaded_bf_results.txt", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults);
        timeResults.clear();
        delete solver;
    }
          break;
    
    // simulated annealing
    case 4: {
        auto solver = new SimulatedAnnealingSolver(graph);
        for (int i = 0; i < testCase->getHowManyTests(); i++) {
            solver->solve();
            solver->getResult("simulated annealing");
            timeResults.push_back((float)solver->getTime() / 1000000);
        }
        saveResult("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/simulated_annealing.txt", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults);
        timeResults.clear();
        delete solver;
    }
          break;

    // multi threaded sa
    case 5: {
        auto solver = new SimulatedAnnealingSolver(graph);
        for (int i = 0; i < testCase->getHowManyTests(); i++) {
            solver->solve();
            solver->getResult("multi threaded sa");
            timeResults.push_back((float)solver->getTime() / 1000000);
        }
        saveResult("C:/Users/kacpe/source/repos/PEA_etap_1/PEA_etap_1/results/multi_threaded_sa_results.txt", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults);
        timeResults.clear();
        delete solver;
    }
          break;

    default: {
        std::cout << "wrong algorithm!\n";
    }
    }
}

std::vector<TestCase*> Tester::sort(std::vector<TestCase*> testCases, int algorithm) {
    std::vector<TestCase*> result;
    for (TestCase* testCase : testCases)
        if (testCase->getAlgorithm() == algorithm)
            result.push_back(testCase);
    return result;
}

// file structure:
// format: isFromFile, fileName, size, algorithm, howManyTests
// algorithm: 
//  0 - brute force,
//  1 - dynamic,
//  2 - branch and bound,
//  3 - multi threaded bf,
//  4 - simulated annealing,
//  5 - multi threaded simulated annealing
// field is equal to 0 if empty
std::vector<TestCase*> Tester::getTestCasesFromFile(std::string fileName) {
    std::vector<TestCase*> result;
    std::ifstream infile("C:/Users/kacpe/Downloads/pea_watki/test/" + fileName);
    bool isFromFile;
    std::string _fileName;
    int size;
    int algorithm;
    int howManyTests;
    while (infile >> isFromFile >> _fileName >> size >> algorithm >> howManyTests)
        result.push_back(new TestCase(isFromFile, _fileName, size, algorithm, howManyTests));
    return result;
}

void Tester::saveResult(std::string fileName, std::string instance, std::vector<float> timeResults) {
    std::ofstream outfile;
    outfile.open(fileName, std::ios_base::app);
    outfile << instance << std::endl;
    for (float result : timeResults)
        outfile << std::fixed << result << std::endl;
    outfile.close();
}
