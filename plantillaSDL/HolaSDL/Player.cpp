#include "Player.h"
#include "Game.h"

using namespace std;

Player::Player(Texture* tex1, Texture* tex2, Texture* tex3, Game* g, int posX, int posY, int liv) : position(posX, posY - 32) {
	game = g;
	textures[0] = tex1;
	textures[1] = tex2;
	textures[2] = tex3;
	vidas = 3;
	forma = Forma::Small;
	estado = Estado::Quieto;
	moveX = 0;
	moveY = 0;
	currentWalkingFrame = 0;
	flipH = SDL_FLIP_NONE;
	onGround = false;
	jumping = false;
}

void Player::handleEvent(SDL_KeyboardEvent& E) {
	if (E.state == SDL_PRESSED &&										//si acabas de pulsar el boton de salto (no mantenido) salta
		E.keysym.sym == SDLK_UP && E.repeat == 0) {
		//if grounded, jump
		if (onGround) {
			moveY = JUMP_POWER;
			onGround = false;
			jumping = true;
		}
	}

	if (E.state == SDL_PRESSED &&										//si tecla derecha Mov = +1
		E.keysym.sym == SDLK_RIGHT) {
		moveX = WALK_POWER;
		flipH = SDL_FLIP_NONE;
	}
	else if (E.state == SDL_PRESSED &&									//si tecla izquierda Mov = -1
		E.keysym.sym == SDLK_LEFT) {
		//Movement x = -1
		int walk = WALK_POWER; // porque no se puede añadir - a una constante, aparentemente
		moveX = -walk;
		flipH = SDL_FLIP_HORIZONTAL;
	}
	else if (E.state == SDL_RELEASED &&									//si sueltas tecla derecha o izquierda Mov = 0
		(E.keysym.sym == SDLK_RIGHT || E.keysym.sym == SDLK_LEFT)) {
		//movement x= 0
		moveX = 0;
	}
}

void Player::update() {
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

	Texture* currentTexture = textures[forma];

	int frameWidth = currentTexture->getFrameWidth();
	int frameHeight = currentTexture->getFrameHeight();
	SDL_Rect predictedRect;
	predictedRect.w = frameWidth;
	predictedRect.h = frameHeight;

	// colisiones VERTICAL en función de la gravedad
	predictedRect.x = position.X();
	predictedRect.y = position.Y() + GRAVITY;
	bool collisionGravity = game->getTileMap()->hit(predictedRect, true).hasCollided(); // Dirección es irrelevante para tilemap
	Collision objectCollisionGravity = game->checkCollisions(predictedRect, true);
	// colisiones VERTICAL en función del movimiento
	predictedRect.y = position.Y() - moveY;
	bool collisionVertical = game->getTileMap()->hit(predictedRect, true).hasCollided(); // Dirección es irrelevante para tilemap
	Collision objectCollisionVertical = game->checkCollisions(predictedRect, true);
	// colisiones HORIZONTAL en función del movimiento previsto
	predictedRect.x = position.X() + moveX;
	predictedRect.y = position.Y();
	bool collisionHorizontal = game->getTileMap()->hit(predictedRect, true).hasCollided(); // Dirección es irrelevante para tilemap
	Collision objectCollisionHorizontal = game->checkCollisions(predictedRect, true);

	// si se ha colisionado con un objeto, con qué? actuar en función (prioridad a la colisión vertical
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

	// cálculo de onGround (en el suelo) y jumping (ascendiendo después de un salto)

	if (!collisionGravity && !collisionVertical) {
		onGround = false;
	}
	else {
		onGround = true;
	}

	if (moveY <= 0) {
		jumping = false;
	}
	else {
		onGround = false;
	}

	// Si se encuentra un objeto encima, parar movimiento. No puede pasar con check de gravedad
 	if (objectCollisionVertical.directionV() == Collision::CollisionDir::Above) {
		moveY = 0;
	}

	// aplicar movimiento VERTICAL
	if (!collisionVertical && !objectCollisionVertical.hasCollided()) {
		position += Point2D(0, -moveY);
	}
	else {
		moveY = 0;
	}
	// aplicar movimiento HORIZONTAL
	if (!collisionHorizontal) {
		if (!(position.X() - game->offset_Return() <= 0 && moveX < 0)) { // Impide moverse a la izquierda del borde de la pantalla
			position += Point2D(moveX, 0);
		}
	}

	// Actualizando el estado de movimiento de Mario
	if (!onGround) {
		estado = Estado::Aire;
	}
	else if (moveX == 0) {
		estado = Estado::Quieto;
	}
	else {
		estado = Estado::Caminando;
	}

	// Mover el mapa hacia adelante si se está moviendo por delante del medio de la pantalla
	if (position.X() - game->offset_Return() > game->WIN_WIDTH / 2 && !game->offset_isLocked()) {
		game->offset_Add(WALK_POWER);
	}

	//cout << position.X() << "|" << position.Y() << " " << collisionGravity << collisionVertical << " " << onGround << " " << jumping << " " << moveX << " " << moveY << endl;
}

void Player::render() {
	
	Texture* currentTexture = textures[forma];

	//void renderFrame(const SDL_Rect& target, int row, int col, SDL_RendererFlip flip) const;

	SDL_Rect rect;
	rect.x = position.X() - game->offset_Return();
	rect.y = position.Y();
	rect.h = currentTexture->getFrameHeight();
	rect.w = currentTexture->getFrameWidth();

	if (forma == Small) {
		if (estado == Estado::Caminando) {
			currentTexture->renderFrame(rect, 0, 2 + currentWalkingFrame, flipH);

			if (currentWalkingFrame >= 2) {
				currentWalkingFrame = 0;
			}
			else {
				currentWalkingFrame++;
			}

		}
		else if (estado == Estado::Aire) {
			currentTexture->renderFrame(rect, 0, 6, flipH);
		}
		else {
			currentTexture->renderFrame(rect, 0, 0, flipH);
		}
	}
}