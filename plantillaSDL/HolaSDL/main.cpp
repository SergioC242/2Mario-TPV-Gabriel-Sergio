#include "checkML.h"

#include <iostream>

#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	try {
		Game game = Game(1);


		cout << "-------------------" << endl;
		cout << "CONTROLES" << endl;
		cout << "Movimiento: flechas" << endl;
		cout << "Pausa: escape" << endl;
		cout << "-------------------" << endl;
		cout << "Gabriel Barroso Bueno" << endl;
		cout << "Sergio Croche Trigo" << endl;
		cout << "-------------------" << endl;

		game.run();
	}
	catch (const std::string& msg) {
		cerr << "Error: " << msg << endl;
	}

	return 0;
}
