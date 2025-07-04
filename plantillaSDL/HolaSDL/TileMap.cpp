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

void TileMap::render() const {
	int offset = game->playstate->offset_Return();

	// Primera columna y fila del mapa visible
	int x0 = offset / (game->TILE_SIZE);
	// Anchura de ese espacio detr�s de la primera columna;
	int d0 = offset % (game->TILE_SIZE);

	int nColsOnScreen = game->WIN_WIDTH / (game->TILE_SIZE);

	int targetCol = x0;
	for (int i = 0; i < nColsOnScreen + 1; i++) {
		for (int j = 0; j < nRows; j++) {
			if (x0 + nColsOnScreen >= nCols) {
				x0 = nCols - (nColsOnScreen) - 1;
				game->playstate->offset_Lock();
			}
			int index = tiledata[j][i + x0];

			if (index != -1) {
				int frameX = index % 9;
				int frameY = index / 9;
				SDL_Rect rect;
				//rect.x = -d0 + i * game->TILE_SIZE;
				rect.x = -d0 + i * game->TILE_SIZE;
				rect.y = j * game->TILE_SIZE;
				rect.w = rect.h = game->TILE_SIZE;

				//cout << index << " " << frameX << "|" << frameY << " " << rect.x << "|" << rect.y << endl;
				tiletexture->renderFrame(rect, frameY, frameX, SDL_FLIP_NONE);
			}
		}
	}
	//cout << nCols << " " << nColsOnScreen << " " << x0 + nColsOnScreen + 1 << " " << x0 << " " << game->offset_Return() << endl;
}

Collision TileMap::hit(const SDL_Rect& rect, Collision::ObjetoTipo tipoObj)
{
	// Celda del nivel que contiene la esquina superior izquierda del rect�ngulo
	int row0 = rect.y / game->TILE_SIZE;
	int col0 = rect.x / game->TILE_SIZE;

	// Celda del nivel que contiene la esquina inferior derecha del rect�ngulo
	int row1 = (rect.y + rect.h) / game->TILE_SIZE;
	int col1 = (rect.x + rect.w) / game->TILE_SIZE;

	for (int i = row0; i <= row1; i++)
		for (int j = col0; j <= col1; j++) {
			if (!(row0 < 0 || row0 > nRows - 1 || col0 < 0 || col0 > nCols - 1 ||
				row1 < 0 || row1 > nRows - 1 || col1 < 0 || col1 > nCols - 1)) { // No comprueba si se saldr�a del tilemap
				int index = tiledata[i][j];
				//cout << i << "|" << j << " " << row0 << "|" << col0 << " " << row1 << "|" << col1 << " " << index << " " << tiletexture->ReturnNCols() << " " << index % nCols << endl;
				if ((index != -1) && ((index % tiletexture->getNumColumns()) < OBSTACLE_THRESHOLD)) { // Est� en las 4 primeras columnas, es obst�culo
					//cout << "COLISSION \n";
					return Collision(true, Collision::CollisionDir::Middle, Collision::Tilemap); // direction is irrelevant
				}
			}
		}
	return Collision(false, Collision::CollisionDir::Middle, Collision::Tilemap); // direction is irrelevant
}
