#include "Tile.h"

Tile::Tile () { }

Tile::Tile(std::string imageFileName) {

    this->image = GraphicFunctions::load_image (imageFileName);

}
