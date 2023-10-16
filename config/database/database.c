#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "../../environment.h"
#include "database.h"

sqlite3 *db;

void openDatabaseConnection() {
    int rc;

    rc = sqlite3_open(DATABASE_FILE_NAME, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
    createDefaultTables();
}

sqlite3 *getDatabaseConnection() {
    return db;
}

void createDefaultTables() {
    char *errMsg = 0;
    char *stmt = "CREATE TABLE IF NOT EXISTS t_git_users("  \
      "id INTEGER PRIMARY KEY AUTOINCREMENT," \
      "configName TEXT NOT NULL UNIQUE," \
      "name TEXT NOT NULL," \
      "email TEXT," \
      "token TEXT);";

    int rc = sqlite3_exec(db, stmt, NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }
}