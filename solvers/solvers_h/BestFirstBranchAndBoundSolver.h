//
// Created by kacpe on 02.11.2021.
//

#ifndef PEA_1_BESTFIRSTBRANCHANDBOUNDSOLVER_H
#define PEA_1_BESTFIRSTBRANCHANDBOUNDSOLVER_H


#include "Solver.h"
#include <algorithm>

class BestFirstBranchAndBoundSolver: public Solver {

public:

    void solve();

    void solveWithOutput();

    using Solver::Solver;

private:

    int finalResult = INT_MAX;

    int firstMin(int vertex);

    int secondMin(int vertex);

    int getStartingLowerBound();

    bool isVisited(int index, const std::vector<int>& path);
};


#endif //PEA_1_BESTFIRSTBRANCHANDBOUNDSOLVER_H
