#include "Goomba.h"
#include "TileMap.h"
#include "Collision.h"

Goomba::Goomba(Texture* tex, Game* g, int posX, int posY) : position(posX + game->TILE_SIZE, posY - 8) {

	texture = tex;
	game = g;
	dirIzq = true;
	frame = 0;
	alive = true;
	onGround = true;
	active = false;
	moveX = 0;
	moveY = 0;
}


//Goomba::~Goomba() {
//	texture = nullptr;
//	game = nullptr;
//}


void Goomba::render() const{
	if(alive)
	{
		texture->renderFrame(rect, 0, frame, SDL_FLIP_NONE);
	}
}

void Goomba::update() {
	if (alive)
	{
		if (!active) {
			active = (game->offset_Return() + game->WIN_WIDTH + game->TILE_SIZE) > position.X();
		}
		else if (alive)
		{
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
			bool collisionGravity = game->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Goomba).hasCollided(); // Direcci�n es irrelevante para tilemap
			Collision objectCollisionGravity = game->checkCollisions(predictedRect, Collision::ObjetoTipo::Goomba);
			// colisiones VERTICAL en funci�n del movimiento
			predictedRect.y = position.Y() - moveY;
			bool collisionVertical = game->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Goomba).hasCollided(); // Direcci�n es irrelevante para tilemap
			Collision objectCollisionVertical = game->checkCollisions(predictedRect, Collision::ObjetoTipo::Goomba);
			// colisiones HORIZONTAL en funci�n del movimiento previsto
			predictedRect.x = position.X() + moveX;
			predictedRect.y = position.Y();
			bool collisionHorizontal = game->getTileMap()->hit(predictedRect, Collision::ObjetoTipo::Goomba).hasCollided(); // Direcci�n es irrelevante para tilemap
			Collision objectCollisionHorizontal = game->checkCollisions(predictedRect, Collision::ObjetoTipo::Goomba);

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

		}

		if (alive)
		{
			if (frame == 0) {
				frame = 1;
			}
			else {
				frame = 0;
			}
		}
		else
		{
			frame = 2;
		}

		rect.x = position.X() - game->offset_Return();
		rect.y = position.Y();
		rect.h = texture->getFrameHeight() * 2;
		rect.w = texture->getFrameWidth() * 2;
	}
}


Collision Goomba::hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj) {
	
		SDL_Rect goombaRect;
		goombaRect.x = position.X();
		goombaRect.y = position.Y();
		goombaRect.h = texture->getFrameHeight() * 2;
		goombaRect.w = texture->getFrameWidth() * 2;

		Collision::CollisionDir dir = Collision::CollisionDir::Middle;

		if (rect.y < goombaRect.y) {
			dir = Collision::CollisionDir::Above;
		}
		else if (rect.y > goombaRect.y - game->TILE_SIZE) {
			dir = Collision::CollisionDir::Below;
		}

		SDL_bool intersection = SDL_HasIntersection(&rect, &goombaRect);
		if (intersection == SDL_TRUE && alive) {

			if (tipoObj == Collision::ObjetoTipo::Player && dir == Collision::CollisionDir::Above &&  alive) {
				alive = false;
				die();
			}
			else if (tipoObj == Collision::ObjetoTipo::moveShell) {
				alive = false;
				die();
			}
			return Collision(true, dir, Collision::Goomba);
		}
		return Collision(false, dir, Collision::Goomba);
	

}

void Goomba::die() {
	game->addScore(100);
}