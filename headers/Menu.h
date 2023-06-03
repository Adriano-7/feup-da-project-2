#ifndef INC_2ND_PROJECT_MENU_H
#define INC_2ND_PROJECT_MENU_H

#include "Database.h"
#include <iostream>
#include <map>
#include <unistd.h>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

/**
 * @class Menu
 *
 * @brief Class responsible for the user interface.
 */
class Menu {
public:
    Menu(Database& database) : database(database) {};
    void showDataSelectionMenu();

private:
    Database database;
    void showSmallGraphMenu();
    void showMediumGraphMenu();
    void showExtraMenu();
    void showMainMenu();
    void showBacktrackingMenu();
    void showTriangularMenu();
    void showSpecialHeuristicMenu();
    void waitForInput();
    int getIntFromUser();
};

#endif