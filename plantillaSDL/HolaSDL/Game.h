#ifndef GAME_H
#define GAME_H

#include <array>
#include <vector>
#include <SDL.h>
#include "checkML.h"

#include "Texture.h"
#include "GameObject.h"
#include "SceneObject.h"
#include "TileMap.h"
#include "Player.h"
#include "gameList.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "AnimationState.h"
#include "EndState.h"
#include "gameStateMachine.h"

#pragma once

using uint = unsigned int;

class TileMap;
class Mushroom;
class Shell;
class Coin;

class Game : private GameStateMachine
{
public:
	// Identificadores de las texturas
	enum TextureName {
		Background,
		Blocks,
		SmallMario,
		SuperMario,
		FireMario,
		GoombaTex,
		KoopaTex,
		PiranhaTex,
		ShellTex,
		CoinTex,
		MushroomTex,
		Plant,
		Star,
		Lift,
		TXT_Numbers,
		TXT_Mario,
		TXT_Lv1,
		TXT_Lv2,
		TXT_Continue,
		TXT_ReturnMenu,
		TXT_Win,
		TXT_Loss,
		TXT_Salir,
		NUM_TEXTURES
	};
	// Constante globales
	static constexpr uint WIN_WIDTH = 544;
	static constexpr uint WIN_HEIGHT = 480;
	static constexpr uint FRAME_RATE = 60;
	static constexpr uint TILE_SIZE = 32;

	// Ventana de la SDL (se destruir� en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;

	// Gamestates
	PlayState* playstate;
	MainMenuState* mainmenu;
	PauseState* pausestate;
	AnimationState* animationstate;
	EndState* endstate;

private:
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	// Interruptor para terminar el juego
	bool exit;

public:
	Texture* getTexture(TextureName name) const { return textures[name]; }

	Game(int worldN);
	~Game();
	void run();
	void statePlay(int w);
	void statePause();
	void stateNotPause();
	void stateMainMenu();
	void stateAnimation(function<bool()> funcAnim);
	void stateAnimationEnd();
	void stateEnd();
	void gameExit();
};

#endif