#include <stdio.h>
#include <stdlib.h>
#include "../domain/entities.h"
#include "../utils/helpers.h"
#include "../domain/usecases.h"

enum MenuOptions {
    LIST_CONFIGURATIONS,
    CREATE_CONFIGURATION,
    USE_CONFIGURATION,
    EXIT
};

void createGitConfigurationUiCliController();

void listGitConfigurationsUiCliController();

void useGitConfigurationUiCliController();

void initGitConfigurationUiCliController() {
    struct MenuOption menuItems[] = {
            {LIST_CONFIGURATIONS,  "List configurations",  listGitConfigurationsUiCliController},
            {CREATE_CONFIGURATION, "Create configuration", createGitConfigurationUiCliController},
            {USE_CONFIGURATION,    "Use configuration",    useGitConfigurationUiCliController},
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

}

void createGitConfigurationUiCliController() {
    struct GitConfiguration config;

    printf("Configuration name: ");
    scanf("%99s", config.configName);

    printf("Username: ");
    scanf("%99s", config.name);

    printf("Email: ");
    scanf("%99s", config.email);

    printf("Token: ");
    scanf("%199s", config.token);

    createGitConfiguration(config);
}

void listGitConfigurationsUiCliController() {
    struct GitConfiguration *configs = listGitConfigurations();

    if (configs == NULL) {
        printf("No configurations found!\n");
        return;
    }

    printf("\n");
    for (int i = 0; configs[i].configName[0] != '\0'; i++) {
        printf("- ConfigName: %s\n", configs[i].configName);
        printf("  Username: %s\n", configs[i].name);
        printf("  Email: %s\n", configs[i].email);
        printf("  Token: %s\n\n", configs[i].token);
    }
}

void useGitConfigurationUiCliController() {
    char inputConfigName[100];
    printf("Which configuration do you want to use? ");
    scanf("%99s", inputConfigName);

    useGitConfiguration(inputConfigName);
}