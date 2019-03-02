/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#include <algorithm>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <thread>


#include "graphics.h"
#include "input.h"
#include "maze.h"
#include "mazewalk.h"


const unsigned winWidth{800};
const unsigned winHeight{800};


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
            std::cerr << "Usage:" << std::endl;
            std::cerr << "    amazing input_filename" << std::endl;
            exit(1);
        }

        /*
         * Parse input file
         */
        std::vector<gridInput> grids;
        parseMazeInputFile(filename, grids);
        auto walker = mazewalk(grids);

        /*
         * Display maze
         */
        unsigned width = winWidth;
        unsigned height = winHeight;
        RenderWindow window({ width, height }, "a-maze-ing!");
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

    } catch (std::exception& e) { std::cerr << "ERROR: " << e.what() << std::endl; exit(2); }

    return 0;
}
