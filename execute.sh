sudo mkdir -p /useGit

sudo apt-get install libsqlite3-dev

sudo chown -R "$USER":"$USER" /useGit

sudo gcc -o /useGit/usegit \
  main.c \
  config/database/database.c \
  controllers/cli.controller.c \
  controllers/ui-cli.controller.c \
  controllers/controllers.factory.c \
  infrastructure/persistence/repositories.c \
  infrastructure/persistence/users/users.c \
  usecases/listGitConfigurations.c \
  usecases/createGitConfiguration.c \
  usecases/useGitConfiguration.c \
  utils/helpers.c \
  -lsqlite3
