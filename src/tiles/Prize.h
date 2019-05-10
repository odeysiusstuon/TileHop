#pragma once
#include "Tile.h"
class Prize : public Tile {
public:
	Prize(const sf::Texture &texture, int tileSize, int x = 0, int y = 0) : Tile(texture, tileSize, x, y, Tile::Prize) { };

};