#include "Menu.h"

Menu::Menu(const sf::Vector2f &initialPos, float spacing)
{
	this->initialPos = initialPos;
	this->spacing = spacing;
	this->items = std::vector<sf::Text>();
	this->currentSelection = -1;
}

int Menu::getCurrentSelection() const
{
	return this->currentSelection;
}

bool Menu::isValidItem(int index) const
{
	return index > 0 && index <= this->items.size();
}

sf::Vector2f Menu::getNextPos() const
{
	if (!this->items.empty())
	{
		sf::Text last = this->items.back();
		return sf::Vector2f(last.getPosition().x, last.getPosition().y + last.getGlobalBounds().height + this->spacing);
	}
	else
	{
		return this->initialPos;
	}
}

sf::Vector2f Menu::getNextPos(float localSpacing) const
{
	if (!this->items.empty())
	{
		sf::Text last = this->items.back();
		return sf::Vector2f(last.getPosition().x, last.getPosition().y + last.getGlobalBounds().height + localSpacing);
	}
	else
	{
		return this->initialPos;
	}
}

void Menu::addItem(const std::string &text, const sf::Font &font, unsigned int size, const sf::Color &fillColor, const sf::Color &outlineColor)
{
	sf::Text item(text, font, size);
	item.setFillColor(fillColor);
	item.setOutlineColor(outlineColor);
	item.setOrigin(item.getLocalBounds().width / 2.f, 0.f);
	item.setPosition(getNextPos());
	this->items.push_back(item);
}

void Menu::addItem(const std::string &text, const sf::Font &font, float localSpacing, unsigned int size, const sf::Color &fillColor, const sf::Color &outlineColor)
{
	sf::Text item(text, font, size);
	item.setFillColor(fillColor);
	item.setOutlineColor(outlineColor);
	item.setOrigin(item.getLocalBounds().width / 2.f, 0.f);
	item.setPosition(getNextPos(localSpacing));
	this->items.push_back(item);
}

void Menu::checkMouse(const sf::Window &window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	bool inAnItem = false;
	for (int i = 0; i < this->items.size(); ++i)
	{
		if (this->items[i].getGlobalBounds().contains(sf::Vector2f((float)mousePos.x, (float)mousePos.y)))
		{
			this->currentSelection = i + 1;
			inAnItem = true;
		}
	}
	if (!inAnItem)
	{
		this->currentSelection = -1;
	}
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (sf::Text item : this->items)
	{
		target.draw(item);
	}
}