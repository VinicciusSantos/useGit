#include <stddef.h>

#ifndef USE_GIT_ENTITIES_H
#define USE_GIT_ENTITIES_H

struct GitConfiguration {
    int id;
    char *configName;
    char *name;
    char *email;
    char *token;
};

struct GitConfigurationList {
    struct GitConfiguration *configurations;
    size_t count;
};

#endif
