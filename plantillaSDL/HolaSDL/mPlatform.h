#pragma once
#include "SceneObject.h"

#include "Texture.h"

class Game;

class mPlatform : public SceneObject
{
private:
    Game* game;
    Texture* texture;
    Point2D position;
    SDL_Rect rect;

    int movSpeed;
    int topY, bottomY;

public:
    mPlatform(Texture* tex, Game* g, int x, int y, int rangeInPixels = 5, int speed = 1);

    virtual void update() override;
    virtual void render() const override;
    virtual Collision hit(SDL_Rect rect, Collision::ObjetoTipo tipoObj) override;
    virtual Point2D returnPos() override { return position; }
    int getMoveY() { return movSpeed; }


    // Heredado vía SceneObject
    SceneObject* clone() const override;

};

