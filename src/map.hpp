#pragma once
#include <array>
#include <string>
#include <gal/include/gal.hpp>
#include "sdl_wrappers.hpp"
#include "input.hpp"

namespace map
{
const auto FILE_PATH = "../../resources/map.txt";

namespace Tile
{
	using type = int;
	enum { NONE = -1, EMPTY = 0, ROAD = 1, HOUSE = 2, SIZE = 3 };
}

const auto TILE_WIDTH  = 16;
const auto TILE_HEIGHT = 16;

template<typename T>
using TileArray = std::array<T, Tile::SIZE>;

const auto CHARACTERS = TileArray<char>{ '.', '#', 'H' };
const auto TEXTURE_FILE_PATHS = TileArray<std::string>{
	"../../resources/grass.bmp",
	"../../resources/road.bmp",
	"../../resources/house.bmp" };

TileArray<SdlTexture> make_textures(Sdl& sdl);

using Map = gal::darray<Tile::type, 2>;

int get_pixel_width(const Map& map);
int get_pixel_height(const Map& map);

void draw(Sdl& sdl, const TileArray<SdlTexture>& textures, const Map& map, const Camera& camera);

Map read();
void print(const Map& map);

}
