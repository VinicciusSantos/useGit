#include <stdlib.h>
#include "utils/helpers.h"
#include "environment.h"
#include "domain/controllers.h"

enum MenuOptions {
    LIST_CONFIGURATIONS,
    CREATE_CONFIGURATION,
    USE_CONFIGURATION,
    EXIT
};

int main() {
    createFolderIfNotExists(FOLDER_PATH);

    struct MenuOption menuItems[] = {
            {LIST_CONFIGURATIONS,  "List configurations",  listGitConfigurationsController},
            {CREATE_CONFIGURATION, "Create configuration", createGitConfigurationController},
            {USE_CONFIGURATION,    "Use configuration",    useGitConfigurationController},
            {EXIT,                 "Exit",                 exit}};

    int selectedOption;
    do {
        selectedOption = buildMenu("Git Credentials Manager", menuItems, 4);
        if (selectedOption != EXIT) {
            clearScreen();
            printHeader(menuItems[selectedOption].label, 60);
            menuItems[selectedOption].function();
            pressEnterToContinue();
        }
    } while (selectedOption != EXIT);

    return 0;
}
