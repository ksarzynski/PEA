#include "SimulatedAnnealingSolver.h"

void SimulatedAnnealingSolver::solve() {
    auto start = std::chrono::high_resolution_clock::now();
    double p = 0.99;
    int solutionFinding = 0;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<double> num(0.0, 1.0);
    std::vector<int> firstSolution;
    for (int i = 0; i < this->size; i++)
        firstSolution.push_back(i);
    std::shuffle(std::begin(firstSolution), std::end(firstSolution), std::default_random_engine(0));
    firstSolution.push_back(firstSolution[0]);
    int firstSolutionCost = this->getCost(firstSolution);
    std::vector<int> bestSolution = firstSolution;
    int bestSolutionCost = this->getCost(bestSolution);
    std::vector<int> solution = firstSolution;
    int solutionCost = this->getCost(solution);
    double tempTemperature = getStartingTemp();
    double startTemperature = tempTemperature;
    while (tempTemperature > 0.1){
        for (int i = 0; i < 0.1 * ((double)this->size * ((double)this->size - 1)) / 2; i++){
            solution = this->getNextSolution(firstSolution, rand() % this->size + 1);
            solutionCost = this->getCost(solution);
            if (solutionCost < firstSolutionCost){
                firstSolution = solution;
                firstSolutionCost = solutionCost;
            }
            else if (num(g) < exp(((double)firstSolutionCost - solutionCost) / tempTemperature)){
                firstSolution = solution;
                firstSolutionCost = solutionCost;
            }
            if (solutionCost < bestSolutionCost){
                bestSolution = solution;
                bestSolutionCost = solutionCost;
            }
        }
        tempTemperature = this->geometricalCooling(tempTemperature, p);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    this->time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    for (int i = 0; i < this->size; i++)
        this->bestPath[i] = bestSolution[i];
    this->bestCost = bestSolutionCost;
}

void SimulatedAnnealingSolver::solveWithOutput() {
    std::cout << "SimulatedAnnealingSolver doesnt have this function implemented\n";
}

int SimulatedAnnealingSolver::getCost(std::vector<int> path){
    if (path.size() == (this->size + 1)){
        int cost = 0;
        for (int i = 0; i < this->size; i++)
            cost += this->graph[path[i]][path[i + 1]];
        return cost;
    }
}

std::vector<int> SimulatedAnnealingSolver::getNextSolution(std::vector<int> solution, int p){
    std::vector<int> nextSolution = solution;
    std::vector<int> temp;
    int tempIndex = 0;
    int start = rand() % (this->size + 1 - p);
    for (int i = 0; i < p; i++)
        temp.push_back(nextSolution[start + i]);
    std::reverse(temp.begin(), temp.end());
    for (int i = start; i < start + p; i++){
        nextSolution[i] = temp[tempIndex];
        tempIndex++;
    }
    nextSolution[this->size] = nextSolution[0];
    return nextSolution;
}

double SimulatedAnnealingSolver::geometricalCooling(double temp, double p){
    return temp * p;
}

double SimulatedAnnealingSolver::getStartingTemp(){
    int sum = 0;
    std::vector<int> solution;
    for (int i = 0; i < this->size; i++)
        solution.push_back(i);
    std::shuffle(std::begin(solution), std::end(solution), std::default_random_engine(0));
    solution.push_back(solution[0]);
    int costToCompare = this->getCost(solution);
    for (int i = 0; i < this->size; i++){
        solution = this->getNextSolution(solution, rand() % this->size + 1);
        sum += abs(costToCompare - this->getCost(solution));
    }
    sum /= this->size;
    return -1 * (sum / log10(0.92));
}

std::vector<int> SimulatedAnnealingSolver::getResult(const std::string& solverType) {
    std::cout << "File name: " << this->fileName << ", expected result: " << this->predictedResult
        << " size: " << this->size << std::endl;
    std::cout << solverType << ": best cost: " << this->bestCost << std::endl;
    std::cout << solverType << ": error (% value): "
        << ((double)this->bestCost / (double)this->predictedResult * 100) - 100<< "%" << std::endl;
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