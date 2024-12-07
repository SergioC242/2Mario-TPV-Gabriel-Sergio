#include <SDL.h>
#include "GameObject.h"
#include "EventHandler.h"
#include <functional>

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

public:


	

	void connect(Callback c) { callback = c; }


	// Heredado vía EventHandler
	void handleEvent(const SDL_Event& e) override;

};

