#ifndef BLOCK_H
#define BLOCK_H

#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"
#include "SceneObject.h"
#include "gameList.h"
#include "checkML.h"
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#pragma once

class Block : public SceneObject {
private:
    enum class Tipo {
        Ladrillo,
        Vacio,
        Pregunta,
        Oculto
    };
    enum class Action {
        Potenciador,
        Moneda,
        Nada
    };
    Tipo tipo;
    Action action;
    Point2D position;
    Texture* texture;
    int startFrame;
    int currentFrame;
    Game* game;
    bool hitAnimFrame;

public:

    //constructor
    Block(Texture* tex, Game* g, char t, char a, int x, int y);
    Block* clone() const { return new Block(*this); }

    void render() const;
    void update();
    void act();
    Collision hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj);
    Point2D returnPos() { return position; }
};

#endif
