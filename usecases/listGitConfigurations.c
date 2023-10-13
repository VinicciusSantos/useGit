#include <stdlib.h>
#include "../domain/entities.h"
#include "../utils/helpers.h"
#include "../environment.h"

struct GitConfiguration *listGitConfigurations() {
    FILE *file = fopen(CONFIG_FILE_PATH, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return NULL;
    }

    struct GitConfiguration *configs = NULL;
    int configCount = 0;

    configs = (struct GitConfiguration *) malloc((configCount + 1) * sizeof(struct GitConfiguration));
    if (configs == NULL) {
        printf("Error allocating memory.\n");
        return NULL;
    }

    while (fscanf(file, "%99[^,],%99[^,],%99[^,],%199[^\n]\n",
                  configs[configCount].configName, configs[configCount].name,
                  configs[configCount].email, configs[configCount].token) == 4) {
        configCount++;


        struct GitConfiguration *newConfig = (struct GitConfiguration *) realloc(configs, (configCount + 1) *
                                                                                          sizeof(struct GitConfiguration));

        if (newConfig == NULL) {
            printf("Error reallocating memory.\n");
            free(configs);
            return NULL;
        }

        configs = newConfig;
    }

    fclose(file);

    if (configCount == 0) {
        free(configs);
        return NULL;
    }

    return configs;
}
