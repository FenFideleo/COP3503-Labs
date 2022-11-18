/* Project 3: Minesweeper
*
*  Student: Erik Meurrens
*
*
*  Notes:
*	
*
*  Planning:
*	
*/

#pragma once
#include "Board.h"
#include "Menu.h"

class Game
{

public:
	sf::RenderWindow* window;
	Board board;
	Menu menu;
	sf::RectangleShape background;

	Game(sf::RenderWindow* window);
	void Draw();
	void Clear();
	void Display();
	void ResizeWindow();
	void MouseButtonPressed(sf::Event& mouseClick);
	void CheckGameState();
};

