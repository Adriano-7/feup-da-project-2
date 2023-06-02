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

vector<Edge *> Node::getAdj(){
    return adj;
}

void Node::addMstEdge(Edge *edge){
    adjMst.push_back(edge);
}

vector<Edge *> Node::getAdjMst(){
    return adjMst;
}


bool Node::isVisited(){
    return visited;
}

double Node::getDistance(){
    return distance;
}

int Node::getId(){
    return id;
}

Edge *Node::getPath(){
    return path;
}

vector<Edge *> Node::getIncoming(){
    return incoming;
}

double Node::getLatitude(){
    return latitude;
}

double Node::getLongitude(){
    return longitude;
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

static bool ascendingDistance(Node* a, Node* b) {
    return a->getDistance() < b->getDistance();
}

Edge* Node::getSelectedEdgeTo(int v){
    for(Edge* edge : adj){
        if(edge->getDest()->getId() == v && edge->isSelected()){
            return edge;
        }
    }
    return nullptr;
}

Edge* Node::getEdgeTo(int v){
    for(Edge* edge : adj){
        if(edge->getDest()->getId() == v){
            return edge;
        }
    }
    return nullptr;
}

void Node::setVisited(bool visited){
    this->visited = visited;
}

void Node::setDistance(double distance){
    this->distance = distance;
}

void Edge::setReverse(Edge* reverse) {
    this->reverse = reverse;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Node::setPath(Edge *path){
    this->path = path;
}

Edge *Node::addEdge(Node *dest, double distance){
    Edge *edge = new Edge(this, dest, distance);
    adj.push_back(edge);
    dest->incoming.push_back(edge);
    return edge;
}

bool Node::removeEdgeTo(Node *dest){
    for (auto it = adj.begin(); it != adj.end(); it++){
        if ((*it)->getDest() == dest){
            adj.erase(it);
            return true;
        }
    }
    return false;
}

unsigned int Node::getDistanceToAdjacentNode(unsigned int i) {
    for (int i = 0; i < this->adj.size(); i++) {
        if (this->adj.at(i)->getDest()->getId() == i) {
            return this->adj.at(i)->getDistance();
        }
    }
    return 0;
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

bool Edge::isSelected() {
    return this->selected;
}

void Edge::setDistance(double distance){
    this->distance = distance;
}

bool Edge::operator<(Edge& edge){
    return this->distance < edge.distance;
}
