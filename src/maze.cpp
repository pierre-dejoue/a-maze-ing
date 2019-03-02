/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#include "maze.h"


#include <stdexcept>
#include <sstream>
#include <vector>


coord& coord::move(direction dir) {
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
    }
    return *this;
}


coord coord::offset(const coord& off) {
    return {x + off.x, y + off.y};
}


std::string coord::str() const {
    std::ostringstream out;
    out << "<" << x << ", " << y << ">";
    return out.str();
}


const coord coord::zero{0, 0};


direction oppositeDirection(direction dir) {
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


mazeFull::mazeFull(int width, int height) : width(width), height(height) {
    grid.resize(width*height, EMPTY);
}


/**
 * Mapping:
 * 0 -> EMPTY
 * 1 -> WALL
 * 2 -> CHEESE
 */
mazeFull::mazeFull(int width, int height, int* mapping) : mazeFull(width, height) {
    for (int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            if(mapping[y * width + x] == 1) { setStatus(coord{x, y}, WALL); }
            if(mapping[y * width + x] == 2) { setStatus(coord{x, y}, CHEESE); }
        }
    }
}


// grid is fully copied from input, and the cheese placed in it.
mazeFull::mazeFull(int width, int height, const std::vector<mazeStatus>& grid, coord cheese) : width(width), height(height), grid(grid) {
    if (!boundCheck(cheese)) { throw std::out_of_range("ctor. coordinate is out of range"); }
    setStatus(cheese, CHEESE);
}


mazeStatus mazeFull::getStatus(const coord& coord) const {
    if (!boundCheck(coord)) { throw std::out_of_range("coordinate is out of range"); }

    return grid[coord.x + coord.y * width];
}


void mazeFull::setStatus(const coord& coord, mazeStatus status) {
    if (!boundCheck(coord)) { throw std::out_of_range("coordinate is out of range"); }
    if(getStatus(coord) == WALL) { throw std::invalid_argument("tried to change the status of a wall"); }

    grid[coord.x + coord.y * width] = status;
}


bool mazeFull::boundCheck(coord pos) const {
    return (pos.x >= 0 && pos.x < width &&
            pos.y >= 0 && pos.y < height);
}


mazeForMouse::mazeForMouse(const mazeFull& maze, const coord& initial, int max_dim) : maze(maze), pos(initial), max_dim(max_dim) {}


bool mazeForMouse::tryMove(direction dir) {
    coord tmp = pos;
    tmp.move(dir);
    if(maze.boundCheck(tmp) && maze.getStatus(tmp) != WALL) {
        pos.move(dir);
        return true;
    } else {
        return false;
    }
}


bool mazeForMouse::foundCheese() const {
    return maze.getStatus(pos) == CHEESE;
}
