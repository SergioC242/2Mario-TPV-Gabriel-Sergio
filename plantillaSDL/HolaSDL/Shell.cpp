#include "Shell.h"

Shell::Shell(Texture* tex, Game* g, int posX, int posY) : position(posX, posY + g->TILE_SIZE) {

	texture = tex;
	game = g;
	dirIzq = false;
	moving = false;
	onGround = true;
	active = false;
	hitCD = 20;
	moveX = 0;
	moveY = 0;
}



void Shell::update(){ 
	
	if (hitCD > 0) {
		hitCD--;
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
	predictedRect.h = frameHeight;

	Collision::ObjetoTipo state;
	if (moving) {
		state = Collision::ObjetoTipo::moveShell;
	}
	else {
		state = Collision::ObjetoTipo::Shell;
	}

	// colisiones VERTICAL en función de la gravedad
	predictedRect.x = position.X();
	predictedRect.y = position.Y() + GRAVITY;
	bool collisionGravity = game->getTileMap()->hit(predictedRect, state).hasCollided(); // Dirección es irrelevante para tilemap
	Collision objectCollisionGravity = game->checkCollisions(predictedRect, state);
	// colisiones VERTICAL en función del movimiento
	predictedRect.y = position.Y() - moveY;
	bool collisionVertical = game->getTileMap()->hit(predictedRect, state).hasCollided(); // Dirección es irrelevante para tilemap
	Collision objectCollisionVertical = game->checkCollisions(predictedRect, state);
	// colisiones HORIZONTAL en función del movimiento previsto
	predictedRect.x = position.X() + moveX;
	predictedRect.y = position.Y();
	bool collisionHorizontal = game->getTileMap()->hit(predictedRect, state).hasCollided(); // Dirección es irrelevante para tilemap
	Collision objectCollisionHorizontal = game->checkCollisions(predictedRect, state);

	// si se ha colisionado con un objeto, con qué? actuar en función (prioridad a la colisión vertical)
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

	// cálculo de onGround (en el suelo)
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
	if ((objectCollisionGravity.object() == Collision::Goomba || objectCollisionGravity.object() == Collision::Koopa) ||
		!collisionHorizontal) {
		if (!(position.X() <= 0 && moveX < 0)) { // Impide moverse a la izquierda del borde del mapa
			position += Vector2D<float>(moveX, 0);
		}
		else {
			dirIzq = !dirIzq;
		}
	}
	else {
		moveX = -moveX;
	}
}

void Shell::render() {

	SDL_Rect rect;
	rect.x = position.X() - game->offset_Return();
	rect.y = position.Y();
	rect.h = texture->getFrameHeight() * 2;
	rect.w = texture->getFrameWidth() * 2;

	texture->renderFrame(rect, 0, 0, SDL_FLIP_NONE);
}
Collision Shell::hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj) {
	SDL_Rect shellRect;
	shellRect.x = position.X();
	shellRect.y = position.Y();
	shellRect.h = texture->getFrameHeight() * 2;
	shellRect.w = texture->getFrameWidth() * 2;

	Collision::CollisionDir dir = Collision::CollisionDir::Middle;

	if (rect.y < shellRect.y) {
		dir = Collision::CollisionDir::Above;
	}
	else if (rect.y > shellRect.y - game->TILE_SIZE) {
		dir = Collision::CollisionDir::Below;
	}

	bool moveDir;
	if (rect.x < shellRect.x) {
		moveDir = true; // left
	}
	else {
		moveDir = false; // right
	}

	if (hitCD <= 0) {
		SDL_bool intersection = SDL_HasIntersection(&rect, &shellRect);
		if (intersection == SDL_TRUE) {
			if (tipoObj == Collision::ObjetoTipo::Player && moveX == 0) {
				startMove(moveDir);
				hitCD = 20;
			}
			else if (tipoObj == Collision::ObjetoTipo::Player && dir == Collision::CollisionDir::Above && moveX != 0) {
				stopMove();
				hitCD = 20;
			}
			return Collision(true, dir, Collision::Shell);
		}
	}
	return Collision(false, dir, Collision::Shell);
}

void Shell::startMove(bool moveDir) {
	int walkp = WALK_POWER;
	if (moveDir) { //left
		moveX = walkp;
	}
	else { // right
		moveX = -walkp;
	}
}