#pragma once
#include "Resources.h"
#include "tiles/Ground.h"
#include "tiles/Void.h"
#include "tiles/Jump.h"
#include "tiles/Prize.h"
#include "tiles/Bedrock.h"
#include <iostream>
#include <fstream>
#include <string>

using std::fstream;
using std::string;

class Map : public sf::Drawable
{
public:
	Map(Resources *resources = nullptr);
	Map(int rows, int cols, int tileSize, Resources *resources);
	~Map();

	void init(int rows, int cols, int tileSize, Resources *resources);

	Tile *getTile(int x, int y) const;
	bool isInitialized() const;
	bool inBounds(int x, int y) const;
	int getRows() const;
	int getColumns() const;
	int getTileSize() const;
	int getInitX() const;
	int getInitY() const;
	//sf::View getView() const;
	sf::IntRect getBounds() const;

	void setTile(int x, int y, Tile *newTile);
	void setResources(Resources *resources);

	void readFile(const string fileName);

private:
	bool initialized;
	int rows;
	int cols;
	int tileSize;
	int initX;
	int initY;
	Tile **arr;
	Resources *resources;
	//sf::View view;
	fstream mapCode;
	
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};