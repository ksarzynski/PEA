#include "Tester.h"

std::vector<std::vector<std::string>> init() {
    std::vector<std::string> emptyFileNames = {};
    std::vector<std::string> bruteForceFileNames = { "m6.atsp" };
    std::vector<std::string> dynamicFileNames = { "m6.atsp" };
    std::vector<std::string> branchAndBoundFileNames = { "m6.atsp" };
    std::vector<std::string> simulatedAnnealingFileNames = { "m6.atsp" };
    std::vector<std::string> tabuSearchFileNames = { "m6.atsp" };
    std::vector<std::vector<std::string>> data;
    data.push_back(bruteForceFileNames);
    data.push_back(dynamicFileNames);
    data.push_back(branchAndBoundFileNames);
    data.push_back(simulatedAnnealingFileNames);
    data.push_back(tabuSearchFileNames);
    return data;
}

int main() {
    Tester::test("init.txt");
}
