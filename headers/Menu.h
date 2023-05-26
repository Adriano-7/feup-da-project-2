#ifndef INC_2ND_PROJECT_MENU_H
#define INC_2ND_PROJECT_MENU_H

#include "Database.h"
#include <iostream>

/**
 * @brief Class responsible for the user interface
 */
class Menu {
    public:
        Menu(Database& database) : database(database) {};
        void showDataSelectionMenu()

    private:
        Database database;
        void showSmallGraphMenu();
        void showMediumGraphMenu();
        void showExtraMenu();
        void showMainMenu();
        void showBacktrackingMenu();
        void showTriangularMenu();
        void showSpecialHeuristicMenu();

        pair<int, int> getNodesFromUser();
        void waitForInput();
        int getIntFromUser();
};

#endif 
