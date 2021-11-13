//
// Created by kacpe on 02.11.2021.
//

#ifndef PEA_1_BRUTEFORCESOLVER_H
#define PEA_1_BRUTEFORCESOLVER_H


#include "Solver.h"
#include <vector>
#include <algorithm>

class BruteForceSolver: public Solver {

public:

    void solve();

    void solveWithOutput();

    using Solver::Solver;
};


#endif //PEA_1_BRUTEFORCESOLVER_H
