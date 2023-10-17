#include <stdlib.h>
#include "../domain/entities.h"
#include "../utils/helpers.h"
#include "../environment.h"
#include "../infrastructure/persistence/repositories.h"

void useGitConfiguration(char *configName) {
    struct GitConfiguration *config = getOneUserByConfigName(configName);

    if (config->configName[0] == '\0') {
        printf("Configuration not found!\n");
        return;
    }

    char GIT_CONFIG_PATH[100];
    char GIT_CREDENTIALS_PATH[100];

    char *username = getenv("USER");
    sprintf(GIT_CONFIG_PATH, "/home/%s/.gitconfig", username);
    sprintf(GIT_CREDENTIALS_PATH, "/home/%s/.git-credentials", username);

    remove(GIT_CONFIG_PATH);
    remove(GIT_CREDENTIALS_PATH);

    FILE *gitconfigFile = fopen(GIT_CONFIG_PATH, "w");
    FILE *gitcredentialsFile = fopen(GIT_CREDENTIALS_PATH, "w");

    if (gitconfigFile == NULL || gitcredentialsFile == NULL) {
        perror("Error to create configuration file");
        printf("Error to create configuration file: %s\n", GIT_CONFIG_PATH);
        printf("Error to create configuration file: %s\n", GIT_CREDENTIALS_PATH);
        return;
    }

    fprintf(gitconfigFile, "[user]\n");
    fprintf(gitconfigFile, "    name = %s\n", config->name);
    fprintf(gitconfigFile, "    email = %s\n", config->email);
    fprintf(gitconfigFile, "[credential]\n");
    fprintf(gitconfigFile, "    helper = store\n");

    fprintf(gitcredentialsFile, "https://%s:%s@github.com\n", config->name, config->token);

    fclose(gitconfigFile);
    fclose(gitcredentialsFile);

    printf("Configuration applied in files '.gitconfig' e '.git-credentials'\n");
}

