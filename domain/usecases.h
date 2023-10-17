#ifndef USE_GIT_USECASES_H
#define USE_GIT_USECASES_H

struct GitConfiguration *listGitConfigurations();

void createGitConfiguration(struct GitConfiguration *config);

void useGitConfiguration(char *configName);

#endif
