/* Project 3: Minesweeper
*
*  Student: Erik Meurrens
*
*
*  Notes:
*	- Window size:
*		- Width = number of columns * 32
*		- Height = (number of rows * 32) + 88	// 88 extra pixels for menu space
*
*  Planning:
*	- May need to resize window if using a differently sized test board or config
*
*/

#include "Game.h"

/*==== CONSTRUCTOR ====*/
Game::Game(sf::RenderWindow* window) {
	board.Load();
	menu.counter.numFlagsPtr = &board.numFlags;
	menu.Load(board.pixelWidth, board.pixelHeight, board.numMines);
	this->window = window;
	window->create(sf::VideoMode(board.pixelWidth, board.pixelHeight + menu.pixelHeight), "Minesweeper");
	background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	background.setFillColor(sf::Color::White);
}

/*==== BEHAVIORS ====*/
void Game::Draw() {
	window->draw(background);
	board.Draw(*(window));
	menu.Draw(*(window));
}

void Game::Clear() {
	window->clear();
}

void Game::Display() {
	window->display();
}

void Game::ResizeWindow() {
	window->setSize(sf::Vector2u(board.pixelWidth, board.pixelHeight + menu.pixelHeight));
}

void Game::MouseButtonPressed(sf::Event& mouseClick) {
	sf::Vector2f mousePos(float(sf::Mouse::getPosition(*window).x), float(sf::Mouse::getPosition(*window).y));
	if (mouseClick.mouseButton.button == sf::Mouse::Left) {
		if (mousePos.x < board.pixelWidth && mousePos.y < board.pixelHeight) {
			board.isClicked(mouseClick, mousePos);
		}
		else if (menu.buttons[Menu::RESET].getGlobalBounds().contains(mousePos)) {
			board.Reload(0);
			ResizeWindow();
			menu.Load(board.pixelWidth, board.pixelHeight, board.numMines);
		}
		else if (menu.buttons[Menu::DEBUG].getGlobalBounds().contains(mousePos)) {
			if (!(board.victory || board.defeat)) {
				board.Debug();
			}
		}
		else if (menu.buttons[Menu::TEST1].getGlobalBounds().contains(mousePos)) {
			board.Reload(1);
			ResizeWindow();
			menu.Load(board.pixelWidth, board.pixelHeight, board.numMines);
		}
		else if (menu.buttons[Menu::TEST2].getGlobalBounds().contains(mousePos)) {
			board.Reload(2);
			ResizeWindow();
			menu.Load(board.pixelWidth, board.pixelHeight, board.numMines);
		}
		else if (menu.buttons[Menu::TEST3].getGlobalBounds().contains(mousePos)) {
			board.Reload(3);
			ResizeWindow();
			menu.Load(board.pixelWidth, board.pixelHeight, board.numMines);
		}
	}
	else if (mouseClick.mouseButton.button == sf::Mouse::Right) {
		if (mousePos.x < board.pixelWidth && mousePos.y < board.pixelHeight) {
			board.isClicked(mouseClick, mousePos);
		}
	}
}

void Game::CheckGameState() {
	if (board.defeat == true) {
		menu.buttons[Menu::RESET].setTexture(TextureManager::GetTexture("face_lose"));
	}
	else if (board.victory == true) {
		menu.buttons[Menu::RESET].setTexture(TextureManager::GetTexture("face_win"));
	}
	else {
		menu.buttons[Menu::RESET].setTexture(TextureManager::GetTexture("face_happy"));
	}
}
