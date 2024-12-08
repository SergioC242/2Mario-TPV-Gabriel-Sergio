#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Game.h"
#include "Block.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Mushroom.h"
#include "Shell.h"
#include "Coin.h"

using namespace std;

// Formato de la especificación de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Número de frames por fila
	uint numRows;		// Número de frames por columna
};

// Directorio raíz de los archivos de textura
const string textureRoot = "../assets/images/";

// Especificación de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	{"blocks.png", 6, 1},
	{"mario.png", 12, 1},
	{"supermario.png", 22, 1},
	{"firemario.png", 21, 1},
	{"goomba.png", 3, 1},
	{"koopa.png", 4, 1},
	{"piranha.png", 2, 1},
	{"shell.png", 2, 1},
	{"coin.png", 4, 1},
	{"mushroom.png", 1, 1},
	{"plant.png", 4, 1},
	{"star.png", 4, 1},
	{"lift.png", 1, 1 },
	{"txt_numbers.png", 10, 1},
	{"txt_mario.png", 1, 1},
	{"txt_lv1.png", 1, 1},
	{"txt_lv2.png", 1, 1},
	{"txt_continue.png", 1, 1},
	{"txt_returnmenu.png", 1, 1},
	{"txt_win.png", 1, 1},
	{"txt_loss.png", 1, 1}
};

Game::Game(int worldN) : exit(false) {

	// Inicializa la SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);

	// Creación de playstates
	//playstate = new PlayState(worldN, this); //se fue a su metodo propio
	mainmenu = new MainMenuState(this);
	GameStateMachine::pushState(mainmenu);
	//GameStateMachine::pushState(playstate);
}



void
Game::run()
{
	//delete prevWorld;

	// Bucle principal del juego

	while (!exit) {
		// Marca de tiempo del inicio de la iteración
		uint32_t inicio = SDL_GetTicks();

		GameStateMachine::update();
		GameStateMachine::render();

		SDL_Event evento;

		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT)
				exit = true;
			else {
				GameStateMachine::handleEvent(evento);
			}
		}
		
		//playstate->update();       // Actualiza el estado de los objetos del juego
		//playstate->render();       // Dibuja los objetos en la venta
		//playstate->handleEvents(); // Maneja los eventos de la SDL (por defecto estaba después de render?)

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraci󮠤el frame
		if (elapsed < Game::FRAME_RATE)
			SDL_Delay(Game::FRAME_RATE - elapsed);
	}
}


void Game::statePlay(int w) {
	playstate = new PlayState(w, this);
	GameStateMachine::replaceState(playstate);
}

void Game::statePause(){
	pausestate = new PauseState(this);
	GameStateMachine::pushState(pausestate);
}

void Game::stateNotPause(){
	GameStateMachine::popState();
}

void Game::stateMainMenu() {
	GameStateMachine::popState();
	mainmenu = new MainMenuState(this); //se puede comentar y ver si va
	GameStateMachine::pushState(mainmenu);
}

void Game::stateAnimation() {
	animationstate = new AnimationState(this, playstate);
	GameStateMachine::pushState(animationstate);
}

void Game::stateAnimationEnd() {
	GameStateMachine::popState();
	playstate->map_reload();
}
void Game::stateEnd() {
	endstate = new EndState(this);
	GameStateMachine::pushState(endstate);
}

void Game::gameExit(){
	exit = true;
}

Game::~Game()
{
	// Elimina las texturas
	for (Texture* texture : textures) delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}