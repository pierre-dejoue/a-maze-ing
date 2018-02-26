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
