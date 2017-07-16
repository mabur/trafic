#pragma once

#include "sdl_wrappers.hpp"

struct Camera
{
	int x;
	int y;
	int max_x;
	int max_y;
	int width;
	int height;
};

Camera handleInput(Camera camera);
