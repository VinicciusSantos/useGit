gcc -o usegit main.c usecases/listGitConfigurations.c usecases/createGitConfiguration.c usecases/useGitConfiguration.c utils/helpers.c controllers/cli.controller.c controllers/ui-cli.controller.c controllers/controllers.factory.c

sudo ./usegit use personal
