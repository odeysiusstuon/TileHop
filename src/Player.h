#pragma once
#include "Map.h"
#include "Mappable.h"

class Player : public Mappable
{
public:
	Player(const sf::Texture &texture, float moveIncrement = 10.f, int size = 0, int x = 0, int y = 0) : Mappable(texture, size, x, y)
	{
		this->alive = true;
		this->currentDir = sf::Keyboard::Unknown;
		this->moving = false;
		this->moveIncrement = moveIncrement;
		this->movePercent = 0.f;
		this->start = sf::Vector2f();
		this->end = sf::Vector2f();
		this->setOrigin(this->getTexture()->getSize().x / 2.f, this->getTexture()->getSize().y / 2.f);
	}

	const sf::Keyboard::Key &getCurrentDir() const;

	bool isAlive() const;
	bool isMoving() const;

	void setAlive(bool alive);
	void setMoving(bool moving);
	void move(int newX, int newY);
	sf::Vector2f getPosFromXY() const;
	sf::Vector2f getPosFromXY(int x, int y) const;
	bool moveDir(const sf::Keyboard::Key &key, const Map &map, const sf::IntRect &bounds, int steps = 1);
	void checkTile(const Map &map);

	// returns true if the player has stopped moving, false otherwise
	bool updateMovement(const Map &map, const sf::Time &dt);

private:
	bool alive;
	sf::Keyboard::Key currentDir;
	bool moving;
	float moveIncrement;
	float movePercent;
	sf::Vector2f start;
	sf::Vector2f end;
	int endX;
	int endY;
};