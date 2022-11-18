/* Project 3: Minesweeper
*
*  Student: Erik Meurrens
*
*
*  Notes:
*	-
* 
*  Planning:
*	- Tile inherits from sf::Sprite class and is (32 x 32 pixels)
*		- Tile can either have mine or not 
*	- Button just exists
*	- MineCounter is meant to count the number of possible mines in the game
*/

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using namespace std;

class Tile : public sf::Sprite
{
public:
	static const unsigned width = 32;
	static const unsigned height = 32;

	vector<Tile*> adjacentTiles;	// vector[0] is top-left tile; count goes counterclockwise
	unsigned int numAdjacentMines;
	bool isFlagged;
	bool isHidden;
	bool hasMine;
	sf::Sprite mineNumber;
	sf::Sprite flagImage;
	sf::Sprite mineImage;

	Tile(unsigned int x = 0, unsigned int y = 0);
	void countAdjacentMines();
	void revealNeighbors(unsigned int& numSuccessfulReveals);
	bool isClicked();
};

class MineCounter
{

public:
	sf::Vector2f position;
	unsigned int* numFlagsPtr;
	unsigned int numMines;
	int count;
	vector<sf::Sprite> digits;

	MineCounter();
	void Update();
	void Draw(sf::RenderWindow& window);
};

// Button class
class Button : public sf::Sprite
{

};
