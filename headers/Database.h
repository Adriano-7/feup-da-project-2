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
    bool loadSmall(string path);
    bool loadMedium(const string& nodesPath, const string& edgesPath);
    bool loadExtra(string path);

    vector<unsigned int> backtracking(double* distance);
    vector<Node*> triangular(double* distance);
    vector<unsigned int> insertionHeuristic_TSP(double* distance);

    bool isToyGraph();

    void printGraph();
    void clear();
private:
    Graph graph;
};


#endif //INC_2ND_PROJECT_DATABASE_H
