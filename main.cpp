#include <string>
#include <math.h>
#include <fstream>
#include <iostream>
#include "Renderer.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;
const int SCREEN_BPP = 32;

SDL_Event event;

Map worldmap;

Renderer renderer;

int tileArraySize = worldmap.tilemapLengthInTiles * worldmap.tilemapHeightInTiles;

std::vector <Entity> Entities;

bool keysHeld [323] = {false};

void FreeAllTileSurfaces ( std::vector <Tile> tileset ) {

    for (unsigned int i = 0; i < tileset.size (); i++) {

        SDL_FreeSurface (tileset[i].image);

    }

}

bool isEntityCollidingWithTile (Entity entity, Map worldmap) {

    for (int i = 0; i < worldmap.tilemapLengthInTiles * worldmap.tilemapHeightInTiles; i++) {

        if (entity.xPosition+entity.xSize > (i % worldmap.tilemapLengthInTiles)*32 && entity.xPosition <= ((i % worldmap.tilemapLengthInTiles)+1)*32
            && entity.yPosition+entity.ySize > (i / worldmap.tilemapHeightInTiles)*32 && entity.yPosition < ((i / worldmap.tilemapHeightInTiles)+1)*32) {


            if (worldmap.tiles [worldmap.tileArray [i]].isCollidable) {

                return true;

            }

        }

    }

    return false;

}

void shiftCameraBasedOnPlayerPosition (Entity player) {

    int playerXPositionOnScreen, playerYPositionOnScreen;

    playerXPositionOnScreen = player.xPosition - worldmap.cameraXOffset;
    playerYPositionOnScreen = player.yPosition - worldmap.cameraYOffset;

    if (playerXPositionOnScreen <= 144 && worldmap.cameraXOffset > 0) {

        worldmap.cameraXOffset += player.xVelocity;

    }

    if (playerXPositionOnScreen >= SCREEN_WIDTH-144 && worldmap.cameraXOffset < 32*15 - SCREEN_WIDTH) {

        worldmap.cameraXOffset += player.xVelocity;

    }

    if (playerYPositionOnScreen <= 144 && worldmap.cameraYOffset > 0) {

        worldmap.cameraYOffset += player.yVelocity;

    }

    if (playerYPositionOnScreen >= SCREEN_WIDTH-144 && worldmap.cameraYOffset < 32*15 - SCREEN_WIDTH) {

        worldmap.cameraYOffset += player.yVelocity;

    }

    if (worldmap.cameraXOffset < 0) { worldmap.cameraXOffset = 0; }
    if (worldmap.cameraYOffset < 0) { worldmap.cameraYOffset = 0; }
    if (worldmap.cameraXOffset > 32*15 - SCREEN_WIDTH) { worldmap.cameraXOffset = 32*15 - SCREEN_WIDTH; }
    if (worldmap.cameraYOffset > 32*15 - SCREEN_WIDTH) { worldmap.cameraYOffset = 32*15 - SCREEN_WIDTH; }

}

void shiftCamera (int x, int y) {

    worldmap.cameraXOffset += x;
    worldmap.cameraYOffset += y;

}

void loadMap (std::string filename, Map &worldmap) {

    std::string line;
   std::ifstream file (filename.c_str ());

    if (file.is_open())  {

        int numberOfTiles;

        file >> worldmap.tilemapLengthInTiles;
        file >> worldmap.tilemapHeightInTiles;

        file >> numberOfTiles; std::cout << numberOfTiles << std::endl;

        for (unsigned int i = 0; i < numberOfTiles; i++) {

            std::string temp_image_path;

            file >> temp_image_path;

            Tile temp (temp_image_path); std::cout << temp_image_path << std::endl;

            file >> temp.isCollidable;

            worldmap.tiles.push_back (temp);

        }

        for (unsigned int i = 0; i < tileArraySize; i++) { std::cout << i << std::endl;

            int temp_integer_input = 0;

            file >> temp_integer_input; worldmap.tileArray.push_back (temp_integer_input);
            file >> temp_integer_input; worldmap.backgroundTileArray.push_back (temp_integer_input);

        }

        int temp_int;

        file >> worldmap.playerXOffset;
        file >> worldmap.playerYOffset;

        file.close();

    } else std::cout << "Unable to open file";

}

void updateEntityPosition (Entity &entity) {

        for (int i = 0; i < abs (entity.xVelocity); i++) {

            if (entity.xVelocity > 0) {

                entity.xPosition++;

                if (entity.isCollidingWithTileOnRight (worldmap)) {

                    int displacement = entity.xPosition % (32 - entity.xSize);

                    entity.xPosition -= displacement;

                    entity.xVelocity = 0;

                    break;

                }

            } else if (entity.xVelocity < 0) {

                entity.xPosition--;

                if (entity.isCollidingWithTileOnLeft (worldmap)) {

                    int displacement = (32*entity.xPosition/32 + 1) % entity.xPosition;

                    entity.xPosition += displacement;

                    entity.xVelocity = 0;

                    break;

                }

            } else {

                break;

            }

        }


        if (!isEntityCollidingWithTile (entity, worldmap) || entity.yVelocity != 0) {

                entity.yPosition += entity.yVelocity;

                if (entity.isOnGround (worldmap)) {

                        std::cout << entity.yPosition << " : " << entity.yVelocity << std::endl;

                        int displacement = entity.yPosition % (32 - entity.ySize);

                        entity.yPosition -= displacement;

                        if (isEntityCollidingWithTile (entity, worldmap)) {

                            std::cout << "Resolving: " << entity.yPosition << " : " << entity.yVelocity << std::endl;

                            entity.yPosition -= entity.yVelocity - (entity.yVelocity - entity.ySize);

                            shiftCamera (0, -1 * displacement);

                        }

                        entity.yVelocity = 0;

                }

                if (entity.isCollidingWithTileFromBelow (worldmap)) {

                    int displacement = 32 - (entity.yPosition % 32);

                    entity.yPosition += displacement;

                    entity.yVelocity = 0;

                } else {

                    entity.yVelocity ++;

                }

            }

}

void updateAllEntityPositions (std::vector <Entity> &Entities) {

    for (unsigned int i = 0; i < Entities.size (); i++) {

        updateEntityPosition (Entities [i]);

    }

}

bool twoEntitiesAreColliding (Entity entity_one, Entity entity_two) {

    if (entity_one.xPosition+entity_one.xSize > entity_two.xPosition
        && entity_one.xPosition <= entity_two.xPosition+entity_two.xSize
        && entity_one.yPosition+entity_one.ySize > entity_two.yPosition
        && entity_one.yPosition < entity_two.yPosition+entity_two.ySize) {

        return true;

    } else {

        return false;

    }

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

    Entity player ("teatest.png"); player.Health = 3; Entities.push_back (player);

    Entity crate ("crate.png"); crate.xPosition = 32; crate.yPosition = 32; crate.xVelocity = 16.00; Entities.push_back (crate);

    loadMap ("hills_01.map", worldmap); player.xPosition = worldmap.playerXOffset; player.yPosition = worldmap.playerYOffset;

    while( quit == false ) {

        if( SDL_PollEvent( &event ) ) {

            if (event.type == SDL_KEYUP) {

                keysHeld[event.key.keysym.sym] = false;

            }

            if( event.type == SDL_KEYDOWN ) {

                keysHeld[event.key.keysym.sym] = true;

                switch( event.key.keysym.sym ) {

                    case SDLK_UP: { SDL_WM_SetCaption( "SDL Platformer - Pressing Up!", NULL);
                        if (Entities [0].isOnGround (worldmap)) { Entities [0].yVelocity -= 10; } } break;


                    default: break;

                }

            }



            else if( event.type == SDL_QUIT ) {

                quit = true;

            }

        }

        if ( keysHeld[SDLK_LEFT] ) {

            if (Entities [0].xVelocity > 0) {

                Entities [0].xVelocity -= 0.75;

            } else {

                Entities [0].xVelocity -= 0.15;

            }

        }

        if ( keysHeld[SDLK_RIGHT] ) {

            if (Entities [0].xVelocity < 0) {

                Entities [0].xVelocity += 0.75;

            } else {

                Entities [0].xVelocity += 0.15;

            }

        }

        SDL_Delay (50);

        renderer.render (Entities, worldmap);

        if( SDL_Flip( renderer.screen ) == -1 ) {

            return 1;

        }

        SDL_FillRect(renderer.screen, NULL, SDL_MapRGB(renderer.screen->format, 0, 0, 0));

        updateAllEntityPositions (Entities);

        if (twoEntitiesAreColliding (Entities [0], Entities [1])) {

            if (Entities [0].xVelocity > 5.00) {  Entities [0].xVelocity --; }

            Entities [1].xPosition += Entities [0].xVelocity / 2;

            Entities [0].xPosition = Entities [1].xPosition - Entities [0].xSize;

        }

        if ( !keysHeld[SDLK_LEFT] && !keysHeld[SDLK_RIGHT] && Entities [0].isOnGround (worldmap)) {

            if (Entities [0].xVelocity > 0) { Entities [0].xVelocity -= 0.75; }
            if (Entities [0].xVelocity < 0) { Entities [0].xVelocity += 0.75; }

        }

        if (Entities [0].xPosition < 0) { Entities [0].xPosition = 0; }

        shiftCameraBasedOnPlayerPosition (Entities [0]);

    }

    FreeAllTileSurfaces (worldmap.tiles);

    SDL_FreeSurface (player.image);

    SDL_Quit();

    return 0;
}
