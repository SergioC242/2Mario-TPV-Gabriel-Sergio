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
	Game* game;
	GameList<GameObject> gameObj;
	list<EventHandler*> eventObj;


public:
	virtual void update(){
		for (auto elem : gameObj) {
			elem->update();
		}
	}
	virtual void render(){
		for (auto elem : gameObj) {
			elem->render();
		}
	}
	void handleEvent(SDL_Event e){
		for (auto elem : eventObj) {
			elem->handleEvent(e); 
		}
	}

	void addEventListener(EventHandler* eventLis) {
		eventObj.push_back(eventLis);
	}

	void addObject(GameObject* obj) {
		gameObj.push_back(obj);
	}


};

