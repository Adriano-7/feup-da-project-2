#ifndef PROJECT_DA_GRAPH_H
#define PROJECT_DA_GRAPH_H

#include <string>
#include <vector>
#include <sstream>
#include <limits>

#include <functional>
#include <queue>
#include <algorithm>

#include <stack>
#include <unordered_set>

#include "NodeEdge.h"
using namespace std;

/**
 * @class Graph
 * @brief Represents a graph data structure.
 */
class Graph {
public:
    bool addNode(int id);
    bool addNode(int id, double latitude, double longitude);
    bool addEdge(Node* source, Node* dest, double distance);

    Node* getNode(int id);
    vector<Node*> getNodes();

    void primMST();

    void Backtracking_aux(unsigned int curIndex, unsigned int count, double cost, double &ans, vector<unsigned int> &path, vector<vector<unsigned int>> paths);
    vector<unsigned int> Backtracking_TSP(double* distance);

    vector<Node*> dfsTriangular(Node* node);
    vector<Node*> tspTriangular(double* distance);
    vector<unsigned int> insertion_TSP(double* distance);

    void clear();

    ~Graph();
private:
    vector<Node*> nodes;
    void resetNodes();
};

#endif
