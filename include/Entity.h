#ifndef ENTITY_H
#define ENTITY_H

#include "GraphicFunctions.h"

class Entity
{
    public:
        Entity();
        Entity (std::string imageFileName);
        virtual ~Entity();

        int Health;
        int MaxHealth;

        int xPosition = 0;
        int yPosition = 0;

        int xVelocity = 0;
        int yVelocity = 0;

        int xAcceleration = 0;
        int yAcceleration = 0;

        int Weight;

        bool isExplodable = false;
        bool isStaticObject = false;

        SDL_Surface* image = NULL;

    protected:

    private:
};

#endif // ENTITY_H
