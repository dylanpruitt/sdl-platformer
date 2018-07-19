#ifndef ENTITY_H
#define ENTITY_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Tile.h"
#include <string>
#include <vector>

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

        int Weight;

        bool isExplodable = false;
        bool isStaticObject = false;

        static const int tileArraySize = 225;

        SDL_Surface* image = NULL;

        bool isOnGround (int tileArray [tileArraySize], std::vector <Tile> tiles);

    protected:

    private:
};

#endif // ENTITY_H
