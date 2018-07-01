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
