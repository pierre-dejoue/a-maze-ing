/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#include "input.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


GridInput::GridInput(const std::string& name, int width, int height)
    : name(name)
    , width(width)
    , height(height)
{
    grid.resize(width * height, EMPTY);
}

enum ParsingState
{
    FILE_START,
    GRID_START,
    WIDTH,
    HEIGHT,
    ROWS,
};

class lineParser
{
public:
    ParsingState state;
    std::vector<GridInput> grids;

    lineParser()
        : state(FILE_START)
        , name()
        , width(0)
        , height(0)
        , rowCounter(0)
    { }

    /*
     * Parse one line from the input file, based on parsing_state
     *
     *    file format:
     *      GRID <title>        <--- beginning of a new grid
     *      80                  <--- width
     *      60                  <--- height
     *        #    #  #         <--- first row. # to mark walls.
     *      ...
     *                          <--- tail blank rows are optional
     */
    bool parseInputLine(const std::string& line_to_parse)
    {
        bool valid_line = false;
        std::string token = line_to_parse.substr(0,4);

        // Only one token, 'GRID', which has the effect of resetting the state machine
        if(token == "GRID")
        {
            state = WIDTH;
            rowCounter = 0;
            name = line_to_parse.substr(5);
            valid_line = true;
        }
        else
        {
            switch (state)
            {
                case FILE_START:
                case GRID_START:
                    valid_line = true;
                    break;

                case WIDTH:
                    width = stoi(line_to_parse);
                    state = HEIGHT;
                    valid_line = true;
                    break;

                case HEIGHT:
                    height = stoi(line_to_parse);
                    grids.push_back(GridInput(name, width, height));
                    state = ROWS;
                    valid_line = true;
                    break;

                case ROWS:
                {
                    int y = 0;
                    for (auto c : line_to_parse) {
                        if (c == '#') {
                            grids.back().grid[rowCounter * width + y] = WALL;
                        }
                        if (y++ == width) {
                            break;
                        }
                    }
                    if (++rowCounter == height) {
                        state = GRID_START;
                    }
                    valid_line = true;
                    break;
                }

                default:
                    assert(0);
                    break;
            }
        }

        return valid_line;
    }

private:
    std::string name;
    int width;
    int height;
    int rowCounter;
};

int parseMazeInputFile(const std::string& filename, std::vector<GridInput>& outgrids)
{
    constexpr unsigned int INPUT_BUFFER_SZ = 2048u;
    try
    {
        std::ifstream inputstream(filename, std::ios_base::in);
        if(!inputstream.is_open()) {
            std::cerr << "Cannot open file " << filename << std::endl;
            return 4;
        }

        lineParser parser;
        char line[INPUT_BUFFER_SZ];
        unsigned int line_nb = 0;
        while(inputstream.good()) {
            line_nb++;
            inputstream.getline(line, INPUT_BUFFER_SZ - 1);
            if (!parser.parseInputLine(std::string(line)))
            {
                std::cerr << "Parsing error on line " << line_nb << " (parsing_state = " << parser.state << "): " << line << std::endl;
            }
        }

        std::cout << "Parsed " << line_nb << " lines and " << parser.grids.size() << " grids in file " << filename << std::endl;
        outgrids = std::move(parser.grids);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error reading file " << filename << ": " << e.what() << std::endl;
        return 5;
    }
    return 0;
}
