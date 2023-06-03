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
    /**
     * @brief Constructs a node with the given ID.
     * @param id The ID of the node.
     */
    Node(int id);

    /**
     * @brief Constructs a node with the given ID, latitude, and longitude.
     * @param id The ID of the node.
     * @param latitude The latitude coordinate of the node.
     * @param longitude The longitude coordinate of the node.
     */
    Node(int id, double latitude, double longitude);

    /**
     * @brief Overloaded less than operator for comparing nodes based on distance.
     * @param node The node to compare with.
     * @return True if this node's distance is less than the other node's distance, False otherwise.
     */
    bool operator<(Node& node) const;

    /**
     * @brief Checks if the node has been visited.
     * @return True if the node has been visited, False otherwise.
     */
    bool isVisited();

    /**
     * @brief Gets the distance of the node from a source node.
     * @return The distance of the node.
     */
    double getDistance();

    /**
     * @brief Gets the path to the node.
     * @return The path to the node.
     */
    Edge* getPath();

    /**
     * @brief Gets the incoming edges to the node.
     * @return The vector of incoming edges.
     */
    vector<Edge*> getIncoming();

    /**
     * @brief Gets the latitude coordinate of the node.
     * @return The latitude coordinate.
     */
    double getLatitude();

    /**
     * @brief Gets the longitude coordinate of the node.
     * @return The longitude coordinate.
     */
    double getLongitude();

    /**
     * @brief Calculates the Haversine distance between two nodes.
     * @param source The source node.
     * @param dest The destination node.
     * @return The Haversine distance between the nodes.
     */
    double haversineDistance(Node* source, Node* dest);

    /**
     * @brief Gets the distance to a specified node.
     * @param node The node to calculate the distance to.
     * @return The distance to the specified node.
     */
    double getDistanceTo(Node* node);

    /**
     * @brief Compares two nodes based on their distance in ascending order.
     * @param a The first node to compare.
     * @param b The second node to compare.
     * @return True if the distance of node a is less than the distance of node b, False otherwise.
     */
    static bool ascendingDistance(Node* a, Node* b);

    /**
     * @brief Gets the edge to a specified node.
     * @param v The ID of the destination node.
     * @return The edge to the specified node, or nullptr if no edge is found.
     */
    Edge* getEdgeTo(int v);

    /**
     * @brief Gets the selected edge to a specified node.
     * @param v The ID of the destination node.
     * @return The selected edge to the specified node, or nullptr if no edge is found.
     */
    Edge* getSelectedEdgeTo(int v);

    /**
     * @brief Sets the visited flag of the node.
     * @param visited The value to set the visited flag to.
     */
    void setVisited(bool visited);

    /**
     * @brief Sets the processing flag of the node.
     * @param processing The value to set the processing flag to.
     */
    void setProcessing(bool processing);

    /**
     * @brief Sets the distance of the node.
     * @param distance The distance to set.
     */
    void setDistance(double distance);

    /**
     * @brief Sets the path to the node.
     * @param path The path to set.
     */
    void setPath(Edge* path);

    /**
     * @brief Adds an edge to the node with the specified destination and distance.
     * @param dest The destination node.
     * @param distance The distance to the destination node.
     * @return The created edge.
     */
    Edge* addEdge(Node* dest, double distance);

    /**
     * @brief Removes the edge to the specified destination node.
     * @param dest The destination node.
     * @return True if the edge was successfully removed, False otherwise.
     */
    bool removeEdgeTo(Node* dest);

    /**
     * @brief Gets the ID of the node.
     * @return The ID of the node.
     */
    int getId();

    /**
     * @brief Gets the adjacent edges of the node.
     * @return The vector of adjacent edges.
     */
    vector<Edge*> getAdj();

    int queueIndex = 0;

    /**
     * @brief Gets the distance to the adjacent node with the specified ID.
     * @param i The ID of the adjacent node.
     * @return The distance to the adjacent node, or 0 if no such node exists.
     */
    unsigned int getDistanceToAdjacentNode(unsigned int i);

private:
    int id;
    double latitude;
    double longitude;
    vector<Edge*> adj;
    bool visited = false;
    double distance = 0;
    Edge* path = nullptr;
    vector<Edge*> incoming;
};

/**
 * @class Edge
 * @brief Represents an edge in a graph.
 */
class Edge {
public:
    /**
     * @brief Constructs an edge with the given origin, destination, and distance.
     * @param orig The origin node of the edge.
     * @param dest The destination node of the edge.
     * @param distance The distance of the edge.
     */
    Edge(Node *orig, Node *dest, double distance);

    /**
     * @brief Gets the destination node of the edge.
     * @return The destination node.
     */
    Node *getDest() const;

    /**
     * @brief Gets the distance of the edge.
     * @return The distance of the edge.
     */
    double getDistance() const;

    /**
     * @brief Gets the origin node of the edge.
     * @return The origin node.
     */
    Node *getOrig() const;

    /**
     * @brief Gets the reverse edge of the edge.
     * @return The reverse edge.
     */
    Edge *getReverse();

    /**
     * @brief Checks if the edge is selected.
     * @return True if the edge is selected, False otherwise.
     */
    bool isSelected();

    /**
     * @brief Sets the distance of the edge.
     * @param distance The distance to set.
     */
    void setDistance(double distance);

    /**
     * @brief Sets the reverse edge of the edge.
     * @param reverse The reverse edge to set.
     */
    void setReverse(Edge *reverse);

    /**
     * @brief Sets the selected flag of the edge.
     * @param selected The value to set the selected flag to.
     */
    void setSelected(bool selected);

    /**
     * @brief Overloaded less than operator for comparing edges based on distance.
     * @param edge The edge to compare with.
     * @return True if this edge's distance is less than the other edge's distance, False otherwise.
     */
    bool operator<(Edge &edge);

private:
    /**
     * @brief The destination node of the edge.
     */
    Node* dest;

    /**
     * @brief The distance of the edge.
     */
    double distance;

    /**
     * @brief Flag indicating whether the edge is selected.
     */
    bool selected = false;

    /**
     * @brief The reverse edge of the edge.
     */
    Edge* reverse = nullptr;

    /**
     * @brief The origin node of the edge.
     */
    Node* orig;
};

#endif
