#include <algorithm>
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

vector<Node*> Graph::dfsTest(){
    for(Node* v: nodes) {v->setVisited(false);}

    nodes[0]->setVisited(true);
    vector<Node*> path = {nodes[0]};

    for(Edge* edge: nodes[0]->getAdjMst()){
        Node* dest = edge->getDest();
        if(!dest->isVisited()){
            vector<Node*> subpath = dfsTriangular(dest);
            path.insert(path.end(), subpath.begin(), subpath.end());
        }
    }

    return path;
}

vector<Node*> Graph::dfsKruskalPath(Node *node) {
    node->setVisited(true);
    vector<Node*> path = {node};

    for (Edge* edge : node->getAdj()) {
        Node* adj = edge->getDest();

        if (edge->isSelected() && !adj->isVisited()) {
            adj->setPath(edge);

            vector<Node*> subpath = dfsKruskalPath(adj);
            path.insert(path.end(), subpath.begin(), subpath.end());
        }
    }

    return path;
}

vector<Node *> Graph::kruskal() {
    if(nodes.empty()) return nodes;

    UFDS ufds = UFDS(nodes.size());

    vector<Edge *> edges;
    for(Node* v: nodes){
        for(Edge* e: v->getAdj()){
            e->setSelected(false);
            if(e->getOrig()->getId() < e->getDest()->getId())
                edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end(), [](Edge* e1, Edge* e2){return e1->getDistance() < e2->getDistance();}); //Ascending order

    int selectedEdges = 0; //To obtain a ST we need to select n-1 edges
    for(Edge* e: edges){
        if(selectedEdges == nodes.size()-1) break;

        Node* origin = e->getOrig();
        Node* dest = e->getDest();
        if(!ufds.isSameSet(origin->getId(), dest->getId())){
            ufds.linkSets(origin->getId(), dest->getId());
            e->setSelected(true);
            origin->addMstEdge(e);
            e->getReverse()->setSelected(true);
            dest->addMstEdge(e->getReverse());
            selectedEdges++;
        }
    }

    for(Node* v: nodes) {v->setVisited(false);}
    nodes[0]->setPath(nullptr);

    return dfsKruskalPath(nodes[0]);
}



vector<Node*> Graph::tspTriangular(double* distance){

    kruskal();
    auto help = dfsTest();
    help.push_back(help[0]);

    *distance = 0;
    for(int i = 0; i < help.size()-1; i++){
        Node* source = help[i];
        Node* dest = help[i+1];
        auto hey = source->getDistanceTo(dest);
        *distance += source->getDistanceTo(dest);
    }


    return help;

    /*
    // Step 1:  Compute a minimum spanning tree T for G from root r
    primMST();

    //Step 2: let H be a list of vertices, ordered according to when they are first visited in a preorder tree walk of T
    vector<Node*> H = dfsTriangular(nodes[0]);
    H.push_back(nodes[0]);

    //Step 3: return the hamiltonian cycle H. The cost of H is the sum of the edge costs in T (if there are no edges connecting one node to another, the cost is the haverside distance between them)
    *distance = 0;
    for(int i = 0; i < H.size()-1; i++){
        Node* source = H[i];
        Node* dest = H[i+1];
        *distance += source->getDistanceTo(dest);
    }

    return H;
     */
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