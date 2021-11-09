//
// Created by kacpe on 02.11.2021.
//

#ifndef PEA_1_SOLVER_H
#define PEA_1_SOLVER_H


#include "../../graph/Graph.h"
#include <vector>

class Solver {

public:
    Solver(Graph* _graph);

    ~Solver();

    virtual void solve() = 0;

    std::vector<int> getResult(const std::string& solverType);

protected:
    int** graph;
    int size;
    int bestCost;
    int* bestPath;
    std::string fileName;
};


#endif //PEA_1_SOLVER_H
