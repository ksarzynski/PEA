//
// Created by kacpe on 08.11.2021.
//

#ifndef PEA_1_NODE_H
#define PEA_1_NODE_H


#include <utility>
#include <vector>

class Node {

public:
    Node(std::vector<int> _tour, int _start, int _end, int _level, int _cost, int _lowerBound);

    struct myComparator{
        bool operator()(const Node* l, const Node* r) const{
            return l->lowerBound > r->lowerBound;
        }
    };

    std::vector<int> getTour(){ return this->tour; };

    int getStart() { return this->start; };

    int getEnd() { return this->end; };

    int getCost() { return this->cost; };

    int getLevel() { return this->level; };

    int getLowerBound() { return this->lowerBound; };

    void setTour(std::vector<int> _tour){ this->tour = std::move(_tour); };

    void setStart(int _start) { this->start = _start; };

    void setEnd(int _end) { this->end = _end; };

    void setCost(int _cost) { this->cost = _cost; };

    void setLevel(int _level) { this->level = _level; };

    void setLowerBound(int _lowerBound) { this->lowerBound = _lowerBound; };

private:

    std::vector<int> tour;
    int start;
    int end;
    int cost;
    int level;
    int lowerBound;
};


#endif //PEA_1_NODE_H
