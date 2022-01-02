#include "Tester.h"

const int NO_ALGORITHMS = 5;
const std::string PATH = "C:/Users/kacpe/Downloads/pea_2/";

void Tester::testWithDataFromFiles(std::vector<std::vector<std::string>> fileNamesForEachAlgorithm, bool output) {
    if (fileNamesForEachAlgorithm.size() != NO_ALGORITHMS) {
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
    // simulated annealing
    for (const std::string& fileName : fileNamesForEachAlgorithm[3]) {
        auto graph = new Graph(fileName);
        auto simulatedAnnealingSolver = new SimulatedAnnealingSolver(graph);
        if (output)
            simulatedAnnealingSolver->solveWithOutput();
        else
            simulatedAnnealingSolver->solve();
        simulatedAnnealingSolver->getResult("simulated annealing");
        delete simulatedAnnealingSolver;
    }
    // tabu search
    for (const std::string& fileName : fileNamesForEachAlgorithm[4]) {
        auto graph = new Graph(fileName);
        auto tabuSearchSolver = new TabuSearchSolver(graph);
        if (output)
            tabuSearchSolver->solveWithOutput();
        else
            tabuSearchSolver->solve();
        tabuSearchSolver->getResult("tabu search");
        delete tabuSearchSolver;
    }
}

void Tester::test(std::string fileName, firstSolutionMethod fsm, nextSolutionMethod nsm, coolingMethod cm, int maxTime) {
    std::string resultsPath = PATH + "PEA_etap_1/results/";
    std::ofstream ofs;
    ofs.open(resultsPath + "brute_force_results_times.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open(resultsPath + "dynamic_results_times.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open(resultsPath + "branch_and_bound_results_times.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open(resultsPath + "simulated_annealing_results_times.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open(resultsPath + "tabu_search_results_times.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open(resultsPath + "brute_force_results_errors.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open(resultsPath + "dynamic_results_errors.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open(resultsPath + "branch_and_bound_results_errors.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open(resultsPath + "simulated_annealing_results_errors.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open(resultsPath + "tabu_search_results.txt_errors", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    test(getTestCasesFromFile(fileName), fsm, nsm, cm, maxTime);
}

void Tester::test(std::vector<TestCase*> testCases, firstSolutionMethod fsm, nextSolutionMethod nsm, coolingMethod cm, int maxTime) {
    // sorting test cases by algorithm so console output is more understandable
    std::vector<TestCase*> bruteForceTestCases = sort(testCases, static_cast<algorithmEnum>(0));
    std::vector<TestCase*> dynamicTestCases = sort(testCases, static_cast<algorithmEnum>(1));
    std::vector<TestCase*> branchAndBoundTestCases = sort(testCases, static_cast<algorithmEnum>(2));
    std::vector<TestCase*> simulatedAnnealingTestCases = sort(testCases, static_cast<algorithmEnum>(3));
    std::vector<TestCase*> tabuSearchTestCases = sort(testCases, static_cast<algorithmEnum>(4));
    // running tests
    for (TestCase* testCase : bruteForceTestCases)
        test(testCase);
    for (TestCase* testCase : dynamicTestCases)
        test(testCase);
    for (TestCase* testCase : branchAndBoundTestCases)
        test(testCase);
    for (TestCase* testCase : simulatedAnnealingTestCases)
        test(testCase, fsm, nsm, cm, maxTime);
    for (TestCase* testCase : tabuSearchTestCases)
        test(testCase, fsm, nsm, cm, maxTime);
}

void Tester::test(TestCase* testCase){
    std::string resultsPath = PATH + "PEA_etap_1/results/";
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
        saveResult(resultsPath + "brute_force_results", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults, std::vector<float>());
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
        saveResult(resultsPath + "dynamic_results", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults, std::vector<float>());
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
        saveResult(resultsPath + "branch_and_bound_results", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults, std::vector<float>());
        timeResults.clear();
        delete solver;
    }
          break;
    }
}

void Tester::test(TestCase* testCase, firstSolutionMethod fsm, nextSolutionMethod nsm, coolingMethod cm, int maxTime) {
    std::string resultsPath = PATH + "PEA_etap_1/results/";
    std::vector<float> timeResults;
    std::vector<float> errorResults;
    // if test case includes file name
    Graph* graph;
    if (testCase->getIsFromFile())
        graph = new Graph(testCase->getFileName());
    // if test case doesnt include file name
    else
        graph = new Graph(testCase->getSize(), testCase->getSize() * 10, false);
    switch (testCase->getAlgorithm()) {
          // simulated annealing
    case 3: {
        auto solver = new SimulatedAnnealingSolver(graph);
        for (int i = 0; i < testCase->getHowManyTests(); i++) {
            solver->setParams(fsm, nsm, cm);
            solver->solveWithOutput();
            timeResults.push_back((float)solver->getTime() / 1000000);
            errorResults.push_back(solver->getError());
        }
        saveResult(resultsPath + "simulated_annealing_results", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults, errorResults);
        timeResults.clear();
        delete solver;
    }
          break;

          // tabu search
    case 4: {
        auto solver = new TabuSearchSolver(graph);
        for (int i = 0; i < testCase->getHowManyTests(); i++) {
            solver->setParams(nsm, fsm, maxTime);
            solver->solveWithOutput();
            solver->getResult("tabu search");
            timeResults.push_back((float)solver->getTime() / 1000000);
            errorResults.push_back(solver->getError());
        }
        saveResult(resultsPath + "tabu_search_results", testCase->getFileName() +
            " size: " + std::to_string(testCase->getSize()), timeResults, errorResults);
        timeResults.clear();
        delete solver;
    }
          break;
    default: {
        std::cout << "wrong algorithm!\n";
    }
    }
}

std::vector<TestCase*> Tester::sort(std::vector<TestCase*> testCases, algorithmEnum algorithm) {
    std::vector<TestCase*> result;
    for (TestCase* testCase : testCases)
        if (testCase->getAlgorithm() == algorithm)
            result.push_back(testCase);
    return result;
}

// file structure:
// format: isFromFile, fileName, size, algorithm, howManyTests
// algorithm: 0 - brute force, 1 - dynamic, 2 - branch and bound, 3 - simulated annealing, 4 - tabu search
// field is equal to 0 if empty
std::vector<TestCase*> Tester::getTestCasesFromFile(std::string fileName) {
    std::vector<TestCase*> result;
    std::ifstream infile(PATH + "test/" + fileName);
    bool isFromFile;
    std::string _fileName;
    int size;
    int algorithm;
    int howManyTests;
    while (infile >> isFromFile >> _fileName >> size >> algorithm >> howManyTests) {
        algorithmEnum algorithm_ = static_cast<algorithmEnum>(algorithm);
        result.push_back(new TestCase(isFromFile, _fileName, size, algorithm_, howManyTests));
    }
    return result;
}

void Tester::saveResult(std::string fileName, std::string instance, std::vector<float> timeResults, std::vector<float> errorResults) {
    std::ofstream outfile;
    outfile.open(fileName + "_times.txt", std::ios_base::app);
    outfile << instance << std::endl;
    for (float result : timeResults)
        outfile << std::fixed << result << std::endl;
    outfile.close();
    outfile.open(fileName + "_errors.txt", std::ios_base::app);
    outfile << instance << std::endl;
    for (float result : errorResults)
        outfile << std::fixed << result << std::endl;
    outfile.close();
}
