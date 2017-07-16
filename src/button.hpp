#pragma once
#include "sdl_wrappers.hpp"
#include <functional>
#include <vector>

struct Button
{
	Button(const SDL_Rect r, const SdlTexture* t, std::function<void(void)> a)
		: rectangle(r), texture(t), action(a) {}
	SDL_Rect rectangle;
	const SdlTexture* texture;
	std::function<void(void)> action;
};

void handle_buttons(const std::vector<Button>& buttons);
