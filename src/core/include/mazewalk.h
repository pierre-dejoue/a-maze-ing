/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#pragma once

#include "input.h"
#include "maze.h"
#include "mouse.h"

#include <memory>
#include <vector>


/*
 * Walk through solving multiple mazes, one mouse step at a time!
 */
class Mazewalk {
public:
    Mazewalk(std::vector<GridInput>& grids);

    MazeFull& nextMouseStep();

private:
    std::vector<GridInput>& grids;
    unsigned int index;
    std::unique_ptr<MazeFull> currentMaze;
    std::unique_ptr<MazeForMouse> mazeformouse;
    std::unique_ptr<Mouse> theMouse;
    Coord previousPos;
    Coord origin;           // Starting position in the maze

    void setupNextMaze(int index);
};
