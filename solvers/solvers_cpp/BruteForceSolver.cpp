//
// Created by kacpe on 02.11.2021.
//

#include "../solvers_h/BruteForceSolver.h"

void BruteForceSolver::solve() {
    std::vector<int> path;
    std::vector<int> bestPath;
    int currentCost;
    int minCost = INT_MAX;
    path.reserve(static_cast<const unsigned int>(this->size + 1));
    for(int i = 0; i < this->size; i++)
        path.push_back(i);
    do{
        currentCost = 0;
        path.push_back(path[0]);
        for(int i = 0; i < this->size; i++)
            currentCost += this->graph[path[i]][path[i + 1]];
        if(currentCost < minCost){
            minCost = currentCost;
            bestPath.clear();
            for(int vertex: path)
                bestPath.push_back(vertex);
        }
        path.pop_back();
    }while(std::next_permutation(path.begin(), path.end()));
    bestPath.push_back(path.at(0));
    this->bestCost = minCost;
    for(int i = 0; i < this->size + 1; i++)
        this->bestPath[i] = bestPath[i];
}

void BruteForceSolver::solveWithOutput() {
    std::vector<int> path;
    std::vector<int> bestPath;
    int currentCost;
    int minCost = INT_MAX;
    path.reserve(static_cast<const unsigned int>(this->size + 1));
    for (int i = 0; i < this->size; i++)
        path.push_back(i);
    do {
        currentCost = 0;
        path.push_back(path[0]);
        for (int i = 0; i < this->size; i++)
            currentCost += this->graph[path[i]][path[i + 1]];
        if (currentCost < minCost) {
            minCost = currentCost;
            std::cout << minCost << "     " << 100 * float(minCost - this->predictedResult) / this->predictedResult << "%" << std::endl;
            bestPath.clear();
            for (int vertex : path)
                bestPath.push_back(vertex);
        }
        path.pop_back();
    } while (std::next_permutation(path.begin(), path.end()));
    bestPath.push_back(path.at(0));
    this->bestCost = minCost;
    for (int i = 0; i < this->size + 1; i++)
        this->bestPath[i] = bestPath[i];
    std::cout << std::endl;
}