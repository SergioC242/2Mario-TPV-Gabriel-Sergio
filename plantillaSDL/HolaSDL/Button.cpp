#include "Button.h"

#include "GameState.h"

#include "checkML.h"

#include "Game.h"


Button::Button(Game* g, int x, int y, int w, int h, Texture* tex) : texture(tex), rect{ x, y, tex->getFrameWidth() * w, tex->getFrameHeight() * h }, game(g), isMouseOver(false)
{
	mushroomTexture = game->getTexture(Game::MushroomTex);
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
void Button::render() const{
	texture->renderFrame(rect, 0, 0);
	SDL_RenderPresent(game->renderer);
}

void Button::update()
{
}
