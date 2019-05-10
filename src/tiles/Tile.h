#pragma once
#include "../Mappable.h"

class Tile : public Mappable
{
public:
	enum Type
	{
		Void,
		Ground,
		Jump,
		Prize,
		Bedrock
	};

	Tile(const sf::Texture &texture, int tileSize, int x = 0, int y = 0, Type type = Void) : Mappable(texture, tileSize, x, y), type(type) { };

	Type getType() const;

private:
	Type type;
};