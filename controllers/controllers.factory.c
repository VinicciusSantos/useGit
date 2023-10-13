#include "../domain/controllers.h"

void controllersFactory(enum controllers controllerType, char **argv) {
    switch (controllerType) {
        case UI_CLI_CONTROLLER:
            initGitConfigurationUiCliController();
            break;
        case CLI_CONTROLLER:
            initGitConfigurationCliController(argv);
            break;
    }
}