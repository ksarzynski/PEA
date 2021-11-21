#pragma once
#include "Solver.h"

class DynamicSolver : public Solver {

public:

    void solve();

    void solveWithOutput();

    using Solver::Solver;

private:

    int** cache;
    int** lastCityArray;
    bool isCacheDone = false;

    int recursiveDynamic(int mask, int currentCity, int visitedAll);

    void getPath();
};

