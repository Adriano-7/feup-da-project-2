#ifndef PROJECT_DA_GRAPH_H
#define PROJECT_DA_GRAPH_H

#include <string>
#include <vector>
#include "NodeEdge.h"
using namespace std;

class Graph {
public:
    bool addNode(int id);
    bool addNode(int id, double latitude, double longitude);
    bool addEdge(Node* source, Node* dest, int distance);

    Node* getNode(int id);
    
private:
    vector<Node*> nodes;
};

#endif
