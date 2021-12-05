#include "BestFirstBranchAndBoundSolver.h"

void BestFirstBranchAndBoundSolver::solve(){ 
    int cost = INT_MAX;
    int upper = INT_MAX;
    int level = 0;
    int start = 0;
    std::vector<int> bestTour;
    std::vector<int> tour;
    std::vector<int> tempTour;
    tour.push_back(start);
    int lowerBound = this->getLowerBound();
    Node* bestNode = new Node(tour, 0, 0, 0, 0, lowerBound);
    std::priority_queue<Node*, std::vector<Node*>, myComparator> pq;
    pq.push(bestNode);
    while (!pq.empty()){
        Node* bestNode = pq.top();
        pq.pop();
        if (bestNode->cost > upper)
            return;
        if (bestNode->tour.size() == this->size){
            int tempCost = bestNode->cost +
                this->graph[bestNode->tour[bestNode->tour.size() - 1]][start];
            if (tempCost < upper){
                upper = tempCost;
                cost = tempCost;
                bestTour = bestNode->tour;
            }
        }
        else{
            for (int i = 0; i < this->size; i++){
                if (!isVisited(i, bestNode->tour)){
                    tempTour = bestNode->tour;
                    tempTour.push_back(i);
                    level = bestNode->level + 1;
                    Node* node = new Node(tempTour, bestNode->end, i, level, bestNode->cost, 0);
                    node->cost += this->graph[node->start][i];
                    if (node->level == 1)
                        node->lowerBound = bestNode->lowerBound
                        - ((getFirstMinCost(i) + getFirstMinCost(node->start)) / 2)
                        + this->graph[node->start][i];
                    else
                        node->lowerBound = bestNode->lowerBound
                        - ((getFirstMinCost(i) + getSecondMinCost(node->start)) / 2)
                        + this->graph[node->start][i];
                    if (node->cost < upper && node->lowerBound <= upper)
                        pq.push(node);
                    else
                        delete node;
                }
            }
        }
        delete bestNode;
    }
    this->bestCost = cost;
    bestTour.push_back(bestTour[0]);
    for (int i = 0; i < this->size + 1; i++)
        this->bestPath[i] = bestTour[i];
}

void BestFirstBranchAndBoundSolver::solveWithOutput(){
    std::cout << "DynamicSolver doesnt have this function implemented\n";
}

int BestFirstBranchAndBoundSolver::getFirstMinCost(int v){
    int min = INT_MAX;
    for (int i = 0; i < this->size; i++)
        if (this->graph[v][i] < min && v != i)
            min = this->graph[v][i];
    return min;
}

int BestFirstBranchAndBoundSolver::getSecondMinCost(int v){
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    for (int i = 0; i < this->size; i++){
        if (v == i)
            continue;
        if (this->graph[v][i] <= min1){
            min2 = min1;
            min1 = this->graph[v][i];
        }
        else if (this->graph[v][i] <= min2 && this->graph[v][i] != min1)
            min2 = this->graph[v][i];
    }
    return min2;
}

int BestFirstBranchAndBoundSolver::getLowerBound(){
    int lowerBound = 0;
    for (int i = 0; i < this->size; i++){
        lowerBound += (this->getFirstMinCost(i) + this->getSecondMinCost(i)) / 2;
    }
    return lowerBound;
}

bool BestFirstBranchAndBoundSolver::isVisited(int index, std::vector<int> path){
    for (int i = 0; i < path.size(); i++)
        if (index == path[i])
            return true;
    return false;
}