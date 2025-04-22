/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#pragma once

#include "maze.h"

#include <string>
#include <vector>


struct GridInput
{
    GridInput(const std::string& name, int width, int height);

    std::string name;
    int width;
    int height;
    std::vector<MazeStatus> grid;
};


int parseMazeInputFile(const std::string& filename, std::vector<GridInput>& outgrids);
