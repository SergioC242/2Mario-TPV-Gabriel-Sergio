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
}

void Player::handleEvent(SDL_KeyboardEvent& E) {
	if (E.state == SDL_PRESSED &&										//si acabas de pulsar el boton de salto (no mantenido) salta
		E.keysym.sym == SDLK_UP && E.repeat == 0) {
		//if grounded, jump
		if (onGround) {
			moveY = JUMP_POWER;
			onGround = false;
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
	bool tileColissionGravity = game->getTileMap()->hit(predictedRect, true).HasCollided();
	//Collision blockColissionGravity = game->checkCollision(predictedRect, true);
	//Collision enemyColissionGravity = game->CheckEnemyCollision(predictedRect, true);
	//cout << enemyColissionGravity.DirectionV() << " ";
	// colisiones VERTICAL en función del movimiento
	predictedRect.y = position.Y() - moveY;
	bool tileColissionVertical = game->getTileMap()->hit(predictedRect, true).HasCollided();
	//Collision blockColissionVertical = game->checkCollision(predictedRect, true);
	//Collision enemyColissionVertical = game->CheckEnemyCollision(predictedRect, true);
	//cout << enemyColissionVertical.DirectionV() << " ";
	// colisiones HORIZONTAL en función del movimiento previsto
	predictedRect.x = position.X() + moveX;
	predictedRect.y = position.Y();
	bool tileColissionHorizontal = game->getTileMap()->hit(predictedRect, true).HasCollided();
	//Collision blockColissionHorizontal = game->checkCollision(predictedRect, true);
	//Collision enemyColissionHorizontal = game->CheckEnemyCollision(predictedRect, true);
	//cout << enemyColissionHorizontal.DirectionV() << endl;


	/*
	* if (tileColissionGravity) cout << "grav colission T" << endl;
	if (tileColissionVertical) cout << "vert colission T" << endl;
	if (tileColissionHorizontal) cout << "hori colission T" << endl;
	if (blockColissionGravity.HasCollided()) cout << "grav colission B" << endl;
	if (blockColissionVertical.HasCollided()) cout << "vert colission B" << endl;
	if (blockColissionHorizontal.HasCollided()) cout << "hori colission B" << endl;
	*/

	// movimiento VERTICAL
	/*
	if (enemyColissionGravity.DirectionV() || enemyColissionVertical.DirectionV() || enemyColissionHorizontal.DirectionV()) {
		moveY = jumpPower;
		onGround = false;
	}
	else if (enemyColissionGravity.HasCollided() || enemyColissionVertical.HasCollided() || enemyColissionHorizontal.HasCollided()) {
		vidas--;
	}*/

	if ((!tileColissionGravity && !tileColissionVertical) || moveY > 0) {
		onGround = false;
	}
	else {
		onGround = true;
	}

	if (!onGround) {
		position += Point2D(0, -moveY);
	}
	// movimiento HORIZONTAL
	if (!tileColissionHorizontal) { //(!tileColissionHorizontal && !blockColissionHorizontal.HasCollided()) {
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

	cout << position.X() << "|" << position.Y() << " " << tileColissionGravity << tileColissionVertical << " " << onGround << " " << moveX << " " << moveY << endl;
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