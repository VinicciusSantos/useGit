#include <sqlite3.h>

#ifndef USE_GIT_DATABASE_H
#define USE_GIT_DATABASE_H

void openDatabaseConnection();

sqlite3 *getDatabaseConnection();

void createDefaultTables();

#endif
