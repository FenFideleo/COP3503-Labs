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

#include "Menu.h"

/*==== LOADING FUNCTIONS ====*/
void Menu::Load(unsigned int pixelWidth, unsigned int originY, unsigned int numMines) {
	this->pixelWidth = pixelWidth;
	pixelHeight = 88;
	position.x = 0.0f;
	position.y = (float)originY;

	for (unsigned int i = RESET; i <= TEST3; i++) {
		buttons.push_back(Button());
		if (i == RESET) {
			buttons[RESET].setPosition((float)(pixelWidth / 2 - 32), (float)originY);
		}
		else {
			buttons[i].setPosition((float)(pixelWidth / 2 + 64 * i + 32), (float)originY);
		}
	}
	buttons[RESET].setTexture(TextureManager::GetTexture("face_happy"));
	buttons[DEBUG].setTexture(TextureManager::GetTexture("debug"));
	buttons[TEST1].setTexture(TextureManager::GetTexture("test_1"));
	buttons[TEST2].setTexture(TextureManager::GetTexture("test_2"));
	buttons[TEST3].setTexture(TextureManager::GetTexture("test_3"));

	// Adjust counter variables
	counter.numMines = numMines;
	counter.position = sf::Vector2f(position.x + 21, position.y);
	counter.Update();
}

/*==== BEHAVIORS ====*/
void Menu::Draw(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < buttons.size(); i++) {
		window.draw(buttons[i]);
	}
	counter.Update();
	counter.Draw(window);
}