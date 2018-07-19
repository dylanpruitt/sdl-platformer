#ifndef RENDERER_H
#define RENDERER_H

#include "Entity.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Tile.h"
#include <string>
#include <vector>

class Renderer
{
    private:
        const int BACKGROUND_INDEX = 3;

    public:
        int cameraXOffset = 0;
        int cameraYOffset = 0;

        static const int TILEMAP_LENGTH = 15;
        static const int TILEMAP_HEIGHT = 15;

        SDL_Surface *screen = NULL;

        void render (Entity player, int tileArray [TILEMAP_LENGTH * TILEMAP_HEIGHT], std::vector <Tile> tiles);

        Renderer ();

};

#endif // RENDERER_H
