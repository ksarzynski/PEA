#pragma once
#include "Solver.h"
#include "Enums.h"
#include <random>

class SimulatedAnnealingSolver :
    public Solver
{
public:

    void solve();

    void solveWithOutput();

    std::vector<int> getResult(const std::string& solverType);

    void printParameters(double p, double q, double endTemperature, firstSolutionMethod fsmChoice, nextSolutionMethod nsmChoice, coolingMethod cmChoice);

    float getError() { return this->error; };

    using Solver::Solver;

private:

    float error;

    void solveWithParams(double p, double q, double endTemperature, firstSolutionMethod fsmChoice, nextSolutionMethod nsmChoice, coolingMethod cmChoice);

    std::vector<int> getStartingSolutionGreedy();

    std::vector<int> getStartingSolutionRandom();

    int getBestNeighbour(int vertex, bool* visited);

    int getCost(std::vector<int> path);

    std::vector<int> getNextSolutionInsert(std::vector<int> solution);

    std::vector<int> getNextSolutionSwap(std::vector<int> solution);

    std::vector<int> getNextSolutionInvert(std::vector<int> solution);

    double geometricalCooling(double temp, double p);

    double cauchyCooling(double temp, double a, double b, int it);

    double getStartingTemp();
};

