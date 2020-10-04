/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#pragma once


#include <iostream>
#include <vector>


enum direction {
    UP,
    LEFT,
    DOWN,
    RIGHT,
};


direction oppositeDirection(direction dir);


class coord {
public:
    int x;
    int y;
    coord() : x(0), y(0) {};
    coord(int x, int y) : x(x), y(y) {};
    coord(const coord& coord) = default;
    coord& operator= (const coord& other) = default;
    coord& move(direction dir);
    coord offset(const coord& off);
    std::string str() const;
    static const coord zero;
};


inline bool operator== (const coord& one, const coord& two) { return one.x == two.x && one.y == two.y; }
inline bool operator!= (const coord& one, const coord& two) { return one.x != two.x || one.y != two.y; }


enum mazeStatus {
    UNKNOWN = 0,
    EMPTY,
    WALL,
    EXPLORED,
    PATH,
    CHEESE,
};


class mazeFull {
public:
    const int width;
    const int height;

    mazeFull(int width, int height);
    mazeFull(int width, int height, int* mapping);
    mazeFull(int width, int height, const std::vector<mazeStatus>& grid, coord cheese);
    mazeStatus getStatus(const coord& coord) const;
    void setStatus(const coord& coord, mazeStatus status);
    bool boundCheck(coord pos) const;

private:
    std::vector<mazeStatus> grid;
};


class mazeForMouse {
public:
    mazeForMouse(const mazeFull& maze, const coord& initial, int max_dim);
    bool tryMove(direction dir);
    bool foundCheese() const;

private:
    const mazeFull& maze;
    coord pos;

public:
    int max_dim;
};
