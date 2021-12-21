#include "TabuSearchSolver.h"

void TabuSearchSolver::solve(){
	auto startAlgorithm = std::chrono::high_resolution_clock::now();
	// todo pass it somehow
	int bansListSize = std::pow(this->size, 2);
	int banDuration = std::sqrt(this->size);
	int moves = std::log2(this->size);
	Solution startSolution;
	if (this->fsm == GREEDY)
		startSolution.path = getStartingSolutionGreedy();
	else
		startSolution.path = getStartingSolutionRandom();
	startSolution.cost = this->getCost(startSolution);
	Solution bestSolution;
	Solution nextSolution;
	Solution currentSolution(startSolution);
	bestSolution = currentSolution;
	std::vector<Ban> bans;
	bool isTimeOver = false;
	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::microseconds timeLimit = std::chrono::microseconds{ 1000000 } * this->maxTime;
	int iter = 0;
	int iterFound = 0;
	int lastChange = 0;
	std::chrono::microseconds duration;
	std::chrono::microseconds timeFound;
	duration = std::chrono::microseconds{ 0 };
	while (!isTimeOver) {
		iter++;
		nextSolution = this->getNextSolution(bestSolution, currentSolution, bans);
		for (int i = 0; i < this->size + 1; i++)
		if (nextSolution.cost != currentSolution.cost)
			lastChange = iter;
		currentSolution = nextSolution;
		if (bansListSize < bans.size()) {
			bans.push_back(Ban(currentSolution.startCity, banDuration));
			bans.push_back(Ban(currentSolution.endCity, banDuration));
		}
		if (currentSolution.cost < bestSolution.cost) {
			bestSolution = currentSolution;
			iterFound = iter;
			timeFound = duration;
		}
		for (int i = 0; i < bans.size(); i++) {
			bans[i].duration -= 1;
			if (bans[i].duration == 0) {
				std::vector<Ban>::iterator it;
				it = bans.begin();
				advance(it, i--);
				bans.erase(it);
			}
		}
		if (iter - lastChange > 5) {
			int* toChange;
			toChange = new int[2 * moves];
			std::vector<int> vertexes;
			for (int i = 1; i < size; i++)
				vertexes.push_back(i);
			for (int i = 0; i < 2 * moves; i++) {
				int temp = rand() % vertexes.size();
				toChange[i] = vertexes[temp];
				std::vector<int>::iterator it;
				it = vertexes.begin();
				advance(it, temp);
				vertexes.erase(it);
			}
			for (int k = 0; k < moves; k++) {
				if (this->nsm == INSERT)
					this->getNextSolutionInsert(currentSolution, 2 * k, 2 * k + 1);
				else if (this->nsm == SWAP)
					this->getNextSolutionSwap(currentSolution, 2 * k, 2 * k + 1);
				else
					this->getNextSolutionInvert(currentSolution, 2 * k, 2 * k + 1);
				currentSolution.cost = this->getCost(currentSolution);
			}
			currentSolution.cost = this->getCost(currentSolution);
		}
		auto end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		if (duration > timeLimit)
			isTimeOver = true;
	}
	for (int i = 0; i < bestSolution.path.size(); i++)
		this->bestPath[i] = bestSolution.path[i];
	this->bestCost = bestSolution.cost;
	auto stopAlgorithm = std::chrono::high_resolution_clock::now();
	this->time = std::chrono::duration_cast<std::chrono::microseconds>(stopAlgorithm - startAlgorithm).count();
}

void TabuSearchSolver::solveWithOutput() {
	this->printParams();
	auto startAlgorithm = std::chrono::high_resolution_clock::now();
	int bansListSize = std::pow(this->size, 2);
	int banDuration = std::sqrt(this->size);
	int moves = std::log2(this->size);
	Solution startSolution;
	if (this->fsm == GREEDY)
		startSolution.path = getStartingSolutionGreedy();
	else
		startSolution.path = getStartingSolutionRandom();
	std::cout << "first solution:\n";
	for (int i = 0; i < startSolution.path.size(); i++)
		std::cout << startSolution.path[i] << " - ";
	std::cout << "\n";
	std::vector<int> firstSolutionToPrint = startSolution.path;
	int firstSolutionCostToPrint = this->getCost(startSolution);
	std::cout << "0 " << firstSolutionCostToPrint << " " << 100 * float(firstSolutionCostToPrint - this->predictedResult) / this->predictedResult << "%\n";
	startSolution.cost = this->getCost(startSolution);
	Solution bestSolution;
	Solution nextSolution;
	Solution currentSolution(startSolution);
	bestSolution = currentSolution;
	std::vector<Ban> bans;
	bool isTimeOver = false;
	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::microseconds timeLimit = std::chrono::microseconds{ 1000000 } *this->maxTime;
	int iter = 0;
	int iterFound = 0;
	int lastChange = 0;
	std::chrono::microseconds duration;
	std::chrono::microseconds timeFound;
	duration = std::chrono::microseconds{ 0 };
	bool print = false;
	int costToPrint = INT_MAX;
	int iterationToPrint = INT_MAX;
	while (!isTimeOver) {
		iter++;
		nextSolution = this->getNextSolution(bestSolution, currentSolution, bans);
		for (int i = 0; i < this->size + 1; i++)
			if (nextSolution.cost != currentSolution.cost)
				lastChange = iter;
		currentSolution = nextSolution;
		if (bansListSize < bans.size()) {
			bans.push_back(Ban(currentSolution.startCity, banDuration));
			bans.push_back(Ban(currentSolution.endCity, banDuration));
		}
		if (currentSolution.cost < bestSolution.cost) {
			bestSolution = currentSolution;
			iterFound = iter;
			timeFound = duration;
		}
		for (int i = 0; i < bans.size(); i++) {
			bans[i].duration -= 1;
			if (bans[i].duration == 0) {
				std::vector<Ban>::iterator it;
				it = bans.begin();
				advance(it, i--);
				bans.erase(it);
			}
		}
		if (iter - lastChange > 5) {
			int* toChange;
			toChange = new int[2 * moves];
			std::vector<int> vertexes;
			for (int i = 1; i < size; i++)
				vertexes.push_back(i);
			for (int i = 0; i < 2 * moves; i++) {
				int temp = rand() % vertexes.size();
				toChange[i] = vertexes[temp];
				std::vector<int>::iterator it;
				it = vertexes.begin();
				advance(it, temp);
				vertexes.erase(it);
			}
			for (int k = 0; k < moves; k++) {
				if (this->nsm == INSERT)
					this->getNextSolutionInsert(currentSolution, 2 * k, 2 * k + 1);
				else if (this->nsm == SWAP)
					this->getNextSolutionSwap(currentSolution, 2 * k, 2 * k + 1);
				else
					this->getNextSolutionInvert(currentSolution, 2 * k, 2 * k + 1);
				currentSolution.cost = this->getCost(currentSolution);
			}
			currentSolution.cost = this->getCost(currentSolution);
		}
		auto end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		if (duration > timeLimit)
			isTimeOver = true;
	}
	std::cout << "0 " << firstSolutionCostToPrint << " " << 100 * float(firstSolutionCostToPrint - this->predictedResult) / this->predictedResult << "%\n";
	for (int i = 0; i < firstSolutionToPrint.size(); i++)
		std::cout << firstSolutionToPrint[i] << " - ";
	std::cout << "\n";
	for (int i = 0; i < bestSolution.path.size(); i++)
		this->bestPath[i] = bestSolution.path[i];
	this->bestCost = bestSolution.cost;
	auto stopAlgorithm = std::chrono::high_resolution_clock::now();
	this->time = std::chrono::duration_cast<std::chrono::microseconds>(stopAlgorithm - startAlgorithm).count();
}

std::vector<int> TabuSearchSolver::getStartingSolutionGreedy() {
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

std::vector<int> TabuSearchSolver::getStartingSolutionRandom() {
	std::random_device rd;
	std::mt19937 g(rd());
	std::uniform_real_distribution<double> num(0.0, 1.0);
	std::vector<int> firstSolution;
	firstSolution.clear();
	for (int i = 0; i < this->size; i++)
		firstSolution.push_back(i);
	std::shuffle(std::begin(firstSolution), std::end(firstSolution), std::default_random_engine(std::time(0)));
	firstSolution.push_back(firstSolution[0]);
	return firstSolution;
}

int TabuSearchSolver::getBestNeighbour(int vertex, bool* visited) {
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

TabuSearchSolver::Solution TabuSearchSolver::getNextSolution(Solution bestSolution, Solution currentSolution, std::vector<Ban> bans) {
	TabuSearchSolver::Solution bestSolutionFound;
	bestSolutionFound.cost = INT_MAX;
	for (int i = 1; i < this->size; i++) {
		for (int j = 1; j < this->size; j++) {
			if (i != j) {
				TabuSearchSolver::Solution nextSolution = currentSolution;
				if (this->nsm == INSERT)
					nextSolution.path = this->getNextSolutionInsert(nextSolution, i, j);
                else if (this->nsm == SWAP)
					nextSolution.path = this->getNextSolutionSwap(nextSolution, i, j);
                else
					nextSolution.path = this->getNextSolutionInvert(nextSolution, i, j);
				nextSolution.startCity = i;
				nextSolution.endCity = j;
                nextSolution.cost = this->getCost(nextSolution);
				if (nextSolution.cost < bestSolution.cost && nextSolution.cost< bestSolutionFound.cost)
					bestSolutionFound = nextSolution;
				if (nextSolution.cost < bestSolutionFound.cost) {
					bool isBanned = false;
					for (int k = 0; k < bans.size(); k++) {
						if (bans[k].city == i || bans[k].city == j)
							isBanned = true;
					}
					if (!isBanned)
						bestSolutionFound = nextSolution;
				}
			}
		}
	}
	if (bestSolutionFound.path.size() > 1)
		return bestSolutionFound;
	else
		return currentSolution;
}

std::vector<int> TabuSearchSolver::getNextSolutionInsert(Solution solution, int i, int j) {
    std::vector<int> result(solution.path);
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

std::vector<int> TabuSearchSolver::getNextSolutionSwap(Solution solution, int i, int j) {
    std::vector<int> nextSolution = solution.path;
    int tempV = nextSolution[i];
    while (j == i)
        j = rand() % this->size;
    nextSolution[i] = nextSolution[j];
    nextSolution[j] = tempV;
    nextSolution[this->size] = nextSolution[0];
    return nextSolution;
}

std::vector<int> TabuSearchSolver::getNextSolutionInvert(Solution solution, int i, int j) {
	if (j > this->size || i > this->size - j)
		return solution.path;
    std::vector<int> nextSolution = solution.path;
    std::vector<int> temp;
    int tempIndex = 0;
    for (int k = 0; k < j; k++)
        temp.push_back(nextSolution[i + k]);
    std::reverse(temp.begin(), temp.end());
    for (int k = i; k < i + j; k++) {
        nextSolution[k] = temp[tempIndex];
        tempIndex++;
    }
    nextSolution[this->size] = nextSolution[0];
    return nextSolution;
}

int TabuSearchSolver::getCost(Solution solution) {
    int cost = 0;
    for (int i = 0; i < solution.path.size() - 1; i++)
        cost += this->graph[solution.path[i]][solution.path[i + 1]];
    return cost;
}

std::vector<int> TabuSearchSolver::getResult(const std::string& solverType) {
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

void TabuSearchSolver::setParams(nextSolutionMethod nsm, firstSolutionMethod fsm, int maxTime) {
	this->nsm = nsm;
	this->fsm = fsm;
	this->maxTime = maxTime;
}

void TabuSearchSolver::printParams() {
	std::cout << "nsm: " << this->nsm << "\n";
	std::cout << "fsm: " << this->fsm << "\n";
	std::cout << "maxTime: " << this->maxTime << "\n";
}