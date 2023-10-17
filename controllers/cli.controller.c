#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../domain/usecases.h"
#include "../domain/entities.h"
#include "../utils/helpers.h"

struct CommandsHandler {
    char *command;

    void (*function)(char **argv);
};

void createGitConfigurationCliController(char **argv);

void listGitConfigurationsCliController(char **argv);

void useGitConfigurationCliController(char **argv);

void handleCommand(char **argv, struct CommandsHandler *commands);

void initGitConfigurationCliController(char **argv) {
    if (argv[1] == NULL) {
        printf("No command provided!\n");
        return;
    }

    struct CommandsHandler commands[] = {
            {"create", createGitConfigurationCliController},
            {"list",   listGitConfigurationsCliController},
            {"use",    useGitConfigurationCliController}
    };
    handleCommand(argv, commands);
}

void handleCommand(char **argv, struct CommandsHandler *commands) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(argv[1], commands[i].command) == 0) {
            commands[i].function(argv);
            return;
        }
    }

    printf("Command not found!\n");
}

void createGitConfigurationCliController(char **argv) {
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

void listGitConfigurationsCliController(char **argv) {
    struct GitConfigurationList *configList = (struct GitConfigurationList *) listGitConfigurations();

    if (configList == NULL) {
        printf("No configurations found!\n");
        return;
    }

    printHeader("Configurations", 50);

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

void useGitConfigurationCliController(char **argv) {
    useGitConfiguration(argv[2]);
}