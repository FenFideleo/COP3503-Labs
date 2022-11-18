/* Project 3: Minesweeper
*
*  Student: Erik Meurrens
*
*
*  Notes:
*	-
*
*  Planning:
*	- For determining mine locations
*		- Use Random::Int(0, numTiles) numMines times and store values in sorted vector
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include "Board.h"
#include "Random.h"
using std::vector;
using std::string;

/*==== LOADING FUNCTIONS ====*/
void Board::identifyTileNeighbors() {
	for (int i = 0; i < (int)tiles.size(); i++) {
		for (int j = 0; j < (int)tiles[0].size(); j++) {
			Tile& currentTile = *tiles[i][j];
			// tiles[0] is top-left tile; count goes counterclockwise
			int a, b;
			for (int tile = 0; tile < 8; tile++) {
				// Set b coordinate value
				if (tile < 3) {
					b = j - 1;
				}
				else if (tile == 3 || tile == 7) {
					b = j;
				}
				else if (tile > 3) {
					b = j + 1;
				}
				// Set a coordinate value
				if (tile == 0 || tile > 5) {
					a = i - 1;
				}
				else if (tile == 1 || tile == 5) {
					a = i;
				}
				else if (tile > 1) {
					a = i + 1;
				}

				if ((a < 0 || b < 0) || (a >= tiles.size() || b >= tiles[0].size())) {
					continue;
				}
				else {
					currentTile.adjacentTiles[tile] = tiles[a][b];
				}
			}
			currentTile.countAdjacentMines();
		}
	}
}

void Board::Load() {
	in.open("boards/config.cfg");
	if (in.is_open()) {
		cout << "Able to open config.cfg" << endl;
	}
	else {
		cout << "Could not open config.cfg" << endl;
		return;
	}

	in >> numColumns;
	in >> numRows;
	in >> numMines;

	numTiles = numColumns * numRows;
	numSafeTiles = numTiles - numMines;
	
	// Before making tiles, determine which tiles have mines
	vector<unsigned int> minedTiles;
	for (unsigned int i = 0; i < numMines; i++) {
		// Determine random mine location
		int randTileLocation = Random::Int(0, numTiles - 1);
		// If location is already mined, redo loop iteration
		if (std::find(minedTiles.begin(), minedTiles.end(), randTileLocation) != minedTiles.end()) {
			i--;
			continue;
		}
		else {
			minedTiles.push_back(randTileLocation);
		}
	}
	// Sort minedTiles in descending order
	std::sort(minedTiles.begin(), minedTiles.end(), [](unsigned int a, unsigned int b) -> bool
	{
		return a > b;
	});

	// Initialize tile objects in vector
	for (unsigned int i = 0; i < numRows; i++) {
		vector<Tile*> tileRow;
		for (unsigned int j = 0; j < numColumns; j++) {
			tileRow.push_back(new Tile(j * Tile::width, i * Tile::height));
			// Check if tile needs to be mined
			if (minedTiles.size() != 0 && (i * numColumns) + j == minedTiles.back()) {
				tileRow[j]->hasMine = true;
				minedTiles.pop_back();
			}
		}
		tiles.push_back(tileRow);
	}
	identifyTileNeighbors();	// Configures Tile object adjacentTiles data

	numFlags = 0;
	numSuccessfulReveals = 0;
	pixelWidth = numColumns * Tile::width;
	pixelHeight = numRows * Tile::height;

	debug = false;
	defeat = false;
	victory = false;

	in.close();
}

void Board::LoadTest(string filename) {
	in.open("boards/" + filename);
	if (in.is_open()) {
		cout << "Able to open " + filename << endl;
	}
	else {
		cout << "Could not open " + filename << endl;
		return;
	}

	numMines = 0;
	
	string dataString;
	while (getline(in, dataString)) {
		vector<Tile*> tileRow;
		std::stringstream ss(dataString);

		char dataToken;
		while (ss >> dataToken) {
			tileRow.push_back(new Tile(tileRow.size() * Tile::width, tiles.size() * Tile::height));
			if ((dataToken - 48) == 1) {
				tileRow[tileRow.size() - 1]->hasMine = true;
				numMines++;
			}
		}

		tiles.push_back(tileRow);
	}
	identifyTileNeighbors();

	numColumns = tiles[0].size();	// Should be 25
	numRows = tiles.size();			// Should be 16
	numTiles = numColumns * numRows;
	numSafeTiles = numTiles - numMines;
	numSuccessfulReveals = 0;
	numFlags = 0;
	pixelWidth = numColumns * Tile::width;
	pixelHeight = numRows * Tile::height;

	debug = false;
	defeat = false;
	victory = false;

	in.close();
}

void Board::deleteTiles() {
	for (unsigned int i = 0; i < tiles.size(); i++) {
		for (unsigned int j = 0; j < tiles[0].size(); j++) {
			delete tiles[i][j];
		}
	}
}

void Board::Reload(int stateNum) {
	// Remove old data
	deleteTiles();
	tiles.clear();
	unsigned int numColumns = 0;
	unsigned int numRows = 0;
	unsigned int numMines = 0;
	unsigned int numTiles = 0;
	unsigned int numFlags = 0;
	unsigned int pixelWidth = 0;
	unsigned int pixelHeight = 0;

	switch (stateNum) {
	case 0: // Reset game by reloading config.cfg
		Load();
		break;
	case 1: // Open testboard1.brd
		LoadTest("testboard1.brd");
		break;
	case 2: // Open testboard2.brd
		LoadTest("testboard2.brd");
		break;
	case 3:	// Open testboard3.brd
		LoadTest("testboard3.brd");
		break;
	case 4: // Open lots_o_mines.brd
		LoadTest("lots_o_mines.brd");
		break;
	case 5: // Open recursion_test.brd
		LoadTest("recursion_test.brd");
		break;
	default:
		cout << "Invalid reload option" << endl;
	}
}

/*==== BEHAVIORS ====*/
void Board::Draw(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < tiles.size(); i++) {
		for (unsigned int j = 0; j < tiles[i].size(); j++) {
			window.draw(*(tiles[i][j]));
			if (tiles[i][j]->isFlagged) {
				window.draw(tiles[i][j]->flagImage);
			}
			if (tiles[i][j]->hasMine && (debug || defeat)) {
				window.draw(tiles[i][j]->mineImage);
			}
			if (!(tiles[i][j]->hasMine) && !(tiles[i][j]->isHidden)) {
				window.draw(tiles[i][j]->mineNumber);
			}
		}
	}
}

void Board::isClicked(sf::Event& mouseClick, sf::Vector2f& mousePos) {
	Tile* currentTile;
	if (mouseClick.mouseButton.button == sf::Mouse::Left) {
		if (!(victory || defeat)) {
			for (unsigned int i = 0; i < tiles.size(); i++) {
				for (unsigned int j = 0; j < tiles[i].size(); j++) {
					currentTile = tiles[i][j];
					if (currentTile->getGlobalBounds().contains(mousePos)) {
						if (currentTile->isFlagged) {
							return;
						}
						else if (currentTile->isHidden) {
							currentTile->setTexture(TextureManager::GetTexture("tile_revealed"));
							currentTile->isHidden = false;
							if (currentTile->hasMine) {
								Defeat();
							}
							else if (!currentTile->hasMine) {
								numSuccessfulReveals++;
								if (currentTile->numAdjacentMines == 0) {
									currentTile->revealNeighbors(numSuccessfulReveals);
								}
								if (numSuccessfulReveals == numSafeTiles) {
									Victory();
								}
							}
						}
					}
				}
			}
		}
	}
	else if (mouseClick.mouseButton.button == sf::Mouse::Right) {
		if (!(victory || defeat)) {
			for (unsigned int i = 0; i < tiles.size(); i++) {
				for (unsigned int j = 0; j < tiles[i].size(); j++) {
					currentTile = tiles[i][j];
					if (currentTile->getGlobalBounds().contains(mousePos) && currentTile->isHidden) {
						currentTile->isFlagged = !(currentTile->isFlagged);
						if (currentTile->isFlagged) {
							numFlags++;
						}
						else {
							numFlags--;
						}
					}
				}
			}
		}
	}
}

void Board::Debug() {
	debug = !debug;
}

void Board::Defeat() {
	defeat = true;
	
	Tile* currentTile;
	for (unsigned int i = 0; i < tiles.size(); i++) {
		for (unsigned int j = 0; j < tiles[i].size(); j++) {
			currentTile = tiles[i][j];
			if (currentTile->hasMine) {
				currentTile->setTexture(TextureManager::GetTexture("tile_revealed"));
				currentTile->isHidden = false;
			}
		}
	}
}

void Board::Victory() {
	victory = true;
	debug = false;
	numFlags = numMines;

	Tile* currentTile;
	for (unsigned int i = 0; i < tiles.size(); i++) {
		for (unsigned int j = 0; j < tiles[i].size(); j++) {
			currentTile = tiles[i][j];
			if (currentTile->hasMine) {
				currentTile->isFlagged = true;
			}
		}
	}
}

/*==== DESTRUCTOR ====*/
Board::~Board() {
	in.close();
	deleteTiles();
}