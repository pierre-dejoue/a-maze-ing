#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include "maze.hpp"
#include <memory>
#include <stack>
#include <vector>

class step {
public:
    direction from;
    step();
    step(direction next);
    bool tryDirection(direction & outdir);

private:
    std::vector<direction> lefttoexplore;
    static const std::vector<direction> allfour;
};


class mouse {
public:
    mouse(mazeForMouse& maze);
    bool nextStep(coord &pos);

private:
    mazeForMouse& maze;
    coord relativePos;
    std::stack<step> path;
    std::vector<mazeStatus> explored;
    int width;

    int to1D(const coord& pos);
    void mark(const coord& pos, mazeStatus status = EXPLORED);
    void markWall(coord pos, direction dir);
    bool isExplored(coord pos, direction dir);
};

#endif // _MOUSE_HPP_
