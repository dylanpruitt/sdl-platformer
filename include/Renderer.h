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

    public:

        SDL_Surface *screen = NULL;

        void render (std::vector <Entity> Entities,
                     Map worldmap);

        Renderer ();

};

#endif // RENDERER_H
