#pragma once
#include "Tile.h"

class Bedrock : public Tile
{
public:
	Bedrock(const sf::Texture &texture, int tileSize, int x = 0, int y = 0) : Tile(texture, tileSize, x, y, Tile::Bedrock) { };

};