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

struct compareNodes{
    bool operator()(Node* a, Node* b) {
        if (a == nullptr) return false;
        if (b == nullptr) return true;
        return a->getDistance() > b->getDistance();
    }
};

void Graph::primMST(){
    //go through all nodes and set distance to infinity and path to null
    priority_queue<Node*, vector<Node*>, compareNodes> pq;
    for(Node* node : nodes){
        node->setDistance(numeric_limits<double>::infinity());
        node->setPath(nullptr);
        if (pq.empty() || pq.top() != node) {
            pq.push(node);
        }
    }

    //set first node distance to 0
    nodes[0]->setDistance(0);

    while(!pq.empty()){
        Node* node = pq.top();
        pq.pop();

        for(Edge* edge : node->getAdj()){
            Node* dest = edge->getDest();
            if(dest->isVisited()) continue;

            double distance = edge->getDistance();
            if(distance < dest->getDistance()){
                dest->setDistance(distance);
                dest->setPath(edge);
                pq.push(dest);
            }
        }
        node->setVisited(true);
    }

    //print MST
    for(Node* node : nodes){
        if(node->getPath() != nullptr){
            cout << node->getPath()->getOrig()->getId() << " " << node->getPath()->getDest()->getId() << " " << node->getPath()->getDistance() << endl;
        }
    }
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