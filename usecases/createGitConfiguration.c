#include <stdlib.h>
#include "../domain/entities.h"
#include "../utils/helpers.h"
#include "../environment.h"

void createGitConfiguration() {
    struct GitConfiguration config;

    printf("Configuration name: ");
    scanf("%99s", config.configName);

    printf("Username: ");
    scanf("%99s", config.name);

    printf("Email: ");
    scanf("%99s", config.email);

    printf("Token: ");
    scanf("%199s", config.token);

    FILE *file = fopen(CONFIG_FILE_PATH, "a");

    if (file == NULL) {
        perror("Error when open file!");
        exit(1);
    }

    fprintf(file, "%s,%s,%s,%s\n", config.configName, config.name, config.email, config.token);

    fclose(file);

    printf("\nConfiguration saved in file '%s'\n\n", CONFIG_FILE_PATH);
}
