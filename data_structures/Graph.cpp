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


double Graph::haversineDistance(Node* source, Node* dest) {
    if(source->getLatitude()==-1 || source->getLongitude()==-1 || dest->getLatitude()==-1 || dest->getLongitude()==-1)
        return 0;

    double lat1 = source->getLatitude() * M_PI / 180.0;
    double lon1 = source->getLongitude() * M_PI / 180.0;
    double lat2 = dest->getLatitude() * M_PI / 180.0;
    double lon2 = dest->getLongitude() * M_PI / 180.0;

    double a = pow(sin((lat2 - lat1) / 2), 2) + pow(sin((lon2 - lon1) / 2), 2) * cos(lat1) * cos(lat2);
    return 6371 * 2 * asin(sqrt(a));
}

void Graph::primMST() {
    MutablePriorityQueue<Node> q;
    vector<Node*> result;

    for(Node* node: nodes){
        node->setDistance(numeric_limits<double>::infinity());
        node->setPath(nullptr);
        node->setVisited(false);
        q.insert(node);
    }

    Node* start = nodes[0];
    start->setDistance(0);
    q.decreaseKey(start);

    while(!q.empty()){
        Node* node = q.extractMin();
        node->setVisited(true);
        result.push_back(node);

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

    for(Node* node : nodes){
        node->setVisited(false);
    }
}


vector<Node*> Graph::dfsTriangular(Node* node) {
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
    // Step 1:  Compute a minimum spanning tree T for G from root r
    primMST();

    //Step 2: let H be a list of vertices, ordered according to when they are first visited in a preorder tree walk of T
    vector<Node*> H = dfsTriangular(nodes[0]);
    H.push_back(nodes[0]);

    //Step 3: return the hamiltonian cycle H. The cost of H is the sum of the edge costs in T (if there are no edges connecting one node to another, the cost is the haverside distance between them)
    *distance = 0;
    for(int i=0; i<H.size()-1; i++){
        Node* source = H[i];
        Node* dest = H[i+1];

        Edge* edge = source->getSelectedEdgeTo(dest->getId());
        if(edge != nullptr){
            *distance += edge->getDistance();
        }
        else{
            *distance += haversineDistance(source, dest);
        }
    }

    return H;
}

Node* Graph::getNode(int id){
    if(id>=0 && id<nodes.size()) return nodes[id];

    return nullptr;
}

vector<Node*> Graph::getNodes(){
    return nodes;
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

pair<double, vector<unsigned int>> Graph::Backtracking_TSP(){
    resetNodes();
    nodes[0]->setVisited(true);

    double shortestDistance = std::numeric_limits<double>::max();
    vector<vector<unsigned int>> paths(nodes.size());
    vector<unsigned int> path(nodes.size());
    paths[0].push_back(0);

    Backtracking_aux(0, 1, 0, shortestDistance, path, paths);

    path.push_back(0);

    return make_pair(shortestDistance, path);
}

void Graph::resetNodes() {
    for (Node* node : nodes) {
        node->setVisited(false);
    }

}