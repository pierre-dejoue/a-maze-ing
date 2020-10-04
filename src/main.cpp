/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */

#include "graphics.h"
#include "input.h"
#include "maze.h"
#include "mazewalk.h"

#include <exception>
#include <iostream>
#include <vector>

constexpr unsigned int winWidth = 800;
constexpr unsigned int winHeight = 800;

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
        std::vector<GridInput> grids;
        parseMazeInputFile(filename, grids);
        auto walker = Mazewalk(grids);

        /*
         * Display maze
         */
        unsigned width = winWidth;
        unsigned height = winHeight;
        sf::RenderWindow window({ width, height }, "a-maze-ing!");
        window.setFramerateLimit(60);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();

            draw(walker.nextMouseStep(), window, 20.0);
            window.display();
        }

    } catch (std::exception& e) { std::cerr << "ERROR: " << e.what() << std::endl; exit(2); }

    return 0;
}
