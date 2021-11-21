#include "BranchAndBoundSolver.h"

void BranchAndBoundSolver::solve() {
    int* currentPath = new int[this->size];
    memset(currentPath, -1, this->size);
    bool* visited = new bool[this->size];
    memset(visited, false, this->size);
    int lowerBound = getFirstLowerBound();
    visited[0] = true;
    currentPath[0] = 0;
    int finalResult = INT_MAX;
    auto start = std::chrono::high_resolution_clock::now();
    recursiveBranchAndBound(lowerBound, 0, 1, visited, currentPath, finalResult);
    auto stop = std::chrono::high_resolution_clock::now();
    this->bestCost = finalResult;
    this->time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    delete[] visited;
    delete[] currentPath;
}

void BranchAndBoundSolver::solveWithOutput() {
    isOutputSaved = false;
    int* currentPath = new int[this->size];
    memset(currentPath, -1, this->size);
    bool* visited = new bool[this->size];
    memset(visited, false, this->size);
    int lowerBound = getFirstLowerBound();
    visited[0] = true;
    currentPath[0] = 0;
    int finalResult = INT_MAX;
    auto start = std::chrono::high_resolution_clock::now();
    recursiveBranchAndBoundWithOutput(lowerBound, 0, 1, visited, currentPath, finalResult);
    this->bestCost = finalResult;
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << this->output1 << "     " << this->output2 << "%" << std::endl;
    this->time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    delete[] visited;
    delete[] currentPath;
}

int BranchAndBoundSolver::getMinEdges(int city) {
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    for (int i = 0; i < this->size; ++i) {
        if (city == i)
            continue;
        if (this->graph[city][i] < min1)
            min1 = this->graph[city][i];
    }
    for (int i = 0; i < this->size; ++i) {
        if (city == i)
            continue;
        if (this->graph[city][i] < min2 && min2 > min1)
            min2 = this->graph[city][i];
    }
    return (min1 + min2) / 2;
}

int BranchAndBoundSolver::getFirstLowerBound() {
    int sum = 0;
    for (int i = 0; i < this->size; ++i)
        sum += getMinEdges(i);
    return sum;
}

void BranchAndBoundSolver::recursiveBranchAndBound(int currentBound, int currentCost, int level, bool* visited, int* currentPath, int& finalResult) {
    if (level == this->size) {
        int currentResult = currentCost + this->graph[currentPath[level - 1]][currentPath[0]];
        if (currentResult < finalResult) {
            finalResult = currentResult;
            for (int i = 0; i < this->size + 1; i++)
                this->bestPath[i] = currentPath[i];
        }
        return;
    }
    for (int i = 0; i < this->size; i++) {
        if (this->graph[level - 1][i] != 0 && !visited[i]) {
            int temp = currentBound;
            currentCost += this->graph[currentPath[level - 1]][i];
            if (level == 1)
                currentBound -= ((getFirstMin(currentPath[level - 1]) + getFirstMin(i)) / 2);
            else
                currentBound -= ((getSecondMin(currentPath[level - 1]) + getFirstMin(i)) / 2);
            if (currentBound + currentCost < finalResult) {
                currentPath[level] = i;
                visited[i] = true;
                recursiveBranchAndBound(currentBound, currentCost, level + 1, visited, currentPath, finalResult);
            }
            currentCost -= this->graph[currentPath[level - 1]][i];
            currentBound = temp;
            memset(visited, false, this->size);
            for (int j = 0; j <= level - 1; ++j)
                visited[currentPath[j]] = true;
        }
    }
}

void BranchAndBoundSolver::recursiveBranchAndBoundWithOutput(int currentBound, int currentCost, int level, bool* visited, int* currentPath, int& finalResult) {
    if (level == this->size) {
        int currentResult = currentCost + this->graph[currentPath[level - 1]][currentPath[0]];
        if (currentResult < finalResult) {
            finalResult = currentResult;
            for (int i = 0; i < this->size + 1; i++)
                this->bestPath[i] = currentPath[i];
            std::cout << finalResult << "     " << 100 * float(finalResult - this->predictedResult) / this->predictedResult
                << "%" << std::endl;
            if (!isOutputSaved) {
                isOutputSaved = true;
                output1 = finalResult;
                output2 = 100 * float(finalResult - this->predictedResult) / this->predictedResult;
            }
        }
        return;
    }
    for (int i = 0; i < this->size; i++) {
        if (this->graph[level - 1][i] != 0 && !visited[i]) {
            int temp = currentBound;
            currentCost += this->graph[currentPath[level - 1]][i];
            if (level == 1)
                currentBound -= ((getFirstMin(currentPath[level - 1]) + getFirstMin(i)) / 2);
            else
                currentBound -= ((getSecondMin(currentPath[level - 1]) + getFirstMin(i)) / 2);
            if (currentBound + currentCost < finalResult) {
                currentPath[level] = i;
                visited[i] = true;
                recursiveBranchAndBoundWithOutput(currentBound, currentCost, level + 1, visited, currentPath, finalResult);
            }
            currentCost-= this->graph[currentPath[level - 1]][i];
            currentBound = temp;
            memset(visited, false, this->size);
            for (int j = 0; j <= level - 1; ++j)
                visited[currentPath[j]] = true;
        }
    }
}

int BranchAndBoundSolver::getFirstMin(int vertex) {
    int min = INT_MAX;
    for (int i = 0; i < this->size; i++)
        if (this->graph[vertex][i] < min && vertex != i)
            min = this->graph[vertex][i];
    return min;
}

int BranchAndBoundSolver::getSecondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < this->size; j++) {
        if (i == j)
            continue;
        if (this->graph[i][j] <= first) {
            second = first;
            first = this->graph[i][j];
        }
        else if (this->graph[i][j] <= second && this->graph[i][j] != first)
            second = this->graph[i][j];
    }
    return second;
}
