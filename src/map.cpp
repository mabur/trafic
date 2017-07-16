#include "map.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace map
{

Tile::type map_object_from_char(char x)
{
	using namespace std;
	const auto first = begin(CHARACTERS);
	const auto last = end(CHARACTERS);
	const auto it = find(first, last, x);
	return static_cast<Tile::type>(distance(first, it));
}

Map read()
{
	using namespace std;
	auto file = ifstream(FILE_PATH);

	auto line = string{};

	auto lines = vector<string>{};
	auto width = size_t{0};
	while (getline(file, line))
	{
		lines.push_back(line);
		width = max(width, line.size());
	}
	const auto height = lines.size();
	
	auto map = Map(width, height);
	for (size_t y = 0; y < height; ++y)
	{
		assert(lines[y].size() == width);
		for (size_t x = 0; x < width; ++x)
		{
			map(x, y) = map_object_from_char(lines[y][x]);
		}
	}

	return map;
}

void print(const Map& map)
{
	const auto width  = map.extent<0>();
	const auto height = map.extent<1>();
	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			std::cout << CHARACTERS[map(x, y)];
		}
		std::cout << std::endl;
	}
}

TileArray<SdlTexture> make_textures(Sdl& sdl)
{
	return {SdlTexture(sdl, map::TEXTURE_FILE_PATHS[0].c_str()),
			SdlTexture(sdl, map::TEXTURE_FILE_PATHS[1].c_str()),
			SdlTexture(sdl, map::TEXTURE_FILE_PATHS[2].c_str())};
}

void draw(Sdl& sdl, const TileArray<SdlTexture>& textures, const Map& map, const Camera& camera)
{
	const auto map_width  = map.extent<0>();
	const auto map_height = map.extent<1>();

	for (auto y = 0; y < map_height; ++y)
	{
		for (auto x = 0; x < map_width; ++x)
		{
			const auto& texture = textures[map(x, y)];
			const auto destination_x = x * TILE_WIDTH  - camera.x;
			const auto destination_y = y * TILE_HEIGHT - camera.y;
			sdl.render_texture(texture, destination_x, destination_y);
		}
	}
}

int get_pixel_width(const Map& map)
{
	return static_cast<int>(map.extent<0>()) * TILE_WIDTH;
}

int get_pixel_height(const Map& map)
{
	return static_cast<int>(map.extent<1>()) * TILE_HEIGHT;
}

}
