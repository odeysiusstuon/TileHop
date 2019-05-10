#pragma once
#include "Tile.h"

class Void : public Tile
{
public:
	Void(const sf::Texture &texture, int tileSize, int x = 0, int y = 0) : Tile(texture, tileSize, x, y, Tile::Void) { };

};