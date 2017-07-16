#pragma once

#include <iostream>
#include <vector>

#include "SDL.h"

void printError(const char* context);
bool noQuitMessage();
bool is_in_rectangle(int x, int y, const SDL_Rect& r);
bool isLeftMouseButtonDown(Uint32 mouse_state);
bool isRightMouseButtonDown(Uint32 mouse_state);

class SdlTexture;

class Sdl
{
public:
    Sdl(const char* window_title, int width, int height);
    ~Sdl();
    void clear();
    void update();
	void setPixels(const Uint32* pixels_begin);
	void render_texture(const SdlTexture& texture, int x, int y);
	SDL_Renderer* renderer;

private:
	int pitch() const;
	int width;
	int height;
	SDL_Window* window;
	SDL_Texture* texture;
	std::vector<Uint32> pixels;
};

class SdlSurface
{
public:
	SdlSurface(const char* file_path)
	{
		surface_ = SDL_LoadBMP(file_path);
		if (!surface_)
		{
			throw "Could not create surface.";
		}
	}
	~SdlSurface()
	{
		SDL_FreeSurface(surface_);
	}
	SDL_Surface* surface_;
};

class SdlTexture
{
public:
	SdlTexture(Sdl& sdl, const char* file_path)
	{
		const auto surface = SdlSurface(file_path);
		texture_ = SDL_CreateTextureFromSurface(sdl.renderer, surface.surface_);
		if (!texture_)
		{
			throw "Could not create texture.";
		}
	}
	~SdlTexture()
	{
		SDL_DestroyTexture(texture_);
	}
	int get_width() const
	{
		int width;
		SDL_QueryTexture(texture_, nullptr, nullptr, &width, nullptr);
		return width;
	}
	int get_height() const
	{
		int height;
		SDL_QueryTexture(texture_, nullptr, nullptr, nullptr, &height);
		return height;
	}

	SDL_Texture* texture_;
private:
};
