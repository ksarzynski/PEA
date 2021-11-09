//#include <vector>
//#include <string>
#include <Tester.h>
//#include <Graph.h>

std::vector<std::vector<std::string>> init(){
    std::vector<std::string> bruteForceFileNames = {"m6.atsp", "m8.atsp", "m9.atsp", "m10.atsp"};
    std::vector<std::string> dynamicFileNames = {"m6.atsp", "m8.atsp", "m9.atsp", "m10.atsp", "m11.atsp",
                                                 "m12.atsp", "m13.atsp", "m14.atsp", "m15.atsp", "m16.atsp",
                                                 "fri26.tsp", "bays29.tsp"};
    std::vector<std::string> branchAndBoundFileNames = {"m6.atsp", "m8.atsp", "m9.atsp", "m10.atsp", "m11.atsp",
                                                        "m12.atsp", "m13.atsp", "m14.atsp", "m15.atsp", "m16.atsp"};
    std::vector<std::vector<std::string>> data;
    data.push_back(bruteForceFileNames);
    data.push_back(dynamicFileNames);
    data.push_back(branchAndBoundFileNames);
    return data;
}

int main() {
    Tester::testWithDataFromFiles(init());
//    auto graph = new Graph();
}
