#ifndef PROJECT_DA_NODEEDGE_H
#define PROJECT_DA_NODEEDGE_H

#include <vector>

using namespace std;

class Edge;

class Node{
public:
    Node(int id);
    Node(int id, double latitude, double longitude);

    vector<Edge *> getAdj();
    bool isVisited();
    double getDistance();
    Edge *getPath();
    vector<Edge *> getIncoming();

    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setDistance(double distance);
    void setPath(Edge *path);
    Edge *addEdge(Node *dest, int distance);
    bool removeEdgeTo(Node *dest);

private:
    int id;
    double latitude;
    double longitude;
    vector<Edge *> adj;

    bool visited = false;
    double distance = 0;
    Edge *path = nullptr;

    vector<Edge *> incoming;
};

class Edge {
public:
    Edge(Node *orig, Node *dest, int distance);

    Node* getDest();
    int getDistance();
    Node* getOrig();
    Edge* getReverse();

    void setDistance(int distance);
    void setReverse(Edge *reverse);

    bool operator<(Edge& edge);

private:
    Node * dest;
    int distance;

    bool selected = false;

    Edge *reverse = nullptr;
    Node *orig;
};



#endif 
