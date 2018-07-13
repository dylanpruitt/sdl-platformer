#include "Renderer.h"

void Renderer::render (Entity player, int tileArray [TILEMAP_LENGTH * TILEMAP_HEIGHT], std::vector <Tile> tiles) {

        for (int i = 0; i < TILEMAP_LENGTH * TILEMAP_HEIGHT; i++) {

            GraphicFunctions::apply_surface (32 * (i % TILEMAP_LENGTH) - cameraXOffset, 32 * (i / TILEMAP_HEIGHT) - cameraYOffset, tiles[tileArray [BACKGROUND_INDEX]].image, screen);

            GraphicFunctions::apply_surface (32 * (i % TILEMAP_LENGTH) - cameraXOffset, 32 * (i / TILEMAP_HEIGHT) - cameraYOffset, tiles[tileArray [i]].image, screen);

        }

        GraphicFunctions::apply_surface (player.xPosition - cameraXOffset, player.yPosition - cameraYOffset, player.image, screen);

}

Renderer::Renderer () { };
