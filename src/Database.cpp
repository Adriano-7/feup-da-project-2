#include "../headers/Database.h"

#include "../data_structures/Graph.h"


using namespace std;
void Database::loadSmall(string path, int nNodes) {
    for (int i = 0; i < nNodes; i++) {
        graph.addNode(i);
    }

    ifstream file(path);
    file.ignore(1000, '\n');

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

void Database::loadExtra(string path, int numEdges){;}

bool Database::nodeExists(int id){return true;}

vector<int> Database::backtracking(int origin, int dest, int* distance){graph.primMST();}
vector<int> Database::triangular(int source, int destination, int* distance){
    graph.primMST();
}
vector<int> Database::specialHeuristic(int source, int destination, int* distance){return vector<int>();}


void Database::printGraph(){
    for(auto node : graph.getNodes()){
        cout << "Node " << node->getId() << endl;
        for(auto edge : node->getAdj()){
            cout << "Edge to " << edge->getDest()->getId() << " with distance " << edge->getDistance() << endl;
        }
    }
}
