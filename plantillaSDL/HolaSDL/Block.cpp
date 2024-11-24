#include "Block.h"
#include "Texture.h"
#include "Collision.h"
using namespace std;

//constructor
Block::Block(Texture* tex, Game* g, char t, char a, int x, int y) : position(x, y) {

    texture = tex;
    tipo = Tipo::Vacio;
    action = Action::Nada;
    startFrame = 0;
    currentFrame = 0;

    if (t == 'B') {
        tipo = Tipo::Ladrillo;
        startFrame = 5;
    }
    else if (t == '0') {
        tipo = Tipo::Vacio;
        startFrame = 4;
    }
    else if (t == '?') {
        tipo = Tipo::Pregunta;
        startFrame = 0;
    }
    else if (t == 'H') {
        tipo = Tipo::Oculto;
        startFrame = -1;
    }

    if (a == 'P') {
        action = Action::Potenciador;
    }
    else if (a == 'C') {
        action = Action::Moneda;
    }
    game = g;
}

Point2D Block::returnPos() {
    return position;
}

void Block::render() {

    SDL_Rect rect;
    rect.x = position.X() - game->offset_Return();
    rect.y = position.Y();
    rect.h = game->TILE_SIZE;
    rect.w = game->TILE_SIZE;

    if (hitAnimFrame) {
        rect.y = position.Y() - (game->TILE_SIZE / 2);
        hitAnimFrame = false;
    }

    // const SDL_Rect& target, int row, int col, SDL_RendererFlip flip
    if (tipo == Tipo::Pregunta) {
        texture->renderFrame(rect, 0, startFrame + currentFrame, SDL_FLIP_NONE);

        if (currentFrame >= 3) {
            currentFrame = 0;
        }
        else {
            currentFrame++;
        }
    }
    else {
        texture->renderFrame(rect, 0, startFrame, SDL_FLIP_NONE);
    }
}

void Block::update() {
    if (tipo == Tipo::Ladrillo) {
        startFrame = 5;
    }
    else if (tipo == Tipo::Vacio) {
        startFrame = 4;
    }
    else if (tipo == Tipo::Pregunta) {
        startFrame = 0;
    }
    else if (tipo == Tipo::Oculto) {
        startFrame = -1;
    }
}

void Block::act() {
    string ac;
    if (action == Action::Moneda) {
        ac = "moneda";
    }
    else if (action == Action::Potenciador) {
        ac = "potenciador";
    }
    cout << "bloque golpeado con accion " << ac << endl;
}

Collision Block::hit(SDL_Rect rect, bool fromPlayer) {

    SDL_Rect blockRect;
    blockRect.x = position.X();
    blockRect.y = position.Y();
    blockRect.w = blockRect.h = game->TILE_SIZE;
    if (tipo == Tipo::Pregunta) {
        // Los bloques pregunta colisionan un poco más abajo, dando prioridad sobre otros bloques a la misma altura
        blockRect.h += 8; 
    }

    Collision::CollisionDir dir = Collision::CollisionDir::Middle;
    
    if (rect.y < blockRect.y) {
        dir = Collision::CollisionDir::Above;
    }
    else if (rect.y > blockRect.y - game->TILE_SIZE) {
        dir = Collision::CollisionDir::Below;
    }

    SDL_bool intersection = SDL_HasIntersection(&rect, &blockRect);
    if (intersection == SDL_TRUE) {

        if (tipo == Tipo::Pregunta && dir == Collision::CollisionDir::Below && fromPlayer && ) {
            tipo = Tipo::Vacio;
            hitAnimFrame = true;
            act();
        }

        return Collision(true, dir, Collision::Block);
    }
    return Collision(false, dir, Collision::Block);
}