// TODO check how to get fixed vector start
// TODO try to do method for 3 or more known cities
// TODO choose 2nd algorithm

#include "MultiThreadedBFSolver.h";

// for 2 first known cities ( size = 5 )
// 01|234
// 02|134
// 03|214
// 04|231

// for 3 first known cities ( size = 4)
// 012|3
// 013|2
// 021|3
// 023|1
// 031|2
// 032|1

// for 3 first known cities ( size = 5)
// 012|34
// 013|24
// 014|23
// 021|34
// 023|14
// 024|13
// 031|24
// 032|14
// 034|12
// 041|23
// 042|13
// 043|12

// threads amount = (size - 1)(size - 2)

void MultiThreadedBFSolver::solve() {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> paths;
    std::vector<std::thread> threads(this->size - 1);
    // preparing paths
    for (int i = 0; i < this->size - 1; i++) {
        paths.push_back(std::vector<int>());
        for (int j = 0; j < this->size; j++)
            paths[i].push_back(j);
    } 
    // fixing paths
    for (int i = 1, index = 2; i < this->size - 1; i++, index++)
        std::swap(paths[i][1], paths[i][index]);
    // creating and starting threads
    threads.clear();
    for (int i = 0; i < this->size - 1; i++) 
        threads.push_back(std::thread(&MultiThreadedBFSolver::run, this, paths[i], 2, i));
    int index = 0;
    for (auto& th : threads)
        th.join();
    auto stop = std::chrono::high_resolution_clock::now();
    this->time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

// path is path to be permutated without last vertex
void MultiThreadedBFSolver::run(std::vector<int> path, int size, int id) {
    std::vector<int> thisThreadBestPath;
    int currentCost;
    int minCost = INT_MAX;
    auto start = std::chrono::high_resolution_clock::now();
    do {
        currentCost = 0;
        path.push_back(path[0]);
        for (int i = 0; i < this->size; i++)
            currentCost += this->graph[path[i]][path[i + 1]];
        if (currentCost < minCost) {
            minCost = currentCost;
            thisThreadBestPath.clear();
            for (int vertex : path)
                thisThreadBestPath.push_back(vertex);
        }
        path.pop_back();
    } while (std::next_permutation(path.begin() + size, path.end()));
    thisThreadBestPath.push_back(path.at(0));
    auto stop = std::chrono::high_resolution_clock::now();
    while (!this->bestCostMutex.try_lock()) {
        this->bestCost = minCost;
        for (int i = 0; i < this->size + 1; i++)
            this->bestPath[i] = thisThreadBestPath[i];
        // std::cout << id + " " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds\n";
        bestCostMutex.unlock();
    }
}

void MultiThreadedBFSolver::solveWithOutput() {
    std::cout << "Not implemented\n";
}