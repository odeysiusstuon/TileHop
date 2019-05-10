#include "Mappable.h"

Mappable::~Mappable()
{
	delete this->texturePointer;
}

int Mappable::getX() const
{
	return this->x;
}

int Mappable::getY() const
{
	return this->y;
}

int Mappable::getSize() const
{
	return this->size;
}

void Mappable::setSize(int newSize)
{
	this->size = newSize;
	this->setScale(sf::Vector2f(this->size / (float)this->getTexture()->getSize().x, this->size / (float)this->getTexture()->getSize().y));
}

void Mappable::move(int newX, int newY)
{
	this->x = newX;
	this->y = newY;
	this->setPosition(getPosFromXY());
}

sf::Vector2f Mappable::getPosFromXY() const
{
	return sf::Vector2f((float)(this->x * this->size), (float)(this->y * this->size));
}