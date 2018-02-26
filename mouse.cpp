#include "maze.hpp"
#include "mouse.hpp"
#include <stack>
#include <vector>

using namespace std;

const vector<direction> step::allfour{ UP, LEFT, DOWN, RIGHT };

step::step() : from(LEFT), lefttoexplore(allfour) {};

step::step(direction next) : from(oppositeDirection(next)) {
    for(auto dir : allfour) {
        if (dir != from && dir != next) {
            lefttoexplore.push_back(dir);
        }
    }
    // favor the same direction on successive steps
    lefttoexplore.push_back(next);
}

bool step::tryDirection(direction & outdir) {
    if(lefttoexplore.empty()) {
        return false;
    } else {
        outdir = lefttoexplore.back();
        lefttoexplore.pop_back();
        return true;
   }
}

mouse::mouse(mazeForMouse& maze) : maze(maze), relativePos(coord::zero), width(2*maze.max_dim + 1) {
    path.push(step());
    explored.resize(width * width, UNKNOWN);
}

// with width = 2* max_dim + 1
int mouse::to1D(const coord& pos) { return (pos.y + maze.max_dim) * width + (pos.x + maze.max_dim); }

void mouse::mark(const coord& pos, mazeStatus status) {
    explored[to1D(pos)] = status;
}

void mouse::markWall(coord pos, direction dir) {
    mark(pos.move(dir), WALL);
}

bool mouse::isExplored(coord pos, direction dir) {
    return explored[to1D(pos.move(dir))] != UNKNOWN;
}

bool mouse::nextStep(coord& outPos) {
    mark(relativePos);  // Mark current position as explored
    if (maze.foundCheese()) {
        outPos = relativePos;
        return true;
    } else if(!path.empty()) {
        direction next;
        if(path.top().tryDirection(next)) {
            // Attempt to move in direction 'next'
            if (!isExplored(relativePos, next)) {
                if (maze.tryMove(next)) {
                    relativePos.move(next);
                    path.push(step(next));
                } else {
                    markWall(relativePos, next);
                }
            } // else, do nothing, the next iteration will attempt another direction
        } else {
            // backtrack
            auto from = path.top().from;
            path.pop();
            if (!path.empty()) {
                if (!maze.tryMove(from)) { throw logic_error("Impossible"); }
                relativePos.move(from);
            }

        }
    } // else if path is empty, we have explored the whole maze and did not find the cheese
    outPos = relativePos;
    return false;
}
