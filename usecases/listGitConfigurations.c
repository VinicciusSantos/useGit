#include "../domain/entities.h"
#include "../infrastructure/persistence/repositories.h"

struct GitConfiguration *listGitConfigurations() {
    struct GitConfiguration *configs = getAllUsers();
    return configs;
}
