#include "button.hpp"

void handle_buttons(const std::vector<Button>& buttons)
{
	// TODO: write wrapper for mouse state.
	auto mouse_x = 0;
	auto mouse_y = 0;
	const auto mouse = SDL_GetMouseState(&mouse_x, &mouse_y);
	if (!isLeftMouseButtonDown(mouse))
	{
		return;
	}
	for (const auto& button : buttons)
	{
		if (is_in_rectangle(mouse_x, mouse_y, button.rectangle))
		{
			button.action();
		}
	}
}