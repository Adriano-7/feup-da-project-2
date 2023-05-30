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
    Edge *addEdge(Node *dest, double distance);
    bool removeEdgeTo(Node *dest);
    int getId();
    vector<Edge *> getAdj() const;


    unsigned int getDistanceToAdjacentNode(unsigned int i);

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
    Edge(Node *orig, Node *dest, double distance);

    Node* getDest() const;
    double getDistance() const;
    Node* getOrig() const;
    Edge* getReverse();

    void setDistance(double distance);
    void setReverse(Edge *reverse);

    bool operator<(Edge& edge);

private:
    Node * dest;
    double distance;

    bool selected = false;

    Edge *reverse = nullptr;
    Node *orig;
};



#endif 
