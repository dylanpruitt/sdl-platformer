#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <vector>
#include "Tile.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;
const int SCREEN_BPP = 32;
const int TILEMAP_LENGTH = 10;

SDL_Surface *screen = NULL;

void FreeAllTileSurfaces ( std::vector <Tile> tileset ) {

    for (unsigned int i = 0; i < tileset.size (); i++) {

        SDL_FreeSurface (tileset[i].image);

    }

}

int main( int argc, char* args[] )
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL )
    {
        return 1;
    }

    SDL_WM_SetCaption( "SDL Platformer", NULL);

    std::vector<Tile> tiles;

    Tile grass ("grass.png"); tiles.push_back (grass);
    Tile dirt ("dirttile.png"); tiles.push_back (dirt);
    Tile alt_dirt ("dirttile2.png"); tiles.push_back (alt_dirt);
    Tile sky ("SkyTile1.png"); tiles.push_back (sky);
    Tile sky_cloud_1 ("SkyTile2.png"); tiles.push_back (sky_cloud_1);
    Tile sky_cloud_2 ("SkyTile3.png"); tiles.push_back (sky_cloud_2);
    Tile foilage ("foilage1.png"); tiles.push_back (foilage);
    Tile alt_foilage ("foilage2.png"); tiles.push_back (alt_foilage);

    int tileArray [TILEMAP_LENGTH * TILEMAP_LENGTH] =
                          { 3,3,3,3,3,3,3,3,3,3,
                            3,3,3,3,3,3,3,4,5,3,
                            3,3,3,3,3,3,3,3,3,3,
                            3,3,3,3,3,3,3,3,3,3,
                            3,3,3,3,3,3,3,3,3,3,
                            6,7,6,7,6,7,6,7,6,7,
                            0,0,0,0,0,0,0,0,0,0,
                            1,2,1,2,1,2,1,2,1,2,
                            1,2,1,2,1,2,1,2,1,2,
                            1,2,1,2,1,2,1,2,1,2
                          };

    for (int i = 0; i < 100; i++) {

        GraphicFunctions::apply_surface (32 * (i % TILEMAP_LENGTH), 32 * (i / TILEMAP_LENGTH), tiles[tileArray [i]].image, screen);

    }

    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    SDL_Delay( 12500 );

    FreeAllTileSurfaces (tiles);

    SDL_Quit();

    return 0;
}
