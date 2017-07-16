#include "SDL.h"
#include "menu.hpp"
#include "button.hpp"

namespace menu
{

map::TileArray<SDL_Rect> get_tile_rectangles()
{
	auto rectangles = map::TileArray<SDL_Rect>{};
	for (size_t i = 0; i < rectangles.size(); ++i)
	{
		rectangles[i].x = 0;
		rectangles[i].y = static_cast<int>(i) * map::TILE_HEIGHT;
		rectangles[i].w = map::TILE_WIDTH;
		rectangles[i].h = map::TILE_HEIGHT;
	}
	return rectangles;
}

void draw(Sdl& sdl, const map::TileArray<SdlTexture>& textures)
{
	SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(sdl.renderer, &MENU_RECTANGLE);

	const auto tile_rectangles = get_tile_rectangles();
	for (size_t i = 0; i < textures.size(); ++i)
	{
		sdl.render_texture(textures[i], tile_rectangles[i].x, tile_rectangles[i].y);
	}
}

map::Tile::type get_clicked_tile(int x, int y)
{
	const auto tile_rectangles = get_tile_rectangles();

	for (size_t i = 0; i < tile_rectangles.size(); ++i)
	{
		if (is_in_rectangle(x, y, tile_rectangles[i]))
		{
			return static_cast<map::Tile::type>(i);
		}
	}
	return map::Tile::NONE;
}

std::vector<Button> make_menu_buttons(
	const map::TileArray<SdlTexture>& textures,
	map::Tile::type& current_construction_tile)
{
	auto buttons = std::vector<Button>{};
	for (auto i = 0; i < map::Tile::SIZE; ++i)
	{
		const auto x = 0;
		const auto y = map::TILE_HEIGHT * i;
		const auto w = map::TILE_WIDTH;
		const auto h = map::TILE_HEIGHT;
		const auto rectangle = SDL_Rect{ x, y, w, h };
		const auto action = [&current_construction_tile, i=i]()
		{
			current_construction_tile = i;
		};
		const auto button = Button{ rectangle, &textures[i], action };
		buttons.push_back(button);
	}
	return buttons;
}

Button make_screen_button(map::Map& map, map::Tile::type& current_construction_tile, const Camera& camera)
{
	const auto action = [&]()
	{
		if (current_construction_tile != map::Tile::NONE)
		{
			auto mouse_x = 0;
			auto mouse_y = 0;
			const auto mouse = SDL_GetMouseState(&mouse_x, &mouse_y);
			const auto tile_x = (camera.x + mouse_x) / map::TILE_WIDTH;
			const auto tile_y = (camera.y + mouse_y) / map::TILE_HEIGHT;
			map(tile_x, tile_y) = current_construction_tile;
		}
	};
	return Button(SCREEN_RECTANGLE, nullptr, action);
}

void update_map(
	map::Map& map,
	const map::TileArray<SdlTexture>& textures, 
	map::Tile::type& current_construction_tile, const Camera& camera)
{
	auto buttons = make_menu_buttons(textures, current_construction_tile);

	const auto button = make_screen_button(map, current_construction_tile, camera);

	buttons.push_back(button);
	handle_buttons(buttons);
	return;
}

}
