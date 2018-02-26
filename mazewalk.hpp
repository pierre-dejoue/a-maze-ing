#ifndef _MAZEWALK_HPP_
#define _MAZEWALK_HPP_

#include <vector>

#include "input.hpp"
#include "maze.hpp"
#include "mouse.hpp"

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
    mazeFull* currentMaze;
    mazeForMouse* mazeformouse;
    mouse* theMouse;
    coord previousPos;
    coord origin;           // Starting position in the maze

    void setupNextMaze(int index);
};

#endif // _MAZEWALK_HPP_
