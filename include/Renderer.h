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

        SDL_Surface *screen = NULL;

        void render (Entity player,
                     Map worldmap);

        Renderer ();

};

#endif // RENDERER_H
