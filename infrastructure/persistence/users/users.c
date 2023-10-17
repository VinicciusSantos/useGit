#include "../../../domain/entities.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sqlite3 *database;

void createUsersRepository(sqlite3 *db) {
    database = db;
}

/* -=- GET ALL USERS -=- */

static int getAllUsersCallBack(void *data, int argc, char **argv, char **azColName);

struct GitConfigurationList *getAllUsers() {
    char *stmt = "SELECT * FROM t_git_users";
    struct GitConfigurationList *data = (struct GitConfigurationList *) malloc(sizeof(struct GitConfigurationList));

    if (!data) {
        fprintf(stderr, "Error while allocating memory for GitConfigurationList.\n");
        return NULL;
    }

    data->configurations = NULL;
    data->count = 0;

    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_exec(database, stmt, getAllUsersCallBack, (void *) data, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        free(data->configurations);
        free(data);
        return NULL;
    }

    return data;
}

static int getAllUsersCallBack(void *data, int argc, char **argv, char **azColName) {
    struct GitConfigurationList *configList = (struct GitConfigurationList *) data;

    struct GitConfiguration newConfig;
    newConfig.id = atoi(argv[0]);
    newConfig.configName = strdup(argv[1]);
    newConfig.name = strdup(argv[2]);
    newConfig.email = strdup(argv[3]);
    newConfig.token = strdup(argv[4]);

    configList->configurations = (struct GitConfiguration *) realloc(configList->configurations,
                                                                     (configList->count + 1) *
                                                                     sizeof(struct GitConfiguration));
    configList->configurations[configList->count] = newConfig;
    configList->count++;

    return 0;
}

/* -=- CREATE USER -=- */

void createUser(struct GitConfiguration *config) {
    char *stmt;
    sqlite3_stmt *preparedStmt;
    int rc;

    if (config == NULL) {
        fprintf(stderr, "Error: config is null.\n");
        return;
    }

    stmt = "INSERT INTO t_git_users (configName, name, email, token) VALUES (?, ?, ?, ?)";

    rc = sqlite3_prepare_v2(database, stmt, -1, &preparedStmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error while creating prepared statement: %s\n", sqlite3_errmsg(database));
        return;
    }

    sqlite3_bind_text(preparedStmt, 1, config->configName, -1, SQLITE_STATIC);
    sqlite3_bind_text(preparedStmt, 2, config->name, -1, SQLITE_STATIC);
    sqlite3_bind_text(preparedStmt, 3, config->email, -1, SQLITE_STATIC);
    sqlite3_bind_text(preparedStmt, 4, config->token, -1, SQLITE_STATIC);

    rc = sqlite3_step(preparedStmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error while inserting data: %s\n", sqlite3_errmsg(database));
        sqlite3_finalize(preparedStmt);
        return;
    }

    sqlite3_finalize(preparedStmt);

    return;
}

/* -=- GET ONE USER BY CONFIG NAME -=- */

static int getOneUserByConfigNameCallBack(void *data, int argc, char **argv, char **azColName);

struct GitConfiguration * getOneUserByConfigName(char *configName) {
    char *stmt = "SELECT * FROM t_git_users WHERE configName = ?";
    struct GitConfiguration *config = (struct GitConfiguration *) malloc(sizeof(struct GitConfiguration));

    char *zErrMsg = 0;
    int rc;

    sqlite3_stmt *preparedStmt;

    rc = sqlite3_prepare_v2(database, stmt, -1, &preparedStmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error while creating prepared statement: %s\n", sqlite3_errmsg(database));
        return config;
    }

    sqlite3_bind_text(preparedStmt, 1, configName, -1, SQLITE_STATIC);

    rc = sqlite3_step(preparedStmt);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Error while getting data: %s\n", sqlite3_errmsg(database));
        sqlite3_finalize(preparedStmt);
        return config;
    }

    config->id = atoi((char *) sqlite3_column_text(preparedStmt, 0));
    config->configName = strdup((char *) sqlite3_column_text(preparedStmt, 1));
    config->name = strdup((char *) sqlite3_column_text(preparedStmt, 2));
    config->email = strdup((char *) sqlite3_column_text(preparedStmt, 3));
    config->token = strdup((char *) sqlite3_column_text(preparedStmt, 4));

    sqlite3_finalize(preparedStmt);

    return config;
}