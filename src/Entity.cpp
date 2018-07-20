#include "Entity.h"

Entity::Entity()
{
    //ctor
}

Entity::Entity (std::string imageFileName)
{
    this->image = GraphicFunctions::load_image (imageFileName);
}

Entity::~Entity()
{
    //dtor
}

bool Entity::isCollidingWithTileFromBelow (Map worldmap) {

     for (int i = 0; i < worldmap.tilemapLengthInTiles * worldmap.tilemapHeightInTiles; i++) {

        if (xPosition+xSize > (i % worldmap.tilemapLengthInTiles)*32 && xPosition <= ((i % worldmap.tilemapLengthInTiles)+1)*32
            &&  yPosition+(ySize / 4) > (i / worldmap.tilemapHeightInTiles)*32 && yPosition < ((i / worldmap.tilemapHeightInTiles)+1)*32) {


            if (worldmap.tiles [worldmap.tileArray [i]].isCollidable) {

                return true;

            }

        }

    }

    return false;

}

bool Entity::isCollidingWithTileOnLeft (Map worldmap) {

     for (int i = 0; i < worldmap.tilemapLengthInTiles * worldmap.tilemapHeightInTiles; i++) {

        if (xPosition > (i % worldmap.tilemapLengthInTiles)*32 && xPosition <= ((i % worldmap.tilemapLengthInTiles)+1)*32
            &&  yPosition+ySize > (i / worldmap.tilemapHeightInTiles)*32 && yPosition < ((i / worldmap.tilemapHeightInTiles)+1)*32) {


            if (worldmap.tiles [worldmap.tileArray [i]].isCollidable) {

                return true;

            }

        }

    }

    return false;

}

bool Entity::isCollidingWithTileOnRight (Map worldmap) {

     for (int i = 0; i < worldmap.tilemapLengthInTiles * worldmap.tilemapHeightInTiles; i++) {

        int minimumBoundXCoordinate = xPosition+xSize-(xSize / 4);

        if (minimumBoundXCoordinate + (ySize / 4) > (i % worldmap.tilemapLengthInTiles)*32 && minimumBoundXCoordinate <= ((i % worldmap.tilemapLengthInTiles)+1)*32
            &&  yPosition+ySize > (i / worldmap.tilemapHeightInTiles)*32 && yPosition < ((i / worldmap.tilemapHeightInTiles)+1)*32) {


            if (worldmap.tiles [worldmap.tileArray [i]].isCollidable) {

                return true;

            }

        }

    }

    return false;

}

bool Entity::isOnGround (Map worldmap) {

     for (int i = 0; i < worldmap.tilemapLengthInTiles * worldmap.tilemapHeightInTiles; i++) {

        int minimumBoundYCoordinate = yPosition+ySize-(ySize / 4);

        if (xPosition+xSize > (i % worldmap.tilemapLengthInTiles)*32 && xPosition <= ((i % worldmap.tilemapLengthInTiles)+1)*32
            &&  minimumBoundYCoordinate + (ySize / 4) >= (i / worldmap.tilemapHeightInTiles)*32 && minimumBoundYCoordinate <= ((i / worldmap.tilemapHeightInTiles)+1)*32) {


            if (worldmap.tiles [worldmap.tileArray [i]].isCollidable) {

                return true;

            }

        }

    }

    return false;

}
