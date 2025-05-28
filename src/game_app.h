#pragma once

#include <SDL.h>
#include "game_of_life.h"

struct AppConfig
{
    int width;
    int height;
    int speed;
};

class GameApp
{
public:
    GameApp(const AppConfig &config);
    ~GameApp();

    void run();

private:
    AppConfig config;
    SDL_Window *window;
    SDL_Renderer *renderer;
    GameOfLife game;
    bool running;
    bool paused;

    void draw();
    void handleEvent(const SDL_Event &e);
};
