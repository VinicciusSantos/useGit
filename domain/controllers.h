#ifndef USE_GIT_CONTROLLERS_H
#define USE_GIT_CONTROLLERS_H

enum controllers {
    UI_CLI_CONTROLLER,
    CLI_CONTROLLER
};

void initGitConfigurationCliController(char **argv);

void initGitConfigurationUiCliController();

void controllersFactory(enum controllers controllerType, char **argv);

#endif
