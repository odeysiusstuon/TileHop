#include "Map.h"

Map::Map(Resources *resources)
{
	this->rows = 0;
	this->cols = 0;
	this->tileSize = 0;
	this->arr = nullptr;
	this->resources = resources;
	this->initialized = false;
	//this->view = sf::View();
}

Map::Map(int rows, int cols, int tileSize, Resources *resources)
{
	this->rows = rows;
	this->cols = cols;
	this->tileSize = tileSize;
	this->arr = (Tile **)std::calloc(rows * cols, sizeof(Tile *));
	std::memset(this->arr, 0, rows * cols);
	this->initialized = true;
	this->resources = resources;
	//this->view = sf::View();
}

Map::~Map()
{
	Tile *currentTile = nullptr;
	for (int y = 0; y < this->rows; ++y)
	{
		for (int x = 0; x < this->cols; ++x)
		{
			currentTile = getTile(x, y);
			if (currentTile != nullptr)
			{
				delete currentTile;
			}
		}
	}
}

void Map::init(int rows, int cols, int tileSize, Resources *resources)
{
	if (!isInitialized())
	{
		this->rows = rows;
		this->cols = cols;
		this->tileSize = tileSize;
		this->arr = (Tile **)std::calloc(rows * cols, sizeof(Tile *));
		std::memset(this->arr, 0, rows * cols);
		this->initialized = true;
		this->resources = resources;
		//this->view = sf::View();
		//this->view.setCenter(sf::Vector2f(cols * tileSize / 2.f + tileSize / 2.f, rows * tileSize / 2.f + tileSize / 2.f));
		//this->view.setSize(sf::Vector2f((float)cols * tileSize, (float)rows * tileSize));
	}
}

Tile *Map::getTile(int x, int y) const
{
	if (inBounds(x, y))
	{
		return *(this->arr + x + y * this->cols);
	}
	else
	{
		return nullptr;
	}
}

bool Map::isInitialized() const
{
	return this->initialized;
}

bool Map::inBounds(int x, int y) const
{
	return x >= 0 && y >= 0 
		&& x < this->cols && y < this->rows;
}

int Map::getRows() const
{
	return this->rows;
}

int Map::getColumns() const
{
	return this->cols;
}

int Map::getTileSize() const
{
	return this->tileSize;
}

void Map::setResources(Resources *resources)
{
	this->resources = resources;
}

void Map::setTile(int x, int y, Tile *newTile)
{
	if (inBounds(x, y))
	{
		*(this->arr + x + y * this->cols) = newTile;
	}
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int y = 0; y < this->rows; ++y)
	{
		for (int x = 0; x < this->cols; ++x)
		{
			target.draw(*getTile(x, y));
		}
	}
}

int Map::getInitX() const
{
	return this->initX;
}

int Map::getInitY() const
{
	return this->initY;
}

//sf::View Map::getView() const
//{
//	return this->view;
//}

sf::IntRect Map::getBounds() const
{
	return sf::IntRect(0, 0, this->cols, this->rows);
}

void Map::readFile(const string fileName) {

	mapCode.open(fileName);
	string tmpLine;
	string grid[51];

	int tmpW;
	int tmpH;
	int tileS;
	mapCode >> tmpW;
	mapCode >> tmpH;
	mapCode >> tileS;
	mapCode >> initX;
	mapCode >> initY;


	// *(map + column + row * tmpW)

	init(tmpH, tmpW, tileS, this->resources);

	int i = 0;
	while (!mapCode.eof() && i < this->rows) {
		mapCode >> tmpLine;
		for (int j = 0; j < this->cols; j++) {
			char tmp = tmpLine.at(j);
			int tileId = (int)tmp - 48;
			switch (tileId)
			{
			case 1:
				this->setTile(j, i, new Ground(this->resources->groundTexture, tileSize, j, i));
				break;
			case 2:
	//			Jump *newJump = new Jump(this->resources->jumpPadTexture, tileSize, j, i);
				this->setTile(j, i, new Jump(this->resources->jumpPadTexture, tileSize, j, i));
				break;
			case 3:
				this->setTile(j, i, new Prize(this->resources->prizeTexture, tileSize, j, i));
				break;
			case 4:
				this->setTile(j, i, new Bedrock(this->resources->bedrockTexture, tileSize, j, i));
				break;
			default:
				this->setTile(j, i, new Void(this->resources->voidTexture, tileSize, j, i));
				break;
			}
		}
		i++;
	}

	//const int tileSize = 16;
	//const int width = 1200;
	//const int height = 800;
	//int** map = new int*[width];
	//// map[height / tileSize][width / tileSize] = { 0 };

	//fstream mapCode;
	//Resources resources;
	//mapCode.open("mapFile.txt");
	//string num;
	//string grid[51];
	//int i = 0;
	//while (!mapCode.eof()) {
	//	mapCode >> num;
	//	grid[i] = num;
	//	//	std::cout << "i: " << i << " " << grid[i] << std::endl;
	//	i++;
	//}


 //   //Determining characters in the file
	//for (int i = 0; i < 51; i++) {
	//	//Checks each number in the string to see what it is
	//	for (int j = 0; j < 75; j++) {		
	//		char tmp = grid[i].at(j);
	//		map[i][j] = (int)tmp-48;
	//	}
	//}
	//return map;
	//	std::cout << "i: " << i << "grid[i].at(j): " << grid[i].at(j) << std::endl;
			
	//		}
}