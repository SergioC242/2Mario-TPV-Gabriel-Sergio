#include "Vector2D.h"
#include "Texture.h"
#include "SceneObject.h"
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "EventHandler.h"
#include <array>
#include <vector>
#include <SDL.h>

#include "mPlatform.h"



#pragma once

class Game;

using uint = unsigned int;

class Player : public SceneObject, public EventHandler
{
private:

	Point2D position;
	Game* game;
	int vidas;
	int currentWalkingFrame;
	enum Estado {
		Quieto,
		Caminando,
		Aire,
		Muerto
	};
	enum Forma {
		Small,
		Super,
		Fire
	};
	Forma forma;
	Estado estado;
	std::array<Texture*, 3> textures;
	int moveX;
	int moveY;
	
	SDL_RendererFlip flipH;

	bool onGround;
	bool jumping;

	bool dead;

public:
	static constexpr uint WALK_POWER = 8;
	static constexpr uint JUMP_POWER = 24; 
	static constexpr uint GRAVITY = 2;
	static constexpr uint MAX_FALL_SPEED = 8; //hay que comprobar si se queda que es negativo

	Player(Texture* tex1, Texture* tex2, Texture* tex3, Game* g, int posX, int posY, int lives);
	Player* clone() const { return new Player(*this); }

	void handleEvent(SDL_KeyboardEvent& E);
	void update();
	void render() const;

	void bounce();
	void makeSuper();
	bool isSuperMario() { return (forma == Super); }

	bool isMovingUp() { return moveY > 0; }

	void die();
	void dieAnimUpdate();

	~Player();

	// Heredado vía EventHandler
	void handleEvent(const SDL_Event& e) override;
};

