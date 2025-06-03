#pragma once
#include "SceneObject.h"
#include "Game.h"
#include "Texture.h"


class mPlatform : public SceneObject
{
private:
    Texture* texture;
    Game* game;
    Point2D position;
    SDL_Rect rect;
    int moveY;
    bool goingUp;
    int minY, maxY;

public:
    mPlatform(Texture* tex, Game* g, int x, int y, int range);
    virtual void render() const override;
    virtual void update() override;
    virtual Collision hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj) override;
    Point2D returnPos() override { return position; }

    int getMoveY() const { return moveY; }

};

