#ifndef TILEMAP_H
#define TILEMAP_H

#include "checkML.h"
#include "Texture.h"
#include "Collision.h"
#include "SceneObject.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <vector>

#pragma once

class Game;

class TileMap : public SceneObject
{

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
	Collision hit(const SDL_Rect& rect, Collision::ObjetoTipo tipoObj);

	int returnNCols() const { return nCols; }
	int returnNRows() const { return nRows; }

	/*
	// Destructora
	~TileMap();
	*/


};

#endif 