#include "NodeEdge.h"

/************************* Node  **************************/

Node::Node(int id){
    this->id = id;
    this->latitude = -1;
    this->longitude = -1;
}

Node::Node(int id, double latitude, double longitude){
    this->id = id;
    this->latitude = latitude;
    this->longitude = longitude;
}

bool Node::operator<(Node & node) const{
    return this->distance < node.distance;
}

bool Node::isVisited(){
    return visited;
}


double Node::getLatitude(){
    return latitude;
}

double Node::getLongitude(){
    return longitude;
}


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

Edge* Node::getEdgeTo(int v){
    for(Edge* edge : adj){
        if(edge->getDest()->getId() == v){
            return edge;
        }
    }
    return nullptr;
}

int Node::getId(){
    return id;
}

vector<Edge *> Node::getAdj(){
    return adj;
}

void Node::setVisited(bool visited){
    this->visited = visited;
}

Edge *Node::addEdge(Node *dest, double distance){
    Edge *edge = new Edge(this, dest, distance);
    adj.push_back(edge);
    dest->incoming.push_back(edge);
    return edge;
}

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


Edge::Edge(Node *orig, Node *dest, double distance): orig(orig), dest(dest), distance(distance) {}

Node* Edge::getDest() const{return this->dest;}

double Edge::getDistance() const {return this->distance;}

Node* Edge::getOrig() const{
    return this->orig;
}

Edge* Edge::getReverse(){
    return this->reverse;
}

void Edge::setReverse(Edge* reverse) {
    this->reverse = reverse;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

bool Edge::isSelected() {
    return this->selected;
}

bool Edge::operator<(Edge& edge){
    return this->distance < edge.distance;
}
