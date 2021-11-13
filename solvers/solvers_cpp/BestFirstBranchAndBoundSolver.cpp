//
// Created by kacpe on 02.11.2021.
//

#include <Node.h>
#include <queue>
#include "../solvers_h/BestFirstBranchAndBoundSolver.h"

void BestFirstBranchAndBoundSolver::solve(){
    int cost;
    int upper = INT_MAX;
    int level;
    std::vector<int> bestTour;
    std::vector<int> tour;
    std::vector<int> tempTour;
    tour.push_back(0);
    int lowerBound = this->getStartingLowerBound();
    std::priority_queue<Node*, std::vector<Node*>, Node::myComparator> pq;
    pq.push(new Node(tour, 0, 0, 0, 0, lowerBound));
    while (!pq.empty()){
        Node* bestNode = pq.top();
        pq.pop();
        if (bestNode->getCost() > upper)
            return;
        if (bestNode->getTour().size() == this->size){
            int tempCost = bestNode->getCost() +
                           this->graph[bestNode->getTour()[bestNode->getTour().size() - 1]][0];
            if (tempCost < upper){
                upper = tempCost;
                cost = tempCost;
                bestTour = bestNode->getTour();
                bestCost = cost;
                bestTour.push_back(bestTour[0]);
                for (int i = 0; i < this->size + 1; i++)
                    this->bestPath[i] = bestTour[i];
            }
        }
        else{
            for (int i = 0; i < this->size; i++){
                if(!isVisited(i, bestNode->getTour())){
                    tempTour = bestNode->getTour();
                    tempTour.push_back(i);
                    level = bestNode->getLevel() + 1;
                    Node* node = new Node(tempTour, bestNode->getEnd(), i, level, bestNode->getCost(), 0);
                    node->setCost(node->getCost() + this->graph[node->getStart()][i]);
                    if (node->getLevel() == 1)
                        node->setLowerBound(bestNode->getLowerBound()
                                           - ((firstMin(i) + firstMin(node->getStart())) / 2)
                                           + this->graph[node->getStart()][i]);
                    else
                        node->setLowerBound(bestNode->getLowerBound()
                                           - ((firstMin(i) + secondMin(node->getStart())) / 2)
                                           + this->graph[node->getStart()][i]);
                    if (node->getCost() < upper && node->getLowerBound() <= upper)
                        pq.push(node);
                    else
                        delete node;
                }
            }
        }
        delete bestNode;
    }
}

void BestFirstBranchAndBoundSolver::solveWithOutput() {
    int cost;
    int upper = INT_MAX;
    int level;
    std::vector<int> bestTour;
    std::vector<int> tour;
    std::vector<int> tempTour;
    tour.push_back(0);
    int lowerBound = this->getStartingLowerBound();
    std::priority_queue<Node*, std::vector<Node*>, Node::myComparator> pq;
    pq.push(new Node(tour, 0, 0, 0, 0, lowerBound));
    while (!pq.empty()) {
        Node* bestNode = pq.top();
        pq.pop();
        if (bestNode->getCost() > upper)
            return;
        if (bestNode->getTour().size() == this->size) {
            int tempCost = bestNode->getCost() +
                this->graph[bestNode->getTour()[bestNode->getTour().size() - 1]][0];
            if (tempCost < upper) {
                upper = tempCost;
                cost = tempCost;
                bestTour = bestNode->getTour();
                bestCost = cost;
                std::cout << cost << "     " << 100 * float(cost - this->predictedResult) / this->predictedResult << "%" << std::endl;
                bestTour.push_back(bestTour[0]);
                for (int i = 0; i < this->size + 1; i++)
                    this->bestPath[i] = bestTour[i];
            }
        }
        else {
            for (int i = 0; i < this->size; i++) {
                if (!isVisited(i, bestNode->getTour())) {
                    tempTour = bestNode->getTour();
                    tempTour.push_back(i);
                    level = bestNode->getLevel() + 1;
                    Node* node = new Node(tempTour, bestNode->getEnd(), i, level, bestNode->getCost(), 0);
                    node->setCost(node->getCost() + this->graph[node->getStart()][i]);
                    if (node->getLevel() == 1)
                        node->setLowerBound(bestNode->getLowerBound()
                            - ((firstMin(i) + firstMin(node->getStart())) / 2)
                            + this->graph[node->getStart()][i]);
                    else
                        node->setLowerBound(bestNode->getLowerBound()
                            - ((firstMin(i) + secondMin(node->getStart())) / 2)
                            + this->graph[node->getStart()][i]);
                    if (node->getCost() < upper && node->getLowerBound() <= upper)
                        pq.push(node);
                    else
                        delete node;
                }
            }
        }
        delete bestNode;
    }
    std::cout << std::endl;
}

int BestFirstBranchAndBoundSolver::firstMin(int vertex){
    int min = INT_MAX;
    for (int i = 0; i < this->size; i++)
        if (this->graph[vertex][i] < min && vertex != i)
             min = this->graph[vertex][i];
    return min;
}

int BestFirstBranchAndBoundSolver::secondMin(int vertex){
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    for (int i = 0; i < this->size; i++){
        if (vertex == i)
            continue;
        if (this->graph[vertex][i] <= min1){
            min2 = min1;
            min1 = this->graph[vertex][i];
        }
        else if (this->graph[vertex][i] <= min2 && this->graph[vertex][i] != min1)
            min2 = this->graph[vertex][i];
    }
    return min2;
}

int BestFirstBranchAndBoundSolver::getStartingLowerBound(){
    int lowerBound = 0;
    for (int i = 0; i < this->size; i++)
        lowerBound += (this->firstMin(i) + this->secondMin(i)) / 2;
    return lowerBound;
}

bool BestFirstBranchAndBoundSolver::isVisited(int index, const std::vector<int>& path) {
    for(int i : path)
        if(i == index)
            return true;
    return false;
}
