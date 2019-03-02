/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#pragma once


#include <cstdlib>
#include <string>
#include <vector>


#include "maze.h"


class gridInput {
public:
    gridInput(std::string name, int width, int height);
public:
    std::string name;
    int width;
    int height;
    std::vector<mazeStatus> grid;
};


void parseMazeInputFile(std::string filename, std::vector<gridInput>& outgrids);
