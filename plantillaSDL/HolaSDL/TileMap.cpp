#include "TileMap.h"
#include "Texture.h"
#include "Game.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "SDL.h"
#include "SDL_image.h"

using namespace std;

TileMap::TileMap(Texture* tex, Game* g, int worldN) {

	tiletexture = tex;
	game = g;

	// game->ReturnTexture(Textures::Tilemap)

	string filename = "../assets/maps/world" + to_string(worldN) + ".csv";
	ifstream csvWorld(filename);

	string line;
	int rows = 0;
	while (getline(csvWorld, line)) rows++;
	rows--;

	csvWorld.close();
	csvWorld.open(filename);
	int cols = 0;
	char buffer = 0;
	getline(csvWorld, line);
	for (int i = 0; i < line.size(); i++) if (line[i] == ',') cols++;

	//cout << "Columnas: " << cols << "\nFilas: " << rows << "\n";

	tiledata = vector<vector<int>>(rows, vector<int>(cols, 0));

	int row = 0;
	while (getline(csvWorld, line) && row < rows) {
		stringstream ss(line);
		string cell;
		int col = 0;
		while (getline(ss, cell, ',') && col < cols) {
			tiledata[row][col] = stoi(cell);
			col++;
		}
		row++;
	}

	nCols = cols;
	nRows = rows;
	/*
	for (int i = 0; i < tiledata.size(); i++) {
		for (int j = 0; j < tiledata[i].size(); j++)
			cout << tiledata[i][j] << " ";
		cout << endl;
	}
	*/
	//cout << nCols << " " << nRows << endl;
}

void TileMap::render() {
	int offset = game->offset_Return();

	// Primera columna y fila del mapa visible
	int x0 = offset / (game->TILE_SIZE * game->RENDER_SCALE_MULT);
	// Anchura de ese espacio detrás de la primera columna;
	int d0 = offset % (game->TILE_SIZE * game->RENDER_SCALE_MULT);

	int nColsOnScreen = game->WIN_WIDTH / (game->TILE_SIZE * game->RENDER_SCALE_MULT);

	int targetCol = x0;
	for (int i = 0; i < nColsOnScreen + 1; i++) {
		for (int j = 0; j < nRows; j++) {
			if (x0 + nColsOnScreen >= nCols) {
				x0 = nCols - (nColsOnScreen) - 1;
				game->offset_Lock();
			}
			int index = tiledata[j][i + x0];

			if (index != -1) {
				int frameX = index % 9;
				int frameY = index / 9;
				SDL_Rect rect;
				//rect.x = -d0 + i * game->TILE_SIZE;
				rect.x = -d0 + i * game->TILE_SIZE * game->RENDER_SCALE_MULT;
				rect.y = j * game->TILE_SIZE * game->RENDER_SCALE_MULT;
				rect.w = rect.h = game->TILE_SIZE * game->RENDER_SCALE_MULT;

				//cout << index << " " << frameX << "|" << frameY << " " << rect.x << "|" << rect.y << endl;
				tiletexture->renderFrame(rect, frameY, frameX, SDL_FLIP_NONE);
			}
		}
	}
	//cout << nCols << " " << nColsOnScreen << " " << x0 + nColsOnScreen + 1 << " " << x0 << " " << game->offset_Return() << endl;
}

Collision TileMap::hit(const SDL_Rect& rect, bool fromPlayer)
{
	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / 32;
	int col0 = rect.x / 32;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h) / 32;
	int col1 = (rect.x + rect.w) / 32;

	for (int i = row0; i <= row1; i++)
		for (int j = col0; j <= col1; j++) {
			int index = tiledata[i][j];
			//cout << i << "|" << j << " " << row0 << "|" << col0 << " " << row1 << "|" << col1 << " " << index << " " << tiletexture->ReturnNCols() << " " << index % nCols << endl;
			if ((index != -1) && ((index % tiletexture->getNumColumns()) < OBSTACLE_THRESHOLD)) { // Está en las 4 primeras columnas, es obstáculo
				//cout << "COLISSION \n";
				return Collision(true, 0, Collision::Tilemap); // direction is irrelevant
			}
		}
	return Collision(false, 0, Collision::Tilemap); // direction is irrelevant
}
