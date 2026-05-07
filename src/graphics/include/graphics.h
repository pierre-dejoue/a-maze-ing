/* Copyright (c) 2018 Pierre DEJOUE
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */
#pragma once

#include <SFML/Graphics.hpp>

#include <string_view>

class MazeFull;

namespace graphics {

void draw(const MazeFull& mazeFull, sf::RenderWindow& window, float scale = 1.0);

std::string_view framework_name_and_version();

} // namespace graphics
