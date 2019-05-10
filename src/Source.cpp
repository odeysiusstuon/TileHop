#include "Game.h"

int main()
{
	const int width = 1200;
	const int height = 800;

	/*******************Sam's Code****************/
		//fstream mapCode;
		//Resources resources;
		//mapCode.open("mapFile.txt");
		//string num;
		//string grid[51];
		//int i = 0;
		//while (!mapCode.eof()) {
		//	mapCode >> num;
		//	grid[i] = num;
		//	i++;
		//}

		////Determining characters in the file
		//for (int i = 0; i < 51; i++) {
		//	//Checks each number in the string to see what it is
		//	for (int j = 0; j < 75; j++) {		
		//		char tmp = grid[i].at(j);
		//		map[i][j] = (int)tmp-48;
		//	}
		//}
	/********************************************************/
	Game game(sf::VideoMode(width, height), "Hello world!");
	//game.mapFromArray((int *)map, height / tileSize, width / tileSize, tileSize);
	//game.mapFromArray((int *)testMap.readFile(), height / tileSize, width / tileSize, tileSize);
	while (game.windowIsOpen())
	{
		game.update();
	}

	return 0;
}