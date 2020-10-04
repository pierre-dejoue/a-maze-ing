/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#pragma once

#include <string>
#include <vector>


enum Direction {
    UP,
    LEFT,
    DOWN,
    RIGHT,
};


Direction oppositeDirection(Direction dir);


class Coord {
public:
    int x;
    int y;
    Coord() : x(0), y(0) {};
    Coord(int x, int y) : x(x), y(y) {};
    Coord(const Coord& coord) = default;
    Coord& operator= (const Coord& other) = default;
    Coord& move(Direction dir);
    Coord offset(const Coord& off);
    std::string str() const;
    static const Coord zero;
};


inline bool operator== (const Coord& one, const Coord& two) { return one.x == two.x && one.y == two.y; }
inline bool operator!= (const Coord& one, const Coord& two) { return one.x != two.x || one.y != two.y; }


enum MazeStatus {
    UNKNOWN = 0,
    EMPTY,
    WALL,
    EXPLORED,
    PATH,
    CHEESE,
};


class MazeFull {
public:
    MazeFull(int width, int height);
    MazeFull(int width, int height, int* mapping);
    MazeFull(int width, int height, const std::vector<MazeStatus>& grid, Coord cheese);
    MazeStatus getStatus(const Coord& coord) const;
    void setStatus(const Coord& coord, MazeStatus status);
    bool boundCheck(Coord pos) const;

public:
    const int width;
    const int height;

private:
    std::vector<MazeStatus> grid;
};


class MazeForMouse {
public:
    MazeForMouse(const MazeFull& maze, const Coord& initial, int max_dim);
    bool tryMove(Direction dir);
    bool foundCheese() const;

private:
    const MazeFull& maze;
    Coord pos;

public:
    int max_dim;
};
