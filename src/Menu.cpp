#include "Menu.h"

void Menu::showDataSelectionMenu() {
    cout << "_________________________________________________" << endl;
    cout << "Welcome to our program!" << endl;
    cout << "Please select an option:" << endl;
    cout << "1 - Choose a small size graph" << endl;
    cout << "2 - Choose a medium/large graph" << endl;
    cout << "3 - Choose a medium/large graph extra connected" << endl;

    int option = getIntFromUser();

    switch (option) {
        case 1:
            showSmallGraphMenu();
            break;
        case 2:
            showMediumGraphMenu();
            break;
        case 3:
            showExtraMenu();
            break;
        default:
            cout << "Invalid option" << endl;
            showDataSelectionMenu();
    }
}

void Menu::showSmallGraphMenu() {
    map<int, string> optionToPath = {{1, "../data/Toy-Graphs/shipping.csv"}, {2, "../data/Toy-Graphs/stadiums.csv"}, {3, "../data/Toy-Graphs/tourism.csv"}};
    map<int, int> optionToNumNodes = {{1, 14}, {2, 11}, {3, 5}};
    cout << "_________________________________________________" << endl;
    cout << "Please the graph you want to load:" << endl;
    cout << "1 - shipping.csv" << endl;
    cout << "2 - stadiums.csv" << endl;
    cout << "3 - tourism.csv" << endl;

    int option = getIntFromUser();

    database.loadSmall(optionToPath[option], optionToNumNodes[option]);
    showMainMenu();
}

void Menu::showMediumGraphMenu() {
    cout << "_________________________________________________" << endl;
    cout << "Please the graph you want to load:" << endl;
    cout << "1 - graph1" << endl;
    cout << "2 - graph2" << endl;
    cout << "3 - graph3" << endl;

    int option = getIntFromUser();
    if(option < 1 || option > 3){
        cout << "Invalid option" << endl;
        showMediumGraphMenu();
    }

    string nodesPath = "../data/Real-world-graphs/graph" + to_string(option) + "/nodes.csv";
    string edgesPath = "../data/Real-world-graphs/graph" + to_string(option) + "/edges.csv";

    database.loadMedium(nodesPath, edgesPath);
    showMainMenu();
}

void Menu::showExtraMenu() {
    map<int, int> optionToNumEdges = {{1,25}, {2,50}, {3,75}, {4,100}, {5,200}, {6,300}, {7,400}, {8,500}, {9,600}, {10,700}, {11,800}, {12,900}};

    cout << "_________________________________________________" << endl;
    cout << "Please the graph you want to load:" << endl;
    cout << "1 - edges_25.csv" << endl;
    cout << "2 - edges_50.csv" << endl;
    cout << "3 - edges_75.csv" << endl;
    cout << "4 - edges_100.csv" << endl;
    cout << "5 - edges_200.csv" << endl;
    cout << "6 - edges_300.csv" << endl;
    cout << "7 - edges_400.csv" << endl;
    cout << "8 - edges_500.csv" << endl;
    cout << "9 - edges_600.csv" << endl;
    cout << "10 - edges_700.csv" << endl;
    cout << "11 - edges_800.csv" << endl;
    cout << "12 - edges_900.csv" << endl;

    int option = getIntFromUser();
    if(option < 1 || option > 12){
        cout << "Invalid option" << endl;
        option = getIntFromUser();
    }

    string path = "../data/Extra_Fully_Connected_Graphs/edges_" + to_string(optionToNumEdges[option]) + ".csv";

    database.loadExtra(path, optionToNumEdges[option]);
    showMainMenu();
}


void Menu::showMainMenu(){
    while (true){
        cout << "_________________________________________________" << endl;
        cout << "Please select an option to solve the TSP:" << endl;
        cout << "1 - Use the Backtracking Algorithm" << endl;
        cout << "2 - Using triangualar approximation heuristic" << endl;
        cout << "3 - Using our own heuristic" << endl;
        cout << "5 - Exit" << endl;

        int option = getIntFromUser();
        switch (option) {
            case 1:
                showBacktrackingMenu();
                waitForInput();
                break;
            case 2:
                showTriangularMenu();
                waitForInput();
                break;
            case 3:
                showSpecialHeuristicMenu();
                waitForInput();
                break;
            case 5:
                return;
            default:
                cout << "Invalid option" << endl;
        }
    }
}

pair<int, int> Menu::getNodesFromUser() {
    cout << "_________________________________________________" << endl;
    cout << "Please select the nodes you want to use:" << endl;
    cout << "Source node: ";
    int source = getIntFromUser();
    while(!database.nodeExists(source)){
        cout << "Invalid node" << endl;
        source = getIntFromUser();
    }

    cout << "Destination node: ";
    int destination = getIntFromUser();
    while(!database.nodeExists(destination)){
        cout << "Invalid node" << endl;
        destination = getIntFromUser();
    }

    return make_pair(source, destination);
}

void Menu::showBacktrackingMenu(){
    pair<int, int> nodes = getNodesFromUser();
    int source = nodes.first;
    int destination = nodes.second;
    int distance;

    vector<int> path = database.backtracking(source, destination, &distance);

    cout << "_________________________________________________" << endl;
    /*
    cout << "The shortest path is: " << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;
    cout << "The distance is: " << distance << endl;
    */
}

void Menu::showTriangularMenu(){
    pair<int, int> nodes = getNodesFromUser();
    int source = nodes.first;
    int destination = nodes.second;
    double distance;

    vector<Node*> path = database.triangular(source, destination, &distance);

    cout << "_________________________________________________" << endl;
    cout << "The shortest path is: " << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->getId() << " ";
    }
    cout << endl;
    cout << "The distance is: " << distance << endl;
}

void Menu::showSpecialHeuristicMenu(){
    pair<int, int> nodes = getNodesFromUser();
    int source = nodes.first;
    int destination = nodes.second;
    int distance;

    vector<int> path = database.specialHeuristic(source, destination, &distance);

    cout << "_________________________________________________" << endl;
    cout << "The shortest path is: " << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " -> ";
    }
    cout << endl;
    cout << "The distance is: " << distance << endl;

}

void Menu::waitForInput() {
    usleep(800000);
    string q;
    cout << endl << "Insert any key to continue: ";
    cin >> q;
    cout << endl;
}

int Menu::getIntFromUser() {
    int input;
    cin >> input;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return getIntFromUser();
    }
    return input;
}
