#ifndef INC_2ND_PROJECT_DATABASE_H
#define INC_2ND_PROJECT_DATABASE_H

#include <iostream>
#include <vector>

using namespace std;

class Database {
public:
    void loadSmall(string path);
    void loadMedium(string nodesPath, string edgesPath);
    void loadExtra(string path, int numEdges);

    bool nodeExists(int id);

    vector<int> backtracking(int origin, int dest, int* distance);
    vector<int> triangular(int source, int destination, int* distance);
    vector<int> specialHeuristic(int source, int destination, int* distance);
};


#endif //INC_2ND_PROJECT_DATABASE_H
