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

using namespace std;

class Database {
public:
    void loadSmall(string path, int nNodes);
    bool loadMedium(const string& nodesPath, const string& edgesPath);
    void loadExtra(string path, int numEdges);

    bool nodeExists(int id);

    vector<int> backtracking(int origin, int dest, int* distance);
    vector<int> triangular(int source, int destination, double* distance);
    vector<int> specialHeuristic(int source, int destination, int* distance);

    void printGraph();
    void drawProgressBar(int progress, int fileSize);

private:
    Graph graph;
};


#endif //INC_2ND_PROJECT_DATABASE_H
