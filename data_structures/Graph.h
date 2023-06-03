#ifndef PROJECT_DA_GRAPH_H
#define PROJECT_DA_GRAPH_H

#include <string>
#include <vector>
#include <sstream>
#include <limits>

#include <functional>
#include <queue>

#include <stack>
#include <unordered_set>

#include "NodeEdge.h"
using namespace std;

class Graph {
public:
    bool addNode(int id);
    bool addNode(int id, double latitude, double longitude);
    bool addEdge(Node* source, Node* dest, double distance);

    Node* getNode(int id);
    vector<Node*> getNodes();

    void primMST();
    vector<Node*> dfsTriangular(Node* node);
    vector<Node*> tspTriangular(double* distance);

    void Backtracking_aux(unsigned int curIndex, unsigned int count, double cost, double &ans, vector<unsigned int> &path, vector<vector<unsigned int>> paths);
    pair<double, vector<unsigned int>> Backtracking_TSP();

    void clear();

    ~Graph();

    pair<double, vector<unsigned int>> insertion_TSP();
    bool isRealWorld = false;

private:
    vector<Node*> nodes;
    void resetNodes();
};

#endif
