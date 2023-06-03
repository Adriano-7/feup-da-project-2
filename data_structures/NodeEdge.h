#ifndef PROJECT_DA_NODEEDGE_H
#define PROJECT_DA_NODEEDGE_H

#include <vector>
#include <math.h>

using namespace std;

class Edge;

/**
 * @class Node
 * @brief Represents a node in a graph.
 */
class Node {
public:
    Node(int id);
    Node(int id, double latitude, double longitude);

    bool operator<(Node & node) const;

    bool isVisited();

    double getLatitude();
    double getLongitude();
    double getDistanceTo(Node* node);
    Edge* getEdgeTo(int v);
    int getId();
    vector<Edge *> getAdj();

    void setVisited(bool visited);
    Edge *addEdge(Node *dest, double distance);

    double haversineDistance(Node* source, Node* dest);

private:
    int id;
    double latitude;
    double longitude;
    vector<Edge *> adj;

    bool visited = false;
    double distance = 0;

    vector<Edge *> incoming;
};

/**
 * @class Edge
 * @brief Represents an edge in a graph.
 */
class Edge {
public:
    Edge(Node *orig, Node *dest, double distance);

    Node* getDest() const;
    double getDistance() const;
    Node* getOrig() const;
    Edge* getReverse();

    void setReverse(Edge *reverse);
    void setSelected(bool selected);

    bool isSelected();

    bool operator<(Edge& edge);

private:
    Node * dest;
    double distance;

    bool selected = false;

    Edge *reverse = nullptr;
    Node *orig;
};



#endif