#include "Graph.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>
#include <limits>

using namespace std;

bool Graph::addNode(int id){
    nodes.push_back(new Node(id));
    return true;
}

bool Graph::addNode(int id, double latitude, double longitude) {
    nodes.push_back(new Node(id, latitude, longitude));
    return true;
}

bool Graph::addEdge(Node* sourceNode, Node* destNode, double distance) {
    Edge* e1 = sourceNode->addEdge(destNode, distance);
    Edge* e2 = destNode->addEdge(sourceNode, distance);

    e1->setReverse(e2);
    e2->setReverse(e1);

    return true;
}

Node* Graph::getNode(int id){
    if(id>=0 && id<nodes.size()) return nodes[id];

    return nullptr;
}

vector<Node*> Graph::getNodes(){
    return nodes;
}

Graph::~Graph() {
    for(auto node : nodes){
        delete node;
    }
}