#include "Button.h"

#include "GameState.h"

#include "checkML.h"


Button::Button(int x, int y, int w, int h, Texture* tex, Texture* mushTex) : rect{ x, y, w, h }, 
																					texture(tex), 
																					mushroomTexture(mushTex), 
																					isMouseOver(false) 
{
	boundingBox = { x, y, w, h }; // Inicializar el bounding box 
}

//Button::Button(GameState* g)
//	: game(g)
//	, boundingBox{ 50, 50, 200, 100 }{}


void Button::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		callback();
	}

}
void Button::render() {
	texture->renderFrame(rect, 0, 0);
}

void Button::update()
{
}
