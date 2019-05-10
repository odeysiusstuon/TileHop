#pragma once
#include <SFML/Graphics.hpp>

class Map;

class Resources
{
public:
	Resources();

	sf::Texture playerTexture;
	sf::Texture voidTexture;
	sf::Texture groundTexture;
	sf::Texture jumpPadTexture;
	sf::Texture prizeTexture;
	sf::Texture bedrockTexture;
	sf::Font mainFont;
	Map *map1;
	Map *map2;
	Map *map3;
	Map *map4;
	Map *map5;
	Map *map6;
	Map *map7;
	Map *map8;
};