#ifndef INC_2ND_PROJECT_DATABASE_H
#define INC_2ND_PROJECT_DATABASE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "../data_structures/Graph.h"
#include "../data_structures/NodeEdge.h"

using namespace std;

class Database {
public:
    void loadSmall(string path, int nNodes);
    void loadMedium(string nodesPath, string edgesPath);
    void loadExtra(string path, int numEdges);

    bool nodeExists(int id);

    pair<double, vector<unsigned int>> backtracking();
    vector<int> triangular(int source, int destination, int* distance);
    vector<int> specialHeuristic(int source, int destination, int* distance);

    void printGraph();

private:
    Graph graph;
};


#endif //INC_2ND_PROJECT_DATABASE_H
