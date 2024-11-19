#include "TileMap.h"
#include "Texture.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "SDL.h"
#include "SDL_image.h"

using namespace std;

TileMap::TileMap(Texture* tex, Game* g, string worldname) {

	tiletexture = tex;
	game = g;

	// game->ReturnTexture(Textures::Tilemap)

	string filename = "../assets/maps/" + worldname + ".csv";
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

void TileMap::Render() {
	int tileSide = Game::TILE_SIZE;
	int wWidth = Game::WIN_WIDTH;
	int wHeight = Game::WIN_HEIGHT;
	int offset = game->returnMapOffset();

	// Primera columna y fila del mapa visible
	int x0 = offset / tileSide;
	// Anchura de esa primera columna;
	int d0 = offset % tileSide;


	int targetCol = x0;
	for (int i = 0; i < wWidth + 1; i++) {
		for (int j = 0; j < wHeight - 1; j++) {
			if (i + x0 >= nCols) {
				x0 = nCols - wWidth - 1;
				game->lockOffset();
			}
			int index = tiledata[j][i + x0];

			if (index != -1) {
				int frameX = index % 9;
				int frameY = index / 9;
				int posX = -d0 + i * tileSide;
				int posY = j * tileSide;

				//cout << i << " " << j << " | " << x0 << " " << targetCol << " " << i + x0 << endl;

				tiletexture->RenderFrame(posX, posY, 2, SDL_FLIP_NONE, frameX, frameY);
			}
		}
	}
}

bool TileMap::Hit(const SDL_Rect& rect, bool fromPlayer)
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
			if ((index != -1) && ((index % tiletexture->ReturnNCols()) < OBSTACLE_THRESHOLD)) { // Está en las 4 primeras columnas, es obstáculo
				//cout << "COLISSION \n";
				return true;
			}
		}
	return false;
}

int TileMap::ReturnNCols() {
	return nCols;
}
int TileMap::ReturnNRows() {
	return nRows;
}
