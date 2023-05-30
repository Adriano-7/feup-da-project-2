#ifndef PROJECT_DA_GRAPH_H
#define PROJECT_DA_GRAPH_H

#include <string>
#include <vector>
#include <math.h>
#include <queue>
#include <sstream>
#include <set>
#include "MutablePriorityQueue.h"

#include "NodeEdge.h"
using namespace std;

class Graph {
public:
    bool addNode(int id);
    bool addNode(int id, double latitude, double longitude);
    bool addEdge(Node* source, Node* dest, double distance);

    double haversineDistance(Node* source, Node* dest);
    void dfs(Node* node, vector<Node*>& res);
    vector<Node *> primMST();

    double dfsTriangular(int source, int destination, vector<bool> &visited, vector<int> &path);
    vector<int> tspTriangular(int source, int destination, double* distance);

    Node* getNode(int id);
    vector<Node*> getNodes();

    ~Graph();
private:
    vector<Node*> nodes;
};

#endif
