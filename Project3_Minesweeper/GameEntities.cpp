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

#include <cmath>
#include "GameEntities.h"

/*====== TILE CLASS FUNCTIONS ======*/
// Constructor
Tile::Tile(unsigned int x, unsigned int y) : sf::Sprite(TextureManager::GetTexture("tile_hidden"))
{
	setPosition((float)x, (float)y);
	numAdjacentMines = 0;
	isFlagged = false;
	isHidden = true;
	hasMine = false;
	
	flagImage.setTexture(TextureManager::GetTexture("flag"));
	flagImage.setPosition(getPosition());
	mineImage.setTexture(TextureManager::GetTexture("mine"));
	mineImage.setPosition(getPosition());
	mineNumber.setPosition(getPosition());
	
	// vector[0] is top-left tile; count goes counterclockwise
	for (unsigned int i = 0; i < 8; i++) {
		adjacentTiles.push_back(nullptr);
	}
}

// Behaviors
void Tile::countAdjacentMines() {
	for (unsigned int i = 0; i < adjacentTiles.size(); i++) {
		if (adjacentTiles[i] == nullptr) {
			continue;
		}
		else if (adjacentTiles[i]->hasMine) {
			numAdjacentMines++;
		}
	}

	if (numAdjacentMines > 0) {
		string textureName = "number_" + std::to_string(numAdjacentMines);
		mineNumber.setTexture(TextureManager::GetTexture(textureName));
	}
}

void Tile::revealNeighbors(unsigned int& numSuccessfulReveals) {
	for (unsigned int i = 0; i < adjacentTiles.size(); i++) {
		if (adjacentTiles[i] == nullptr) {
			continue;
		}
		else if (!adjacentTiles[i]->hasMine && adjacentTiles[i]->isHidden && !adjacentTiles[i]->isFlagged) {
			adjacentTiles[i]->setTexture(TextureManager::GetTexture("tile_revealed"));
			adjacentTiles[i]->isHidden = false;
			numSuccessfulReveals++;

			if (adjacentTiles[i]->numAdjacentMines == 0) {
				adjacentTiles[i]->revealNeighbors(numSuccessfulReveals);
			}
		}
	}
}

/*===== MINECOUNTER CLASS FUNCTIONS =====*/
MineCounter::MineCounter() {
	numMines = 0;
	count = numMines;
	position = sf::Vector2f(0, 0);
	for (int i = 0; i < 3; i++) {
		digits.push_back(sf::Sprite(TextureManager::GetTexture("digits")));
		digits[i].setPosition(float(i * 21), 0.0);
		digits[i].setTextureRect(sf::IntRect(0, 0, 21, 32));
	}
}

void MineCounter::Update() {
	count = numMines - *numFlagsPtr;

	unsigned char digit;
	for (unsigned int i = 0; i < digits.size(); i++) {
		digits[i].setPosition(float((i + 1) * 21), float((int)position.y));
		if (count < 0 && i == 0) {
			digits[i].setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
		}
		else {
			int tmp = count;
			tmp /= ((int)pow(10.0, 2.0 - i));
			digit = unsigned char(std::abs(tmp)) % 10;
			digits[i].setTextureRect(sf::IntRect(digit * 21, 0, 21, 32));
		}
	}
}

void MineCounter::Draw(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < digits.size(); i++) {
		window.draw(digits[i]);
	}
}

/*===== BUTTON CLASS FUNCTIONS ======*/


