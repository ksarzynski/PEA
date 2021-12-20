#include "SimulatedAnnealingSolver.h"

void SimulatedAnnealingSolver::solve() {
    solveWithParams(0.99, 0.1, 0.1, RANDOM, INSERT, GEOMETRICAL);
    solveWithParams(0.99, 0.1, 0.1, RANDOM, INSERT, CAUCHY);
    solveWithParams(0.99, 0.1, 0.1, RANDOM, SWAP, GEOMETRICAL);
    solveWithParams(0.99, 0.1, 0.1, RANDOM, SWAP, CAUCHY);
    solveWithParams(0.99, 0.1, 0.1, RANDOM, INVERT, GEOMETRICAL);
    solveWithParams(0.99, 0.1, 0.1, RANDOM, INVERT, CAUCHY);
    solveWithParams(0.99, 0.1, 0.1, GREEDY, INSERT, GEOMETRICAL);
    solveWithParams(0.99, 0.1, 0.1, GREEDY, INSERT, CAUCHY);
    solveWithParams(0.99, 0.1, 0.1, GREEDY, SWAP, GEOMETRICAL);
    solveWithParams(0.99, 0.1, 0.1, GREEDY, SWAP, CAUCHY);
    solveWithParams(0.99, 0.1, 0.1, GREEDY, INVERT, GEOMETRICAL);
    solveWithParams(0.99, 0.1, 0.1, GREEDY, INVERT, CAUCHY);
}

void SimulatedAnnealingSolver::solveWithOutput() {
    std::cout << "SimulatedAnnealingSolver doesnt have this function implemented yet\n";
}

// p - value used by geometrical cooling method
// q - value used to scale amount of iterations done
// end temperature - value of temperature that stops algorithm
// firstSolutionMethod: 0 - greedy, 1 - random
// nextSolutionMethod: 0 - invert, else swap
// coolingMethod: 0 - geometrical, else - cauchy
void SimulatedAnnealingSolver::solveWithParams(double p, double q, double endTemperature,
    firstSolutionMethod fsmChoice, nextSolutionMethod nsmChoice, coolingMethod cmChoice){
    this->printParameters(p, q, endTemperature, fsmChoice, nsmChoice, cmChoice);
    auto start = std::chrono::high_resolution_clock::now();
    int counter = 0;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<double> num(0.0, 1.0);
    std::vector<int> firstSolution;
    if(fsmChoice == RANDOM)
        firstSolution = this->getStartingSolutionRandom();
    else
        firstSolution = this->getStartingSolutionGreedy();
    int firstSolutionCost = this->getCost(firstSolution);
    std::vector<int> bestSolution = firstSolution;
    int bestSolutionCost = this->getCost(bestSolution);
    std::vector<int> solution = firstSolution;
    int solutionCost = this->getCost(solution);
    double tempTemperature = getStartingTemp();
    double startTemperature = tempTemperature;
    while (tempTemperature > endTemperature) {
        counter++;
        for (int i = 0; i < q * ((double)this->size * ((double)this->size - 1)) / 2; i++) {
            if (nsmChoice == INSERT)
                solution = this->getNextSolutionInsert(firstSolution);
            else if (nsmChoice == SWAP)
                solution = this->getNextSolutionSwap(firstSolution);
            else
                solution = this->getNextSolutionInvert(firstSolution);
            solutionCost = this->getCost(solution);
            if (solutionCost < firstSolutionCost) {
                firstSolution = solution;
                firstSolutionCost = solutionCost;
            }
            else if (num(g) < exp(((double)firstSolutionCost - solutionCost) / tempTemperature)) {
                firstSolution = solution;
                firstSolutionCost = solutionCost;
            }
            if (solutionCost < bestSolutionCost) {
                bestSolution = solution;
                bestSolutionCost = solutionCost;
            }
        }
        if (cmChoice == GEOMETRICAL)
            tempTemperature = this->geometricalCooling(tempTemperature, p);
        else
            tempTemperature = this->cauchyCooling(tempTemperature, 0.999, 0.0001, counter);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    this->time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    for (int i = 0; i < this->size; i++)
        this->bestPath[i] = bestSolution[i];
    this->bestCost = bestSolutionCost;
    this->getResult("simulated annealing");
}

std::vector<int> SimulatedAnnealingSolver::getStartingSolutionGreedy(){
    std::vector<int> result;
    int startVertex = 0;
    bool* visited = new bool[this->size];
    for (int i = 0; i < this->size; i++)
        visited[i] = false;
    visited[startVertex] = true;
    result.clear();
    result.push_back(startVertex);
    for (int i = 0; i < this->size - 1; i++)
        result.push_back(this->getBestNeighbour(result[i], visited));
    result.push_back(result[0]);
    return result;
}

std::vector<int> SimulatedAnnealingSolver::getStartingSolutionRandom(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<double> num(0.0, 1.0);
    std::vector<int> firstSolution;
    for (int i = 0; i < this->size; i++)
        firstSolution.push_back(i);
    std::shuffle(std::begin(firstSolution), std::end(firstSolution), std::default_random_engine(0));
    firstSolution.push_back(firstSolution[0]);
    return firstSolution;
}

int SimulatedAnnealingSolver::getBestNeighbour(int vertex, bool* visited) {
    int bestNeighbour = -1;
    int cost = INT_MAX;
    for (int i = 0; i < this->size; i++) {
        if (i != vertex && !visited[i] && this->graph[vertex][i] < cost) {
            bestNeighbour = i;
            cost = this->graph[vertex][i];
        }
    }
    visited[bestNeighbour] = true;
    return bestNeighbour;
}

int SimulatedAnnealingSolver::getCost(std::vector<int> path) {
    if (path.size() == (this->size + 1)) {
        int cost = 0;
        for (int i = 0; i < this->size; i++)
            cost += this->graph[path[i]][path[i + 1]];
        return cost;
    }
}

std::vector<int> SimulatedAnnealingSolver::getNextSolutionInsert(std::vector<int> solution){
    std::vector<int> result(solution);
    int i = 0;
    int j = 0;
    if (i > j) {
        int temp = result[i];
        for (int k = i; k > j; k--)
            result[k] = result[k - 1];
        result[j] = temp;
    }
    else {
        int temp = result[i];
        for (int k = i; k < j; k++)
            result[k] = result[k + 1];
        result[j] = temp;
    }
    return result;
}

std::vector<int> SimulatedAnnealingSolver::getNextSolutionSwap(std::vector<int> solution){
    std::vector<int> nextSolution = solution;
    int v1 = rand() % this->size;
    int v2 = rand() % this->size;
    int tempV = nextSolution[v1];
    while (v2 == v1)
        v2 = rand() % this->size;
    nextSolution[v1] = nextSolution[v2];
    nextSolution[v2] = tempV;
    nextSolution[this->size] = nextSolution[0];
    return nextSolution;
}

std::vector<int> SimulatedAnnealingSolver::getNextSolutionInvert(std::vector<int> solution){
    int p = rand() % this->size + 1;
    std::vector<int> nextSolution = solution;
    std::vector<int> temp;
    int tempIndex = 0;
    int start = rand() % (this->size + 1 - p);
    for (int i = 0; i < p; i++)
        temp.push_back(nextSolution[start + i]);
    std::reverse(temp.begin(), temp.end());
    for (int i = start; i < start + p; i++) {
        nextSolution[i] = temp[tempIndex];
        tempIndex++;
    }
    nextSolution[this->size] = nextSolution[0];
    return nextSolution;
}

double SimulatedAnnealingSolver::geometricalCooling(double temp, double p) {
    return temp * p;
}

double SimulatedAnnealingSolver::cauchyCooling(double temp, double a, double b, int it) {
    return (temp / (a + it * b));
}

double SimulatedAnnealingSolver::getStartingTemp() {
    int sum = 0;
    std::vector<int> solution;
    for (int i = 0; i < this->size; i++)
        solution.push_back(i);
    std::shuffle(std::begin(solution), std::end(solution), std::default_random_engine(0));
    solution.push_back(solution[0]);
    int costToCompare = this->getCost(solution);
    for (int i = 0; i < this->size; i++) {
        solution = this->getNextSolutionInvert(solution);
        sum += abs(costToCompare - this->getCost(solution));
    }
    sum /= this->size;
    return -1 * (sum / log10(0.92));
}

std::vector<int> SimulatedAnnealingSolver::getResult(const std::string& solverType) {
    std::cout << "File name: " << this->fileName << ", expected result: " << this->predictedResult
        << " size: " << this->size << std::endl;
    std::cout << solverType << ": best cost: " << this->bestCost << std::endl;
    this->error = ((float)this->bestCost / (float)this->predictedResult * 100) - 100;
    std::cout << solverType << ": error (% value): "
        << this->error << "%" << std::endl;
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

void SimulatedAnnealingSolver::printParameters(double p, double q, double endTemperature,
    firstSolutionMethod fsmChoice, nextSolutionMethod nsmChoice, coolingMethod cmChoice) {
    std::cout << "p: " << p << "\n";
    std::cout << "q: " << q << "\n";
    std::cout << "endTemperature: " << endTemperature << "\n";
    std::cout << "firstSolutionMethod: " << fsmChoice << "\n";
    std::cout << "nextSolutionMethod: " << nsmChoice << "\n";
    std::cout << "coolingMethod: " << cmChoice << "\n";
}