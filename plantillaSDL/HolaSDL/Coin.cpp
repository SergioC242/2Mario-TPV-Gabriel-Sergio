#include "Coin.h"



Coin::Coin(Texture* tex, Game* g, int posX, int posY) : position(posX, posY) {

	texture = tex;
	game = g;
	active = true;
}
//Coin::~Coin() {
//	texture = nullptr;
//	game = nullptr;
//}

void Coin::update(){}

void Coin::render() {
	if(active)
	{
		SDL_Rect rect;
		rect.x = position.X() - game->offset_Return();
		rect.y = position.Y();
		rect.h = texture->getFrameHeight() * 2;
		rect.w = texture->getFrameWidth() * 2;

		texture->renderFrame(rect, 0, 0, SDL_FLIP_NONE);
	}
}

Collision Coin::hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj) {
	if (active)
	{
		SDL_Rect coinRect;
		coinRect.x = position.X();
		coinRect.y = position.Y();
		coinRect.h = texture->getFrameHeight() * 2;
		coinRect.w = texture->getFrameWidth() * 2;

		Collision::CollisionDir dir = Collision::CollisionDir::Middle;

		SDL_bool intersection = SDL_HasIntersection(&rect, &coinRect);
		if (intersection == SDL_TRUE && tipoObj == Collision::ObjetoTipo::Player) {
			game->addScore(100);
			active = false;
			return Collision(true, dir, Collision::Coin);
		}
		return Collision(false, dir, Collision::Coin);
	}
}