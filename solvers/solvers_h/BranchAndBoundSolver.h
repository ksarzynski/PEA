//
// Created by kacpe on 02.11.2021.
//

#ifndef PEA_1_BRANCHANDBOUNDSOLVER_H
#define PEA_1_BRANCHANDBOUNDSOLVER_H


#include "Solver.h"
#include <algorithm>

class BranchAndBoundSolver: public Solver {

public:
    void solve();
    using Solver::Solver;

private:
    int finalResult = INT_MAX;

    int firstMin(int vertex);

    int secondMin(int vertex);

    int getStartingLowerBound();

    bool isVisited(int index, const std::vector<int>& path);
};


#endif //PEA_1_BRANCHANDBOUNDSOLVER_H
