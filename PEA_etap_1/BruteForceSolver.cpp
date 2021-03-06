#include "BruteForceSolver.h"

void BruteForceSolver::solve() {
    std::vector<int> path;
    std::vector<int> bestPath;
    int currentCost;
    int minCost = INT_MAX;
    path.reserve(static_cast<const unsigned int>(this->size + 1));
    for (int i = 0; i < this->size; i++)
        path.push_back(i);
    auto start = std::chrono::high_resolution_clock::now();
    do {
        currentCost = 0;
        path.push_back(path[0]);
        for (int i = 0; i < this->size; i++)
            currentCost += this->graph[path[i]][path[i + 1]];
        if (currentCost < minCost) {
            minCost = currentCost;
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
    auto stop = std::chrono::high_resolution_clock::now();
    this->time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

void BruteForceSolver::solveWithOutput() {
    bool isOutputSaved = false;
    float output1;
    float output2;
    std::vector<int> path;
    std::vector<int> bestPath;
    int currentCost;
    int minCost = INT_MAX;
    path.reserve(static_cast<const unsigned int>(this->size + 1));
    for (int i = 0; i < this->size; i++)
        path.push_back(i);
    auto start = std::chrono::high_resolution_clock::now();
    do {
        currentCost = 0;
        path.push_back(path[0]);
        for (int i = 0; i < this->size; i++)
            currentCost += this->graph[path[i]][path[i + 1]];
        if (currentCost < minCost) {
            minCost = currentCost;
            if (!isOutputSaved) {
                isOutputSaved = true;
                output1 = minCost;
                output2 = 100 * float(minCost - this->predictedResult) / this->predictedResult;
            }
            std::cout << minCost << "     " << 100 * float(minCost - this->predictedResult) / this->predictedResult
                << "%" << std::endl;
            bestPath.clear();
            for (int vertex : path)
                bestPath.push_back(vertex);
        }
        path.pop_back();
    } while (std::next_permutation(path.begin(), path.end()));
    std::cout << output1 << "     " << output2 << "%" << std::endl;
    bestPath.push_back(path.at(0));
    this->bestCost = minCost;
    for (int i = 0; i < this->size + 1; i++)
        this->bestPath[i] = bestPath[i];
    std::cout << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    this->time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}