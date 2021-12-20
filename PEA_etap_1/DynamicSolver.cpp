#include "DynamicSolver.h"

void DynamicSolver::solve() {
    int visitedAll = (1 << this->size) - 1;
    cache = new int* [(1 << this->size)];
    lastCityArray = new int* [(1 << this->size)];
    for (int i = 0; i < (1 << this->size); i++) {
        cache[i] = new int[this->size];
        lastCityArray[i] = new int[this->size];
        for (int j = 0; j < this->size; j++) {
            cache[i][j] = -1;
            lastCityArray[i][j] = -1;
        }
    }
    auto start = std::chrono::high_resolution_clock::now();
    this->recursiveDynamic(1, 0, visitedAll);
    auto stop = std::chrono::high_resolution_clock::now();
    this->time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    getPath();
    for (int i = 0; i < (1 << this->size); i++) {
        delete[] cache[i];
        delete[] lastCityArray[i];
    }
    delete[] cache;
    delete[] lastCityArray;
}

void DynamicSolver::solveWithOutput() {
    std::cout << "DynamicSolver doesnt have this function implemented\n";
}

int DynamicSolver::recursiveDynamic(int mask, int currentCity, int visitedAll) {
    if (mask == visitedAll)
        return this->graph[currentCity][0];
    if (cache[mask][currentCity] != -1)
        return cache[mask][currentCity];
    int cost = INT_MAX;
    int tempCity = -1;
    for (int city = 0; city < this->size; city++) {
        if ((mask & (1 << city)) == 0) {
            int newCost = this->graph[currentCity][city] + recursiveDynamic(mask | (1 << city), city, visitedAll);
            if (newCost < cost) {
                cost = newCost;
                tempCity = city;
            }
            this->bestCost = cost;
        }
    }
    lastCityArray[mask][currentCity] = tempCity;
    return cache[mask][currentCity] = cost;
}

void DynamicSolver::getPath() {
    bestPath[0] = 0;
    int index = 1;
    int mask = 1;
    int lastCityIndex = 0;
    int tempLastCityIndex;
    for (int i = 0; i < this->size - 1; ++i) {
        bestPath[index] = lastCityArray[mask][lastCityIndex];
        index++;
        tempLastCityIndex = lastCityIndex;
        lastCityIndex = lastCityArray[mask][lastCityIndex];
        mask += (1 << lastCityArray[mask][tempLastCityIndex]);
    }
    bestPath[this->size] = 0;
}
