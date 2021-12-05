#pragma once
#include "Solver.h"
#include <random>

class SimulatedAnnealingSolver :
    public Solver
{
public:

    void solve();

    void solveWithOutput();

    std::vector<int> getResult(const std::string& solverType);

    using Solver::Solver;

private:

    int getCost(std::vector<int> path);

    std::vector<int> getNextSolution(std::vector<int> solution, int p);

    double geometricalCooling(double temp, double p);

    double getStartingTemp();
};

