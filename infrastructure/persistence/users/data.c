#include "../../../domain/entities.h"
#include <sqlite3.h>
#include <stdio.h>

sqlite3 *db;

void createUsersRepository(sqlite3 *database) {
    db = database;
}

static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

struct GitConfiguration getAllUsers() {
    char *errMsg = 0;
    char *stmt = "SELECT * FROM t_git_users";
    int rc = sqlite3_exec(db, stmt, callback, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }
}
