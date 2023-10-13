#include "utils/helpers.h"
#include "environment.h"
#include "domain/controllers.h"

int main(int argc, char **argv) {
    createFolderIfNotExists(FOLDER_PATH);

    if (argc > 1) {
        controllersFactory(CLI_CONTROLLER, argv);
    } else {
        controllersFactory(UI_CLI_CONTROLLER, argv);
    }

    return 0;
}
