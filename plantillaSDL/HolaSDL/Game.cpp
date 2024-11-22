#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Game.h"

using namespace std;

// Formato de la especificación de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Número de frames por fila
	uint numRows;		// Número de frames por columna
};

// Directorio raíz de los archivos de textura
const string textureRoot = "../assets/imgs/";

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
	{"mushroom.png", 1, 1},
	{"plant.png", 4, 1},
	{"star.png", 4, 1},
};

Game::Game(int worldN)
	: exit(false)
{
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

	// Color de fondo
	SDL_SetRenderDrawColor(renderer, 38, 132, 255, 255);

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);

	// Crea los elementos del juego
	//tilemap = new TileMap(textures[Background], this, worldN);
	//player = new Player(textures[SmallMario], textures[SuperMario], textures[FireMario], this, 1 * TILE_SIZE, 14 * TILE_SIZE, 3);
	loadMap(worldN);
	// Crea los objetos del juego
	
}

void Game::loadMap(int worldN) {

	tilemap = new TileMap(textures[Background], this, worldN);

	string filename = "../assets/maps/world" + to_string(worldN) + ".txt";
	ifstream txtWorld(filename);

	char tipo;
	float posX;
	float posY;
	float spawnPosX;
	float spawnPosY;
	char atrib1;
	char atrib2;
	string line;
	while (getline(txtWorld, line)) {
		//cout << line << endl;
		istringstream l(line);
		l >> tipo;
		l >> posX;
		l >> posY;
		spawnPosX = (posX - 1) * TILE_SIZE;
		spawnPosY = (posY - 2) * TILE_SIZE;
		if (tipo == 'M') { // mario: 3 atributos
			l >> atrib1;
			cout << "MARIO - " << posX << "|" << posY << "  " << atrib1 << "\n";
			cout << "SPAWNING AT " << spawnPosX << "|" << spawnPosY << endl;
			player = new Player(textures[SmallMario], textures[SuperMario], textures[FireMario], this, spawnPosX, spawnPosY, atrib1);
		}
		else if (tipo == 'B') { // bloque: 4 atributos
			l >> atrib1;
			l >> atrib2;
			cout << "BLOQUE - " << posX << "|" << posY << "  " << atrib1 << " " << atrib2 << "\n";
			cout << "SPAWNING AT " << spawnPosX << "|" << spawnPosY << endl;
			//Block* block = new Block(ReturnTexture(Textures::Blocks), this, atrib1, atrib2, spawnPosX, spawnPosY);
			//blocks.push_back(block);
		}
		else if (tipo == 'G') { // goomba: 2 atributos
			spawnPosX += 0.5 * TILE_SIZE; // Prevención de clipping
			cout << "GOOMBA - " << posX << "|" << posY << "\n";
			cout << "SPAWNING AT " << spawnPosX << "|" << spawnPosY << endl;
			//Goomba* goomba = new Goomba(ReturnTexture(Textures::Goomba), this, windowW, windowH, spawnPosX, spawnPosY);
			//goombas.push_back(goomba);
		}
		else if (tipo == 'K') { // koopa: 2 atributos
			spawnPosY -= 0.5 * TILE_SIZE; // Prevención de clipping
			cout << "KOOPA - " << posX << "|" << posY << "\n";
			cout << "SPAWNING AT " << spawnPosX << "|" << spawnPosY << endl;
			//Koopa* koopa = new Koopa(ReturnTexture(Textures::Koopa), this, windowW, windowH, spawnPosX, spawnPosY);
			//koopas.push_back(koopa);
		}

		cout << "------------------\n";
	}
	cout << "|                |\n" << "------------------\n";
}

Game::~Game()
{
	// Elimina los objetos del juego
	
	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void
Game::run()
{
	// Bucle principal del juego
	while (!exit) {
		// Marca de tiempo del inicio de la iteración
		uint32_t inicio = SDL_GetTicks();

		
		update();       // Actualiza el estado de los objetos del juego
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL (por defecto estaba después de render?)

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		/*
		if (!lockOffset) { // AVANCE POR FUERZA BRUTA
			offset_Add(8);
		}
		*/

		// Duerme el resto de la duraci󮠤el frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// Pinta los objetos del juego
	
	/*
	test
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.h = rect.w = 32;
	textures[SmallMario]->renderFrame(rect, 0, 1, SDL_FLIP_NONE);
	*/
	

	// Renderiza tilemap
	tilemap->render();
	// Renderiza player
	player->render();

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// Actualiza los objetos del juego
	player->update();
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			exit = true;
		else if (evento.type == SDL_KEYDOWN || evento.type == SDL_KEYUP) {
			player->handleEvent(evento.key);
		}
	}
}

int 
Game::offset_Return() {
	return mapOffset;
}
void 
Game::offset_Add(int n) {
	mapOffset += n;
}
void 
Game::offset_Lock() {
	lockOffset = true;
}
bool 
Game::offset_isLocked() {
	return lockOffset;
}
