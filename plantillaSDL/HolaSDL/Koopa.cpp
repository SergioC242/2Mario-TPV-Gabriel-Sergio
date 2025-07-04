#include "Koopa.h"
#include "TileMap.h"
#include "Collision.h"

Koopa::Koopa(Texture* tex, Game* g, int posX, int posY) : position(posX + game->TILE_SIZE, posY - 32) {

	texture = tex;
	game = g;
	dirIzq = true;
	frame = 0;
	onGround = true;
}


void Koopa::render() const{
	if (dirIzq) texture->renderFrame(rect, 0, frame, SDL_FLIP_NONE);
	else texture->renderFrame(rect, 0, frame, SDL_FLIP_HORIZONTAL);
}

void Koopa::update() {
	int walkp = WALK_POWER;
	if (dirIzq) {
		moveX = -walkp;
	}
	else {
		moveX = walkp;
	}

	int maxfallspeed = MAX_FALL_SPEED;

	if (onGround) {
		moveY = 0;
	}
	else {
		if (moveY <= -maxfallspeed) {
			moveY = -maxfallspeed;
		}
		else {
			moveY -= GRAVITY;
		}
	}

	int frameWidth = texture->getFrameWidth() * 2;
	int frameHeight = texture->getFrameHeight() * 2;
	SDL_Rect predictedRect;
	predictedRect.w = frameWidth;
	predictedRect.h = frameHeight / 4 * 3;

	// colisiones VERTICAL en funci�n de la gravedad
	predictedRect.x = position.X();
	predictedRect.y = position.Y() + frameHeight / 4 + GRAVITY;
	bool collisionGravity = game->playstate->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Koopa).hasCollided(); // Direcci�n es irrelevante para tilemap
	Collision objectCollisionGravity = game->playstate->checkCollisions(predictedRect, Collision::ObjetoTipo::Koopa);
	// colisiones VERTICAL en funci�n del movimiento
	predictedRect.y = position.Y() + frameHeight / 4 - moveY;
	bool collisionVertical = game->playstate->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Koopa).hasCollided(); // Direcci�n es irrelevante para tilemap
	Collision objectCollisionVertical = game->playstate->checkCollisions(predictedRect, Collision::ObjetoTipo::Koopa);
	// colisiones HORIZONTAL en funci�n del movimiento previsto
	predictedRect.x = position.X() + moveX;
	predictedRect.y = position.Y() + frameHeight / 4;
	bool collisionHorizontal = game->playstate->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Koopa).hasCollided(); // Direcci�n es irrelevante para tilemap
	Collision objectCollisionHorizontal = game->playstate->checkCollisions(predictedRect, Collision::ObjetoTipo::Koopa);

	// si se ha colisionado con un objeto, con qu�? actuar en funci�n (prioridad a la colisi�n vertical)
	if (objectCollisionGravity.hasCollided()) {
		if (objectCollisionGravity.object() == Collision::Block) {
			collisionGravity = true;
		}
	}
	else if (objectCollisionVertical.hasCollided()) {
		if (objectCollisionVertical.object() == Collision::Block) {
			collisionHorizontal = true;
		}
	}
	else if (objectCollisionHorizontal.hasCollided()) {
		if (objectCollisionHorizontal.object() == Collision::Block) {
			collisionHorizontal = true;
		}
	}

	// c�lculo de onGround (en el suelo)
	if (!collisionGravity && !collisionVertical) {
		onGround = false;
	}
	else {
		onGround = true;
	}

	// aplicar movimiento VERTICAL
	if (!onGround) {
		position += Vector2D<float>(0, -moveY);
	}
	else {
		moveY = 0;
	}
	// aplicar movimiento HORIZONTAL
	if (!collisionHorizontal) {
		if (!(position.X() <= 0 && moveX < 0)) { // Impide moverse a la izquierda del borde del mapa
			position += Vector2D<float>(moveX, 0);
		}
		else {
			dirIzq = !dirIzq;
		}
	}
	else {
		dirIzq = !dirIzq;
	}
	
	if (frame == 0) {
		frame = 1;
	}
	else {
		frame = 0;
	}

	rect.x = position.X() - game->playstate->offset_Return();
	rect.y = position.Y();
	rect.h = texture->getFrameHeight() * 2;
	rect.w = texture->getFrameWidth() * 2;

	
}


Collision Koopa::hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj) {
	SDL_Rect koopaRect;
	koopaRect.x = position.X();
	koopaRect.y = position.Y() + texture->getFrameHeight() * 2 / 4;
	koopaRect.h = texture->getFrameHeight() * 2 / 4 * 3;
	koopaRect.w = texture->getFrameWidth() * 2;

	Collision::CollisionDir dir = Collision::CollisionDir::Middle;

	if (rect.y < koopaRect.y) {
		dir = Collision::CollisionDir::Above;
	}
	else if (rect.y > koopaRect.y - game->TILE_SIZE) {
		dir = Collision::CollisionDir::Below;
	}

	SDL_bool intersection = SDL_HasIntersection(&rect, &koopaRect);
	if (intersection == SDL_TRUE) {
		Collision::ObjetoTipo type = Collision::Koopa;
		if (tipoObj == Collision::ObjetoTipo::Player && dir == Collision::CollisionDir::Above) {
			die();
		}
		return Collision(true, dir, type);
	}
	return Collision(false, dir, Collision::Koopa);
}

void Koopa::die() {
	game->playstate->addScore(100);
	game->playstate->createShell(position.X(), position.Y());
	delete this;
}