#include <limits>
#include "../headers/Database.h"

#include "../data_structures/Graph.h"


using namespace std;

/*
origem,destino,distancia
0,1,3.1
0,5,4.0
*/

void Database::loadSmall(string path, int nNodes) {
    //Initialize graph with nodes
    for (int i = 0; i < nNodes; i++) {
        graph.addNode(i);
    }

    ifstream file(path);
    file.ignore(1000, '\n'); // ignore first line

    if (!file.is_open()) {
        cout << "Error opening toy graph" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() != 3) {
            cout << "The following line is invalid: " << line << endl;
            return;
        }
        string origin_id = fields[0];
        string dest_id = fields[1];
        string distance = fields[2];

        graph.addEdge(graph.getNode(stoi(origin_id)), graph.getNode(stoi(dest_id)), stod(distance));
    }
    file.close();
}
void Database::printGraph(){
    for(auto node : graph.getNodes()){
        cout << "Node " << node->getId() << endl;
        for(auto edge : node->getAdj()){
            cout << "Edge to " << edge->getDest()->getId() << " with distance " << edge->getDistance() << endl;
        }
    }
}
void Database::loadMedium(string nodesPath, string edgesPath){;}
void Database::loadExtra(string path, int numEdges){;}
bool Database::nodeExists(int id){return true;}


pair<double, vector<unsigned int>> Database::backtracking() {
    return graph.Backtracking_TSP();
}
vector<int> Database::triangular(int source, int destination, int* distance){
    return vector<int>();
}
vector<int> Database::specialHeuristic(int source, int destination, int* distance){
    return vector<int>();
}

/*
void Database::readStations(set<string> stations, set<string> lines) {
    ifstream file("../data/stations.csv");
    file.ignore(1000, '\n'); // ignore first line

    if (!file.is_open()) {
        cout << "Error opening stations.csv" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ';')) {
            fields.push_back(field);
        }
        if (fields.size() != 5) {
            cout << "The following line is invalid: " << line << endl;
            return;
        }

        string name = fields[0];
        string district = fields[1];
        string municipality = fields[2];
        string township = fields[3];
        string line = fields[4];

        if (!stations.empty() && stations.find(name) == stations.end()) {
            continue;
        }

        if (!lines.empty() && lines.find(line) == lines.end()) {
            continue;
        }

        Station *station = new Station(name, district, municipality, township, line);
        graph.addNode(*station);
        nameToStation[name] = station;
        municipalityToStations[municipality].insert(name);
        districtToMunicipalities[district].insert(municipality);
    }
    file.close();
    return;
}
void Database::readNetwork() {
    ifstream file("../data/network.csv");
    file.ignore(1000, '\n'); // ignore first line

    if (!file.is_open()) {
        cout << "Error opening network.csv" << endl;
        return;
    }

    string line;
    int lineCount = 0;
    while (getline(file, line)) {
        lineCount++;
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ';')) {
            fields.push_back(field);
        }
        if (fields.size() != 4) {
            cout << "Line" << lineCount << " is invalid: " << line << endl;
        }

        string orig = fields[0];
        string dest = fields[1];
        int capacity = stoi(fields[2]);
        string serviceType = fields[3];
        ServiceType service;
        if(serviceType == "STANDARD")
            service = STANDARD;
        else if(serviceType == "ALFA PENDULAR")
            service = ALFA_PENDULAR;
        else{
            cout << "Line " << lineCount << " service type is invalid: " << line << endl;
        }

        Station *origStation = nameToStation[orig];
        Station *destStation = nameToStation[dest];

        if (origStation == nullptr || destStation== nullptr)
            continue;

        graph.addBidirectionalEdge(graph.getNode(orig), graph.getNode(dest), capacity, service);
    }
    file.close();
    return;
}

*/

/*
int loadGraph(int graph){    
    if (graph == 4 || graph == 5 || graph == 6)
        ifstream nodes;
        ifstream edges;
    else 
        ifstream file;
        
    switch (graph){
        case 1:
            file.open("../data/Toy-Graphs/shipping.csv");
            break;
        
        case 2:
            file.open("../data/Toy-Graphs/stadiums.csv");
            break;
        
        case 3:
            file.open("../data/Toy-Graphs/tourism.csv");
            break;
        case 4:
            file.open("../data/Real-world-graphs/tourism.csv");
    }

        
    return 0;
}
*/

