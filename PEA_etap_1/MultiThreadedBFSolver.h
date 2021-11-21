#pragma once
#include "Solver.h"
#include <vector>
#include <algorithm>
#include <mutex>
#include <thread>

class MultiThreadedBFSolver : public Solver {

public:

    void solve();

    void solveWithOutput();

    using Solver::Solver;

private:

    std::mutex bestCostMutex;
    std::mutex bestPathMutex;

    void run(std::vector<int> path, int size, int id);
};

