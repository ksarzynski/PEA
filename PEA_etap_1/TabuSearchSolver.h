#pragma once
#include "Solver.h"
#include "Enums.h"
#include <random>
#include <math.h>

class TabuSearchSolver :
    public Solver
{

public:

    void solve();

    void solveWithOutput();

    std::vector<int> getResult(const std::string& solverType);

    void setParams(nextSolutionMethod nsm, firstSolutionMethod fsm, int maxTime);

    void printParams();

    float getError() { return this->error; };

    using Solver::Solver;

    class Ban {
    public:
        int city;
        int duration;
        Ban(int city, int duration) {
            this->city = city;
            this->duration = duration;
        }
    };

    class Solution {
    public:
        int cost;
        int startCity;
        int endCity;
        std::vector<int> path;
        Solution() {
            this->cost = INT_MAX;
            this->startCity = -1;
            this->endCity = -1;
            this->path = std::vector<int>();
        }
        Solution(int cost, int startCity, int endCity, std::vector<int> path) {
            this->cost = cost;
            this->startCity = startCity;
            this->endCity = endCity;
            this->path = path;
        }
        Solution(const Solution& solution) {
            this->cost = solution.cost;
            this->startCity = solution.startCity;
            this->endCity = solution.endCity;
            this->path = solution.path;
        }
    };

private:

    float error;

    nextSolutionMethod nsm;

    firstSolutionMethod fsm;

    int maxTime;

    Solution getNextSolution(Solution bestSolution, Solution currentSolution, std::vector<Ban> bans);

    std::vector<int> getStartingSolutionGreedy();

    std::vector<int> getStartingSolutionRandom();

    int getBestNeighbour(int vertex, bool* visited);

    std::vector<int> getNextSolutionInsert(Solution solution, int i, int j);

    std::vector<int> getNextSolutionSwap(Solution solution, int i, int j);

    std::vector<int> getNextSolutionInvert(Solution solution, int i, int j);

    int getCost(Solution solution);
};

