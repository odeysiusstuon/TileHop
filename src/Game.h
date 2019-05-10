#pragma once
#include "Menu.h"
#include "Map.h"
#include "Player.h"
#include <queue>

// basically how fast the player moves
#define PLAYER_MOVE_INCREMENT 10.f

// the lower, the slower (2.f seems to be the sweet spot)
#define PLAYER_DEATH_SPEED 2.f

// a percentage of zoom
#define ZOOM_FACTOR 0.8f

// title
#define TITLE "TILE HOP"

class Game
{
public:
	Game(const sf::VideoMode &videoMode, const std::string &title) : window(videoMode, title)
	{
		this->resources = new Resources();
		this->mainMenu = Menu(sf::Vector2f(videoMode.width / 2.f, videoMode.height * 0.1f), 20.f);
		this->mainMenu.addItem(TITLE, this->resources->mainFont, 200U, sf::Color::Magenta);
		this->mainMenu.addItem("Play", this->resources->mainFont, 100.f, 72U);
		this->mainMenu.addItem("Exit", this->resources->mainFont, 72U, sf::Color::Red);
		this->maps.push_back(this->resources->map1);
		this->maps.push_back(this->resources->map2);
		this->maps.push_back(this->resources->map3);
		this->maps.push_back(this->resources->map4);
		this->maps.push_back(this->resources->map5);
		this->maps.push_back(this->resources->map6);
		this->maps.push_back(this->resources->map7);
		this->maps.push_back(this->resources->map8);
		this->state = InMenu;
		this->currentView = this->window.getView();
		this->window.setView(currentView);
		this->inputBuffer = std::queue<sf::Keyboard::Key>();
		this->currentMap = -1;
		this->currentBounds = sf::IntRect();
		this->player = new Player(resources->playerTexture, PLAYER_MOVE_INCREMENT);
		this->updateClock = sf::Clock();
	}
	~Game();

	enum State
	{
		InMenu,
		InGame,
		PlayerDying,
		GameOver
	};

	Resources *getResources() const;
	State getState() const;

	void setMap(int index);
	bool windowIsOpen() const;
	bool updatePlayerMovement(const sf::Time &dt);
	void update();

private:
	Menu mainMenu;
	sf::RenderWindow window;
	Resources *resources;
	std::vector<Map *> maps;
	std::queue<sf::Keyboard::Key> inputBuffer;
	int currentMap;
	sf::View currentView;
	State state;
	sf::IntRect currentBounds;
	Player *player;
	sf::Clock updateClock;
};