#ifndef PROJECT_DA_GRAPH_H
#define PROJECT_DA_GRAPH_H

#include <string>
#include <vector>
#include <math.h>
#include <queue>
#include <sstream>
#include "MutablePriorityQueue.h"

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

    ~Graph();
private:
    vector<Node*> nodes;
};

#endif
