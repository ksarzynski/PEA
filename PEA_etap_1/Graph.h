#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

class Graph
{

public:

    Graph();
    Graph(int size, int range, bool symmetrical);
    explicit Graph(const std::string& fileName);
    ~Graph();
    void printGraph();
    void loadGraph(const std::string& fileName);
    int** getGraph();
    int getSize();
    std::string getFileName() { return this->fileName; };
    int getPredictedResult() { return this->predictedResult; };

private:

    int** graph;
    int size;
    bool isInitialized;
    std::string fileName;
    int predictedResult;

    void initEmptyGraph(int _size);
    void initRandomSymmetricalGraph(int range);
    void initRandomAsymmetricalGraph(int range);
};

