//
// Created by kacpe on 08.11.2021.
//

#include "Node.h"

Node::Node(std::vector<int> _tour, int _start, int _end, int _level, int _cost, int _lowerBound) {
    this->tour = std::move(_tour);
    this->start = _start;
    this->end = _end;
    this->level = _level;
    this->cost = _cost;
    this->lowerBound = _lowerBound;
}
