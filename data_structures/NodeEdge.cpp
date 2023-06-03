#include "NodeEdge.h"

/************************* Node  **************************/

/**
 * @brief Constructs a node with the given ID.
 * @param id The ID of the node.
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
 */
bool Node::operator<(Node & node) const{
    return this->distance < node.distance;
}

/**
 * @brief Gets the adjacent edges of the node.
 * @return A vector of adjacent edges.
 */
vector<Edge *> Node::getAdj(){
    return adj;
}

/**
 * @brief Checks if the node has been visited.
 * @return True if the node has been visited, False otherwise.
 */
bool Node::isVisited(){
    return visited;
}

/**
 * @brief Gets the distance of the node from a source node.
 * @return The distance of the node.
 */
double Node::getDistance(){
    return distance;
}

/**
 * @brief Gets the ID of the node.
 * @return The ID of the node.
 */
int Node::getId(){
    return id;
}

/**
 * @brief Gets the path to the node.
 * @return The path to the node.
 */
Edge *Node::getPath(){
    return path;
}

/**
 * @brief Gets the incoming edges to the node.
 * @return A vector of incoming edges.
 */
vector<Edge *> Node::getIncoming(){
    return incoming;
}

/**
 * @brief Gets the latitude coordinate of the node.
 * @return The latitude coordinate of the node.
 */
double Node::getLatitude(){
    return latitude;
}

/**
 * @brief Gets the longitude coordinate of the node.
 * @return The longitude coordinate of the node.
 */
double Node::getLongitude(){
    return longitude;
}

/**
 * @brief Calculates the haversine distance between two nodes.
 * @param source The source node.
 * @param dest The destination node.
 * @return The haversine distance between the two nodes.
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

/**
 * @brief Gets the distance to a specified node.
 * @param node The node to calculate the distance to.
 * @return The distance to the specified node.
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
 * @brief Static function to compare nodes based on distance in ascending order.
 * @param a The first node.
 * @param b The second node.
 * @return True if the distance of node a is less than the distance of node b, False otherwise.
 */
static bool ascendingDistance(Node* a, Node* b) {
    return a->getDistance() < b->getDistance();
}

/**
 * @brief Gets the selected edge to a specified node.
 * @param v The ID of the destination node.
 * @return The selected edge to the specified node, or nullptr if no edge is found.
 */
Edge* Node::getSelectedEdgeTo(int v){
    for(Edge* edge : adj){
        if(edge->getDest()->getId() == v && edge->isSelected()){
            return edge;
        }
    }
    return nullptr;
}

/**
 * @brief Gets the edge to a specified node.
 * @param v The ID of the destination node.
 * @return The edge to the specified node, or nullptr if no edge is found.
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
 * @brief Sets the visited flag of the node.
 * @param visited The value to set the visited flag to.
 */
void Node::setVisited(bool visited){
    this->visited = visited;
}

/**
 * @brief Sets the distance of the node from a source node.
 * @param distance The distance to set.
 */
void Node::setDistance(double distance){
    this->distance = distance;
}

/**
 * @brief Sets the reverse edge of the edge.
 * @param reverse The reverse edge to set.
 */
void Edge::setReverse(Edge* reverse) {
    this->reverse = reverse;
}

/**
 * @brief Sets the selected flag of the edge.
 * @param selected The value to set the selected flag to.
 */
void Edge::setSelected(bool selected) {
    this->selected = selected;
}


/**
 * @brief Sets the path to the node.
 * @param path The path to set.
 */
void Node::setPath(Edge *path){
    this->path = path;
}

/**
 * @brief Adds an edge to the node.
 * @param dest The destination node of the edge.
 * @param distance The distance of the edge.
 * @return The added edge.
 */
Edge *Node::addEdge(Node *dest, double distance){
    Edge *edge = new Edge(this, dest, distance);
    adj.push_back(edge);
    dest->incoming.push_back(edge);
    return edge;
}

/**
 * @brief Removes an edge to a specified node.
 * @param dest The destination node of the edge to remove.
 * @return True if the edge was successfully removed, False otherwise.
 */
bool Node::removeEdgeTo(Node *dest){
    for (auto it = adj.begin(); it != adj.end(); it++){
        if ((*it)->getDest() == dest){
            adj.erase(it);
            return true;
        }
    }
    return false;
}

/**
 * @brief Gets the distance to an adjacent node.
 * @param i The ID of the adjacent node.
 * @return The distance to the adjacent node, or 0 if no adjacent node is found.
 */
unsigned int Node::getDistanceToAdjacentNode(unsigned int i) {
    for (int i = 0; i < this->adj.size(); i++) {
        if (this->adj.at(i)->getDest()->getId() == i) {
            return this->adj.at(i)->getDistance();
        }
    }
    return 0;
}


/********************** Edge  ****************************/

/**
 * @brief Constructs an edge with the given origin, destination, and distance.
 * @param orig The origin node of the edge.
 * @param dest The destination node of the edge.
 * @param distance The distance of the edge.
 */
Edge::Edge(Node* orig, Node* dest, double distance): orig(orig), dest(dest), distance(distance) {}


/**
 * @brief Gets the destination node of the edge.
 * @return The destination node.
 */
Node* Edge::getDest() const{return this->dest;}

/**
 * @brief Gets the distance of the edge.
 * @return The distance of the edge.
 */
double Edge::getDistance() const {return this->distance;}

/**
 * @brief Gets the origin node of the edge.
 * @return The origin node.
 */
Node* Edge::getOrig() const{
    return this->orig;
}

/**
 * @brief Gets the reverse edge of the edge.
 * @return The reverse edge.
 */
Edge* Edge::getReverse(){
    return this->reverse;
}

/**
 * @brief Checks if the edge is selected.
 * @return True if the edge is selected, False otherwise.
 */
bool Edge::isSelected() {
    return this->selected;
}

/**
 * @brief Sets the distance of the edge.
 * @param distance The distance to set.
 */
void Edge::setDistance(double distance){
    this->distance = distance;
}

/**
 * @brief Overloaded less than operator for comparing edges based on distance.
 * @param edge The edge to compare with.
 * @return True if this edge's distance is less than the other edge's distance, False otherwise.
 */
bool Edge::operator<(Edge& edge){
    return this->distance < edge.distance;
}
