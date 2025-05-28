#include "game_app.h"
#include <iostream>

namespace
{
    constexpr int CELL_SIZE = 16;
    constexpr int WINDOW_POS_X = 100;
    constexpr int WINDOW_POS_Y = 100;
    constexpr int BG_R = 30, BG_G = 30, BG_B = 30, BG_A = 255;
    constexpr int CELL_R = 0, CELL_G = 200, CELL_B = 0, CELL_A = 255;
    constexpr int GRID_R = 60, GRID_G = 60, GRID_B = 60, GRID_A = 255;
    constexpr int FRAME_DELAY_MS = 10;
}

GameApp::GameApp(const AppConfig &cfg)
    : config(cfg),
      game(cfg.width, cfg.height),
      window(nullptr),
      renderer(nullptr),
      running(true),
      paused(true)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("SDL_Init failed");
    }

    window = SDL_CreateWindow("Game of Life", WINDOW_POS_X, WINDOW_POS_Y, config.width * CELL_SIZE, config.height * CELL_SIZE, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::runtime_error("SDL_CreateWindow failed");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("SDL_CreateRenderer failed");
    }
}

GameApp::~GameApp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameApp::draw()
{
    SDL_SetRenderDrawColor(renderer, BG_R, BG_G, BG_B, BG_A);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, CELL_R, CELL_G, CELL_B, CELL_A);
    for (int y = 0; y < game.getHeight(); y++)
        for (int x = 0; x < game.getWidth(); x++)
            if (game.getCell(x, y))
            {
                SDL_Rect cell = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                SDL_RenderFillRect(renderer, &cell);
            }

    SDL_SetRenderDrawColor(renderer, GRID_R, GRID_G, GRID_B, GRID_A);
    for (int x = 0; x <= game.getWidth(); x++)
        SDL_RenderDrawLine(renderer, x * CELL_SIZE, 0, x * CELL_SIZE, game.getHeight() * CELL_SIZE);
    for (int y = 0; y <= game.getHeight(); y++)
        SDL_RenderDrawLine(renderer, 0, y * CELL_SIZE, game.getWidth() * CELL_SIZE, y * CELL_SIZE);

    SDL_RenderPresent(renderer);
}

void GameApp::handleEvent(const SDL_Event &e)
{
    switch (e.type)
    {
    case SDL_QUIT:
        running = false;
        break;
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            running = false;
            break;
        case SDLK_SPACE:
            paused = !paused;
            break;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
    {
        int mx = e.button.x / CELL_SIZE;
        int my = e.button.y / CELL_SIZE;

        // Проверка на мышь в пределах окна
        if (mx >= 0 && mx < config.width && my >= 0 && my < config.height)
        {
            bool state = !game.getCell(mx, my);
            game.setCell(mx, my, state);
        }
        break;
    }
    default:
        break;
    }
}

void GameApp::run()
{
    Uint32 lastUpdate = SDL_GetTicks();

    while (running)
    {
        SDL_Event e;

        while (SDL_PollEvent(&e))
            handleEvent(e);

        if (!paused && SDL_GetTicks() - lastUpdate > static_cast<Uint32>(config.speed))
        {
            game.step();
            lastUpdate = SDL_GetTicks();
        }

        draw();
        SDL_Delay(FRAME_DELAY_MS);
    }
}
