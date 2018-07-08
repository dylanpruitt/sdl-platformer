#ifndef ENTITY_H
#define ENTITY_H

#include "GraphicFunctions.h"

class Entity
{
    public:
        Entity();
        Entity (std::string imageFileName);
        virtual ~Entity();

        int Health = 1;
        int MaxHealth = 1;

        int xSize = 16;
        int ySize = 16;

        int xPosition = 0;
        int yPosition = 0;

        double xVelocity = 0;
        double yVelocity = 0;

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
