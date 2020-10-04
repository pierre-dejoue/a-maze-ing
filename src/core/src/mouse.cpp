/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#include "mouse.h"

#include "maze.h"

#include <stack>
#include <stdexcept>
#include <vector>


const std::vector<Direction> MouseStep::allfour{ UP, LEFT, DOWN, RIGHT };


MouseStep::MouseStep() : from(LEFT), lefttoexplore(allfour) {};


MouseStep::MouseStep(Direction next) : from(oppositeDirection(next)) {
    for(auto dir : allfour) {
        if (dir != from && dir != next) {
            lefttoexplore.push_back(dir);
        }
    }
    // favor the same direction on successive steps
    lefttoexplore.push_back(next);
}


bool MouseStep::tryDirection(Direction & outdir) {
    if(lefttoexplore.empty()) {
        return false;
    } else {
        outdir = lefttoexplore.back();
        lefttoexplore.pop_back();
        return true;
   }
}


Mouse::Mouse(MazeForMouse& maze) : maze(maze), relativePos(Coord::zero), width(2*maze.max_dim + 1) {
    path.push(MouseStep());
    explored.resize(width * width, UNKNOWN);
}


// with width = 2* max_dim + 1
int Mouse::to1D(const Coord& pos) { return (pos.y + maze.max_dim) * width + (pos.x + maze.max_dim); }


void Mouse::mark(const Coord& pos, MazeStatus status) {
    explored[to1D(pos)] = status;
}


void Mouse::markWall(Coord pos, Direction dir) {
    mark(pos.move(dir), WALL);
}


bool Mouse::isExplored(Coord pos, Direction dir) {
    return explored[to1D(pos.move(dir))] != UNKNOWN;
}


bool Mouse::nextStep(Coord& outPos) {
    mark(relativePos);  // Mark current position as explored
    if (maze.foundCheese()) {
        outPos = relativePos;
        return true;
    } else if(!path.empty()) {
        Direction next;
        if(path.top().tryDirection(next)) {
            // Attempt to move in direction 'next'
            if (!isExplored(relativePos, next)) {
                if (maze.tryMove(next)) {
                    relativePos.move(next);
                    path.push(MouseStep(next));
                } else {
                    markWall(relativePos, next);
                }
            } // else, do nothing, the next iteration will attempt another direction
        } else {
            // backtrack
            auto from = path.top().from;
            path.pop();
            if (!path.empty()) {
                if (!maze.tryMove(from)) { throw std::logic_error("Impossible"); }
                relativePos.move(from);
            }

        }
    } // else if path is empty, we have explored the whole maze and did not find the cheese
    outPos = relativePos;
    return false;
}
