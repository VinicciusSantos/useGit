#include <stdbool.h>
#include <string.h>
#include "../domain/entities.h"
#include "../utils/helpers.h"
#include "../environment.h"

void useGitConfiguration() {
    char inputConfigName[100];
    printf("Which configuration do you want to use? ");
    scanf("%99s", inputConfigName);

    FILE *file = readFile(CONFIG_FILE_PATH);

    struct GitConfiguration config;
    bool configFound = false;

    while (fscanf(file, "%99[^,],%99[^,],%99[^,],%199[^\n]\n",
                  config.configName, config.name, config.email, config.token) == 4) {
        if (strcmp(config.configName, inputConfigName) == 0) {
            configFound = true;
            break;
        }
    }

    fclose(file);

    if (configFound) {
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
    } else {
        printf("Configuration '%s' not found.\n", inputConfigName);
    }
}