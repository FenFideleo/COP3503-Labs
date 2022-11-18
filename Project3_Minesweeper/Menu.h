/* Project 3: Minesweeper
*
*  Student: Erik Meurrens
*
*
*  Notes:
*	-
*
*  Planning:
*	
*/
#pragma once
#include "GameEntities.h"
class Menu
{
public:
	static enum buttonName { RESET = 0, DEBUG = 1, TEST1 = 2, TEST2 = 3, TEST3 = 4 };
	vector<Button> buttons;
	MineCounter counter;

	sf::Vector2f position;
	unsigned int pixelWidth;
	unsigned int pixelHeight;
	
	void Load(unsigned int pixelWidth, unsigned int originY, unsigned int numMines);
	void Draw(sf::RenderWindow& window);
};

