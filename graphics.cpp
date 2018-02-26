#include "graphics.hpp"
#include "maze.hpp"

using namespace sf;

const Color unknownTile{0, 0, 0};
const Color emptyTile{250, 250, 250};
const Color wallTile{105, 105, 105};
const Color cheeseTile{255, 216, 0};
const Color exploredTile{160, 160, 240};
const Color pathTile{0, 0, 160};

void draw(const mazeFull& mazeFull, RenderWindow& window, float scale) {
    auto width = window.getSize().x;
    auto height = window.getSize().y;
    Vector2f origin{width / 2 - mazeFull.width / 2 * scale, height / 2 - mazeFull.height / 2 * scale};

    for (int y = 0; y < mazeFull.height; y++) {
        for (int x = 0; x < mazeFull.width; x++) {
           RectangleShape rectangle({scale, scale});
           rectangle.setPosition({origin.x + scale * x, origin.y + scale * y});
           switch(mazeFull.getStatus(coord{x, y})) {
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
           }
           window.draw(rectangle);
        }
    }
}

