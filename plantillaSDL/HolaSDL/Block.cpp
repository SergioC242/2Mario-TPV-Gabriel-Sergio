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
    else if (a == 'M') {
        action = Action::Moneda;
    }
    game = g;
}

void Block::render() {

    SDL_Rect rect;
    rect.x = position.X() - game->offset_Return();
    rect.y = position.Y();
    rect.h = game->TILE_SIZE*2;
    rect.w = game->TILE_SIZE*2;

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

}

Collision Block::hit(SDL_Rect rect, bool fromPlayer) {

    SDL_Rect blockRect;
    blockRect.x = position.X();
    blockRect.y = position.Y();
    blockRect.w = blockRect.h = game->TILE_SIZE;

    bool above = false;
    if (rect.x < blockRect.x) {
        above = true;
    }
    SDL_bool intersection = SDL_HasIntersection(&rect, &blockRect);
    if (intersection == SDL_TRUE) {
        return Collision(true, above, Collision::Block);
    }
    return Collision(false, above, Collision::Block);
}