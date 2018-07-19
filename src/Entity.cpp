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

bool Entity::isOnGround (int tileArray [tileArraySize], std::vector <Tile> tiles) {

     for (int i = 0; i < tileArraySize; i++) { int LENGTH_QUICK_FIX = 15;

        int minimumBoundYCoordinate = yPosition+ySize-(ySize / 4);

        if (xPosition+xSize > (i % LENGTH_QUICK_FIX)*32 && xPosition <= ((i % LENGTH_QUICK_FIX)+1)*32
            &&  minimumBoundYCoordinate + (ySize / 4) >= (i / LENGTH_QUICK_FIX)*32 && minimumBoundYCoordinate <= ((i / LENGTH_QUICK_FIX)+1)*32) {


            if (tiles [tileArray [i]].isCollidable) {

                return true;

            }

        }

    }

    return false;

}
