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
		GameState* gamestate;
		Game* game;

public:

	Button(Game* g, int x, int y, int w, int h, Texture* tex);
	//Button(GameState* game);

	

	void connect(Callback c) { callback = c; }


	// Heredado v�a EventHandler
	void handleEvent(const SDL_Event& e) override;

	virtual void render() const;


	// Heredado v�a GameObject
	void update() override;

};

