#pragma once
#include <SFML/Graphics.hpp>

class Mappable : public sf::Sprite
{
public:
	Mappable(const sf::Texture &texture, int size = 0, int x = 0, int y = 0)
	{
		this->texturePointer = new sf::Texture(texture);
		this->setTexture(*this->texturePointer);
		setSize(size);
		move(x, y);
	}
	~Mappable();

	int getX() const;
	int getY() const;
	int getSize() const;
	
	void setSize(int newSize);
	void move(int newX, int newY);

	sf::Vector2f getPosFromXY() const;

protected:
	sf::Texture *texturePointer;
	int x;
	int y;
	int size;
};