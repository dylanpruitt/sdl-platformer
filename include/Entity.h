#ifndef ENTITY_H
#define ENTITY_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Map.h"
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
        bool isMoveable = true;

        SDL_Surface* image = NULL;

        void handleTileCollisions (Map worldmap);

        bool isCollidingWithTile (Map worldmap);

        bool isOnGround (Map worldmap);

        bool isCollidingWithTileOnLeft (Map worldmap);

        bool isCollidingWithTileOnRight (Map worldmap);

        bool isCollidingWithTileFromBelow (Map worldmap);

    protected:

    private:
};

#endif // ENTITY_H
