/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#include "maze.h"

#include <stdexcept>
#include <sstream>
#include <vector>


Coord& Coord::move(Direction dir) {
    switch (dir) {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            throw std::invalid_argument("unknown direction");
    }
    return *this;
}


Coord Coord::offset(const Coord& off) {
    return {x + off.x, y + off.y};
}


std::string Coord::str() const {
    std::ostringstream out;
    out << "<" << x << ", " << y << ">";
    return out.str();
}


const Coord Coord::zero{0, 0};


Direction oppositeDirection(Direction dir) {
    switch (dir) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        default:
            throw std::invalid_argument("unknown direction");
    }
}


MazeFull::MazeFull(int width, int height) : width(width), height(height) {
    grid.resize(width*height, EMPTY);
}


/**
 * Mapping:
 * 0 -> EMPTY
 * 1 -> WALL
 * 2 -> CHEESE
 */
MazeFull::MazeFull(int width, int height, int* mapping) : MazeFull(width, height) {
    for (int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            if(mapping[y * width + x] == 1) { setStatus(Coord{x, y}, WALL); }
            if(mapping[y * width + x] == 2) { setStatus(Coord{x, y}, CHEESE); }
        }
    }
}


// grid is fully copied from input, and the cheese placed in it.
MazeFull::MazeFull(int width, int height, const std::vector<MazeStatus>& grid, Coord cheese) : width(width), height(height), grid(grid) {
    if (!boundCheck(cheese)) { throw std::out_of_range("ctor. coordinate is out of range"); }
    setStatus(cheese, CHEESE);
}


MazeStatus MazeFull::getStatus(const Coord& coord) const {
    if (!boundCheck(coord)) { throw std::out_of_range("coordinate is out of range"); }

    return grid[coord.x + coord.y * width];
}


void MazeFull::setStatus(const Coord& coord, MazeStatus status) {
    if (!boundCheck(coord)) { throw std::out_of_range("coordinate is out of range"); }
    if(getStatus(coord) == WALL) { throw std::invalid_argument("tried to change the status of a wall"); }

    grid[coord.x + coord.y * width] = status;
}


bool MazeFull::boundCheck(Coord pos) const {
    return (pos.x >= 0 && pos.x < width &&
            pos.y >= 0 && pos.y < height);
}


MazeForMouse::MazeForMouse(const MazeFull& maze, const Coord& initial, int max_dim) : maze(maze), pos(initial), max_dim(max_dim) {}


bool MazeForMouse::tryMove(Direction dir) {
    Coord tmp = pos;
    tmp.move(dir);
    if(maze.boundCheck(tmp) && maze.getStatus(tmp) != WALL) {
        pos.move(dir);
        return true;
    } else {
        return false;
    }
}


bool MazeForMouse::foundCheese() const {
    return maze.getStatus(pos) == CHEESE;
}
