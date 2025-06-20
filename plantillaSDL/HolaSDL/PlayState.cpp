﻿#include "PlayState.h"

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
#include "mPlatform.h"

using namespace std;

PlayState::PlayState(int worldN, Game* g) {
	world = worldN;
	game = g;
	objectVectorPos = 0;
	mapOffset = 0;
	score = 0;
	lockOffset = false;
	loadMap(world);
	vida = 3;
	
}

void PlayState::loadMap(int worldN) {

	tilemap = new TileMap(game->getTexture(Game::Background), game, worldN);
	createdItems.push_back(tilemap);

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
		istringstream l(line);
		l >> tipo;
		l >> posX;
		l >> posY;
		spawnPosX = (posX - 1) * Game::TILE_SIZE;
		spawnPosY = (posY - 2) * Game::TILE_SIZE;
		if (tipo == 'M') { // mario: 3 atributos
			l >> atrib1;
			//cout << "MARIO - " << posX << "|" << posY << "  " << atrib1 << "\n";
			//cout << "SPAWNING AT " << spawnPosX << "|" << spawnPosY << endl;
			storedPlayer = new Player(game->getTexture(Game::SmallMario), game->getTexture(Game::SuperMario), game->getTexture(Game::FireMario), game, spawnPosX, spawnPosY, atrib1);
			player = storedPlayer->clone();
			addEventListener(player);
		}
		else if (tipo == 'B') { // bloque: 4 atributos
			l >> atrib1;
			l >> atrib2;
			//cout << "BLOQUE - " << posX << "|" << posY << "  " << atrib1 << " " << atrib2 << "\n";
			//cout << "SPAWNING AT " << spawnPosX << "|" << spawnPosY << endl;
			Block* block = new Block(game->getTexture(Game::Blocks), game, atrib1, atrib2, spawnPosX, spawnPosY);
			createdItems.push_back(block);
		}
		else if (tipo == 'G') { // goomba: 2 atributos
			//spawnPosX += 0.5 * Game::TILE_SIZE; // Prevención de clipping
			//cout << "GOOMBA - " << posX << "|" << posY << "\n";
			//cout << "SPAWNING AT " << spawnPosX << "|" << spawnPosY << endl;
			Goomba* goomba = new Goomba(game->getTexture(Game::GoombaTex), game, spawnPosX, spawnPosY);
			createdItems.push_back(goomba);
		}
		else if (tipo == 'K') { // koopa: 2 atributos
			spawnPosY -= 0.5 * Game::TILE_SIZE; // Prevención de clipping
			//cout << "KOOPA - " << posX << "|" << posY << "\n";
			//cout << "SPAWNING AT " << spawnPosX << "|" << spawnPosY << endl;
			Koopa* koopa = new Koopa(game->getTexture(Game::KoopaTex), game, spawnPosX, spawnPosY);
			createdItems.push_back(koopa);
		}
		else if (tipo == 'C') { // koopa: 2 atributos
			//spawnPosY -= 0.5 * TILE_SIZE; // Prevención de clipping
			//cout << "COIN - " << posX << "|" << posY << "\n";
			//cout << "SPAWNING AT " << spawnPosX << "|" << spawnPosY << endl;
			Coin* coin = new Coin(game->getTexture(Game::CoinTex), game, spawnPosX, spawnPosY);
			createdItems.push_back(coin);
		}
		else if (tipo == 'L') { // plataforma móvil
			int velocidad;
			l >> velocidad;
			mPlatform* plat = new mPlatform(
				game->getTexture(Game::Lift),      
				game,
				(posX - 1) * Game::TILE_SIZE,         
				(posY - 2) * Game::TILE_SIZE,         
				game->WIN_HEIGHT + Game::TILE_SIZE,   // altura: mueve hasta arriba de pantalla antes de reiniciar
				velocidad							  // velocidad
			);
			createdItems.push_back(plat);
		}

		//cout << "------------------\n";
	}
	//cout << "|                |\n" << "------------------\n";
}

void PlayState::map_reload() {
	if (vida <= 0) {
		game->stateEnd();
	}
	vida--;
	mapOffset = 0;
	for (auto obj : lista) {
		delete obj;
	}
	if (player) {

		removeEventListener(player);
		delete player;
		player = nullptr;
	}
	objectVectorPos = 0;
	player = storedPlayer->clone();
	addEventListener(player);
}

void PlayState::map_next() {
	if (world == 2) {
		game->stateEnd();
	}
	else
	{
		world++;
		mapOffset = 0;
		for (auto obj : lista) {
			delete obj;
		}
		objectVectorPos = 0;
		createdItems.clear();
		loadMap(world);
	}
}

void PlayState::addVisibleObjects() {
	if (objectVectorPos > createdItems.size())objectVectorPos = createdItems.size();
	for (int i = objectVectorPos; i < createdItems.size(); i++) {
		if (createdItems[i]->returnPos().X() < (mapOffset + Game::WIN_WIDTH + Game::TILE_SIZE)) { // Está en pantalla
			/*SceneObject* so = createdItems[i]->clone();
			lista.push_back(so);
			addObject(so);*/
			lista.push_back(createdItems[i]->clone());
			
			objectVectorPos++;
		}
	}
}

Collision PlayState::checkCollisions(SDL_Rect rect, Collision::ObjetoTipo tipoObj) {
	for (auto obj : lista) {
		int distX = abs(obj->returnPos().Y() - rect.y);
		int distY = abs(obj->returnPos().Y() - rect.y);
		if (distX < Game::TILE_SIZE && distY < Game::TILE_SIZE) { // Solo comprueba objetos cerca
			Collision collision = obj->hit(rect, tipoObj);
			if (collision.hasCollided()) {
				return collision;
			}
		}
	}
	return Collision(false, Collision::CollisionDir::Middle, Collision::None);
}

void
PlayState::render()
{
	SDL_RenderClear(game->renderer);
	// Color de fondo
	if (world == 1) {
		SDL_SetRenderDrawColor(game->renderer, 38, 132, 255, 255);
	}
	if (world == 2) {
		SDL_SetRenderDrawColor(game->renderer, 10, 0, 10, 255);
	}

	// Pinta los objetos del juego
	for (auto elem : lista) {
		elem->render();
	}
	//GameState::render();


	// Renderiza player
	if (player) player->render();
	// Renderiza objetos del mapa

	SDL_RenderPresent(game->renderer);
}

void
PlayState::update()
{
	// Actualiza player
	if (player) player->update();
	// Actualiza los objetos del juego
	addVisibleObjects();
	for (auto elem : lista) {
		elem->update();
	}
}

void
PlayState::handleEvents(SDL_Event e)
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT) {
			//exit = true;
		}
		else if (evento.type == SDL_KEYDOWN || evento.type == SDL_KEYUP) {

			//if (evento.key.keysym.sym == SDLK_ESCAPE) {
			//	
			//	game->statePause();
			//}
			//else if (player) player->handleEvent(evento.key);
		}
	}
}

void PlayState::createMushrooms(int x, int y) {
	Mushroom* mushroom = new Mushroom(game->getTexture(Game::MushroomTex), game, x, y - Game::TILE_SIZE);
	lista.push_back(mushroom);
}
void PlayState::createShell(int x, int y) {
	Shell* shell = new Shell(game->getTexture(Game::ShellTex), game, x, y - Game::TILE_SIZE * 2);
	lista.push_back(shell);
}

int
PlayState::offset_Return() const {
	return mapOffset;
}
void
PlayState::offset_Add(int n) {
	mapOffset += n;
}
void
PlayState::offset_Lock() {
	lockOffset = true;
}
bool
PlayState::offset_isLocked() const {
	return lockOffset;
}

void
PlayState::addScore(int n) {
	score += n;
	cout << "SCORE: " << to_string(score) << endl;
}

PlayState::~PlayState() {
	// Elimina los objetos del mapa cargado
	for (GameObject* obj : createdItems) {
		delete obj;
	}
	createdItems.clear();

	// Elimina todos los objetos activos en la lista
	for (SceneObject* obj : lista) {
		delete obj;
	}
	

	if (player) {
		delete player;
		player = nullptr;
	}

	//Delete Stored Player
	if (storedPlayer) {
		delete storedPlayer;
		storedPlayer = nullptr;
	}
}