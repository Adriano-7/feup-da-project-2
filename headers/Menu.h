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
        void showDataSelectionMenu();

    private:
        Database database;

        void showSubsetMenu();
        void showMainMenu();
        void showStationInfoMenu();
        void showTwoStationsInfoMenu();
        void showNetworkInfoMenu();
        void showChangeCapacityMenu();

        int getIntFromUser();

        void waitForInput();
};

#endif 
