#include "GameState.h"
#include <SDL.h>
#include <functional>

#pragma once

using Callback = std::function<void(void)>;

class AnimationState : public GameState
{
private:
	GameState* prevState;
	Game* game;
	Callback callback;
	function<bool()> anim;
public:
	AnimationState(Game* g, GameState* pS, function<bool()> funcAnim);
	virtual void update();
	virtual void render();
	void connect(Callback c) { callback = c; }
};

