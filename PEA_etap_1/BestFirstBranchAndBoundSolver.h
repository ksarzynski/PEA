#pragma once
#include <queue>
#include "Solver.h"


class BestFirstBranchAndBoundSolver :
    public Solver
{
public:
    
    void solve();

    void solveWithOutput();

    using Solver::Solver;

private:

    class Node
    {
    public:

        std::vector<int> tour;
        int start;
        int end;
        int cost;
        int lowerBound;
        int level;

        Node(std::vector<int> tour, int start, int end, int level, int cost, int lowerBound)
        {
            this->tour = tour;
            this->start = start;
            this->end = end;
            this->cost = cost;
            this->level = level;
            this->lowerBound = lowerBound;
        }
    };

    struct myComparator
    {
        bool operator()(const Node* l, const Node* r) const
        {
            return l->lowerBound > r->lowerBound;
        }
    };
    
    int getFirstMinCost(int v);

    int getSecondMinCost(int v);

    int getLowerBound();

    bool isVisited(int index, std::vector<int> path);
};

