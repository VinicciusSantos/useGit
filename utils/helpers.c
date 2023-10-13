#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
#include "environment.h"

void clearScreen() {
    system("clear");
}

void pressEnterToContinue() {
    printf("\nPress enter to continue...");
    getchar();
    getchar();
    clearScreen();
}

void createFolderIfNotExists(const char *folderName) {
    bool folderExists = access(folderName, F_OK) != -1;
    if (!folderExists) {
        if (mkdir(folderName, 0777) == 0) {
            printf("Folder %s created with success!\n", folderName);
        } else {
            printf("Error when create folder!\n");
            perror("Error");
        }
    }
}

FILE *readFile(char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("File %s not found!", filename);
        return NULL;
    }
    return file;
}

void printTimes(int times, char *text) {
    for (int i = 0; i < times; i++) {
        printf("%s", text);
    }
}

void printInCenter(int size, char *text) {
    int spaces = (size - strlen(text)) / 2;
    printTimes(spaces, " ");
    printf("%s", text);
}

void printHeader(char *title, int size) {
    printTimes(size, "=");
    printf("\n");
    printInCenter(size, title);
    printf("\n");
    printTimes(size, "=");
    printf("\n");
}

int buildMenu(char *title, struct MenuOption options[], int count) {
    int menu_width = 30;

    clearScreen();
    printHeader(title, menu_width);

    for (int i = 0; i < count; i++) {
        printf(" %d. %s\n", options[i].code, options[i].label);
    }

    int option;
    printTimes(menu_width, "=");
    printf("\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    return option;
}

char *getGitConfigFilePath() {
    char configFilePath[100];
    char *username = getenv("USER");
    sprintf(configFilePath, "/home/%s/%s", username, ".gitconfig");
    return configFilePath;
}

char *getGitCredentialsFilePath() {
    char filePath[100];
    char *username = getenv("USER");
    sprintf(filePath, "/home/%s/%s", username, ".git-credentials");
    return filePath;
}