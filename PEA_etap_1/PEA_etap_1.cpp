#include "Tester.h"
#include "MultiThreadedBFSolver.h"

std::vector<std::vector<std::string>> init() {
    std::vector<std::string> emptyFileNames = {};
    std::vector<std::string> bruteForceFileNames = { "m6.atsp", "m8.atsp", "m9.atsp", "m10.atsp", "m11.atsp",
                                                 "m12.atsp" };
    std::vector<std::string> dynamicFileNames = { "m6.atsp", "m8.atsp", "m9.atsp", "m10.atsp", "m11.atsp",
                                                 "m12.atsp", "m13.atsp", "m14.atsp", "m15.atsp", "m16.atsp", "br17.atsp",
                                                 "gr21.tsp" };
    std::vector<std::string> branchAndBoundFileNames = { "m6.atsp", "m8.atsp", "m9.atsp", "m10.atsp", "m11.atsp",
                                                        "m12.atsp", "m13.atsp", "m14.atsp", "m15.atsp" };
    std::vector<std::vector<std::string>> data;
    data.push_back(bruteForceFileNames);
    data.push_back(dynamicFileNames);
    data.push_back(branchAndBoundFileNames);
    return data;
}

int main() {
    //auto numThreads = std::thread::hardware_concurrency();
    //std::cout << "threads: " << numThreads << std::endl;
    // Tester::testWithDataFromFiles(init(), true);
    // Tester::test("init.txt");
    // auto graph = new Graph(8, 25, false);
    auto graph = new Graph("m13.atsp");
    auto solver = new MultiThreadedBFSolver(graph);
    solver->solve();
    solver->getResult("multi threaded bf");
}
