#include "checkML.h"
#include "Texture.h"
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
	int tileS;
	const int OBSTACLE_THRESHOLD = 4; // Número de columnas de la textura donde se contienen los obstáculos

public:
	// Constructora
	TileMap(Texture* tex, Game* g, string worldname, string tilesetname, int tilesize);

	// Dibujar el mapa
	void Render();

	// Actualizar el mapa
	void Update() { };

	// Detectar colisiones
	bool Hit(const SDL_Rect& rect, bool fromPlayer);

	int ReturnNCols();
	int ReturnNRows();

	/*
	// Destructora
	~TileMap();
	*/


};