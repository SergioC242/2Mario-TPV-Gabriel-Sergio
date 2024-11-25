#include "Shell.h"

Shell::Shell(Texture* tex, Game* g, int posX, int posY) : position(posX /* + game->TILE_SIZE*/, posY) {

	texture = tex;
	game = g;
	dirIzq = false;
	moving = false;
	onGround = true;
	active = false;
}



void Shell::update(){}

void Shell::render() {

	SDL_Rect rect;
	rect.x = position.X() - game->offset_Return();
	rect.y = position.Y();
	rect.h = texture->getFrameHeight();
	rect.w = texture->getFrameWidth();

	texture->renderFrame(rect, 0, 0, SDL_FLIP_NONE);
}
Collision Shell::hit(SDL_Rect rect, bool fromPlayer) {
	SDL_Rect shellRect;
	shellRect.x = position.X();
	shellRect.y = position.Y();
	shellRect.h = texture->getFrameHeight();
	shellRect.w = texture->getFrameWidth();

	Collision::CollisionDir dir = Collision::CollisionDir::Middle;

	if (rect.y < shellRect.y) {
		dir = Collision::CollisionDir::Above;
	}
	else if (rect.y > shellRect.y - game->TILE_SIZE) {
		dir = Collision::CollisionDir::Below;
	}

	SDL_bool intersection = SDL_HasIntersection(&rect, &shellRect);
	if (intersection == SDL_TRUE) {

		if (dir == Collision::CollisionDir::Above && fromPlayer/* && moving shell*/) {
			//stop shell
		}
		return Collision(true, dir, Collision::Shell);
	}
	return Collision(false, dir, Collision::Shell);
}