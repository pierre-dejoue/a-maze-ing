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


GridInput::GridInput(std::string name, int width, int height) : name(name), width(width), height(height) {
    grid.resize(width * height, EMPTY);
}

enum ParsingState {
    FILE_START,
    GRID_START,
    WIDTH,
    HEIGHT,
    ROWS,
};


const int INPUT_BUFFER_SZ = 2048;


class lineParser {
public:
    ParsingState state;
    std::vector<GridInput> grids;

    lineParser() : state(FILE_START), name(""), width(0), height(0), rowCounter(0) {}

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
    bool parseInputLine(const std::string& line_to_parse) {
        bool valid_line = false;
        std::string token = line_to_parse.substr(0,4);

        // Only one token, 'GRID', which has the effect of resetting the state machine
        if(token == "GRID") {
            state = WIDTH;
            rowCounter = 0;
            name = line_to_parse.substr(5);
            valid_line = true;
        } else {
            switch (state) {
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


void parseMazeInputFile(std::string filename, std::vector<GridInput>& outgrids) {
    std::ifstream inputstream;
    inputstream.open(filename);
    if(!inputstream.is_open()) {
        std::cerr << "Cannot open file " << filename << std::endl;
        exit(1);
    }

    lineParser parser;

    char line[INPUT_BUFFER_SZ];
    int line_nb = 0;
    bool is_line_ok;
    while(inputstream.good()) {
        line_nb++;
        inputstream.getline(line, INPUT_BUFFER_SZ - 1);
        if((is_line_ok = parser.parseInputLine(std::string(line))) == false) {
            std::cerr << "Parsing error on line " << line_nb << " (parsing_state = " << parser.state << "): " << line << std::endl;
        }
    }

    std::cout << "parsed " << line_nb << " lines." << std::endl;

    // Close file. TODO: use RAII to mimic a try/finally block
    inputstream.close();

    outgrids = parser.grids;
}
