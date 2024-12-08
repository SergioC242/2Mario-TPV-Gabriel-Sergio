#include "Button.h"

#include "GameState.h"

#include "checkML.h"

#include "Game.h"


Button::Button(Game* g, int x, int y, int w, int h, Texture* tex) : texture(tex), rect{ x, y, tex->getFrameWidth() * w, tex->getFrameHeight() * h }, game(g), isMouseOver(false)
{
	isMouseOver = false;
	mushroomTexture = game->getTexture(Game::MushroomTex);
	mrect.w = mushroomTexture->getFrameWidth();
	mrect.h = mushroomTexture->getFrameHeight();
	mrect.x = x - mrect.w - 10;
	mrect.y = y;
}

//Button::Button(GameState* g)
//	: game(g)
//	, boundingBox{ 50, 50, 200, 100 }{}


void Button::handleEvent(const SDL_Event& e)
{
	int mouseX = e.button.x;
	int mouseY = e.button.y;

	if (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h)
	{
		isMouseOver = true;
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {

			callback();

		}
		cout << isMouseOver << endl;
	}
	else {
		isMouseOver = false;
		cout << isMouseOver << endl;
	}

}
void Button::render() const{
	texture->renderFrame(rect, 0, 0);
	cout << isMouseOver << endl;
	if (isMouseOver) {
		mushroomTexture->renderFrame(mrect, 0, 0);
	}
}

void Button::update()
{
}
