#include "Block.h"
#include "Texture.h"
#include "Collision.h"
#include "Mushroom.h"
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

void Block::render() const{
    // const SDL_Rect& target, int row, int col, SDL_RendererFlip flip
    if (tipo == Tipo::Pregunta) {
        texture->renderFrame(rect, 0, startFrame + currentFrame, SDL_FLIP_NONE);
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
    rect.x = position.X() - game->playstate->offset_Return();
    rect.y = position.Y();
    rect.h = Game::TILE_SIZE;
    rect.w = Game::TILE_SIZE;

    if (hitAnimFrame) {
        rect.y = position.Y() - (Game::TILE_SIZE / 2);
        hitAnimFrame = false;
    }
    if (tipo == Tipo::Pregunta) {
        if (currentFrame >= 3) {
            currentFrame = 0;
        }
        else {
            currentFrame++;
        }
    }
}

void Block::act() {
    string ac;
    if (action == Action::Moneda) {
        game->playstate->addScore(200);
    }
    else if (action == Action::Potenciador) {
        game->playstate->createMushrooms(position.X(), position.Y());
    }
}

void Block::destroyBrick() {
    game->playstate->addScore(50);
    delete this;
}

Collision Block::hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj) {

    SDL_Rect blockRect;
    blockRect.x = position.X();
    blockRect.y = position.Y();
    blockRect.w = blockRect.h = Game::TILE_SIZE;
    if (tipo == Tipo::Pregunta) {
        // Los bloques pregunta colisionan un poco m�s abajo, dando prioridad sobre otros bloques a la misma altura
        blockRect.h += 8; 
    }

    Collision::CollisionDir dir = Collision::CollisionDir::Middle;
    
    if (rect.y < blockRect.y) {
        dir = Collision::CollisionDir::Above;
    }
    else if (rect.y > blockRect.y - Game::TILE_SIZE) {
        dir = Collision::CollisionDir::Below;
    }

    SDL_bool intersection = SDL_HasIntersection(&rect, &blockRect);
    if (intersection == SDL_TRUE) {
        
        Collision::ObjetoTipo type = Collision::Block;
        if (tipoObj == Collision::ObjetoTipo::Player && dir == Collision::CollisionDir::Below) {
            if (tipo == Tipo::Pregunta) {
                tipo = Tipo::Vacio;
                hitAnimFrame = true;
                act();
            }
            else if (tipo == Tipo::Ladrillo && game->playstate->isSuperMario()) {
                destroyBrick();
            }
        }

        return Collision(true, dir, type);
    }
    return Collision(false, dir, Collision::Block);
}