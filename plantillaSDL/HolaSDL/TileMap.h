#ifndef TILEMAP_H
#define TILEMAP_H

#include "checkML.h"
#include "Texture.h"
#include "Collision.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <vector>

using namespace std;

#pragma once

class Game;

class TileMap {

private:
	Game* game;
	Texture* tiletexture; // No usamos la clase Texture porque el tilemap no maneja "frames" (nuestra Texture sólo secciona la imagen en horizontal)
	vector<vector<int>> tiledata;
	int nCols;
	int nRows;
	const int OBSTACLE_THRESHOLD = 4; // Número de columnas de la textura donde se contienen los obstáculos

public:
	// Constructora
	TileMap(Texture* tex, Game* g, int worldN);

	// Dibujar el mapa
	void render();

	// Detectar colisiones
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	int returnNCols() { return nCols; }
	int returnNRows() { return nRows; }

	/*
	// Destructora
	~TileMap();
	*/


};

#endif 