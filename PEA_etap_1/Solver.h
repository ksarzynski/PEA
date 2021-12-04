#pragma once
#include "Graph.h"
#include <vector>
#include <chrono>

class Solver {

public:
    Solver(Graph* _graph);

    ~Solver();

    virtual void solve() = 0;

    virtual void solveWithOutput() = 0;

    std::vector<int> getResult(const std::string& solverType);

    long long getTime();

protected:
    int** graph;
    int size;
    int bestCost;
    int* bestPath;
    std::string fileName;
    int predictedResult;
    long long time;
};

