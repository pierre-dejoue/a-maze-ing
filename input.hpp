/* Copyright (c) 2018, Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "maze.hpp"

#include <stdlib.h>
#include <string>
#include <vector>

class gridInput {
public:
    std::string name;
    int width;
    int height;
    std::vector<mazeStatus> grid;

    gridInput(std::string name, int width, int height);
};

void parseMazeInputFile(std::string filename, std::vector<gridInput>& outgrids);

#endif // _INPUT_HPP_
