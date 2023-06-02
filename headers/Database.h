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

using namespace std;

class Database {
public:
    bool loadSmall(string path);
    bool loadMedium(const string& nodesPath, const string& edgesPath);
    bool loadExtra(string path);

    bool nodeExists(int id);

    pair<double, vector<unsigned int>> backtracking();
    vector<Node*> triangular(double* distance);
    vector<int> specialHeuristic(double* distance);

    void printGraph();
    void drawProgressBar(int progress, int fileSize);
    pair<int, vector<unsigned int>> insertionHeuristic_TSP();


        void clear();
private:
    Graph graph;
};


#endif //INC_2ND_PROJECT_DATABASE_H
