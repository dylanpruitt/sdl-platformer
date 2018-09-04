#include "Renderer.h"

void Renderer::render (std::vector <Entity> Entities,
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

        for (unsigned int i = 0; i < Entities.size (); i++) {

         GraphicFunctions::apply_surface (Entities [i].xPosition - worldmap.cameraXOffset, Entities [i].yPosition - worldmap.cameraYOffset, Entities [i].image, screen);

        }

}

Renderer::Renderer () { };
