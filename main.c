#include "utils/helpers.h"
#include "environment.h"
#include "domain/controllers.h"
#include "config/database/database.h"

int main(int argc, char **argv) {
    clearScreen();
    createFolderIfNotExists(FOLDER_PATH);

    openDatabaseConnection();

    if (argc > 1) {
        controllersFactory(CLI_CONTROLLER, argv);
    } else {
        controllersFactory(UI_CLI_CONTROLLER, argv);
    }

    return 0;
}
