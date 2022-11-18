/* Project 3: Minesweeper
*
*  Student: Erik Meurrens
*
*
*  Notes:
*	- Board contains a grid of spaces (Vector of vectors (rows w/ tiles))
* 
*	- Setup:
*		- Uses config.cfg to configure board dimensions
*		- First line is number of columns (columns == Tiles in a row i == tiles[i].size())
*		- Second line is number of rows (rows.size())
*		- Third line is number of mines on board
*		- There exists preset "test" boards to be loaded to give predictable results
* 
*	- Mine count:
*		- Set by config.cfg, or equal to number of mines in premade grid
*		- Assigned at random (e.g. from 0 to numTiles)
* 
*	- Tile count:
*		- Equal to number of columns * number of rows
* 
*	Planning:
*		- Will likely need to have an input stream to read data from config.cfg and other boards
*			- loadData() function
*/

#pragma once
#include <fstream>
#include "GameEntities.h"
using namespace std;

class Board
{
	ifstream in;
	

	void identifyTileNeighbors();
	void deleteTiles();

public:
	bool debug;
	bool victory;
	bool defeat;
	vector<vector<Tile*>> tiles;
	unsigned int numColumns;
	unsigned int numRows;
	unsigned int numMines;
	unsigned int numSafeTiles;
	unsigned int numTiles;
	unsigned int numFlags;
	unsigned int numSuccessfulReveals;
	unsigned int pixelWidth;
	unsigned int pixelHeight;

	void Load();
	void LoadTest(string fileName);
	void Reload(int stateNum);
	void Draw(sf::RenderWindow& window);
	void isClicked(sf::Event& mouseClick, sf::Vector2f& mousePos);
	void Debug();
	void Defeat();
	void Victory();
	
	~Board();
};

