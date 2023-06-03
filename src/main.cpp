#include "headers/Database.h"
#include "headers/Menu.h"

/**
 * @brief Initializes the program.
 *
 * @return An integer indicating the exit status of the program.
 */
int main(){
    Database database;
    database.printGraph();
    Menu menu(database);
    menu.showDataSelectionMenu();
    return 0;
}
