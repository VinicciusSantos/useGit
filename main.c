#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include "utils.h"

#define FOLDER_PATH "/useGit"
#define CONFIG_FILE_PATH "/useGit/config.csv"
#define GIT_CONFIG_PATH "/home/vinicius/.gitconfig"
#define GIT_CREDENTIALS_PATH "/home/vinicius/.git-credentials"

enum MenuOptions
{
    LIST_CONFIGURATIONS,
    CREATE_CONFIGURATION,
    USE_CONFIGURATION,
    EXIT
};

struct GitConfiguration
{
    char configName[100];
    char name[100];
    char email[100];
    char token[200];
};

void listGitConfigurations();
void createGitConfiguration();
void useGitConfiguration();

int main()
{
    struct MenuOption menuItems[] = {
        {LIST_CONFIGURATIONS, "Listar configurações", listGitConfigurations},
        {CREATE_CONFIGURATION, "Criar configuração", createGitConfiguration},
        {USE_CONFIGURATION, "Usar configuração", useGitConfiguration},
        {EXIT, "Sair", exit}};

    buildMenu(menuItems, 4);

    return 0;
}

void listGitConfigurations()
{
    FILE *file = readFile(CONFIG_FILE_PATH);

    struct GitConfiguration config;
    int configCount = 0;

    while (fscanf(file, "%99[^,],%99[^,],%99[^,],%199[^\n]\n",
                  config.configName, config.name, config.email, config.token) == 4)
    {
        configCount++;
        printf("\n#%i - Config para %s:\n\n", configCount, config.configName);
        printf("Name: %s\n", config.name);
        printf("Email: %s\n", config.email);
        printf("Token: %s\n\n", config.token);
    }

    fclose(file);

    if (configCount == 0)
    {
        printf("No configurations found.\n");
    }
}

void createGitConfiguration()
{
    struct GitConfiguration config;

    printf("Digite o nome da configuração: ");
    scanf("%99s", config.configName);

    printf("Digite o nome de usuário: ");
    scanf("%99s", config.name);

    printf("Digite o email: ");
    scanf("%99s", config.email);

    printf("Digite o token: ");
    scanf("%199s", config.token);

    FILE *file = fopen(CONFIG_FILE_PATH, "a");

    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fprintf(file, "%s,%s,%s,%s\n", config.configName, config.name, config.email, config.token);

    fclose(file);

    printf("\nConfiguração salva no arquivo '%s'\n\n", CONFIG_FILE_PATH);
}

void useGitConfiguration()
{
    char inputConfigName[100];
    printf("Digite o nome da configuração que deseja usar: ");
    scanf("%99s", inputConfigName);

    FILE *file = readFile(CONFIG_FILE_PATH);

    struct GitConfiguration config;
    bool configFound = false;

    while (fscanf(file, "%99[^,],%99[^,],%99[^,],%199[^\n]\n",
                  config.configName, config.name, config.email, config.token) == 4)
    {
        if (strcmp(config.configName, inputConfigName) == 0)
        {
            configFound = true;
            break;
        }
    }

    fclose(file);

    if (configFound)
    {
        remove(GIT_CONFIG_PATH);
        remove(GIT_CREDENTIALS_PATH);

        FILE *gitconfigFile = fopen(GIT_CONFIG_PATH, "w");
        FILE *gitcredentialsFile = fopen(GIT_CREDENTIALS_PATH, "w");

        if (gitconfigFile == NULL || gitcredentialsFile == NULL)
        {
            perror("Erro ao criar os arquivos de configuração");
            return;
        }

        fprintf(gitconfigFile, "[user]\n");
        fprintf(gitconfigFile, "    name = %s\n", config.name);
        fprintf(gitconfigFile, "    email = %s\n", config.email);
        fprintf(gitconfigFile, "[credential]\n");
        fprintf(gitconfigFile, "    helper = store\n");

        fprintf(gitcredentialsFile, "https://%s:%s@github.com\n", config.name, config.token);

        fclose(gitconfigFile);
        fclose(gitcredentialsFile);

        printf("Configuração aplicada nos arquivos '.gitconfig' e '.git-credentials'\n");
    }
    else
    {
        printf("Configuração com o nome '%s' não encontrada.\n", inputConfigName);
    }
}
