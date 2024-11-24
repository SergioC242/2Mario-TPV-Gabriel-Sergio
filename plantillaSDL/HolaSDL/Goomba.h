#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"


#pragma once
class TileMap;
class Goomba : public GameItem
{
private:
	Vector2D<float> position;
	bool dirIzq; //si no se esta moviendo a la izquierda se esta moviendo a la derecha
	Texture* texture;
	Game* game;
	int frame;
	bool alive;
	bool onGround;
	bool active;

public: 
	static constexpr uint gravity = 8;
	static constexpr uint moveX = 8;


	Goomba(Texture* tex, Game* g /*, int wWidth, int wHeight*/, int posX, int posY);
	void Update();
	void Render();
	Collision Hit(SDL_Rect rect, bool fromPlayer);
	void Die();

};

