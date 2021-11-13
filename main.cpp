#include <Tester.h>

std::vector<std::vector<std::string>> init(){
    std::vector<std::string> bruteForceFileNames = { "m6.atsp", "m8.atsp", "m9.atsp", "m10.atsp" };
    std::vector<std::string> dynamicFileNames = { "m6.atsp", "m8.atsp", "m9.atsp", "m10.atsp", "m11.atsp",
                                                 "m12.atsp", "m13.atsp", "m14.atsp", "m15.atsp", "m16.atsp"};
    std::vector<std::string> bestFirstBoundFileNames = { "m6.atsp", "m8.atsp", "m9.atsp", "m10.atsp", "m11.atsp",
                                                        "m12.atsp", "m13.atsp", "m14.atsp", "m15.atsp", "m16.atsp" };
    std::vector<std::string> depthFirstBranchAndBoundFileNames = { "m6.atsp", "m8.atsp", "m9.atsp", "m10.atsp", "m11.atsp",
                                                        "m12.atsp", "m13.atsp", "m14.atsp", "m15.atsp", "m16.atsp", "br17.atsp" };
    std::vector<std::string> depthFirstBranchAndBoundFileNames2 = { "m16.atsp" };
    std::vector<std::vector<std::string>> data;
    //data.push_back(bruteForceFileNames);
    //data.push_back(dynamicFileNames);
    data.push_back({});
    data.push_back({});
    data.push_back(bestFirstBoundFileNames);
    data.push_back(depthFirstBranchAndBoundFileNames);
    return data;
}

int main() {
    Tester::testWithDataFromFiles(init(), false);
}
