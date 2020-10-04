/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#pragma once


#include <memory>
#include <vector>


#include "input.h"
#include "maze.h"
#include "mouse.h"


/*
 * Walk through solving multiple mazes, one mouse step at a time!
 */
class mazewalk {
public:
    mazewalk(std::vector<gridInput>& grids);

    mazeFull& nextMouseStep();

private:
    std::vector<gridInput>& grids;
    unsigned int index;
    std::unique_ptr<mazeFull> currentMaze;
    std::unique_ptr<mazeForMouse> mazeformouse;
    std::unique_ptr<mouse> theMouse;
    coord previousPos;
    coord origin;           // Starting position in the maze

    void setupNextMaze(int index);
};
