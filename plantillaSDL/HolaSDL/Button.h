#include <SDL.h>
#include "GameObject.h"
#include "EventHandler.h"
#include <functional>
#include "Game.h"


using Callback = std::function<void(void)>;

#pragma once
class Button : public GameObject, public EventHandler
{
private: 
		SDL_Rect rect; 
		SDL_Texture* texture; 
		SDL_Texture* mushroomTexture; 
		Callback callback; 
		bool isMouseOver;
		SDL_Rect boundingBox;
		GameState* game;

public:

	Button(int x, int y, int w, int h, SDL_Texture* tex, SDL_Texture* mushTex);
	//Button(GameState* game);

	

	void connect(Callback c) { callback = c; }


	// Heredado vía EventHandler
	void handleEvent(const SDL_Event& e) override;


	// Heredado vía GameObject
	void update() override;

};

