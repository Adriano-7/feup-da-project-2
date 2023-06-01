#include "../headers/Database.h"

using namespace std;

bool Database::loadSmall(string path) {
    ifstream file(path);
    file.ignore(1000, '\n');

    if (!file.is_open()) {
        cout << "Error opening toy graph" << endl;
        return false;
    }

    string line;

    while (getline(file, line)) {
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ',')) {
            fields.push_back(field);
        }

        string origin_id = fields[0];
        graph.addNode(stoi(origin_id));

        string dest_id = fields[1];
        graph.addNode(stoi(dest_id));

        string distance = fields[2];

        graph.addEdge(graph.getNode(stoi(origin_id)), graph.getNode(stoi(dest_id)), stod(distance));
    }

    file.close();
    return true;
}

bool Database::loadMedium(const string& nodesPath, const string& edgesPath) {
    ifstream nodesInput(nodesPath);
    ifstream edgesInput(edgesPath);

    if (!nodesInput.is_open() || !edgesInput.is_open()) {
        cerr << "Failed to open input files." << endl;
        return false;
    }

    cout << "Loading nodes...";

    string line;
    nodesInput.ignore(1000, '\n');

    while (getline(nodesInput, line)) {
        istringstream iss(line);
        string idStr, longitudeStr, latitudeStr;
        if (!(getline(iss, idStr, ',') &&
              getline(iss, longitudeStr, ',') &&
              getline(iss, latitudeStr, ','))) {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }

        int id;
        double longitude, latitude;
        try {
            id = stoi(idStr);
            longitude = stod(longitudeStr);
            latitude = stod(latitudeStr);
        } catch (const exception& e) {
            cerr << "Error converting values: " << e.what() << endl;
            continue;
        }

        graph.addNode(id, longitude, latitude);
    }

    cout << endl;

    cout << "Loading edges...";

    edgesInput.ignore(1000, '\n');
    while (getline(edgesInput, line)) {
        istringstream iss(line);
        string origemStr, destinoStr, distanciaStr;
        if (!(getline(iss, origemStr, ',') &&
              getline(iss, destinoStr, ',') &&
              getline(iss, distanciaStr, ','))) {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }

        int origem, destino;
        double distancia;
        try {
            origem = stoi(origemStr);
            destino = stoi(destinoStr);
            distancia = stod(distanciaStr);
        } catch (const exception& e) {
            cerr << "Error converting values: " << e.what() << endl;
            continue;
        }

        Node* source = graph.getNode(origem);
        Node* destination = graph.getNode(destino);
        if (!source || !destination) {
            cerr << "Invalid source or destination node id in line: " << line << endl;
            continue;
        }

        graph.addEdge(source, destination, distancia);
    }

    return true;
}

bool Database::loadExtra(string path){
    ifstream file(path);
    if(!file.is_open()){
        cout << "Error opening extra graph" << endl;
        return false;
    }

    string line;
    while(getline(file, line)){
        vector<string> fields;
        istringstream stream(line);
        string field;
        while(getline(stream, field, ',')){
            fields.push_back(field);
        }
        if(fields.size() != 3){
            cout << "The following line is invalid: " << line << endl;
            return false;
        }

        string origin_id = fields[0];
        graph.addNode(stoi(origin_id));

        string dest_id = fields[1];
        graph.addNode(stoi(dest_id));

        string distance = fields[2];

        graph.addEdge(graph.getNode(stoi(origin_id)), graph.getNode(stoi(dest_id)), stod(distance));
    }

    file.close();
    return true;
}

bool Database::nodeExists(int id){
    return graph.getNode(id) != nullptr;
}

pair<double, vector<unsigned int>> Database::backtracking() {
    return graph.Backtracking_TSP();
}

vector<Node*> Database::triangular(double* distance){
    return graph.tspTriangular(distance);
}
vector<int> Database::specialHeuristic(double* distance){
    return vector<int>();
}

void Database::printGraph(){
    for(auto node : graph.getNodes()){
        cout << "Node " << node->getId() << endl;
        for(auto edge : node->getAdj()){
            cout << "Edge to " << edge->getDest()->getId() << " with distance " << edge->getDistance() << endl;
        }
    }
}

void Database::clear() {
    graph.clear();
}