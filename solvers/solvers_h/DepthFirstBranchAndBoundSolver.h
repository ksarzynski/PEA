//
// Created by kacpe on 02.11.2021.
//

#ifndef PEA_1_DEPTHFIRSTBRANCHANDBOUNDSOLVER_H
#define PEA_1_DEPTHFIRSTBRANCHANDBOUNDSOLVER_H


#include "Solver.h"
#include <algorithm>

class DepthFirstBranchAndBoundSolver : public Solver {

public:

    void solve();

    void solveWithOutput();

    using Solver::Solver;

private:
    
    int min_edges(int city);

    int first_lower_bound();

    void bnb_recursive(int curr_bound, int curr_weight, int level, bool* visited, int* curr_path, int& final_res);

    int first_min(int i);

    int second_min(int i);
};


#endif //PEA_1_DEPTHFIRSTBRANCHANDBOUNDSOLVER_H
