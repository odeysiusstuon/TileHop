#include "Game.h"

Game::~Game()
{
	delete this->resources;
	delete this->player;
}

Resources *Game::getResources() const
{
	return this->resources;
}

Game::State Game::getState() const
{
	return this->state;
}

//void Game::newMap(int rows, int cols, int tileSize)
//{
//	if (this->currentMap->isInitialized())
//	{
//		delete this->currentMap;
//		this->currentMap = new Map();
//	}
//	this->currentMap->init(rows, cols, tileSize, this->resources);
//	this->currentBounds = sf::IntRect(0, 0, cols - 1, rows - 1);
//}

void Game::setMap(int index) {
	if (index >= 0 && index < this->maps.size() && this->maps[index]->isInitialized())
	{
		Map *mapPtr = this->maps[index];
		this->currentMap = index;
		this->currentBounds = mapPtr->getBounds();
		this->player->setAlive(true);
		this->player->setSize(mapPtr->getTileSize());
		this->player->move(mapPtr->getInitX(), mapPtr->getInitY());
		this->currentView.setCenter(this->player->getPosition());
		this->currentView.setSize(this->window.getSize().x  * ZOOM_FACTOR, this->window.getSize().y * ZOOM_FACTOR);
		this->window.setView(this->currentView);
	}
	/*currentMap = mapPtr;
	this->currentBounds = currentMap->getBounds();
	this->player->setSize(currentMap->getTileSize());
	this->player->move(currentMap->getInitX(), currentMap->getInitY());*/
	//currentMap->readFile("mapFile.txt");
}

bool Game::windowIsOpen() const
{
	return this->window.isOpen();
}

bool Game::updatePlayerMovement(const sf::Time &dt)
{
	if (!this->inputBuffer.empty() && !this->player->isMoving() && this->player->isAlive())
	{
		Map *mapPtr = this->maps[this->currentMap];
		sf::Keyboard::Key currentKey = this->inputBuffer.front();
		this->player->moveDir(currentKey, *mapPtr, this->currentBounds);
		this->inputBuffer.pop();
		/*if (playerMoved)
		{
			this->player->checkTile(*mapPtr);
			if (this->player->isAlive())
			{
				int steps = 1;
				Tile *tPtr = mapPtr->getTile(this->player->getX(), this->player->getY());
				while (playerMoved && tPtr != nullptr && tPtr->getType() == Tile::Jump && this->player->isAlive())
				{
					steps = ((Jump*)tPtr)->get_skips();
					playerMoved = this->player->moveDir(currentKey, this->currentBounds, steps);
					if (playerMoved)
					{
						if (!this->player->isAlive())
						{
							this->state = PlayerDying;
						}
						tPtr = mapPtr->getTile(this->player->getX(), this->player->getY());
					}
				}
			}
			else
			{
				this->state = PlayerDying;
			}
		}*/
		return false;
	}
	else if (this->player->isMoving())
	{
		bool stopped = this->player->updateMovement(*this->maps[this->currentMap], dt);
		return stopped;
	}
	return false;
}

void Game::update()
{
	sf::Time dt = this->updateClock.restart();
	sf::Event currentEvent;
	switch (getState())
	{
	case InMenu:
		while (this->window.pollEvent(currentEvent))
		{
			switch (currentEvent.type)
			{
			case sf::Event::Closed:
				this->window.close();
				break;
			case sf::Event::MouseButtonPressed:
				//std::cout << "click" << std::endl;
				this->mainMenu.checkMouse(this->window);
				int selection = this->mainMenu.getCurrentSelection();
				switch (selection)
				{
				// Play
				case 2:
					this->state = InGame;
					setMap(0);
					break;
				// Exit
				case 3:
					this->window.close();
					break;
				default:
					break;
				}
				break;
			}
		}

		this->window.clear();

		this->window.draw(this->mainMenu);

		this->window.display();
		break;
	default:
	case PlayerDying:
	case InGame:
	{
		Map *mapPtr = this->maps[this->currentMap];
		while (this->window.pollEvent(currentEvent))
		{
			switch (currentEvent.type)
			{
			case sf::Event::Closed:
				this->window.close();
				break;
			case sf::Event::KeyPressed:
			{
				if (this->player->isAlive())
				{
					switch (currentEvent.key.code)
					{
					case sf::Keyboard::Right:
						this->inputBuffer.push(sf::Keyboard::Right);
						break;
					case sf::Keyboard::Down:
						this->inputBuffer.push(sf::Keyboard::Down);
						break;
					case sf::Keyboard::Left:
						this->inputBuffer.push(sf::Keyboard::Left);
						break;
					case sf::Keyboard::Up:
						this->inputBuffer.push(sf::Keyboard::Up);
						break;
					}
				}
			}
			}
		}

		// if the player has reached the end and stopped moving
		if (updatePlayerMovement(dt))
		{
			this->player->checkTile(*mapPtr);
			if (this->player->isAlive())
			{
				Tile *tPtr = mapPtr->getTile(this->player->getX(), this->player->getY());
				if (tPtr != nullptr) 
				{
					switch (tPtr->getType())
					{
					case Tile::Jump:
						this->player->moveDir(this->player->getCurrentDir(), *mapPtr, this->currentBounds, ((Jump *)tPtr)->get_skips());
						break;
					case Tile::Prize:
						setMap(this->currentMap + 1);
						break;
					}
				}
			}
			else
			{
				this->state = PlayerDying;
			}
		}

		if (this->state == PlayerDying)
		{
			//std::cout << dt.asSeconds() << std::endl;
			sf::Vector2f currentScale = this->player->getScale();
			sf::Vector2f newScale = sf::Vector2f(currentScale.x - PLAYER_DEATH_SPEED * dt.asSeconds(), currentScale.y - PLAYER_DEATH_SPEED * dt.asSeconds());
			if (newScale.x <= 0 || newScale.y <= 0)
			{
				this->player->setSize(mapPtr->getTileSize());
				this->player->move(mapPtr->getInitX(), mapPtr->getInitY());
				this->state = InGame;
				this->player->setAlive(true);
				while (!this->inputBuffer.empty())
				{
					this->inputBuffer.pop();
				}
			}
			else
			{
				this->player->setScale(newScale);
			}
			//this->player->setSize((int)(this->player->getSize() - PLAYER_DEATH_SPEED * dt.asSeconds()));
		}

		this->window.clear();
		this->currentView.setCenter(this->player->getPosition());
		this->window.setView(this->currentView);
		if (mapPtr->isInitialized())
		{
			this->window.draw(*mapPtr);
		}
		this->window.draw(*this->player);
		this->window.display();
		break;
	}
	case GameOver:
		break;
	}
}