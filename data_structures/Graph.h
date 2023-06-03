#ifndef PROJECT_DA_GRAPH_H
#define PROJECT_DA_GRAPH_H

#include <string>
#include <vector>
#include <sstream>
#include <limits>

#include <functional>
#include <queue>

#include <stack>
#include <unordered_set>

#include "NodeEdge.h"
using namespace std;

/**
 * @class Graph
 * @brief Represents a graph data structure.
 */
class Graph {
public:
    /**
     * @brief Adds a node to the graph.
     *
     * @param id The ID of the node.
     * @return True if the node is added successfully, false otherwise.
     */
    bool addNode(int id);

    /**
     * @brief Adds a node with latitude and longitude to the graph.
     *
     * @param id The ID of the node.
     * @param latitude The latitude of the node.
     * @param longitude The longitude of the node.
     * @return True if the node is added successfully, false otherwise.
     */
    bool addNode(int id, double latitude, double longitude);

    /**
     * @brief Adds an edge between two nodes in the graph.
     *
     * @param source The source node of the edge.
     * @param dest The destination node of the edge.
     * @param distance The distance between the nodes.
     * @return True if the edge is added successfully, false otherwise.
     */
    bool addEdge(Node* source, Node* dest, double distance);

    /**
     * @brief Retrieves a node with the specified ID.
     *
     * @param id The ID of the node to retrieve.
     * @return A pointer to the node if found, nullptr otherwise.
     */
    Node* getNode(int id);

    /**
     * @brief Retrieves all the nodes in the graph.
     *
     * @return A vector containing all the nodes in the graph.
     */
    vector<Node*> getNodes();

    /**
     * @brief Implements Prim's algorithm for finding the Minimum Spanning Tree (MST) of the graph.
     */
    void primMST();

    /**
     * @brief Performs a depth-first search (DFS) traversal to find a triangular path in the graph.
     *
     * @param node The starting node for the DFS traversal.
     * @return A vector containing the nodes in the triangular path.
     */
    vector<Node*> dfsTriangular(Node* node);

    /**
     * @brief Solves the Traveling Salesman Problem (TSP) using the triangular inequality heuristic.
     *        It first constructs the Minimum Spanning Tree (MST) using Prim's algorithm,
     *        then performs a depth-first search (DFS) to find a triangular path,
     *        and calculates the total distance of the path.
     *
     * @param distance A pointer to a variable to store the total distance of the triangular path.
     * @return A vector containing the nodes in the triangular path.
     */
    vector<Node*> tspTriangular(double* distance);

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
     */
    void Backtracking_aux(unsigned int curIndex, unsigned int count, double cost, double& ans,
                          vector<unsigned int>& path, vector<vector<unsigned int>> paths);

    /**
     * @brief Solves the Traveling Salesman Problem (TSP) using the backtracking algorithm.
     *        It finds the shortest Hamiltonian cycle in the graph by performing backtracking.
     *
     * @return A pair consisting of the shortest distance and the path representing the cycle.
     */
    pair<double, vector<unsigned int>> Backtracking_TSP();

    /**
     * @brief Clears the graph by deleting all nodes and edges.
     */
    void clear();

    /**
     * @brief Destructor for the Graph class.
     *        Deletes all the nodes in the graph.
     */
    ~Graph();

private:
    vector<Node*> nodes; /**< The vector containing all the nodes in the graph. */

    /**
     * @brief Resets the 'visited' flag of all nodes in the graph to false.
     */
    void resetNodes();
};

#endif
