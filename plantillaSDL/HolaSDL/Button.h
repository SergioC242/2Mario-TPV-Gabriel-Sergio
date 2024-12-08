#include <SDL.h>
#include "GameObject.h"
#include "EventHandler.h"
#include <functional>
#include "GameState.h"
#include "Texture.h"
#pragma once

using Callback = std::function<void(void)>;


class Button : public GameObject, public EventHandler
{
private: 
		SDL_Rect rect; 
		Texture* texture; 
		Texture* mushroomTexture; 
		Callback callback; 
		bool isMouseOver;
		SDL_Rect boundingBox;
		GameState* game;

public:

	Button(int x, int y, int w, int h, Texture* tex, Texture* mushTex);
	//Button(GameState* game);

	

	void connect(Callback c) { callback = c; }


	// Heredado vía EventHandler
	void handleEvent(const SDL_Event& e) override;

	virtual void render();


	// Heredado vía GameObject
	void update() override;

};

