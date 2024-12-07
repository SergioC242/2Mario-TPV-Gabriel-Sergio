#include "Coin.h"



Coin::Coin(Texture* tex, Game* g, int posX, int posY) : position(posX, posY) {
	texture = tex;
	game = g;
}

void Coin::update(){
	rect.x = position.X() - game->playstate->offset_Return();
	rect.y = position.Y();
	rect.h = texture->getFrameHeight() * 2;
	rect.w = texture->getFrameWidth() * 2;
}

void Coin::render() const{
	texture->renderFrame(rect, 0, 0, SDL_FLIP_NONE);
}

Collision Coin::hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj) {
	SDL_Rect coinRect;
	coinRect.x = position.X();
	coinRect.y = position.Y();
	coinRect.h = texture->getFrameHeight() * 2;
	coinRect.w = texture->getFrameWidth() * 2;

	Collision::CollisionDir dir = Collision::CollisionDir::Middle;

	SDL_bool intersection = SDL_HasIntersection(&rect, &coinRect);
	if (intersection == SDL_TRUE && tipoObj == Collision::ObjetoTipo::Player) {
		Collision::ObjetoTipo type = Collision::Coin;
		game->playstate->addScore(100);
		delete this;
		return Collision(true, dir, type);
	}
	return Collision(false, dir, Collision::Coin);
}