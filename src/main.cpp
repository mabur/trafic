#include <iostream>
#include "sdl_wrappers.hpp"
#include "map.hpp"
#include "input.hpp"
#include "menu.hpp"

int main(int, char**)
{	
	auto map = map::read();

	map::print(map);

    const auto window_title = "Trafic";
	const auto camera_width = 640;
	const auto camera_height = 480;

	auto sdl = Sdl(window_title, camera_width, camera_height);

	const auto map_textures = map::make_textures(sdl);

	auto camera = Camera{};
	camera.x = 0;
	camera.y = 0;
	camera.max_x = map::get_pixel_width(map) - camera_width;
	camera.max_y = map::get_pixel_height(map) - camera_height;
	camera.width = camera_width;
	camera.height = camera_height;

	map::Tile::type current_construction_tile = map::Tile::ROAD;

	auto buttons = menu::make_menu_buttons(map_textures, current_construction_tile);
	const auto button = menu::make_screen_button(map, current_construction_tile, camera);
	buttons.push_back(button);

    while (noQuitMessage())
    {
		camera = handleInput(camera);
		handle_buttons(buttons);

		map::draw(sdl, map_textures, map, camera);
		menu::draw(sdl, map_textures);
		SDL_RenderPresent(sdl.renderer);
    }
    return 0;
}
