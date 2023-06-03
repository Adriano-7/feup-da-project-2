#ifndef INC_2ND_PROJECT_MENU_H
#define INC_2ND_PROJECT_MENU_H

#include "Database.h"
#include <iostream>
#include <map>
#include <unistd.h>
#include <limits>
#include <chrono>

/**
 * @class Menu
 *
 * @brief Class responsible for the user interface.
 */
class Menu {
public:
    /**
     * Constructor for the Menu class.
     *
     * @param database The instance of the Database class used by the menu.
     */
    Menu(Database& database);

    /**
     * Displays the data selection menu.
     */
    void showDataSelectionMenu();

private:
    Database database; ///< The instance of the database used by the menu.

    /**
     * Displays the menu for selecting a small size graph.
     */
    void showSmallGraphMenu();

    /**
     * Displays the menu for selecting a medium/large graph.
     */
    void showMediumGraphMenu();

    /**
     * Displays the menu for selecting an extra connected graph.
     */
    void showExtraMenu();

    /**
     * Displays the main menu and handles user input.
     */
    void showMainMenu();

    /**
     * Displays the menu for the Backtracking TSP algorithm and computes the shortest path.
     */
    void showBacktrackingMenu();

    /**
     * Displays the menu for the triangular approximation heuristic and computes the shortest path.
     */
    void showTriangularMenu();

    /**
     * Displays the menu for a special heuristic and computes the shortest path.
     */
    void showSpecialHeuristicMenu();

    /**
     * Waits for user input.
     */
    void waitForInput();

    /**
     * Retrieves an integer input from the user.
     *
     * @return The integer input.
     */
    int getIntFromUser();
};

#endif // INC_2ND_PROJECT_MENU_H
