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

void Graph::dfs(Node* node, vector<Node*>& res) {
    node->setVisited(true);
    for(Edge* edge : node->getAdj()){
        Node* dest = edge->getDest();
        if(!dest->isVisited()){
            res.push_back(dest);
            res.push_back(node);
            dfs(dest, res);
        }
    }
}

vector<Node *> Graph::primMST() {
    MutablePriorityQueue<Node> q;
    vector<Node *> res;

    for(Node* node: nodes){
        node->setDistance(numeric_limits<double>::infinity());
        node->setPath(nullptr);
        node->setVisited(false);
        q.insert(node);
    }

    nodes[0]->setDistance(0);
    q.decreaseKey(nodes[0]);

    while(!q.empty()){
        Node* node = q.extractMin();
        node->setVisited(true);
        res.push_back(node);

        for(Edge* edge : node->getAdj()){
            Node* dest = edge->getDest();
            if(!dest->isVisited() && edge->getDistance() < dest->getDistance()){
                dest->setDistance(edge->getDistance());
                dest->setPath(edge);
                q.decreaseKey(dest);
            }
        }
    }

    return res;
}


vector<int> Graph::tspTriangular(int source, int destination, double* distance){
    Node* sourceNode = getNode(source);
    if(sourceNode == nullptr) {
        cout << "Source node not found" << endl;
        return vector<int>();
    }

    Node* destinationNode = getNode(destination);
    if(destinationNode == nullptr) {
        cout << "Destination node not found" << endl;
        return vector<int>();
    }

    // Step 1: Compute minimum spanning tree and pseudotour
    auto res = primMST();

    cout << "MST: " << endl;
    for(Node* const node : res){
        if(node->getPath() != nullptr){
            cout << node->getPath()->getOrig()->getId() << " --- " << node->getId() << " cost: " << node->getPath()->getDistance() << endl;
        }
    }

    return vector<int>();

    /*
     *     for(const auto v : res) {
        ss << v->getId() << "<-";
        if ( v->getPath() != nullptr ) {
            ss << v->getPath()->getOrig()->getId();
        }
        ss << "|";
    }
     *
    dfs(sourceNode, res);

    // Step 2: Create tour from pseudotour
    set<Node*> visited;
    vector<int> tour;
    for(Node* node : res){
        if(visited.find(node) == visited.end()){
            visited.insert(node);
            tour.push_back(node->getId());
        }
    }

    // Add the last edge from the destination node to the source node
    tour.push_back(sourceNode->getId());
    
    return tour;
     */
}


/*
vector<int> Graph::tspTriangular(int source, int destination, double* distance){
    Node* sourceNode = getNode(source);
    if(sourceNode == nullptr) cout << "Source node not found" << endl; return vector<int>();

    Node* destinationNode = getNode(destination);
    if(destinationNode == nullptr) cout << "Destination node not found" << endl; return vector<int>();

    
    auto res = primMST();
    dfs(sourceNode, res);
    
    return vector<int>();


    vector<bool> visited(nodes.size(), false);
    vector<int> path;
    path.push_back(source);
    visited[source] = true;
    *distance = dfsTriangular(source, destination, visited, path);

    vector<int> t_star;
    for (int i = 0; i < path.size(); i++) {
        int vertex = path[i];
        if (find(t_star.begin(), t_star.end(), vertex) == t_star.end()) {
            t_star.push_back(vertex);
        }
    }

    double t_star_cost = 0;
    for (int i = 0; i < t_star.size() - 1; i++) {
        int u = t_star[i];
        int v = t_star[i+1];
        Edge* edge = nodes[u]->getEdgeTo(v);
        t_star_cost += edge->getDistance();
    }

    return t_star;
     */




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