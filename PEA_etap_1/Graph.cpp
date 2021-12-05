#include "Graph.h"

Graph::Graph() {
    this->size = 10;
    this->graph = new int* [this->size];
    for (int i = 0; i < this->size; i++)
        this->graph[i] = new int[this->size];
    initRandomSymmetricalGraph(20);
    this->isInitialized = true;
    this->fileName = "";
    this->predictedResult = -1;
}

Graph::Graph(int size, int range, bool symmetrical) {
    this->size = size;
    this->graph = new int* [this->size];
    for (int i = 0; i < this->size; i++)
        this->graph[i] = new int[this->size];
    if (symmetrical)
        initRandomSymmetricalGraph(range);
    else
        initRandomAsymmetricalGraph(range);
    this->isInitialized = true;
}

Graph::Graph(const std::string& fileName) {
    this->graph = nullptr;
    this->size = -1;
    isInitialized = false;
    this->loadGraph(fileName);
    isInitialized = true;
}

Graph::~Graph() {
    for (int i = 0; i < this->size; i++)
        delete[] this->graph[i];
    delete[] this->graph;
}

void Graph::printGraph() {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++)
            std::cout << std::setw(3) << graph[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Graph::loadGraph(const std::string& fileName) {
    std::ifstream myFile;
    myFile.open("C:/Users/kacpe/Downloads/ak2/data/" + fileName);
    if (myFile.good()) {
        std::string data;
        std::getline(myFile, data);
        this->fileName = data;
        std::getline(myFile, data);
        int tempSize = std::stoi(data);
        this->initEmptyGraph(tempSize);
        for (int i = 0; i < this->size; i++) {
            std::getline(myFile, data);
            std::istringstream inputStringStream(data);
            for (int j = 0; j < this->size; j++) {
                inputStringStream >> this->graph[i][j];
                if (i == j)
                    this->graph[i][j] = -1;
            }
        }
        std::getline(myFile, data);
        this->predictedResult = std::stoi(data);
        myFile.close();
    }
    else
        std::cout << "file wasn't good\n";
}

int** Graph::getGraph() { return this->graph; }

int Graph::getSize() { return this->size; }

void Graph::initEmptyGraph(int _size) {
    if (this->isInitialized) {
        for (int i = 0; i < this->size; i++)
            delete[] this->graph[i];
        delete[] this->graph;
    }
    this->size = _size;
    this->graph = new int* [this->size];
    for (int i = 0; i < this->size; i++)
        this->graph[i] = new int[this->size];
}

void Graph::initRandomSymmetricalGraph(int range) {
    srand(time(nullptr));
    int index = 0;
    for (int i = 0; i < this->size; i++) {
        for (int j = index; j < this->size; j++) {
            if (i == j)
                graph[i][j] = -1;
            else {
                this->graph[i][j] = rand() % range + 1;
                this->graph[j][i] = this->graph[i][j];
            }
        }
    }
}

void Graph::initRandomAsymmetricalGraph(int range) {
    srand(time(nullptr));
    for (int i = 0; i < this->size; i++)
        for (int j = 0; j < this->size; j++) {
            if (i == j)
                this->graph[i][j] = -1;
            else
                this->graph[i][j] = rand() % range + 1;
        }
}