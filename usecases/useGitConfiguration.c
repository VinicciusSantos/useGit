#include <string.h>
#include "../domain/entities.h"
#include "../utils/helpers.h"
#include "../environment.h"

struct GitConfiguration checkIfConfigExists(FILE *file, char* configName);

void useGitConfiguration(char* configName) {
    FILE *file = readFile(CONFIG_FILE_PATH);

    struct GitConfiguration config = checkIfConfigExists(file, configName);

    fclose(file);

    if (config.configName[0] == '\0') {
        printf("Configuration not found!\n");
        return;
    }
    
    remove(GIT_CONFIG_PATH);
    remove(GIT_CREDENTIALS_PATH);

    FILE *gitconfigFile = fopen(GIT_CONFIG_PATH, "w");
    FILE *gitcredentialsFile = fopen(GIT_CREDENTIALS_PATH, "w");

    if (gitconfigFile == NULL || gitcredentialsFile == NULL) {
        perror("Error to create configuration file");
        return;
    }

    fprintf(gitconfigFile, "[user]\n");
    fprintf(gitconfigFile, "    name = %s\n", config.name);
    fprintf(gitconfigFile, "    email = %s\n", config.email);
    fprintf(gitconfigFile, "[credential]\n");
    fprintf(gitconfigFile, "    helper = store\n");

    fprintf(gitcredentialsFile, "https://%s:%s@github.com\n", config.name, config.token);

    fclose(gitconfigFile);
    fclose(gitcredentialsFile);

    printf("Configuration applied in files '.gitconfig' e '.git-credentials'\n");
}

struct GitConfiguration checkIfConfigExists(FILE *file, char* configName) {
    struct GitConfiguration config;

    while (fscanf(file, "%99[^,],%99[^,],%99[^,],%199[^\n]\n",
                  config.configName, config.name,
                  config.email, config.token) == 4) {
        if (strcmp(config.configName, configName) == 0) {
            return config;
        }
    }
    return config;
}