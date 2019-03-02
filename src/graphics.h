/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#pragma once


#include <SFML/Graphics.hpp>


#include "maze.h"


void draw(const mazeFull& mazeFull, sf::RenderWindow& window, float scale = 1.0);
