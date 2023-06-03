#include "NodeEdge.h"

/************************* Node  **************************/

/**
 * @brief Constructs a node with the given ID.
 * @param id The ID of the node.
 * @details Time Complexity: O(1)
 */
Node::Node(int id){
    this->id = id;
    this->latitude = -1;
    this->longitude = -1;
}

/**
 * @brief Constructs a node with the given ID, latitude, and longitude.
 * @param id The ID of the node.
 * @param latitude The latitude coordinate of the node.
 * @param longitude The longitude coordinate of the node.
 * @details Time Complexity: O(1)
 */
Node::Node(int id, double latitude, double longitude){
    this->id = id;
    this->latitude = latitude;
    this->longitude = longitude;
}

/**
 * @brief Overloaded less than operator for comparing nodes based on distance.
 * @param node The node to compare with.
 * @return True if this node's distance is less than the other node's distance, False otherwise.
 * @details Time Complexity: O(1)
 */
bool Node::operator<(Node & node) const{
    return this->distance < node.distance;
}

/**
 * @brief Checks if the node has been visited.
 * @return True if the node has been visited, False otherwise.
 * @details Time Complexity: O(1)
 */
bool Node::isVisited(){
    return visited;
}


/**
 * @brief Gets the latitude coordinate of the node.
 * @return The latitude coordinate of the node.
 * @details Time Complexity: O(1)
 */
double Node::getLatitude(){
    return latitude;
}

/**
 * @brief Gets the longitude coordinate of the node.
 * @return The longitude coordinate of the node.
 * @details Time Complexity: O(1)
 */
double Node::getLongitude(){
    return longitude;
}

/**
 * @brief Gets the distance to a specified node.
 * @param node The node to calculate the distance to.
 * @return The distance to the specified node.
 *
 * @details Time Complexity: O(1)
 */
double Node::getDistanceTo(Node* node){
    Edge* edge = getEdgeTo(node->getId());

    if(edge != nullptr){
        return edge->getDistance();
    }
    else if(this->latitude != -1 && this->longitude != -1 && node->getLatitude() != -1 && node->getLongitude() != -1){
        return haversineDistance(this, node);
    }

    return 0;
}

/**
 * @brief Gets the edge to a specified node.
 * @param v The ID of the destination node.
 * @return The edge to the specified node, or nullptr if no edge is found.
 *
 * @details Time Complexity: O(E), where E is the number of edges.
 */
Edge* Node::getEdgeTo(int v){
    for(Edge* edge : adj){
        if(edge->getDest()->getId() == v){
            return edge;
        }
    }
    return nullptr;
}


/**
 * @brief Gets the ID of the node.
 * @return The ID of the node.
 * @details Time Complexity: O(1)
 */
int Node::getId(){
    return id;
}

/**
 * @brief Gets the adjacent edges of the node.
 * @return A vector of adjacent edges.
 * @details Time Complexity: O(1)
 */
vector<Edge *> Node::getAdj(){
    return adj;
}

/**
 * @brief Sets the visited flag of the node.
 * @param visited The value to set the visited flag to.
 * @details Time Complexity: O(1)
 */
void Node::setVisited(bool visited){
    this->visited = visited;
}

/**
 * @brief Adds an edge to the node.
 * @param dest The destination node of the edge.
 * @param distance The distance of the edge.
 * @return The added edge.
 *
 * @details Time Complexity: O(1)
 */
Edge *Node::addEdge(Node *dest, double distance){
    Edge *edge = new Edge(this, dest, distance);
    adj.push_back(edge);
    dest->incoming.push_back(edge);
    return edge;
}

/**
 * @brief Calculates the haversine distance between two nodes.
 * @param source The source node.
 * @param dest The destination node.
 * @return The haversine distance between the two nodes.
 *
 * @details Time Complexity: O(1)
 */
double Node::haversineDistance(Node* source, Node* dest) {
    if(source->getLatitude()==-1 || source->getLongitude()==-1 || dest->getLatitude()==-1 || dest->getLongitude()==-1)
        return 0;

    double lat1 = source->getLatitude() * M_PI / 180.0;
    double lon1 = source->getLongitude() * M_PI / 180.0;
    double lat2 = dest->getLatitude() * M_PI / 180.0;
    double lon2 = dest->getLongitude() * M_PI / 180.0;

    double delta_lat = lat2 - lat1;
    double delta_lon = lon2 - lon1;

    double aux = sin(delta_lat/2) * sin(delta_lat/2) + cos(lat1) * cos(lat2) * sin(delta_lon/2) * sin(delta_lon/2);
    double c = 2.0 * atan2(sqrt(aux), sqrt(1.0-aux));
    return 6371000 * c;
}

/********************** Edge  ****************************/

/**
 * @brief Constructs an edge with the given origin, destination, and distance.
 * @param orig The origin node of the edge.
 * @param dest The destination node of the edge.
 * @param distance The distance of the edge.
 * 
 * @details Time Complexity: O(1)
 */
Edge::Edge(Node* orig, Node* dest, double distance): orig(orig), dest(dest), distance(distance) {}


/**
 * @brief Gets the destination node of the edge.
 * @return The destination node.
 * @details Time Complexity: O(1)
 */
Node* Edge::getDest() const{return this->dest;}

/**
 * @brief Gets the distance of the edge.
 * @return The distance of the edge.
 * @details Time Complexity: O(1)
 */
double Edge::getDistance() const {return this->distance;}

/**
 * @brief Gets the origin node of the edge.
 * @return The origin node.
 * @details Time Complexity: O(1)
 */
Node* Edge::getOrig() const{
    return this->orig;
}

/**
 * @brief Gets the reverse edge of the edge.
 * @return The reverse edge.
 * @details Time Complexity: O(1)
 */
Edge* Edge::getReverse(){
    return this->reverse;
}

/**
 * @brief Sets the reverse edge of the edge.
 * @param reverse The reverse edge to set.
 * @details Time Complexity: O(1)
 */
void Edge::setReverse(Edge* reverse) {
    this->reverse = reverse;
}

/**
 * @brief Sets the selected flag of the edge.
 * @param selected The value to set the selected flag to.
 * @details Time Complexity: O(1)
 */
void Edge::setSelected(bool selected) {
    this->selected = selected;
}

/**
 * @brief Checks if the edge is selected.
 * @return True if the edge is selected, False otherwise.
 * @details Time Complexity: O(1)
 */
bool Edge::isSelected() {
    return this->selected;
}

/**
 * @brief Overloaded less than operator for comparing edges based on distance.
 * @param edge The edge to compare with.
 * @return True if this edge's distance is less than the other edge's distance, False otherwise.
 * @details Time Complexity: O(1)
 */
bool Edge::operator<(Edge& edge){
    return this->distance < edge.distance;
}
