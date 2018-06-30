#ifndef TILE_H
#define TILE_H

#include "GraphicFunctions.h"

class Tile
{
    public:
        Tile ();
        Tile (std::string imageFileName);
        virtual ~Tile();

        SDL_Surface* image = NULL;

        bool isCollidable;

    protected:

    private:
};

#endif // TILE_H
