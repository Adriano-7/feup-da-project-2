#include "Menu.h"

/**
 * @brief Displays the data selection menu.
 */
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

/**
 * @brief Displays the menu for selecting a small size graph.
 */
void Menu::showSmallGraphMenu() {
    map<int, string> optionToPath = {{1, "../data/Toy-Graphs/shipping.csv"}, {2, "../data/Toy-Graphs/stadiums.csv"}, {3, "../data/Toy-Graphs/tourism.csv"}};
    cout << "_________________________________________________" << endl;
    cout << "Please the graph you want to load:" << endl;
    cout << "1 - shipping.csv" << endl;
    cout << "2 - stadiums.csv" << endl;
    cout << "3 - tourism.csv" << endl;

    int option = getIntFromUser();

    database.loadSmall(optionToPath[option]);
    showMainMenu();
}

/**
 * @brief Displays the menu for selecting a medium/large graph.
 */
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

/**
 * @brief Displays the menu for selecting an extra connected graph.
 */
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

    database.loadExtra(path);
    showMainMenu();
}

/**
 * @brief Displays the main menu and handles user input.
 */
void Menu::showMainMenu(){
    while (true){
        cout << "_________________________________________________" << endl;
        cout << "Please select an option to solve the TSP:" << endl;
        cout << "1 - Use the Backtracking_TSP Algorithm" << endl;
        cout << "2 - Using triangualar approximation heuristic" << endl;
        cout << "3 - Using our own heuristic" << endl;
        cout << "4 - Change graph" << endl;
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
            case 4:
                database.clear();
                showDataSelectionMenu();
                return;
            case 5:
                return;
            default:
                cout << "Invalid option" << endl;
        }
    }
}

/**
 * @brief Displays the menu for the Backtracking TSP algorithm and computes the shortest path.
 */
void Menu::showBacktrackingMenu() {
    double distance = 0;

    auto start = high_resolution_clock::now();
    vector<unsigned int> path = database.backtracking(&distance);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "_________________________________________________" << endl;
    if(database.isToyGraph()){
        cout << "The shortest path is: " << endl;
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] <<  " -> ";
        }
        cout << endl;
    }

    cout << "The distance is: " << distance << endl;
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
}

/**
 * @brief Displays the menu for the triangular approximation heuristic and computes the shortest path.
 */
void Menu::showTriangularMenu(){
    double distance = 0;

    auto start = high_resolution_clock::now();
    vector<Node*> path = database.triangular(&distance);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "_________________________________________________" << endl;
    if(database.isToyGraph()){
        cout << "The shortest path is: " << endl;
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] <<  " -> ";
        }
        cout << endl;
    }

    cout << "The distance is: " << distance << endl;
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
}

/**
 * @brief Displays the menu for a special heuristic and computes the shortest path.
 */
void Menu::showSpecialHeuristicMenu(){
    double distance = 0;

    auto start = high_resolution_clock::now();
    vector<unsigned int> path = database.insertionHeuristic_TSP(&distance);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "_________________________________________________" << endl;
    if(database.isToyGraph()){
        cout << "The shortest path is: " << endl;
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] <<  " -> ";
        }
        cout << endl;
    }

    cout << "The distance is: " << distance << endl;
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
}

/**
 * @brief Waits for user input.
 */
void Menu::waitForInput() {
    usleep(800000);
    string q;
    cout << endl << "Insert any key to continue: ";
    cin >> q;
    cout << endl;
}

/**
 * @brief Retrieves an integer input from the user.
 *
 * @return The integer input.
 */
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
