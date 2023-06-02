#ifndef PROJECT_DA_GRAPH_H
#define PROJECT_DA_GRAPH_H

#include <string>
#include <vector>
#include <math.h>
#include <sstream>
#include "MutablePriorityQueue.h"
#include <limits>

#include <stack>
#include <unordered_set>

#include "NodeEdge.h"
using namespace std;

class Graph {
public:
    bool addNode(int id);
    bool addNode(int id, double latitude, double longitude);
    bool addEdge(Node* source, Node* dest, double distance);

    double haversineDistance(Node* source, Node* dest);

    void primMST();
    vector<Node*> dfsTriangular(Node* node);
    vector<Node*> tspTriangular(double* distance);

    Node* getNode(int id);
    vector<Node*> getNodes();

    void clear();

    ~Graph();

    void Backtracking_aux(unsigned int curIndex, unsigned int count, double cost, double &ans, vector<unsigned int> &path, vector<vector<unsigned int>> paths);
    pair<double, vector<unsigned int>> Backtracking_TSP();

    pair<double, vector<unsigned int>> insertion_TSP();
    bool isRealWorld = false;



private:
    vector<Node*> nodes;
    void resetNodes();
};

#endif
