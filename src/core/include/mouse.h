/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#pragma once

#include "maze.h"

#include <stack>
#include <vector>


class MouseStep {
public:
    Direction from;
    MouseStep();
    MouseStep(Direction next);
    bool tryDirection(Direction & outdir);

private:
    std::vector<Direction> lefttoexplore;
    static const std::vector<Direction> allfour;
};


class Mouse {
public:
    Mouse(MazeForMouse& maze);
    bool nextStep(Coord &pos);

private:
    MazeForMouse& maze;
    Coord relativePos;
    std::stack<MouseStep> path;
    std::vector<MazeStatus> explored;
    int width;

    int to1D(const Coord& pos);
    void mark(const Coord& pos, MazeStatus status = EXPLORED);
    void markWall(Coord pos, Direction dir);
    bool isExplored(Coord pos, Direction dir);
};
