#include "..\solvers_h\DepthFirstBranchAndBoundSolver.h"

void DepthFirstBranchAndBoundSolver::solve() {
    int* currentPath = new int[this->size];
    memset(currentPath, -1, this->size);
    bool* visited = new bool[this->size];
    memset(visited, false, this->size);
    int lowerBound = first_lower_bound();
    visited[0] = true;
    currentPath[0] = 0;
    int finalResult = INT_MAX;
    auto start = std::chrono::high_resolution_clock::now();
    bnb_recursive(lowerBound, 0, 1, visited, currentPath, finalResult);
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "bnb final result: " << finalResult << " time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "\n";
    delete[] visited;
    delete[] currentPath;
}

void DepthFirstBranchAndBoundSolver::solveWithOutput() {

}

int DepthFirstBranchAndBoundSolver::min_edges(int city) {
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    for (int i = 0; i < this->size; ++i){
        if (city == i)
            continue;
        if (this->graph[city][i] < min1)
            min1 = this->graph[city][i];
    }
    for (int i = 0; i < this->size; ++i){
        if (city == i)
            continue;
        if (this->graph[city][i] < min2 && min2 > min1)
            min2 = this->graph[city][i];
    }
    return (min1 + min2) / 2;
}

int DepthFirstBranchAndBoundSolver::first_lower_bound() {
    int sum = 0;
    for (int i = 0; i < this->size; ++i)
        sum += min_edges(i);
    return sum;
}

void DepthFirstBranchAndBoundSolver::bnb_recursive(int currentBound, int curr_weight, int level, bool* visited, int* currentPath, int& finalResult) {
    if (level == this->size){
        int currentResult = curr_weight + this->graph[currentPath[level - 1]][currentPath[0]];
        if (currentResult < finalResult)
            finalResult = currentResult;
        return;
    }
    for (int i = 0; i < this->size; i++){
        if (this->graph[level - 1][i] != 0 && !visited[i]){
            int temp = currentBound;
            curr_weight += this->graph[currentPath[level - 1]][i];
            if (level == 1)
                currentBound -= ((first_min(currentPath[level - 1]) + first_min(i)) / 2);
            else
                currentBound -= ((second_min(currentPath[level - 1]) + first_min(i)) / 2);
            if (currentBound + curr_weight < finalResult){
                currentPath[level] = i;
                visited[i] = true;
                bnb_recursive(currentBound, curr_weight, level + 1, visited, currentPath, finalResult);
            }
            curr_weight -= this->graph[currentPath[level - 1]][i];
            currentBound = temp;
            memset(visited, false, this->size);
            for (int j = 0; j <= level - 1; ++j)
                visited[currentPath[j]] = true;
        }
    }
}

int DepthFirstBranchAndBoundSolver::first_min(int vertex) {
    int min = INT_MAX;
    for (int i = 0; i < this->size; i++)
        if (this->graph[vertex][i] < min && vertex != i)
            min = this->graph[vertex][i];
    return min;
}

int DepthFirstBranchAndBoundSolver::second_min(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < this->size; j++){
        if (i == j)
            continue;
        if (this->graph[i][j] <= first){
            second = first;
            first = this->graph[i][j];
        }
        else if (this->graph[i][j] <= second && this->graph[i][j] != first)
            second = this->graph[i][j];
    }
    return second;
}