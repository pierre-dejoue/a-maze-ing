/* Copyright (c) 2018, Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#include "mazewalk.hpp"

#include <algorithm>
#include <cstdlib>

using namespace std;


coord randomEmptyLocation(const gridInput& grid) {
    bool found = false;
    coord result;
    while (!found) {
        int x = rand() % grid.width;
        int y = rand() % grid.height;
        if (grid.grid[y * grid.width + x] == EMPTY) {
            found = true;
            result = {x, y};
        }
    }
    return result;
}

mazewalk::mazewalk(vector<gridInput>& grids) : grids(grids) {
    if (grids.empty()) { throw invalid_argument("Empty maze list!"); }
    index = 0;
    setupNextMaze(index);
}

mazeFull& mazewalk::nextMouseStep() {
    coord relativePos;
    coord currentPos;
    bool foundCheese;

    do {
        foundCheese = theMouse->nextStep(relativePos);

        if (foundCheese) {
            if (++index == grids.size()) {
                index = 0;
            }
            setupNextMaze(index);
        } else {
            currentPos = relativePos.offset(origin);
            if (currentPos != previousPos) {
                if(currentMaze->getStatus(currentPos) == EMPTY) {
                    currentMaze->setStatus(currentPos, PATH);
                } else if (currentMaze->getStatus(previousPos) == PATH) {
                    currentMaze->setStatus(previousPos, EXPLORED);
                }
            }
        }
    } while (!foundCheese && previousPos == currentPos);

    previousPos = currentPos;

    return *currentMaze;
}

void mazewalk::setupNextMaze(int index) {
    // change grid
    gridInput& currentGrid = grids.at(index);

    // random cheese and mouse positions
    origin = randomEmptyLocation(currentGrid);
    auto cheesePosition = randomEmptyLocation(currentGrid);

    // Initialize all the things
    currentMaze.reset(new mazeFull(currentGrid.width, currentGrid.height, currentGrid.grid, cheesePosition));
    mazeformouse.reset(new mazeForMouse(*currentMaze, origin, max(currentGrid.width, currentGrid.height)));
    theMouse.reset(new mouse(*mazeformouse));
    previousPos = origin;
}
