#include "Resources.h"
#include "Map.h"

Resources::Resources()
{
	bool successful = true;
	this->playerTexture = sf::Texture();
	if (!this->playerTexture.loadFromFile("resources/sprites/player.png"))
	{
		std::cout << "player.png failed to load" << std::endl;
	}
	this->voidTexture = sf::Texture();
	if (!this->voidTexture.loadFromFile("resources/sprites/void.png"))
	{
		std::cout << "void.png failed to load" << std::endl;
	}
	this->groundTexture = sf::Texture();
	if (!this->groundTexture.loadFromFile("resources/sprites//tile.png"))
	{
		std::cout << "tile.png failed to load" << std::endl;
	}
	this->jumpPadTexture = sf::Texture();
	if (!this->jumpPadTexture.loadFromFile("resources/sprites/tile_jump.png"))
	{
		std::cout << "tile_jump.png failed to load" << std::endl;
	}
	this->prizeTexture = sf::Texture();
	if (!this->prizeTexture.loadFromFile("resources/sprites/prize.png"))
	{
		std::cout << "prize.png failed to load" << std::endl;
	}
	this->bedrockTexture = sf::Texture();
	if (!this->bedrockTexture.loadFromFile("resources/sprites/bedrock.png"))
	{
		std::cout << "bedrock.png failed to load" << std::endl;
	}
	this->mainFont = sf::Font();
	if (!this->mainFont.loadFromFile("resources/fonts/mainFont.ttf"))
	{
		std::cout << "mainFont.ttf failed to load" << std::endl;
	}

	this->map1 = new Map(this);
	this->map1->readFile("resources/maps/map1.txt");

	this->map2 = new Map(this);
	this->map2->readFile("resources/maps/map2.txt");

	this->map3 = new Map(this);
	this->map3->readFile("resources/maps/map3.txt");

	this->map4 = new Map(this);
	this->map4->readFile("resources/maps/map4.txt");

	this->map5 = new Map(this);
	this->map5->readFile("resources/maps/map5.txt");

	this->map6 = new Map(this);
	this->map6->readFile("resources/maps/map6.txt");

	this->map7 = new Map(this);
	this->map7->readFile("resources/maps/map7.txt");

	this->map8 = new Map(this);
	this->map8->readFile("resources/maps/map8.txt");
}