/* Copyright (c) 2018, Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#include "graphics.hpp"
#include "input.hpp"
#include "maze.hpp"
#include "mazewalk.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <thread>

const int winWidth{800};
const int winHeight{800};

using namespace std;
using namespace sf;

int main(int argc, char *argv[])
{
    try {
        /*
         * Process command line
         */
        char * filename;
        if(argc == 2)
        {
            filename = argv[1];  // input filename
        }
        else
        {
            cerr << "Usage:" << endl;
            cerr << "    amazing input_filename" << endl;
            exit(1);
        }

        /*
         * Parse input file
         */
        vector<gridInput> grids;
        parseMazeInputFile(filename, grids);
        auto walker = mazewalk(grids);

        /*
         * Display maze
         */
        RenderWindow window({winWidth, winHeight}, "A Maze Ing!");
        window.setFramerateLimit(60);

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear();

            draw(walker.nextMouseStep(), window, 20.0);
            window.display();
        }

    } catch (exception& e) { cerr << "ERROR: " << e.what() << endl; exit(1); }

    return 0;
}
