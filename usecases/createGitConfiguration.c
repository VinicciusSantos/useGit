#include "../domain/entities.h"
#include "../infrastructure/persistence/repositories.h"

void createGitConfiguration(struct GitConfiguration *config) {
    createUser(config);
}
