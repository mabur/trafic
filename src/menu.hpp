#pragma once

#include "sdl_wrappers.hpp"
#include "map.hpp"
#include "button.hpp"

namespace menu
{
const auto MENU_RECTANGLE   = SDL_Rect{ 0, 0, 32, 480 };
const auto SCREEN_RECTANGLE = SDL_Rect{ 32, 0, 640 - 32, 480 };

void draw(Sdl& sdl, const map::TileArray<SdlTexture>& textures);

map::Tile::type get_clicked_tile(int x, int y);

void update_map(
	map::Map& map,
	const map::TileArray<SdlTexture>& textures,
	map::Tile::type& current_construction_tile,
	const Camera& camera);

std::vector<Button> make_menu_buttons(
	const map::TileArray<SdlTexture>& textures,
	map::Tile::type& current_construction_tile);

Button make_screen_button(
	map::Map& map,
	map::Tile::type& current_construction_tile,
	const Camera& camera);

}