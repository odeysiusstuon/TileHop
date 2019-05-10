#include "Player.h"

const sf::Keyboard::Key &Player::getCurrentDir() const
{
	return this->currentDir;
}

bool Player::isAlive() const
{
	return this->alive;
}

bool Player::isMoving() const
{
	return this->moving;
}

sf::Vector2f Player::getPosFromXY() const
{
	return sf::Vector2f(this->x * this->size + this->size / 2.f, this->y * this->size + this->size / 2.f);
}

sf::Vector2f Player::getPosFromXY(int x, int y) const
{
	return sf::Vector2f(x * this->size + this->size / 2.f, y * this->size + this->size / 2.f);
}

void Player::move(int newX, int newY)
{
	this->x = newX;
	this->y = newY;
	this->setPosition(getPosFromXY());
}

bool Player::moveDir(const sf::Keyboard::Key &key, const Map &map, const sf::IntRect &bounds, int steps)
{
	bool valid = false;
	int newX = this->x;
	int newY = this->y;
	int minX = bounds.left;
	int minY = bounds.top;
	int maxX = bounds.left + bounds.width;
	int maxY = bounds.top + bounds.height;
	switch (key)
	{
	case sf::Keyboard::Right:
		newX += steps;
		break;
	case sf::Keyboard::Down:
		newY += steps;
		break;
	case sf::Keyboard::Left:
		newX -= steps;
		break;
	case sf::Keyboard::Up:
		newY -= steps;
		break;
	}
	Tile *nextTile = map.getTile(newX, newY);
	if (newX >= minX && newX <= maxX
		&& newY >= minY && newY <= maxY
		&& nextTile != nullptr
		&& nextTile->getType() != Tile::Bedrock)
	{
		if (this->x != newX || this->y != newY)
		{
			valid = true;
		}
		this->currentDir = key;
		this->moving = true;
		this->movePercent = 0.f;
		this->start = getPosFromXY();
		this->end = getPosFromXY(newX, newY);
		this->endX = newX;
		this->endY = newY;
		/*this->move(newX, newY);*/
	}
	return valid;
}

void Player::checkTile(const Map &map)
{
	Tile *currentTile = map.getTile(this->x, this->y);
	if (currentTile != nullptr)
	{
		switch (map.getTile(this->x, this->y)->getType())
		{
		case Tile::Void:
			this->alive = false;
			break;
		default:
			// most likely a ground
			break;
		}
	}
	else
	{
		// player is out of bounds or something
		this->move(map.getInitX(), map.getInitY());
	}
}

bool Player::updateMovement(const Map &map, const sf::Time &dt)
{
	if (isMoving())
	{
		if (this->movePercent < 1.f)
		{
			//std::cout << this->end.x << " " << this->end.y << std::endl;
			//std::cout << this->start.x << " " << this->start.y << std::endl;
			this->setPosition(this->start.x + (this->end.x - this->start.x) * this->movePercent, this->start.y + (this->end.y - this->start.y) * this->movePercent);
			this->movePercent += this->moveIncrement * dt.asSeconds();
		}
		else
		{
			this->move(this->endX, this->endY);
			this->moving = false;
			return true;
		}
	}
	return false;
}

void Player::setAlive(bool alive) {
	this->alive = alive;
}

void Player::setMoving(bool moving)
{
	this->moving = moving;
}