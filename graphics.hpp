/* Copyright (c) 2018, Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include "maze.hpp"
#include <SFML/Graphics.hpp>

void draw(const mazeFull& mazeFull, sf::RenderWindow& window, float scale = 1.0);


#endif // _GRAPHICS_HPP_
