#include <string>
#include <unordered_map>
#include <iostream>
#include "game_app.h"

namespace
{
    constexpr int DEFAULT_WIDTH = 50;
    constexpr int DEFAULT_HEIGHT = 50;
    constexpr int DEFAULT_SPEED = 100;
}

AppConfig parseArgs(int argc, char *argv[])
{
    AppConfig config{DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_SPEED};
    std::unordered_map<std::string, int *> argMap = {
        {"--width", &config.width},
        {"--height", &config.height},
        {"--speed", &config.speed}};

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (argMap.count(arg) && i + 1 < argc)
            *argMap[arg] = std::stoi(argv[++i]);
    }

    return config;
}

int main(int argc, char *argv[])
{
    AppConfig config = parseArgs(argc, argv);

    try
    {
        GameApp app(config);
        app.run();
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
