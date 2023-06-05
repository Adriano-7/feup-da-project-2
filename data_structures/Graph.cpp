#include <iostream>
#include "Graph.h"

using namespace std;

/**
 * @brief Adds a node to the graph.
 *
 * @param id The ID of the node.
 * @return True if the node is added successfully, false otherwise.
 * @details Time-Complexity: O(1)
 */
bool Graph::addNode(int id) {
    int size = nodes.size();
    if (id < size && nodes[id] != NULL)
        return false;

    for (int i = size; i <= id; i++) {
        nodes.push_back(new Node(i));
    }

    return true;
}

/**
 * @brief Adds a node with latitude and longitude to the graph.
 *
 * @param id The ID of the node.
 * @param latitude The latitude of the node.
 * @param longitude The longitude of the node.
 * @return True if the node is added successfully, false otherwise.
 * @details Time-Complexity: O(1)
 */
bool Graph::addNode(int id, double latitude, double longitude) {
    nodes.push_back(new Node(id, latitude, longitude));
    return true;
}

/**
 * @brief Adds an edge between two nodes in the graph.
 *
 * @param sourceNode The source node of the edge.
 * @param destNode The destination node of the edge.
 * @param distance The distance between the nodes.
 * @return True if the edge is added successfully, false otherwise.
 * @details Time-Complexity: O(1)
 */
bool Graph::addEdge(Node* sourceNode, Node* destNode, double distance) {
    Edge* e1 = sourceNode->addEdge(destNode, distance);
    Edge* e2 = destNode->addEdge(sourceNode, distance);

    e1->setReverse(e2);
    e2->setReverse(e1);

    return true;
}

/**
 * @brief Retrieves a node with the specified ID.
 *
 * @param id The ID of the node to retrieve.
 * @return A pointer to the node if found, nullptr otherwise.
 * @details Time-Complexity: O(1)
 */
Node* Graph::getNode(int id) {
    if (id >= 0 && id < nodes.size())
        return nodes[id];
    return nullptr;
}

/**
 * @brief Retrieves all the nodes in the graph.
 *
 * @return A vector containing all the nodes in the graph.
 * @details Time-Complexity: O(1)
 */
vector<Node*> Graph::getNodes() {
    return nodes;
}

/**
 * @brief Implements Prim's algorithm for finding the Minimum Spanning Tree (MST) of the graph.
 *        Sets the 'visited' and 'selected' flags of the edges accordingly.
 * @details Time-Complexity: O((V + E) * log V), where E is the number of edges and V is the number of vertices.
 */
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

/**
 * @brief Auxiliary function for the Backtracking_TSP algorithm.
 *        It performs backtracking to find the shortest Hamiltonian cycle in the graph.
 *
 * @param curIndex The current index of the node being processed.
 * @param count The number of nodes visited so far.
 * @param cost The current cost of the path.
 * @param ans A reference to the variable storing the shortest distance.
 * @param path A reference to the vector storing the path with the shortest distance.
 * @param paths A vector storing the paths for each node during the backtracking process.
 * @details Time-Complexity: O((V-1)!), where V is the number of vertices.
 */
void Graph::Backtracking_aux(unsigned int curIndex, unsigned int count, double cost, double &ans,
                             vector<unsigned int> &path, vector<vector<unsigned int>> paths) {
    if (count == nodes.size()){
        for (Edge* edge : nodes[curIndex]->getAdj()){
            if (edge->getOrig()->getId() == 0 || edge->getDest()->getId() == 0){
                double new_cost = cost + edge->getDistance();
                if (new_cost < ans){
                    ans = new_cost;
                    path = paths[curIndex];
                }
            }
        }
        return;
    }

    for (Edge* edge : nodes[curIndex]->getAdj()){
        int nextPos = edge->getOrig()->getId() == curIndex ? edge->getDest()->getId() : edge->getOrig()->getId();
        if (!nodes[nextPos]->isVisited()){
            nodes[nextPos]->setVisited(true);
            paths[nextPos] = paths[curIndex];
            paths[nextPos].push_back(nextPos);

            Backtracking_aux(nextPos, count + 1, cost + edge->getDistance(), ans, path, paths);
            nodes[nextPos]->setVisited(false);
        }
    }
}

/**
 * @brief Solves the Traveling Salesman Problem (TSP) using the backtracking algorithm.
 *        It finds the shortest Hamiltonian cycle in the graph by performing backtracking.
 *
 * @param distance A pointer to a variable to store the total distance of the cycle.
 * @return A vector containing the indices of the nodes in the cycle.
 * @details Time-Complexity: O((V-1)!), where V is the number of vertices.
 */
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

/**
 * @brief Performs a depth-first search (DFS) traversal to find a triangular path in the graph.
 *
 * @param node The starting node for the DFS traversal.
 * @return A vector containing the nodes in the triangular path.
 * @details Time-Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
 */
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

/**
 * @brief Solves the Traveling Salesman Problem (TSP) using the triangular inequality heuristic.
 *        It first constructs the Minimum Spanning Tree (MST) using Prim's algorithm,
 *        then performs a depth-first search (DFS) to find a triangular path,
 *        and calculates the total distance of the path.
 *
 * @param distance A pointer to a variable to store the total distance of the triangular path.
 * @return A vector containing the nodes in the triangular path.
 * @details Time-Complexity: O(V^2), where V is the number of vertices.
 */
vector<Node*> Graph::tspTriangular(double* distance) {
    primMST();

    vector<Node*> H = dfsTriangular(nodes[0]);
    H.push_back(nodes[0]);

    *distance = 0;
    for (int i = 0; i < H.size() - 1; i++) {
        Node* source = H[i];
        Node* dest = H[i + 1];
        *distance += source->getDistanceTo(dest);
    }
    return H;
}

/**
 * @brief Solves the Traveling Salesman Problem (TSP) using the cheapest insertion heuristic.
 *        It starts with an initial cycle containing only the starting node (0),
 *        and iteratively inserts the remaining nodes into the cycle at the position
 *        where it results in the minimum increase in total distance.
 *
 * @param distance A pointer to a variable to store the total distance of the cycle.
 * @return A vector containing the indices of the nodes in the cycle.
 * @details Time-Complexity: O(V^3), where V is the number of vertices.
 */
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

/**
 * @brief sets the type of the graph.
 * @param type The type of the graph.
 * @details time complexity: O(1)
 */
void Graph::setGraphType(GraphType type){
    this->type = type;
}

/**
 * @brief Returns the type of the graph.
 * @return The type of the graph.
 * @details time complexity: O(1)
 */
GraphType Graph::getGraphType(){
    return type;
}

/**
 * @brief Clears the graph by deleting all nodes and edges.
 * @details time complexity: O(V), where V is the number of vertices.
 */
void Graph::clear() {
    for (Node* node : nodes) {
        delete node;
    }
    nodes.clear();
}

/**
 * @brief Destructor for the Graph class.
 *        Deletes all the nodes in the graph.
 */
Graph::~Graph() {
    for (auto node : nodes) {
        delete node;
    }
}

/**
 * @brief Resets the 'visited' flag of all nodes in the graph to false.
 */
void Graph::resetNodes() {
    for (Node* node : nodes) {
        node->setVisited(false);
    }
}
