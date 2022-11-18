/* Project 3: Minesweeper
*
*  Student: Erik Meurrens
*
*
*  Notes:
*	- Rules overview:
*		- Exists a board that contains a grid of space, where each space could be a mine or not
*		- Player clicks on space and it gets revealed
*		- Goal is to reveal all spaces that are not mines, while avoiding those that are
*		- If space is revealed
*			- If mine, game ends
*			- If not mine, shows number of mines adjacent to that space (0-8, w/ 0 showing as an empty tile)
*			- If space has no adjacent mines, all non-mine spaces adjacent are also revealed
*		- When all non-mine spaces have been revealed, player wins
* 
*	- Other features:
*		- Flags: Right-clicking a hidden space places a flag on the tile, which cannot be revealed till removal
*		- Mine counter: Tracks mines on the board; Decrements w/ every flag place (can go negative)
*		- Restart button: Smiley face centered at top or bottom of windows lets you restart a new board with
*							everything reset and mines randomized
* 
*	- Non-standard features for project:
*		- Debug button: Toggle visibility of mines on the board	(Debug mode can be on/off for final submission)
*		- Test Buttons #1-3: Loads a file with specific board layout
* 
*
*  Planning:	 
*			
*/

#include "Game.h"

int main() {
	// Initialize program
	sf::RenderWindow window;
	Game game(&window);

	while (window.isOpen()) {
		game.ResizeWindow();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				game.MouseButtonPressed(event);
			}
		}

		game.CheckGameState();
		game.Clear();
		game.Draw();
		game.Display();
	}

	TextureManager::Clear();
	return 0;
}