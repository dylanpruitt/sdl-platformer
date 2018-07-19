#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <math.h>
#include <iostream>
#include "Renderer.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;
const int SCREEN_BPP = 32;

SDL_Event event;

Renderer renderer;

const int tileArraySize = renderer.TILEMAP_LENGTH * renderer.TILEMAP_HEIGHT;


bool keysHeld [323] = {false};

void FreeAllTileSurfaces ( std::vector <Tile> tileset ) {

    for (unsigned int i = 0; i < tileset.size (); i++) {

        SDL_FreeSurface (tileset[i].image);

    }

}

bool isEntityCollidingWithTile (Entity entity, int tileArray [tileArraySize], std::vector <Tile> tiles) {

    for (int i = 0; i < renderer.TILEMAP_LENGTH * renderer.TILEMAP_HEIGHT; i++) {

        if (entity.xPosition+entity.xSize > (i % renderer.TILEMAP_LENGTH)*32 && entity.xPosition <= ((i % renderer.TILEMAP_LENGTH)+1)*32
            && entity.yPosition+entity.ySize > (i / renderer.TILEMAP_HEIGHT)*32 && entity.yPosition < ((i / renderer.TILEMAP_HEIGHT)+1)*32) {


            if (tiles [tileArray [i]].isCollidable) {

                return true;

            }

        }

    }

    return false;

}

bool isOnGround (Entity entity, int tileArray [tileArraySize], std::vector <Tile> tiles) {

     for (int i = 0; i < renderer.TILEMAP_LENGTH * renderer.TILEMAP_HEIGHT; i++) {

        int minimumBoundYCoordinate = entity.yPosition+entity.ySize-(entity.ySize / 4);

        if (entity.xPosition+entity.xSize > (i % renderer.TILEMAP_LENGTH)*32 && entity.xPosition <= ((i % renderer.TILEMAP_LENGTH)+1)*32
            &&  minimumBoundYCoordinate + (entity.ySize / 4) >= (i / renderer.TILEMAP_HEIGHT)*32 && minimumBoundYCoordinate <= ((i / renderer.TILEMAP_HEIGHT)+1)*32) {


            if (tiles [tileArray [i]].isCollidable) {

                return true;

            }

        }

    }

    return false;

}

std::vector <int> returnIndicesOfAllTilesEntityIsIn (Entity entity, int tileArray [tileArraySize], std::vector <Tile> tiles) {

    std::vector <int> tileIndices;

    for (int i = 0; i < renderer.TILEMAP_LENGTH * renderer.TILEMAP_HEIGHT; i++) {

        if (entity.xPosition+entity.xSize > (i % renderer.TILEMAP_LENGTH)*32 && entity.xPosition < (i % renderer.TILEMAP_LENGTH + 1) * 32
            && entity.yPosition+entity.ySize > (i / renderer.TILEMAP_HEIGHT)*32 && entity.yPosition < ((i / renderer.TILEMAP_HEIGHT)+1)*32) {

            tileIndices.push_back (i);

        }

    }

    return tileIndices;

}

bool isEntityCollidingWithTileOnLeftOrRight (Entity entity, int tileArray [tileArraySize], std::vector <Tile> tiles, std::vector <int> tileIndices) {

    for (unsigned int i = 0; i < tileIndices.size (); i++) {

        if (tiles [tileArray [tileIndices [i]]].isCollidable) {

            return true;

        }

    }

}

void shiftCameraBasedOnPlayerPosition (Entity player) {

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

void shiftCamera (int x, int y) {

    renderer.cameraXOffset += x;
    renderer.cameraYOffset += y;

}

int main( int argc, char* args[] )
{

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
    Tile cave_background_2 ("cave_background_2.png"); cave_background_2.isCollidable = false; tiles.push_back (cave_background_2);
    Tile cave_background_3 ("cave_background_3.png"); cave_background_3.isCollidable = false; tiles.push_back (cave_background_3);
    Tile cave_background_4 ("cave_background_4.png"); cave_background_4.isCollidable = false; tiles.push_back (cave_background_4);


    int tileArray [tileArraySize] =
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
                            1,8,8,8,8,8,8,8,8,9,4,5,3,3,0,
                            1,2,1,8,8,8,8,8,10,3,3,3,3,3,1,
                            1,2,1,2,1,2,1,8,11,3,3,3,0,0,1,
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
                        if (player.isOnGround (tileArray, tiles)) { player.yVelocity -= 10; } } break;


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

        player.xPosition += player.xVelocity;

        if (isEntityCollidingWithTileOnLeftOrRight (player, tileArray, tiles, returnIndicesOfAllTilesEntityIsIn (player, tileArray, tiles))) {

            if (player.xVelocity > 0) {

                    int displacement = player.xPosition % (32 - player.xSize);

                    player.xPosition -= displacement;

                    player.xVelocity = 0;

            }

            if (player.xVelocity < 0) {

                    int displacement = (32*player.xPosition/32 + 1) % (player.xPosition) + 1;

                    player.xPosition += displacement;

                    player.xVelocity = 0;

            }

        }

        if (!isEntityCollidingWithTile (player, tileArray, tiles) || player.yVelocity != 0) {

            player.yPosition += player.yVelocity;

            if (player.isOnGround (tileArray, tiles)) {

                    std::cout << player.yPosition << " : " << player.yVelocity << std::endl;

                    int displacement = player.yPosition % (32 - player.ySize);

                    player.yPosition -= displacement;

                    if (isEntityCollidingWithTile (player, tileArray, tiles)) {

                        std::cout << "Resolving: " << player.yPosition << " : " << player.yVelocity << std::endl;

                        player.yPosition -= player.yVelocity - (player.yVelocity - player.ySize);

                        shiftCamera (0, -1 * displacement);

                    }

                    player.yVelocity = 0;

            }

            if (isEntityCollidingWithTile (player, tileArray, tiles)) {

                if (player.yVelocity < 0) {

                    int displacement = 32 - (player.yPosition % 32);

                    player.yPosition += displacement;

                    player.yVelocity = 0;

                }

            } else {

                player.yVelocity ++;

            }

        }

        if ( !keysHeld[SDLK_LEFT] && !keysHeld[SDLK_RIGHT] && player.isOnGround (tileArray, tiles)) {

            if (player.xVelocity > 0) { player.xVelocity -= 0.75; }
            if (player.xVelocity < 0) { player.xVelocity += 0.75; }

        }

        if (player.xPosition < 0) { player.xPosition = 0; }

        shiftCameraBasedOnPlayerPosition (player);

    }

    FreeAllTileSurfaces (tiles);

    SDL_FreeSurface (player.image);

    SDL_Quit();

    return 0;
}
