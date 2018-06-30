#ifndef GRAPHICFUNCTIONS_H
#define GRAPHICFUNCTIONS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

namespace GraphicFunctions
{

    extern SDL_Surface *load_image( std::string filename );

    extern void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );


};

#endif // GRAPHICFUNCTIONS_H
