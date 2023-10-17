#include "repositories.h"

void createRepositories(sqlite3 *db) {
    createUsersRepository(db);
}