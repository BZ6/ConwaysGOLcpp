#pragma once
#include <vector>

class GameOfLife
{
public:
    GameOfLife(int width, int height);

    void clear();
    void setCell(int x, int y, bool alive);
    bool getCell(int x, int y) const;
    void step();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    const std::vector<std::vector<bool>> &getField() const { return field; }

private:
    int width, height;
    std::vector<std::vector<bool>> field;

    int countNeighbors(int x, int y) const;
    bool nextCellState(int x, int y) const;
};
