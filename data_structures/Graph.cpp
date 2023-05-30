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


double Graph::haversineDistance(Node* source, Node* dest) {
    double lat1 = source->getLatitude() * M_PI / 180.0;
    double lon1 = source->getLongitude() * M_PI / 180.0;
    double lat2 = dest->getLatitude() * M_PI / 180.0;
    double lon2 = dest->getLongitude() * M_PI / 180.0;

    double a = pow(sin((lat2 - lat1) / 2), 2) + pow(sin((lon2 - lon1) / 2), 2) * cos(lat1) * cos(lat2);
    return 6371 * 2 * asin(sqrt(a));
}

void Graph::primMST(Node* start, double* cost) {
    MutablePriorityQueue<Node> q;

    for(Node* node: nodes){
        node->setDistance(numeric_limits<double>::infinity());
        node->setPath(nullptr);
        node->setVisited(false);
        q.insert(node);
    }

    start->setDistance(0);
    q.decreaseKey(start);

    while(!q.empty()){
        Node* node = q.extractMin();
        node->setVisited(true);

        for(Edge* edge : node->getAdj()){
            Node* dest = edge->getDest();
            if(!dest->isVisited() && edge->getDistance() < dest->getDistance()){
                dest->setDistance(edge->getDistance());
                dest->setPath(edge);
                q.decreaseKey(dest);
            }
        }
        if(node->getPath() != nullptr){
            node->getPath()->setSelected(true);
        }
    }

    *cost = 0;
    for(Node* node : nodes){
        if(node->getPath() != nullptr){
            *cost += node->getPath()->getDistance();
        }
    }
}


vector<Node*> Graph::dfsTriangular(Node* start) {
    for(Node* node : nodes) {
        node->setVisited(false);
    }

    vector<Node*> path;
    stack<Node*> s;
    s.push(start);

    while(!s.empty()) {
        Node* current = s.top();
        s.pop();

        if(current->isVisited()) {
            continue;
        }

        current->setVisited(true);
        path.push_back(current);

        for(Edge* edge : current->getAdj()) {
            if(edge->isSelected()) {
                Node* next = edge->getDest();
                s.push(next);
            }
        }
    }

    return path;
}

vector<Node*> Graph::tspTriangular(int source, int destination, double* distance){
    Node* sourceNode = getNode(source);
    if(sourceNode == nullptr) {
        cout << "Source node not found" << endl;
        return vector<Node*>();
    }

    Node* destinationNode = getNode(destination);
    if(destinationNode == nullptr) {
        cout << "Destination node not found" << endl;
        return vector<Node*>();
    }

    // Step 1:  compute a minimum spanning tree T for G from root r
    *distance = 0;
    primMST(sourceNode, distance);

    //Step 2: let H be a list of vertices, ordered according to when they are first visited in a preorder tree walk of T
    return dfsTriangular(sourceNode);

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