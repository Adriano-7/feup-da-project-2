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

void Node::setPath(Edge *path){
    this->path = path;
}

Edge *Node::addEdge(Node *dest, int distance){
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


/********************** Edge  ****************************/


Edge::Edge(Node *orig, Node *dest, int distance): orig(orig), dest(dest), distance(distance) {}

Node* Edge::getDest(){return this->dest;}

int Edge::getDistance() {return this->distance;}

Node* Edge::getOrig(){
    return this->orig;
}

Edge* Edge::getReverse(){
    return this->reverse;
}

void Edge::setDistance(int distance){
    this->distance = distance;
}

bool Edge::operator<(Edge& edge){
    return this->distance < edge.distance;
}
