#include "Renderer.h"

void Renderer::render (Entity player,
                       Map worldmap) {

        for (unsigned int i = 0; i < worldmap.tileArray.size (); i++) {

            GraphicFunctions::apply_surface (32 * (i % worldmap.tilemapLengthInTiles) - worldmap.cameraXOffset,
                                             32 * (i / worldmap.tilemapHeightInTiles) - worldmap.cameraYOffset,
                                             worldmap.tiles[worldmap.backgroundTileArray [i]].image,
                                             screen);

            GraphicFunctions::apply_surface (32 * (i % worldmap.tilemapLengthInTiles) - worldmap.cameraXOffset,
                                             32 * (i / worldmap.tilemapHeightInTiles) - worldmap.cameraYOffset,
                                             worldmap.tiles[worldmap.tileArray [i]].image, screen);

        }

        GraphicFunctions::apply_surface (player.xPosition - worldmap.cameraXOffset, player.yPosition - worldmap.cameraYOffset, player.image, screen);

}

Renderer::Renderer () { };
