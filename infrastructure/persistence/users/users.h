#include <sqlite3.h>

#ifndef USE_GIT_USERS_H
#define USE_GIT_USERS_H

void createUsersRepository(sqlite3 *database);

struct GitConfiguration *getAllUsers();

void createUser(struct GitConfiguration *config);

struct GitConfiguration * getOneUserByConfigName(char *configName);

#endif
