#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <vector>

class Map
{
    public:
        Map();
        virtual ~Map();

        int tilemapLengthInTiles = 15;
        int tilemapHeightInTiles = 15;

        int cameraXOffset = 0;
        int cameraYOffset = 0;


        std::vector<Tile> tiles;

        std::vector<int> tileArray;
        std::vector<int> backgroundTileArray;

    protected:

    private:
};

#endif // MAP_H
