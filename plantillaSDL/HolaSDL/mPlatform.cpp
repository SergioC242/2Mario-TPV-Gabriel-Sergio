#include "mPlatform.h"
#include "Collision.h"

mPlatform::mPlatform(Texture* tex, Game* g, int x, int y, int range)
    : texture(tex), game(g), position(x, y), moveY(1), goingUp(false) {
    minY = y - range;
    maxY = y + range;
}

void mPlatform::update() {
    if (goingUp) {
        position += Point2D(0, -moveY);
        if (position.Y() <= minY) goingUp = false;
    }
    else {
        position += Point2D(0, moveY);
        if (position.Y() >= maxY) goingUp = true;
    }

    rect.x = position.X() - game->playstate->offset_Return();
    rect.y = position.Y();
    rect.w = texture->getFrameWidth();
    rect.h = texture->getFrameHeight();
}

void mPlatform::render() const {
    texture->render(rect);
}

Collision mPlatform::hit(SDL_Rect r, Collision::ObjetoTipo tipoObj) {
    SDL_Rect platRect = {
        position.X(),
        position.Y(),
        texture->getFrameWidth(),
        texture->getFrameHeight()
    };

    Collision::CollisionDir dir = Collision::CollisionDir::Middle;
    if (r.y + r.h <= platRect.y + 5) {
        dir = Collision::CollisionDir::Above;
    }

    if (SDL_HasIntersection(&r, &platRect)) {
        return Collision(true, dir, Collision::ObjetoTipo::MovingPlatform, this);
    }

    return Collision(false, dir, Collision::None);
}

