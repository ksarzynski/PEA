//
// Created by kacpe on 02.11.2021.
//

#ifndef PEA_1_DYNAMICSOLVER_H
#define PEA_1_DYNAMICSOLVER_H


#include "Solver.h"
#include <map>

class DynamicSolver : public Solver {

public:
    void solve();
    using Solver::Solver;

private:
    std::map<std::string, int[2]> cache;
    int recursiveDynamic(int mask, int currentCity, int visitedAll);
    void getPath();
};


#endif //PEA_1_DYNAMICSOLVER_H
