#include "Button.h"
#include "SDL.h"



Button::Button(int x, int y, int w, int h, SDL_Texture* tex, SDL_Texture* mushTex) : rect{ x, y, w, h }, 
																					texture(tex), 
																					mushroomTexture(mushTex), 
																					isMouseOver(false) 
{
	boundingBox = { x, y, w, h }; // Inicializar el bounding box 
}

void Button::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		callback();
	}

}

void Button::update()
{
}
