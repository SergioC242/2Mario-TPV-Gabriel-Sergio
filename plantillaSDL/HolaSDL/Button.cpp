#include "Button.h"

#include "GameState.h"

#include "checkML.h"

#include "Game.h"


Button::Button(Game* g, int x, int y, int w, int h, Texture* tex) : rect{ x, y, w, h }, game(g), isMouseOver(false) 
{
	texture = tex;
	//mushroomTexture = game->getTexture(Game::MushroomTex);
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
