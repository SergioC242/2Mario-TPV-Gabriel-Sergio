#include "Player.h"
#include "Game.h"

using namespace std;

Player::Player(Texture* tex1, Texture* tex2, Texture* tex3, Game* g, int posX, int posY, int liv) : position(posX, posY - 32) {
	game = g;
	textures[0] = tex1;
	textures[1] = tex2;
	textures[2] = tex3;
	forma = Forma::Small;
	estado = Estado::Quieto;
	moveX = 0;
	moveY = 0;
	currentWalkingFrame = 0;
	flipH = SDL_FLIP_NONE;
	onGround = false;
	jumping = false;
	dead = false;
}

void Player::handleEvent(SDL_KeyboardEvent& E) {
	
}

void Player::update() {

	if (position.X() > 6296) {
		game->playstate->map_next();
	}

	if (position.Y() > Game::WIN_HEIGHT) {
		die();
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

	Texture* currentTexture = textures[forma];

	int frameWidth = currentTexture->getFrameWidth() * 2;
	int frameHeight = currentTexture->getFrameHeight() * 2;
	SDL_Rect predictedRect;
	predictedRect.x = position.X();
	predictedRect.y = position.Y();
	predictedRect.w = frameWidth;
	predictedRect.h = game->TILE_SIZE; // El sprite de mario es 36px pero un bloque es 32px
	if (forma == Super) {
		predictedRect.h = predictedRect.h * 2;
	}

	//cout << predictedRect.x << "|" << predictedRect.y << " " << predictedRect.w << "|" << predictedRect.h << endl;

	// colisiones VERTICAL en función de la gravedad
	predictedRect.y = position.Y() + GRAVITY;
	bool collisionGravity = game->playstate->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Player).hasCollided(); // Dirección es irrelevante para tilemap
	Collision objectCollisionGravity = game->playstate->checkCollisions(predictedRect, Collision::ObjetoTipo::Player);
	// colisiones VERTICAL en función del movimiento
	predictedRect.y = position.Y() - moveY;
	bool collisionVertical = game->playstate->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Player).hasCollided(); // Dirección es irrelevante para tilemap
	Collision objectCollisionVertical = game->playstate->checkCollisions(predictedRect, Collision::ObjetoTipo::Player);
	// colisiones HORIZONTAL en función del movimiento previsto
	predictedRect.x = position.X() + moveX;
	predictedRect.y = position.Y();
	bool collisionHorizontal = game->playstate->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Player).hasCollided(); // Dirección es irrelevante para tilemap
	Collision objectCollisionHorizontal = game->playstate->checkCollisions(predictedRect, Collision::ObjetoTipo::Player);

	// Si se encuentra un objeto encima, parar movimiento. No puede pasar con check de gravedad
	if (objectCollisionVertical.directionV() == Collision::CollisionDir::Above) {
		moveY = 0;
	}

	// si se ha colisionado con un objeto, con qué? actuar en función (prioridad a la colisión vertical
	if (objectCollisionGravity.hasCollided()) {
		if (objectCollisionGravity.object() == Collision::Block) {
			collisionGravity = true;
		}
		else if (objectCollisionGravity.object() == Collision::Goomba || objectCollisionGravity.object() == Collision::Koopa) {
			if (objectCollisionGravity.directionV() == Collision::Above) {
				// bounce, enemy handles the rest
				bounce();
				collisionVertical = false;
			}
			else {
				// take damage
				if (forma == Forma::Super) {
					forma = Forma::Small;
				}
				else if (forma == Forma::Small) {
					//die
				}
			}
		}
		else if (objectCollisionGravity.object() == Collision::Mushroom) {
			if (forma == Forma::Small) {
				makeSuper();
			}
		}
	}
	else if (objectCollisionVertical.hasCollided()) {
		if (objectCollisionVertical.object() == Collision::Block) {
			collisionVertical = true;
		}
		else if (objectCollisionVertical.object() == Collision::Goomba || objectCollisionVertical.object() == Collision::Koopa) {
			if (objectCollisionVertical.directionV() == Collision::Above) {
				// bounce, enemy handles the rest
				bounce();
				collisionVertical = false;
			}
			else {
				// take damage
				if (forma == Forma::Super) {
					forma = Forma::Small;
				}
				else if (forma == Forma::Small) {
					//die
				}
			}
		}
		else if (objectCollisionVertical.object() == Collision::Mushroom) {
			//mario grande
			if (forma == Forma::Small) {
				makeSuper();
				cout << "Mario Grande" << endl;
			}
			else {
				vidas++;
				cout << "vidas: " << vidas << endl;
			}
		}
	}
	else if (objectCollisionHorizontal.hasCollided()) {
		if (objectCollisionHorizontal.object() == Collision::Block) {
			collisionHorizontal = true;
		}
		else if (objectCollisionHorizontal.object() == Collision::Goomba || objectCollisionVertical.object() == Collision::Koopa) {
			// take damage
			if (forma == Forma::Super) {
				forma = Forma::Small;
			}
			else if (forma == Forma::Small) {
				die();
			}
		}
		else if (objectCollisionHorizontal.object() == Collision::Mushroom) {
			if (forma == Forma::Small) {
				makeSuper();
				cout << "Mario Grande" << endl;
			}
			else {
				vidas++;
				cout << "vidas: " << vidas << endl;
			}
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

	// aplicar movimiento VERTICAL
	if (!collisionVertical) {
		position += Point2D(0, -moveY);
	}
	else {
		moveY = 0;
	}
	// aplicar movimiento HORIZONTAL
	if (!collisionHorizontal) {
		if (!(position.X() - game->playstate->offset_Return() <= 0 && moveX < 0)) { // Impide moverse a la izquierda del borde de la pantalla
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

	//cout << position.X() - game->playstate->offset_Return() << " " << Game::WIN_WIDTH / 2 << "t" << game->playstate->offset_isLocked();

	// Mover el mapa hacia adelante si se está moviendo por delante del medio de la pantalla
	if (position.X() - game->playstate->offset_Return() > Game::WIN_WIDTH / 2 && !game->playstate->offset_isLocked()) {
		game->playstate->offset_Add(WALK_POWER);
	}

	//cout << position.X() << "|" << position.Y() << " " << collisionGravity << collisionVertical << " " << onGround << " " << jumping << " " << moveX << " " << moveY;
	//cout << moveX << " " << moveY << endl;

	rect.x = position.X() - game->playstate->offset_Return();
	rect.y = position.Y();
	rect.h = currentTexture->getFrameHeight() * 2;
	rect.w = currentTexture->getFrameWidth() * 2;
	if (forma == Super) {
		rect.h = rect.h;
		rect.w = rect.w;
	}

	if (estado == Estado::Caminando) {
		if (currentWalkingFrame >= 2) {
			currentWalkingFrame = 0;
		}
		else {
			currentWalkingFrame++;
		}

	}
}

void Player::render() const {
	
	Texture* currentTexture = textures[forma];

	//void renderFrame(const SDL_Rect& target, int row, int col, SDL_RendererFlip flip) const;

	if (dead) {
		textures[Forma::Small]->renderFrame(rect, 0, 1);
	}
	else if (estado == Estado::Caminando) {
		currentTexture->renderFrame(rect, 0, 2 + currentWalkingFrame, flipH);
	}
	else if (estado == Estado::Aire) {
		currentTexture->renderFrame(rect, 0, 6, flipH);
	}
	else {
		currentTexture->renderFrame(rect, 0, 0, flipH);
	}
}

void Player::bounce() {
	moveY = JUMP_POWER / 2;
	onGround = false;
	jumping = true;
}

void Player::makeSuper() {
	int tilesize = game->TILE_SIZE;
	position += Point2D(0, -tilesize);
	forma = Forma::Super;
}

void Player::die() {
	estado = Estado::Muerto;
	dead = true;
	moveX = 0;
	moveY = JUMP_POWER;
	game->stateAnimation();
}

bool Player::dieAnimCallback() {
	if (position.Y() < Game::WIN_HEIGHT) {
		int maxfallspeed = MAX_FALL_SPEED;
		if (moveY <= -maxfallspeed) {
			moveY = -maxfallspeed;
		}
		else {
			moveY -= GRAVITY;
		}
		return true;
	}
	return false;
}

Player::~Player() {
	//for (Texture* tex : textures) delete tex;
}

void Player::handleEvent(const SDL_Event& e)
{
	if (e.key.keysym.sym == SDLK_ESCAPE) {
			
			game->statePause();
		}
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
	{
		SDL_KeyboardEvent E = e.key;
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
}
