#include "input.hpp"

#include <algorithm>

#include "SDL.h"

Camera handleInput(Camera camera)
{
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	//auto mouse_x = 0;
	//auto mouse_y = 0;
	//const auto mouse = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
	const auto keyboard = SDL_GetKeyboardState(NULL);

	const auto SPEED = 4;
	auto speed_x = 0;
	auto speed_y = 0;

	if (keyboard[SDL_SCANCODE_LEFT])
	{
		speed_x -= SPEED;
	}
	if (keyboard[SDL_SCANCODE_RIGHT])
	{
		speed_x += SPEED;
	}
	if (keyboard[SDL_SCANCODE_UP])
	{
		speed_y -= SPEED;
	}
	if (keyboard[SDL_SCANCODE_DOWN])
	{
		speed_y += SPEED;
	}
	camera.x += speed_x;
	camera.y += speed_y;
	camera.x = std::min(std::max(camera.x, 0), camera.max_x);
	camera.y = std::min(std::max(camera.y, 0), camera.max_y);

	//if (isLeftMouseButtonDown(mouse))
	//{
	//	velocity_camera(1) += velocity;
	//}
	//if (isRightMouseButtonDown(mouse))
	//{
	//	velocity_camera(1) -= velocity;
	//}

	return camera;
}
