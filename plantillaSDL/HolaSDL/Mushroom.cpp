#include "Mushroom.h"


Mushroom::Mushroom(Texture* tex, Game* g, int posX, int posY) : position(posX /* + game->TILE_SIZE*/, posY) {

	texture = tex;
	game = g;
	dirIzq = false;
	onGround = true;
}

//Mushroom::~Mushroom() {
//	texture = nullptr;
//	game = nullptr;
//}



void Mushroom::update() {
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
	predictedRect.h = frameHeight;

	// colisiones VERTICAL en funci�n de la gravedad
	predictedRect.x = position.X();
	predictedRect.y = position.Y() + GRAVITY;
	bool collisionGravity = game->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Mushroom).hasCollided(); // Direcci�n es irrelevante para tilemap
	Collision objectCollisionGravity = game->checkCollisions(predictedRect, Collision::ObjetoTipo::Mushroom);
	// colisiones VERTICAL en funci�n del movimiento
	predictedRect.y = position.Y() - moveY;
	bool collisionVertical = game->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Mushroom).hasCollided(); // Direcci�n es irrelevante para tilemap
	Collision objectCollisionVertical = game->checkCollisions(predictedRect, Collision::ObjetoTipo::Mushroom);
	// colisiones HORIZONTAL en funci�n del movimiento previsto
	predictedRect.x = position.X() + moveX;
	predictedRect.y = position.Y();
	bool collisionHorizontal = game->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Mushroom).hasCollided(); // Direcci�n es irrelevante para tilemap
	Collision objectCollisionHorizontal = game->checkCollisions(predictedRect, Collision::ObjetoTipo::Mushroom);

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
	rect.x = position.X() - game->offset_Return();
	rect.y = position.Y();
	rect.h = texture->getFrameHeight() * 2;
	rect.w = texture->getFrameWidth() * 2;
}


void Mushroom::render() const{
	texture->renderFrame(rect, 0, 0, SDL_FLIP_NONE);
}
Collision Mushroom::hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj) {
	SDL_Rect mushroomRect;
	mushroomRect.x = position.X();
	mushroomRect.y = position.Y();
	mushroomRect.h = texture->getFrameHeight() * 2;
	mushroomRect.w = texture->getFrameWidth() * 2;


	Collision::CollisionDir dir = Collision::CollisionDir::Middle;

	SDL_bool intersection = SDL_HasIntersection(&rect, &mushroomRect);
	if (intersection == SDL_TRUE && tipoObj == Collision::ObjetoTipo::Player) {
		Collision::ObjetoTipo type = Collision::Mushroom;
		//disappear mushroom
		game->addScore(1000);
		delete this;
		return Collision(true, dir, type); //esto tiene que ser mushroom
	}
	return Collision(false, dir, Collision::Mushroom);
}