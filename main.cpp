#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <math.h>
#include <iostream>
#include "Renderer.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;
const int SCREEN_BPP = 32;
const int TILEMAP_LENGTH = 15;

SDL_Event event;

bool keysHeld [323] = {false};

void FreeAllTileSurfaces ( std::vector <Tile> tileset ) {

    for (unsigned int i = 0; i < tileset.size (); i++) {

        SDL_FreeSurface (tileset[i].image);

    }

}

bool isEntityCollidingWithTile (Entity entity, int tileArray [TILEMAP_LENGTH * TILEMAP_LENGTH], std::vector <Tile> tiles) {

    for (int i = 0; i < TILEMAP_LENGTH * TILEMAP_LENGTH; i++) {

        if (entity.xPosition+entity.xSize >= (i % TILEMAP_LENGTH)*32 + 1 && entity.xPosition <= ((i % TILEMAP_LENGTH)+1)*32
            && entity.yPosition+entity.ySize >= (i / TILEMAP_LENGTH)*32 && entity.yPosition <= ((i / TILEMAP_LENGTH)+1)*32) {


            if (tiles [tileArray [i]].isCollidable) {

                return true;

            }

        }

    }

    return false;

}

std::vector <int> returnIndicesOfAllTilesEntityIsIn (Entity entity, int tileArray [TILEMAP_LENGTH * TILEMAP_LENGTH], std::vector <Tile> tiles) {

    std::vector <int> tileIndices;

    for (int i = 0; i < TILEMAP_LENGTH * TILEMAP_LENGTH; i++) {

        if (entity.xPosition+entity.xSize >= (i % TILEMAP_LENGTH)*32 && entity.xPosition <= (i % TILEMAP_LENGTH + 1) * 32
            && entity.yPosition+entity.ySize >= (i / TILEMAP_LENGTH)*32+1 && entity.yPosition <= ((i / TILEMAP_LENGTH)+1)*32) {

            tileIndices.push_back (i);

        }

    }

    return tileIndices;

}

bool isEntityCollidingWithTileOnLeftOrRight (Entity entity, int tileArray [TILEMAP_LENGTH * TILEMAP_LENGTH], std::vector <Tile> tiles, std::vector <int> tileIndices) {

    for (unsigned int i = 0; i < tileIndices.size (); i++) {

        if (tiles [tileArray [tileIndices [i]]].isCollidable) {

            return true;

        }

    }

}

void shiftCameraBasedOnPlayerPosition (Entity player, Renderer &renderer) {

    int playerXPositionOnScreen, playerYPositionOnScreen;

    playerXPositionOnScreen = player.xPosition - renderer.cameraXOffset;
    playerYPositionOnScreen = player.yPosition - renderer.cameraYOffset;

    if (playerXPositionOnScreen <= 144 && renderer.cameraXOffset > 0) {

        renderer.cameraXOffset += player.xVelocity;

    }

    if (playerXPositionOnScreen >= SCREEN_WIDTH-144 && renderer.cameraXOffset < 32*15 - SCREEN_WIDTH) {

        renderer.cameraXOffset += player.xVelocity;

    }

    if (playerYPositionOnScreen <= 144 && renderer.cameraYOffset > 0) {

        renderer.cameraYOffset += player.yVelocity;

    }

    if (playerYPositionOnScreen >= SCREEN_WIDTH-144 && renderer.cameraYOffset < 32*15 - SCREEN_WIDTH) {

        renderer.cameraYOffset += player.yVelocity;

    }

    if (renderer.cameraXOffset < 0) { renderer.cameraXOffset = 0; }
    if (renderer.cameraYOffset < 0) { renderer.cameraYOffset = 0; }
    if (renderer.cameraXOffset > 32*15 - SCREEN_WIDTH) { renderer.cameraXOffset = 32*15 - SCREEN_WIDTH; }
    if (renderer.cameraYOffset > 32*15 - SCREEN_WIDTH) { renderer.cameraYOffset = 32*15 - SCREEN_WIDTH; }

}

int main( int argc, char* args[] )
{

    Renderer renderer;

    bool quit = false;

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;
    }

    renderer.screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( renderer.screen == NULL )
    {
        return 1;
    }

    SDL_WM_SetCaption( "SDL Platformer", NULL);

    Entity player ("teatest.png"); player.Health = 3;

    std::vector<Tile> tiles;

    Tile grass ("grass.png"); tiles.push_back (grass);
    Tile dirt ("dirttile.png"); tiles.push_back (dirt);
    Tile alt_dirt ("dirttile2.png"); tiles.push_back (alt_dirt);
    Tile sky ("SkyTile1.png"); sky.isCollidable = false; tiles.push_back (sky);
    Tile sky_cloud_1 ("SkyTile2.png"); sky_cloud_1.isCollidable = false; tiles.push_back (sky_cloud_1);
    Tile sky_cloud_2 ("SkyTile3.png"); sky_cloud_2.isCollidable = false; tiles.push_back (sky_cloud_2);
    Tile foilage ("foilage1.png"); foilage.isCollidable = false; tiles.push_back (foilage);
    Tile alt_foilage ("foilage2.png"); alt_foilage.isCollidable = false; tiles.push_back (alt_foilage);
    Tile cave_background ("cave_background.png"); cave_background.isCollidable = false; tiles.push_back (cave_background);

    int tileArray [TILEMAP_LENGTH * TILEMAP_LENGTH] =
                          { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
                            3,3,3,3,3,3,3,4,5,3,3,3,3,3,3,
                            3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,
                            3,3,3,3,3,3,6,3,3,7,3,3,3,3,3,
                            6,3,3,3,3,3,0,3,3,0,3,3,3,3,3,
                            0,7,6,7,6,7,3,7,0,2,3,3,3,3,3,
                            2,0,0,0,0,0,0,0,1,2,3,3,3,3,3,
                            1,2,1,2,1,2,1,2,1,2,3,3,3,3,3,
                            1,2,1,2,1,2,1,2,1,2,3,3,3,3,3,
                            1,2,1,2,1,2,1,2,1,2,3,3,3,3,3,
                            1,2,1,8,8,8,8,8,8,8,3,3,3,3,3,
                            1,8,8,8,8,8,8,8,8,3,4,5,3,3,0,
                            1,2,1,8,8,8,8,8,8,3,3,3,3,3,1,
                            1,2,1,2,1,2,1,8,8,3,3,3,0,0,1,
                            1,2,1,2,1,2,1,2,0,0,0,0,1,2,1,
                          };

     while( quit == false ) {

        if( SDL_PollEvent( &event ) ) {

            if (event.type == SDL_KEYUP) {

                keysHeld[event.key.keysym.sym] = false;

            }

            if( event.type == SDL_KEYDOWN ) {

                keysHeld[event.key.keysym.sym] = true;

                switch( event.key.keysym.sym ) {

                    case SDLK_UP: { SDL_WM_SetCaption( "SDL Platformer - Pressing Up!", NULL);
                        if (isEntityCollidingWithTile (player, tileArray, tiles)) { player.yVelocity -= 10; } } break;


                    default: break;

                }

            }



            else if( event.type == SDL_QUIT ) {

                quit = true;

            }

        }

            if ( keysHeld[SDLK_LEFT] ) {

                if (player.xVelocity > 0) {

                    player.xVelocity -= 0.75;

                } else {

                    player.xVelocity -= 0.15;

                }

            }

            if ( keysHeld[SDLK_RIGHT] ) {

                if (player.xVelocity < 0) {

                    player.xVelocity += 0.75;

                } else {

                    player.xVelocity += 0.15;

                }

            }

        SDL_Delay (50);

        renderer.render (player, tileArray, tiles);

        if( SDL_Flip( renderer.screen ) == -1 ) {

            return 1;

        }

        SDL_FillRect(renderer.screen, NULL, SDL_MapRGB(renderer.screen->format, 0, 0, 0));

        if (!isEntityCollidingWithTile (player, tileArray, tiles) || player.yVelocity != 0) {

            player.yPosition += player.yVelocity;

            if (isEntityCollidingWithTile (player, tileArray, tiles)) {

                if (player.yVelocity > 0) {

                    int displacement = player.yPosition % (32 - player.ySize);

                    player.yPosition -= displacement;

                    player.yVelocity = 0;

                }

                if (player.yVelocity < 0) {

                    int displacement = 32 - (player.yPosition % 32);

                    player.yPosition += displacement + 1;

                    player.yVelocity = 0;

                }

            } else {

                player.yVelocity ++;

            }

        }

        player.xPosition += player.xVelocity;

        if (isEntityCollidingWithTileOnLeftOrRight (player, tileArray, tiles, returnIndicesOfAllTilesEntityIsIn (player, tileArray, tiles))) {

            if (player.xVelocity > 0) {

                    int displacement = player.xPosition % (32 - player.xSize);

                    player.xPosition -= displacement;

                    player.xVelocity = 0;

            }

            if (player.xVelocity < 0) {

                    int displacement = (32*player.xPosition/32 + 1) % (player.xPosition) + 1; std::cout << player.xPosition << " _ " << displacement << std::endl;

                    player.xPosition += displacement;

                    player.xVelocity = 0;

            }

        }

        if ( !keysHeld[SDLK_LEFT] && !keysHeld[SDLK_RIGHT] && isEntityCollidingWithTile (player, tileArray, tiles)) {

            if (player.xVelocity > 0) { player.xVelocity -= 0.75; }
            if (player.xVelocity < 0) { player.xVelocity += 0.75; }

        }

        if (player.xPosition < 0) { player.xPosition = 0; }

        shiftCameraBasedOnPlayerPosition (player, renderer);

    }

    FreeAllTileSurfaces (tiles);

    SDL_FreeSurface (player.image);

    SDL_Quit();

    return 0;
}
