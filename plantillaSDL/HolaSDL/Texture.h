#ifndef TEXTURE_H
#define TEXTURE_H

#include "checkML.h"
#include <SDL.h>

class Texture
{
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	int width;
	int height;
	int nrows;
	int ncolumns;
	int frameWidth;
	int frameHeight;

	static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename);

public:
	/// Create a texture by loading it from the given file
	Texture(SDL_Renderer* renderer, const char* filename, int rows = 1, int columns = 1);
	/// Create a texture from an SDL texture
	Texture(SDL_Renderer* renderer, SDL_Texture* texture, int rows = 1, int columns = 1);

	// Textures cannot be copied, but they can be moved
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture(Texture&& other);
	Texture& operator=(Texture&& other);

	~Texture();

	/// Width of a frame in pixels
	int getFrameWidth() const;
	/// Height of a frame in pixels
	int getFrameHeight() const;
	/// Number of frames in each row
	int getNumRows() const;
	/// Number of frames in each column
	int getNumColumns() const;

	/// Render the whole picture filling the entire screen
	void render() const;
	/// Render the whole picture to the given rectangle
	void render(const SDL_Rect& target) const;
	/// Render a rectangle full screen
	void renderRect(const SDL_Rect& source) const;
	/// Render the whole picture with additional options from SDL_RenderCopyEx
	void render(const SDL_Rect& target,
		double angle,
		const SDL_Point* center = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	/// Render a frame to the given rectangle
	void renderFrame(const SDL_Rect& target, int row, int col) const;
	/// Render a frame to the given rectangle
	void renderFrame(const SDL_Rect& target, int row, int col, SDL_RendererFlip flip) const;
	/// Render a frame with additional options from SDL_RenderCopyEx
	void renderFrame(const SDL_Rect& target,
		int row,
		int col,
		double angle,
		const SDL_Point* center = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	/// Render the whole picture to the given rectangle with modified color
	void render(const SDL_Rect& target, SDL_Color color) const;
};

inline int
Texture::getFrameWidth() const
{
	return frameWidth;
}

inline int
Texture::getFrameHeight() const
{
	return frameHeight;
}

inline int
Texture::getNumRows() const
{
	return nrows;
}

inline int
Texture::getNumColumns() const
{
	return ncolumns;
}

#endif
