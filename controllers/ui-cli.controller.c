#include <stdio.h>
#include "../domain/usecases.h"
#include "../domain/entities.h"

void createGitConfigurationController() {
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

void listGitConfigurationsController() {
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

void useGitConfigurationController() {
    char inputConfigName[100];
    printf("Which configuration do you want to use? ");
    scanf("%99s", inputConfigName);

    useGitConfiguration(inputConfigName);
}