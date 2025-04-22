/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#include "graphics.h"

#include "maze.h"

#include <cassert>


const sf::Color unknownTile{0, 0, 0};
const sf::Color emptyTile{250, 250, 250};
const sf::Color wallTile{105, 105, 105};
const sf::Color cheeseTile{255, 216, 0};
const sf::Color exploredTile{160, 160, 240};
const sf::Color pathTile{0, 0, 160};


void draw(const MazeFull& mazeFull, sf::RenderWindow& window, float scale)
{
    auto width = window.getSize().x;
    auto height = window.getSize().y;
    const sf::Vector2f origin{width / 2 - mazeFull.width / 2 * scale, height / 2 - mazeFull.height / 2 * scale};

    for (int y = 0; y < mazeFull.height; y++)
    {
        for (int x = 0; x < mazeFull.width; x++)
        {
           sf::RectangleShape rectangle({scale, scale});
           rectangle.setPosition({origin.x + scale * x, origin.y + scale * y});
           switch (mazeFull.getStatus(Coord{ x, y }))
           {
               case UNKNOWN:
                   rectangle.setFillColor(unknownTile);
                   break;
               case EMPTY:
                   rectangle.setFillColor(emptyTile);
                   break;
               case WALL:
                   rectangle.setFillColor(wallTile);
                   break;
               case CHEESE:
                   rectangle.setFillColor(cheeseTile);
                   break;
               case EXPLORED:
                   rectangle.setFillColor(exploredTile);
                   break;
               case PATH:
                   rectangle.setFillColor(pathTile);
                   break;
               default:
                   assert(0);
           }
           window.draw(rectangle);
        }
    }
}
