#include "Solver.h"

Solver::Solver(Graph* _graph) {
    this->graph = _graph->getGraph();
    this->size = _graph->getSize();
    this->bestCost = INT_MAX;
    this->bestPath = new int[this->size + 1];
    this->fileName = _graph->getFileName();
    this->predictedResult = _graph->getPredictedResult();
}

Solver::~Solver() {
    for (int i = 0; i < this->size; i++)
        delete[] this->graph[i];
    delete[] this->graph;
    delete[] this->bestPath;
}

std::vector<int> Solver::getResult(const std::string& solverType) {
    std::cout << "File name: " << this->fileName << ", expected result: " << this->predictedResult
        << " size: " << this->size << std::endl;
    std::cout << solverType << ": best cost: " << this->bestCost << std::endl;
    std::cout << solverType << ": best path: ";
    for (int i = 0; i < this->size; i++) {
        std::cout << bestPath[i] << " - ";
    }
    std::cout << bestPath[0] << std::endl;
    std::cout << std::fixed;
    std::cout << solverType << ": time: " << (float)this->time / 1000000 << " seconds" << std::endl << std::endl;
    std::vector<int> result;
    result.push_back(bestCost);
    for (int i = 0; i < this->size + 1; i++)
        result.push_back(bestPath[i]);
    return result;
}

long long Solver::getTime() {
    return this->time;
}