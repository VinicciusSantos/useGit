#include <stdio.h>

#ifndef USE_GIT_HELPERS_H
#define USE_GIT_HELPERS_H

typedef void (*MenuFunction)();

struct MenuOption {
    int code;
    char label[100];
    MenuFunction function;
};

void clearScreen();

void pressEnterToContinue();

void createFolderIfNotExists(const char *folderName);

FILE *readFile(char *filename);

void printTimes(int times, char *text);

void printInCenter(int size, char *text);

void printHeader(char *title, int size);

int buildMenu(char *title, struct MenuOption options[], int count);

#endif