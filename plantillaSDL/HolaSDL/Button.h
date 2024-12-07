#include <SDL.h>
#include "GameObject.h"
#include "EventHandler.h"
#include <vector>

#pragma once
class Button : public GameObject, public EventHandler
{
private:
	SDL_Rect rect;
	bool isMouseOver;


};

