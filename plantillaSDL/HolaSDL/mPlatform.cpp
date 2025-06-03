#include "mPlatform.h"
#include "Collision.h"
#include "Game.h"

 
mPlatform::mPlatform(Texture* tex, Game* g, int x, int y, int rangeInPixels, int speed)
    : texture(tex), game(g), position(x, y), movSpeed(speed)
{
    rect.w = texture->getFrameWidth() * 2;
    rect.h = texture->getFrameHeight();
    rect.x = position.X();
    rect.y = position.Y();
    topY = y;
    bottomY = y + rangeInPixels;
}

void mPlatform::update() {
    /*
    position += Point2D(0, movSpeed);

    if (position.Y() <= topY || position.Y() >= bottomY) {
        movSpeed = -movSpeed;
    }

    rect.x = position.X() - game->playstate->offset_Return();
    rect.y = position.Y();
    */
    position += Point2D(0, -movSpeed); // sube

    // si ha salido por arriba, reaparece abajo
    if(movSpeed > 0)
    {
        if (position.Y() + rect.h < 0) {
            position = Point2D(position.X(), Game::WIN_HEIGHT);
        }
    }
    else {
        if (position.Y() + rect.h > Game::WIN_HEIGHT) {
            position = Point2D(position.X(), 0);
        }
    }

    rect.x = position.X() - game->playstate->offset_Return();
    rect.y = position.Y();
}

void mPlatform::render() const {
    texture->render(rect);
}

Collision mPlatform::hit(SDL_Rect r, Collision::ObjetoTipo tipoObj) {
    SDL_Rect platRect = {
        position.X(),
        position.Y(),
        texture->getFrameWidth() * 2,
        texture->getFrameHeight()
    };

    Collision::CollisionDir dir = Collision::CollisionDir::Middle;
    if (r.y + r.h <= platRect.y) {
        dir = Collision::CollisionDir::Above;
    }

    if (SDL_HasIntersection(&r, &platRect)) {
        return Collision(true, dir, Collision::ObjetoTipo::MovingPlatform, this);
    }

    return Collision(false, dir, Collision::None);
}

SceneObject* mPlatform::clone() const
{
    return new mPlatform(*this);
}

