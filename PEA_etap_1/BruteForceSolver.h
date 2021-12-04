#pragma once
#include "Solver.h"
#include <vector>
#include <algorithm>

class BruteForceSolver : public Solver {

public:

    void solve();

    void solveWithOutput();

    using Solver::Solver;
};

