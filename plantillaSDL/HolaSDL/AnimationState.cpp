#include "AnimationState.h"
#include "gameStateMachine.h"
#include "Game.h"

AnimationState::AnimationState(Game* g, GameState* pS) {
	game = g;
	prevState = pS;
}

void
AnimationState::render() {
	// Renderiza los objetos del gamestate previo
	prevState->render();
}

void
AnimationState::update() {
	// while (función callback da true) repetir la función callback hasta que de false
	game->stateAnimationEnd();
}