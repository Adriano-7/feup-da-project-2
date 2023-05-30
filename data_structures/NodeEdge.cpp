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

vector<Edge *> Node::getAdj(){
    return adj;
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

void Node::setVisited(bool visited){
    this->visited = visited;
}

void Node::setDistance(double distance){
    this->distance = distance;
}

void Edge::setReverse(Edge* reverse) {
    this->reverse = reverse;
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

void Edge::setDistance(double distance){
    this->distance = distance;
}

bool Edge::operator<(Edge& edge){
    return this->distance < edge.distance;
}
