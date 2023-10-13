#include <stdio.h>
#include <string.h>
#include "../domain/usecases.h"
#include "../domain/entities.h"

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

void listGitConfigurationsCliController(char **argv) {
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

void useGitConfigurationCliController(char **argv) {
    useGitConfiguration(argv[2]);
}