//
// Created by kacpe on 02.11.2021.
//

#include "../solvers_h/DynamicSolver.h"

void DynamicSolver::solve(){
    int visitedAll = (1 << this->size) - 1;
    std::map<std::string, int[2]> cache;
    this->recursiveDynamic(1, 0, visitedAll);
    getPath();
}

int DynamicSolver::recursiveDynamic(int mask, int currentCity, int visitedAll){
    if(mask == visitedAll)
        return this->graph[currentCity][0];
    if(cache.find(std::to_string(mask) + std::to_string(currentCity)) != cache.end())
        return cache[std::to_string(mask) + std::to_string(currentCity)][0];
    int cost = INT_MAX;
    int tempCity = -1;
    for(int city = 0; city < this->size; city++){
        if((mask & (1 << city)) == 0){
            int newCost = this->graph[currentCity][city] + recursiveDynamic(mask | (1 << city), city, visitedAll);
            if(newCost < cost){
                cost = newCost;
                tempCity = city;
            }
            this->bestCost = cost;
        }
    }
    cache[std::to_string(mask) + std::to_string(currentCity)][1] = tempCity;
    cache[std::to_string(mask) + std::to_string(currentCity)][0] = cost;
    return cache[std::to_string(mask) + std::to_string(currentCity)][0];
}

void DynamicSolver::getPath() {
    bestPath[0] = 0;
    int index = 1;
    int mask = 1;
    int lastCityIndex = 0;
    int tempLastCityIndex;
    for (int i = 0; i < this->size - 1; ++i) {
        bestPath[index] = cache[std::to_string(mask) + std::to_string(lastCityIndex)][1];
        index++;
        tempLastCityIndex = lastCityIndex;
        lastCityIndex = cache[std::to_string(mask) + std::to_string(lastCityIndex)][1];
        mask += (1 << cache[std::to_string(mask) + std::to_string(tempLastCityIndex)][1]);
    }
    bestPath[this->size] = 0;
}
