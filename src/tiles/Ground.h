#pragma once
#include "Tile.h"

class Ground : public Tile
{
public:
	Ground(const sf::Texture &texture, int tileSize, int x = 0, int y = 0) : Tile(texture, tileSize, x, y, Tile::Ground) { };

};