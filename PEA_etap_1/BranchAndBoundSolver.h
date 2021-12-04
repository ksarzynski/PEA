#pragma once
#include "Solver.h"
#include <algorithm>

class BranchAndBoundSolver : public Solver {

public:

    void solve();

    void solveWithOutput();

    using Solver::Solver;

private:

    bool isOutputSaved;
    float output1;
    float output2;

    int getMinEdges(int city);

    int getFirstLowerBound();

    void recursiveBranchAndBound(int currentBound, int currentCost, int level, bool* visited, int* currentPath,
        int& finalResult);

    void recursiveBranchAndBoundWithOutput(int currentBound, int currentCost, int level, bool* visited, int* currentPath,
        int& finalResult);

    int getFirstMin(int city);

    int getSecondMin(int city);
};

