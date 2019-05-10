#pragma once
#include "Tile.h"

class Jump : public Tile
{
public:
	Jump(const sf::Texture &texture, int tileSize, int x = 0, int y = 0, int skips = 3) : Tile(texture, tileSize, x, y, Tile::Jump), number_of_skips(skips) { };

	int get_skips() const;


private:
	int number_of_skips;

};
