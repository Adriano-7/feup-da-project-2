#ifndef INC_2ND_PROJECT_DATABASE_H
#define INC_2ND_PROJECT_DATABASE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include <fstream>
#include <iostream>
#include <filesystem>

#include "../data_structures/Graph.h"
#include "../data_structures/NodeEdge.h"
#include <limits>

/**
 * @class Database
 *
 * @brief Class responsible for managing the graph database.
 */
class Database {
public:
    /**
     * Loads a small size graph from the specified path.
     *
     * @param path The path to the graph file.
     * @return True if the graph is loaded successfully, false otherwise.
     */
    bool loadSmall(std::string path);

    /**
     * Loads a medium/large size graph from the specified nodes and edges files.
     *
     * @param nodesPath The path to the nodes file.
     * @param edgesPath The path to the edges file.
     * @return True if the graph is loaded successfully, false otherwise.
     */
    bool loadMedium(const std::string& nodesPath, const std::string& edgesPath);

    /**
     * Loads an extra connected graph from the specified path.
     *
     * @param path The path to the graph file.
     * @return True if the graph is loaded successfully, false otherwise.
     */
    bool loadExtra(std::string path);

    /**
     * Checks if a node with the given ID exists in the graph.
     *
     * @param id The ID of the node.
     * @return True if the node exists, false otherwise.
     */
    bool nodeExists(int id);

    /**
     * Computes the shortest path using the Backtracking TSP algorithm.
     *
     * @return A pair containing the distance and the sequence of node IDs representing the shortest path.
     */
    std::pair<double, std::vector<unsigned int>> backtracking();

    /**
     * Computes the shortest path using the triangular approximation heuristic.
     *
     * @param distance Pointer to store the computed distance.
     * @return A vector of Node pointers representing the shortest path.
     */
    std::vector<Node*> triangular(double* distance);

    /**
     * Computes the shortest path using a special heuristic.
     *
     * @param distance Pointer to store the computed distance.
     * @return A vector of integers representing the shortest path.
     */
    std::vector<int> specialHeuristic(double* distance);

    /**
     * Prints the graph.
     */
    void printGraph();

    /**
     * Draws a progress bar based on the given progress and file size.
     *
     * @param progress The current progress.
     * @param fileSize The size of the file.
     */
    void drawProgressBar(int progress, int fileSize);

    /**
     * Clears the graph database.
     */
    void clear();

private:
    Graph graph;
};

#endif // INC_2ND_PROJECT_DATABASE_H
