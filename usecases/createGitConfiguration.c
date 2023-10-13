#include <stdlib.h>
#include "../domain/entities.h"
#include "../utils/helpers.h"
#include "../environment.h"

void createGitConfiguration(struct GitConfiguration config) {
    FILE *file = fopen(CONFIG_FILE_NAME, "a");

    if (file == NULL) {
        perror("Error when open file!");
        exit(1);
    }

    fprintf(file, "%s,%s,%s,%s\n", config.configName, config.name, config.email, config.token);

    fclose(file);

    printf("\nConfiguration saved in file '%s'\n\n", CONFIG_FILE_NAME);
}
