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
    struct GitConfiguration *config = (struct GitConfiguration *) malloc(sizeof(struct GitConfiguration));

    if (config == NULL) {
        fprintf(stderr, "Error while allocating memory for GitConfiguration.\n");
        return;
    }

    config->configName = (char *) malloc(100);
    config->name = (char *) malloc(100);
    config->email = (char *) malloc(100);
    config->token = (char *) malloc(200);

    if (config->configName == NULL || config->name == NULL || config->email == NULL || config->token == NULL) {
        fprintf(stderr, "Error while allocating memory for GitConfiguration.\n");
        free(config);
        return;
    }

    printf("Configuration name: ");
    scanf("%99s", config->configName);

    printf("Username: ");
    scanf("%99s", config->name);

    printf("Email: ");
    scanf("%99s", config->email);

    printf("Token: ");
    scanf("%199s", config->token);

    createGitConfiguration(config);

    free(config->configName);
    free(config->name);
    free(config->email);
    free(config->token);

    free(config);
}

void listGitConfigurationsUiCliController() {
    struct GitConfigurationList *configList = (struct GitConfigurationList *) listGitConfigurations();

    if (configList == NULL) {
        printf("No configurations found!\n");
        return;
    }

    int count = configList->count;
    struct GitConfiguration *configs = configList->configurations;

    for (int i = 0; i < count; i++) {
        printf("ID: %d\n", configs[i].id);
        printf("Config Name: %s\n", configs[i].configName);
        printf("Name: %s\n", configs[i].name);
        printf("Email: %s\n", configs[i].email);
        printf("Token: %s\n", configs[i].token);
        printf("\n");
    }

    free(configList->configurations);
    free(configList);
}

void useGitConfigurationUiCliController() {
    char inputConfigName[100];
    printf("Which configuration do you want to use? ");
    scanf("%99s", inputConfigName);

    useGitConfiguration(inputConfigName);
}