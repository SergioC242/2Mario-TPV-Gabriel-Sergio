#include "AnimationState.h"
#include "gameStateMachine.h"
#include "Game.h"

AnimationState::AnimationState(Game* g, GameState* pS, function<bool()> funcAnim) {
	game = g;
	prevState = pS;
	anim = funcAnim;
}

void
AnimationState::render() {
	// Renderiza los objetos del gamestate previo
	prevState->render();
}

void
AnimationState::update() {
	// while (función callback da true) repetir la función callback hasta que de false
	if (anim() == true) {}
	else {
		game->stateAnimationEnd();
	}
}