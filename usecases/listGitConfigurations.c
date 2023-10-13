#include "../domain/entities.h"
#include "../utils/helpers.h"
#include "../environment.h"

void listGitConfigurations() {
    FILE *file = readFile(CONFIG_FILE_PATH);

    struct GitConfiguration config;
    int configCount = 0;

    while (fscanf(file, "%99[^,],%99[^,],%99[^,],%199[^\n]\n",
                  config.configName, config.name, config.email, config.token) == 4) {
        configCount++;
        printf("\n#%i - Config para %s:\n\n", configCount, config.configName);
        printf("Name: %s\n", config.name);
        printf("Email: %s\n", config.email);
        printf("Token: %s\n\n", config.token);
    }

    fclose(file);

    if (configCount == 0) {
        printf("No configurations found.\n");
    }
}