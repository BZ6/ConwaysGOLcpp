#include "game_of_life.h"

GameOfLife::GameOfLife(int w, int h) : width(w), height(h), field(h, std::vector<bool>(w, false)) {}

void GameOfLife::clear()
{
    for (auto &row : field)
        std::fill(row.begin(), row.end(), false);
}

void GameOfLife::setCell(int x, int y, bool alive)
{
    while (x < 0)
        x += width;
    while (y < 0)
        y += height;

    field[y % height][x % width] = alive;
}

bool GameOfLife::getCell(int x, int y) const
{
    while (x < 0)
        x += width;
    while (y < 0)
        y += height;

    return field[y % height][x % width];
}

int GameOfLife::countNeighbors(int x, int y) const
{
    int count = 0;

    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dx == 0 && dy == 0)
                continue;
            if (getCell(x + dx, y + dy))
                count++;
        }

    return count;
}

bool GameOfLife::nextCellState(int x, int y) const
{
    int neighbors = countNeighbors(x, y);

    if (getCell(x, y))
        return (neighbors == 2 || neighbors == 3);

    return (neighbors == 3);
}

void GameOfLife::step()
{
    std::vector<std::vector<bool>> next = field;

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            next[y][x] = nextCellState(x, y);

    field = std::move(next);
}
