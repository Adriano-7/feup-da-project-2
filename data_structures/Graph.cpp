#include <iostream>
#include "Graph.h"

using namespace std;

bool Graph::addNode(int id){
    int size = nodes.size();
    if(id < size && nodes[id] != NULL)
        return false;

    for(int i = size; i <= id; i++){
        nodes.push_back(new Node(i));
    }

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

void Graph::primMST() {
    priority_queue<Edge*, vector<Edge*>, function<bool(Edge*, Edge*)>> pq
                                        ([](Edge* a, Edge* b) {return a->getDistance() > b->getDistance();});

    nodes[0]->setVisited(true);

    for (Edge* edge : nodes[0]->getAdj()) {pq.push(edge);}

    while (!pq.empty()) {
        Edge* minWeightEdge = pq.top();
        pq.pop();

        Node* source = minWeightEdge->getOrig();
        Node* dest = minWeightEdge->getDest();

        if(source->isVisited() && dest->isVisited())
            continue;

        minWeightEdge->setSelected(true);
        minWeightEdge->getReverse()->setSelected(true);

        dest->setVisited(true);
        for (Edge* edge : dest->getAdj()) {
            if(!edge->getDest()->isVisited()){
                pq.push(edge);
            }
        }
    }

    resetNodes();
}


void Graph::Backtracking_aux(unsigned int curIndex, unsigned int count, double cost, double &ans,
                             vector<unsigned int> &path, vector<vector<unsigned int>> paths) {
    if (count == nodes.size()){
        for (auto e : nodes[curIndex]->getAdj()){
            if (e->getOrig()->getId() == 0 || e->getDest()->getId() == 0){
                double new_cost = cost + e->getDistance();
                if (new_cost < ans){
                    ans = new_cost;
                    path = paths[curIndex];
                }
            }
        }
        return;
    }

    for (auto e : nodes[curIndex]->getAdj()){
        int nextPos = e->getOrig()->getId() == curIndex ? e->getDest()->getId() : e->getOrig()->getId();
        if (!nodes[nextPos]->isVisited()){
            nodes[nextPos]->setVisited(true);
            paths[nextPos] = paths[curIndex];
            paths[nextPos].push_back(nextPos);

            Backtracking_aux(nextPos, count + 1, cost + e->getDistance(), ans, path, paths);
            nodes[nextPos]->setVisited(false);
        }
    }
}

vector<unsigned int> Graph::Backtracking_TSP(double* distance) {
    resetNodes();
    nodes[0]->setVisited(true);

    double shortestDistance = std::numeric_limits<double>::max();
    vector<vector<unsigned int>> paths(nodes.size());
    vector<unsigned int> path(nodes.size());
    paths[0].push_back(0);

    Backtracking_aux(0, 1, 0, shortestDistance, path, paths);

    path.push_back(0);
    *distance = shortestDistance;

    return path;
}

vector<Node*> Graph::dfsTriangular(Node* node){
    node->setVisited(true);
    vector<Node*> path = {node};

    for (Edge* edge : node->getAdj()) {
        if (edge->isSelected()) {
            Node* dest = edge->getDest();
            if (!dest->isVisited()) {
                vector<Node*> subpath = dfsTriangular(dest);
                path.insert(path.end(), subpath.begin(), subpath.end());
            }
        }
    }

    return path;
}

vector<Node*> Graph::tspTriangular(double* distance){
    primMST();

    vector<Node*> H = dfsTriangular(nodes[0]);
    H.push_back(nodes[0]);

    *distance = 0;
    for(int i = 0; i < H.size()-1; i++){
        Node* source = H[i];
        Node* dest = H[i+1];
        *distance += source->getDistanceTo(dest);
    }
    return H;
}

vector<unsigned int> Graph::insertion_TSP(double* distance) {
    vector<unsigned int> path;
    path.push_back(0);

    unsigned int bestPos = 0;
    double bestCost = numeric_limits<double>::max();

    for (unsigned int i = 1; i < nodes.size(); i++) {
        double cost = nodes[0]->getDistanceTo(nodes[i]);
        if (cost < bestCost) {
            bestCost = cost;
            bestPos = i;
        }
    }

    path.push_back(bestPos);

    while (path.size() < nodes.size()) {
        bestPos = 0;
        bestCost = numeric_limits<double>::max();

        for (unsigned int k = 0; k < nodes.size(); k++) {
            if (find(path.begin(), path.end(), k) == path.end()) {
                double nearestDist = numeric_limits<double>::max();

                for (unsigned int j = 0; j < path.size(); j++) {
                    double dist = nodes[path[j]]->getDistanceTo(nodes[k]);
                    if (dist < nearestDist) {
                        nearestDist = dist;
                        bestPos = k;
                    }
                }

                if (nearestDist < bestCost) {
                    bestCost = nearestDist;
                }
            }
        }

        unsigned int insertionIndex = 0;
        double minInsertionCost = numeric_limits<double>::max();

        for (unsigned int i = 0; i < path.size() - 1; i++) {
            unsigned int j = i + 1;
            double insertionCost = nodes[path[i]]->getDistanceTo(nodes[bestPos]) +
                                   nodes[bestPos]->getDistanceTo(nodes[path[j]]) -
                                   nodes[path[i]]->getDistanceTo(nodes[path[j]]);
            if (insertionCost < minInsertionCost) {
                minInsertionCost = insertionCost;
                insertionIndex = j;
            }
        }

        path.insert(path.begin() + insertionIndex, bestPos);
    }

    path.push_back(0);
    *distance = 0;

    for (unsigned int i = 0; i < path.size() - 1; i++) {
        *distance += nodes[path[i]]->getDistanceTo(nodes[path[i + 1]]);
    }

    return path;
}


void Graph::clear() {
    for(Node* node : nodes){
        delete node;
    }
    nodes.clear();
}

Graph::~Graph() {
    for(auto node : nodes){
        delete node;
    }
}

void Graph::resetNodes() {
    for (Node* node : nodes) {
        node->setVisited(false);
    }
}
