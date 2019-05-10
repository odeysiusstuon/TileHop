#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu : public sf::Drawable
{
public:
	Menu(const sf::Vector2f &initialPos = sf::Vector2f(), float spacing = 5.f);

	int getCurrentSelection() const;
	bool isValidItem(int index) const;

	sf::Vector2f getNextPos() const;
	sf::Vector2f getNextPos(float localSpacing) const;
	void addItem(const std::string &text, const sf::Font &font, unsigned int size = 30U, const sf::Color &fillColor = sf::Color::Blue, const sf::Color &outlineColor = sf::Color::White);
	void addItem(const std::string &text, const sf::Font &font, float localSpacing, unsigned int size = 30U, const sf::Color &fillColor = sf::Color::Blue, const sf::Color &outlineColor = sf::Color::White);
	void checkMouse(const sf::Window &window);

private:
	sf::Vector2f initialPos;
	float spacing;
	std::vector<sf::Text> items;
	int currentSelection;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};