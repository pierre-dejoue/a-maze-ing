/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */

#include "graphics.h"
#include "input.h"
#include "maze.h"
#include "mazewalk.h"

#include <cassert>
#include <exception>
#include <iostream>
#include <optional>
#include <vector>

constexpr unsigned int WIN_W = 800;
constexpr unsigned int WIN_H = 800;

int main(int argc, char *argv[])
{
    try
    {
        /*
         * Process command line
         */
        if (argc != 2)
        {
            std::cerr << "Usage:" << std::endl;
            std::cerr << "    amazing input_filename" << std::endl;
            exit(1);
        }
        const char* input_filename = argv[1];
        assert(input_filename != nullptr);

        /*
         * Parse input file
         */
        std::vector<GridInput> grids;
        {
            const int err_code = parseMazeInputFile(input_filename, grids);
            if (err_code != 0)
            {
                exit(err_code);
            }
        }
        auto walker = Mazewalk(grids);

        /*
         * Display maze
         */
        sf::RenderWindow window(sf::VideoMode({ WIN_W, WIN_H }), "a-maze-ing!");
        window.setFramerateLimit(60);

        while (window.isOpen())
        {
            while (const std::optional<sf::Event> event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>()) { window.close(); }
            }
            window.clear();
            draw(walker.nextMouseStep(), window, 20.0f);
            window.display();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        exit(2);
    }

    return 0;
}
