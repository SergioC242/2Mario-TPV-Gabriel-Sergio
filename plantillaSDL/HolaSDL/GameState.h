#include "checkML.h"
#include "gameList.h"
#include "GameObject.h"
#include "SceneObject.h"
#include "EventHandler.h"

#include <list>;


#pragma once
class GameState
{
private:
	GameList<SceneObject> obj;
	list<EventHandler*> event;


public:
	void update(){}
	void render(){}
	void handleEvent(SDL_Event e){}

};

