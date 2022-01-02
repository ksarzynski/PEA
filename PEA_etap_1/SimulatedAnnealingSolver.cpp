#include "SimulatedAnnealingSolver.h"

void SimulatedAnnealingSolver::solve() {
    this->solveWithParams(0.99, 0.5, 0.1);
}

void SimulatedAnnealingSolver::solveWithOutput() {
    this->solveWithParamsAndOutput(0.99, 0.1, 0.1);
}

// p - value used by geometrical cooling method
// q - value used to scale amount of iterations done
// end temperature - value of temperature that stops algorithm
void SimulatedAnnealingSolver::solveWithParams(double p, double q, double endTemperature) {
    this->printParameters(p, q, endTemperature, this->fsm, this->nsm, this->cm);
    auto start = std::chrono::high_resolution_clock::now();
    int counter = 0;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<double> num(0.0, 1.0);
    std::default_random_engine(std::time(0));
    std::vector<int> firstSolution;
    if (this->fsm == RANDOM)
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
            if (this->nsm == INSERT)
                solution = this->getNextSolutionInsert(firstSolution);
            else if (this->nsm == SWAP)
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
        if (this->cm== GEOMETRICAL)
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

void SimulatedAnnealingSolver::solveWithParamsAndOutput(double p, double q, double endTemperature) {
    // print parameters for better end result
    this->printParameters(p, q, endTemperature, this->fsm, this->nsm, this->cm);
    // initialize variables and random number generator
    auto start = std::chrono::high_resolution_clock::now();
    int counter = 0;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<double> num(0.0, 1.0);
    std::default_random_engine(std::time(0));
    std::vector<int> firstSolution;
    // create first solution using choosen algorithm
    if (this->fsm == RANDOM)
        firstSolution = this->getStartingSolutionRandom();
    else
        firstSolution = this->getStartingSolutionGreedy();
    std::cout << "first solution:\n";
    for (int i = 0; i < firstSolution.size(); i++)
        std::cout << firstSolution[i] << " - ";
    std::cout << "\n";
    std::vector<int> firstSolutionToPrint = firstSolution;
    int firstSolutionCostToPrint = this->getCost(firstSolution);
    std::cout << "0 " << firstSolutionCostToPrint << " " << 100 * float(firstSolutionCostToPrint - this->predictedResult) / this->predictedResult << "%\n";
    int firstSolutionCost = this->getCost(firstSolution);
    std::vector<int> bestSolution = firstSolution;
    int bestSolutionCost = this->getCost(bestSolution);
    std::vector<int> solution = firstSolution;
    int solutionCost = this->getCost(solution);
    double tempTemperature = getStartingTemp();
    double startTemperature = tempTemperature;
    int iter = 0;
    // main loop
    while (tempTemperature > endTemperature) {
        counter++;
        bool print = false;
        int costToPrint = INT_MAX;
        iter++;
        // for each temperature there is size^2/2 iterations
        for (int i = 0; i < q * ((double)this->size * ((double)this->size - 1)) / 2; i++) {
            // get next solution using choosen algorithm
            if (this->nsm == INSERT)
                solution = this->getNextSolutionInsert(firstSolution);
            else if (this->nsm == SWAP)
                solution = this->getNextSolutionSwap(firstSolution);
            else
                solution = this->getNextSolutionInvert(firstSolution);
            solutionCost = this->getCost(solution);
            // accept it as current one if its better than the previous one
            if (solutionCost < firstSolutionCost) {
                firstSolution = solution;
                firstSolutionCost = solutionCost;
            }
            // in case new solution is worse
            // check if it should be accepted
            else if (num(g) < exp(((double)firstSolutionCost - solutionCost) / tempTemperature)) {
                firstSolution = solution;
                firstSolutionCost = solutionCost;
            }
            // save best solution
            if (solutionCost < bestSolutionCost) {
                costToPrint = solutionCost;
                print = true;
                bestSolution = solution;
                bestSolutionCost = solutionCost;
            }
        }
        if (print)
            std::cout << iter << " " << costToPrint << " " << 100 * float(bestSolutionCost - this->predictedResult) / this->predictedResult << "%\n";
        // decrease temperature using choosen algorithm
        if (this->cm == GEOMETRICAL)
            tempTemperature = this->geometricalCooling(tempTemperature, p);
        else
            tempTemperature = this->cauchyCooling(tempTemperature, 0.999, 0.0001, counter);
    }
    std::cout << "0 " << firstSolutionCostToPrint << " " << 100 * float(firstSolutionCostToPrint - this->predictedResult) / this->predictedResult << "%\n";
    for (int i = 0; i < firstSolution.size(); i++)
        std::cout << firstSolution[i] << " - ";
    std::cout << "\n";
    auto stop = std::chrono::high_resolution_clock::now();
    this->time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    for (int i = 0; i < this->size; i++)
        this->bestPath[i] = bestSolution[i];
    this->bestCost = bestSolutionCost;
    this->getResult("simulated annealing");
}

std::vector<int> SimulatedAnnealingSolver::getStartingSolutionGreedy() {
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

std::vector<int> SimulatedAnnealingSolver::getStartingSolutionRandom() {
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

std::vector<int> SimulatedAnnealingSolver::getNextSolutionInsert(std::vector<int> solution) {
    std::vector<int> result;
    for (int i = 0; i < solution.size(); i++)
        result.push_back(solution[i]);
    int i = rand() % (this->size - 1);
    int j = rand() % (this->size - 1);
    if (i > j) {
        int temp = result[i];
        for (int k = i; k > j; k--)
            result[k] = result[k - 1];
        result[j] = temp;
    }
    else if (j > i) {
        int temp = result[i];
        for (int k = i; k < j; k++)
            result[k] = result[k + 1];
        result[j] = temp;
    }
    result[this->size] = result[0];
    return result;
}           

std::vector<int> SimulatedAnnealingSolver::getNextSolutionSwap(std::vector<int> solution) {
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

std::vector<int> SimulatedAnnealingSolver::getNextSolutionInvert(std::vector<int> solution) {
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
    std::shuffle(std::begin(solution), std::end(solution), std::default_random_engine(std::time(0)));
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

void SimulatedAnnealingSolver::setParams(firstSolutionMethod fsm, nextSolutionMethod nsm, coolingMethod cm) {
    this->fsm = fsm;
    this->nsm = nsm;
    this->cm = cm;
}

void SimulatedAnnealingSolver::getParams(firstSolutionMethod fsmChoice, nextSolutionMethod nsmChoice, coolingMethod cmChoice) {
    int tests = 5;
    float error;
    float bestError = INT_MAX;
    long long bestTime = LLONG_MAX;
    double bestP;
    double bestQ;
    double bestEndTemperature;
    long long time;
    for (double p = 0.85; p < 1; p += 0.1)
        for (double q = 0.1; q < 1.01; q += 0.1)
            for (double endTemperature = 0.1; endTemperature < 5; endTemperature += 0.1) {
                error = 0;
                for (int l = 0; l < tests; l++) {
                    this->solveWithParams(p, q, endTemperature);
                    error += this->getError();
                }
                error /= tests;
                time = this->getTime();
                if (error <= bestError && time < bestTime) {
                    bestTime = time;
                    bestError = error;
                    bestP = p;
                    bestQ = q;
                    bestEndTemperature = endTemperature;
                }
            }
    std::cout << "---------------------------------------------\n";
    std::cout << "bestError: " << bestError << std::endl;
    std::cout << "bestP: " << bestP << std::endl;
    std::cout << "bestQ: " << bestQ << std::endl;
    std::cout << "bestEndTemperature: " << bestEndTemperature << std::endl;
    std::cout << "---------------------------------------------\n";
    std::cout << "time: " << bestTime << std::endl << std::endl;
}