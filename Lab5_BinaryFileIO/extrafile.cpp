/* COP3503C Lab 5: Binary IO
*
*  Student: Erik Meurrens
*
*  Notes:
*	- Will be loading LEGO set data (1. Set number, 2. Theme, 3. Name of set, 4. Number of parts, 5. Price (USD)
*	- Must read data, store data (Lego set class?), and search it
*	- Remember to convert to stored data type (e.g. stoi (string to integer), stof(string to float), etc.)
*		- Consider invalid arguments
*	- Remember to read/write in bytes (char*) and cast accordingly
*
*/

#include <iostream>
#include "extrafile.h"
using namespace std;

/*========================================= WEAPONS CLASS FUNCTIONS =========================================*/
/*==== CONSTRUCTOR(S) ====*/
Starfleets::Starship::Weapon::Weapon(string type, int power, float efficiency) {
	this->type = type;
	this->power = power;
	this->efficiency = efficiency;
}

/*========================================= STARSHIPS STRUCT FUNCTIONS =========================================*/
/*==== CONSTRUCTOR(S) ====*/
Starfleets::Starship::Starship() {
	name = "default";
	shipClass = "default";
	length = 0;
	shieldCapacity = 0;
	maxWarpSpeed = 0.0;
	totalFirepower = 0;
	hasWeapon = false;
}

/*==== ACCESSOR(S) ====*/
// Prints formatted info of Starship
void Starfleets::Starship::printInfo() {
	cout << "Name: " << name << endl
		<< "Class: " << shipClass << endl
		<< "Length: " << length << endl
		<< "Shield capacity: " << shieldCapacity << endl
		<< "Maximum Warp: " << maxWarpSpeed << endl
		<< "Armaments: " << endl;

	if (hasWeapon == true) {
		for (unsigned int i = 0; i < weapons.size(); i++) {
			cout << weapons[i]->type << ", " << weapons[i]->power << ", " << weapons[i]->efficiency << endl;
		}
		cout << "Total firepower: " << totalFirepower << endl;
	}
	else {
		cout << "Unarmed" << endl;
	}
}

// Returns power of most powerful weapon of Starship
int Starfleets::Starship::strongestWeaponPower() {
	int maxPower = weapons[0]->power;
	for (unsigned int i = 1; i < weapons.size(); i++) {
		if (weapons[i]->power > maxPower) {
			maxPower = weapons[i]->power;
		}
	}
	return maxPower;
}

/*==== DESTRUCTOR ====*/
Starfleets::Starship::~Starship() {
	for (unsigned int i = 0; i < weapons.size(); i++) {
		delete weapons[i];
	}
}

/*========================================= STARFLEETFILE STRUCT FUNCTIONS =========================================*/
/*==== CONSTRUCTOR(S) ====*/
Starfleets::StarfleetFile::StarfleetFile(string filename) {
	this->filename = filename;

	// Ensure file stream can be opened
	openFileStream(filename);

	// Load data into struct members
	loadData();
}

/*==== ACCESSOR(S) ====*/
// Attempts to open file from either my absolute directory or program's directory
void Starfleets::StarfleetFile::openFileStream(string filename) {
	// Attempt to open file from my file directory
	string fileDirectory = "F:/UF/COP3503C/Lab and Project files/Lab 5 - Binary IO/";
	fileDirectory = fileDirectory + filename;
	in.open(fileDirectory, ios_base::binary);

	// Check if file is open; if not, try program directory
	if (!in.is_open()) {
		in.close();		// Just in case
		in.open(filename, ios_base::binary);		// Open file in program directory
	}
	else {
		return;
	}

	// Check if file is open again; if not, tough luck
	if (!in.is_open()) {
		in.close();
		cout << "Unable to open file" << endl;
	}
}

// Initializes member values to defaults
// Adds Ship objects to ships vector based on file data
// Based off of Ship vector data, reassign member values
void Starfleets::StarfleetFile::loadData() {

	//Initialize default values 
	numShips = 0;
	mostPowerfulWeapon = nullptr;
	mostPowerfulShip = nullptr;
	weakestShip = nullptr;

	// Read ship count from file and assign to numShips
	in.read((char*)&numShips, sizeof(numShips));

	// Iterate through loop numShips times ensuring to follow file format to store data in new Starship objects
	for (unsigned int i = 0; i < numShips; i++) {
		// Add new Starship to ships vector
		ships.push_back(new Starship);

		/*--- Input ship data into new Starship ---*/
		{
			// Store ship name
			unsigned int strLength;								// Make var to store string lengths
			in.read((char*)&strLength, sizeof(strLength));		// Read name data length
			char* shipName = new char[strLength];				// Create char array to store character data
			in.read(shipName, strLength);						// Read name data into char array
			ships[i]->name = shipName;							// Store shipName data into name string field of current Starship
			delete[] shipName;									// Clean up data

			// Store ship class
			in.read((char*)&strLength, sizeof(strLength));		// Read class data length
			char* shipClass = new char[strLength];				// Create char array to store character data
			in.read(shipClass, strLength);						// Read class data into char array
			ships[i]->shipClass = shipClass;					// Store shipClass data into class string field of current Starship
			delete[] shipClass;									// Clean up data

			// Store ship length
			in.read((char*)&(ships[i]->length), sizeof(ships[i]->length));

			// Store ship's rated shield capacity
			in.read((char*)&(ships[i]->shieldCapacity), sizeof(ships[i]->shieldCapacity));

			// Store ship's rated warp speed
			in.read((char*)&(ships[i]->maxWarpSpeed), sizeof(ships[i]->maxWarpSpeed));

			// Check to see if ship has weapons
			unsigned int numWeapons;							// Make var to store weapon count
			in.read((char*)&numWeapons, sizeof(numWeapons));	// Store weapon count from data and assign to numWeapons

			// If Starship has weapons, store weapons in Starship's weapons vector
			if (numWeapons != 0) {
				ships[i]->hasWeapon = true;

				// Iterate through loop numWeapons time and make a new Weapon object according to the data
				for (unsigned int j = 0; j < numWeapons; j++) {
					// Store weapon's name
					in.read((char*)&strLength, sizeof(strLength));	// Store weapon name data length temporarily
					char* weaponName = new char[strLength];			// Create char array to store character data
					in.read(weaponName, strLength);					// Read weapon name data to weaponName

					// Store weapon's power rating, and add to totalFirepower
					int weaponPower;
					in.read((char*)&weaponPower, sizeof(weaponPower));
					ships[i]->totalFirepower += weaponPower;

					// Store weapon's power consumption
					float weaponEfficiency;
					in.read((char*)&weaponEfficiency, sizeof(weaponEfficiency));

					// Add new Weapon object to Starship's weapons vector
					ships[i]->weapons.push_back(new Starship::Weapon(weaponName, weaponPower, weaponEfficiency));

					// Clean up unused dynamic memory
					delete[] weaponName;
				}
			}
		}

		// Make sure to check current Starship's values to superlative value
		// First, check to see if Starship is unarmed; if it isn't, it can't have a superlative value
		if (ships[i]->hasWeapon) {
			// If on first iteration of loop, current Starship must be superlative
			if (i == 0) {
				mostPowerfulWeapon = ships[i];
				mostPowerfulShip = ships[i];
				weakestShip = ships[i];
			}
			else {
			// Compare current superlative values to current Starship's values
			// If Starship's value is greater than (or lesser than) current superlative value, replace respective Starship*
				if (ships[i]->strongestWeaponPower() > mostPowerfulWeapon->strongestWeaponPower()) {
					mostPowerfulWeapon = ships[i];
				}
				if (ships[i]->totalFirepower > mostPowerfulShip->totalFirepower) {
					mostPowerfulShip = ships[i];
				}
				if (ships[i]->totalFirepower < weakestShip->totalFirepower) {
					weakestShip = ships[i];
				}
			}
		}
		else {
			// Add Starship to unarmedShips vector
			unarmedShips.push_back(ships[i]);
		}
	}
}
	

/*==== DESTRUCTOR(S) ====*/
Starfleets::StarfleetFile::~StarfleetFile() {
	in.close();

	for (unsigned int i = 0; i < ships.size(); i++) {
		delete ships[i];
	}
}

/*========================================= STARFLEETS CLASS FUNCTIONS =========================================*/
/*==== CONSTRUCTOR(S) ====*/
Starfleets::Starfleets(int input) {
	// Load files according to input
	loadFiles(input);

	// Initialize data values
	calculateDataFields();
}

// Creates new StarfleetFile objects according to input
// Adds StarfleetFile pointers to files vector
// Assigns numFiles files.size()
void Starfleets::loadFiles(int input) {
	// Create array of all possible file names
	string possibleFiles[] = { "friendlyships.shp", "enemyships.shp"};

	// Load files according to input value
	switch (input) {
		case 1: {	// Load friendlyships.shp
			files.push_back(new StarfleetFile("friendlyships.shp"));
			break;
		}
		case 2: {	// Load enemyships.shp
			files.push_back(new StarfleetFile("enemyships.shp"));
			break;
		}
		case 3: {	// Load all possible files
			for (int i = 0; i < 2; i++) {
				files.push_back(new StarfleetFile(possibleFiles[i]));
			}
			break;
		}
		default: {	// Invalid input
			cout << "Invalid input" << endl;
			break;
		}
	}

	numFiles = files.size();
}

// Initializes all Starfleets's data values
// Adjusts data values according to StarfleetFile values in vector
void Starfleets::calculateDataFields() {

	// Initialize values to defaults
	numShips = 0;
	mostPowerfulWeapon = nullptr;
	mostPowerfulShip = nullptr;
	weakestShip = nullptr;

	// Set data values by iterating through each StarfleetFile
	for (unsigned int i = 0; i < numFiles; i++) {
		// Add numShips of current StarfleetFile
		numShips += files[i]->numShips;

		// Adjust superlative values
		if (i == 0) {
			// First iteration, so superlatives are first StarfleetFile's superlatives
			mostPowerfulWeapon = files[i]->mostPowerfulWeapon;
			mostPowerfulShip = files[i]->mostPowerfulShip;
			weakestShip = files[i]->weakestShip;
		}
		else {
			// Check to see if current StarfleetFile's superlative values are greater than or less than Starfleet's values
			if (files[i]->mostPowerfulWeapon->strongestWeaponPower() > mostPowerfulWeapon->strongestWeaponPower()) {
				mostPowerfulWeapon = files[i]->mostPowerfulWeapon;
			}
			if (files[i]->mostPowerfulShip->totalFirepower > mostPowerfulShip->totalFirepower) {
				mostPowerfulShip = files[i]->mostPowerfulShip;
			}
			if (files[i]->weakestShip->totalFirepower < weakestShip->totalFirepower) {
				weakestShip = files[i]->weakestShip;
			}
		}
	}
}

/*==== ACCESSOR(S) ====*/
void Starfleets::printAllShips() {
	for (unsigned int i = 0; i < numFiles; i++) {
		for (unsigned int j = 0; j < files[i]->numShips; j++) {
			files[i]->ships[j]->printInfo();
			cout << endl;
		}
	}
}

void Starfleets::printMostPowerfulWeapon() {
	mostPowerfulWeapon->printInfo();
	cout << endl;
}

void Starfleets::printMostPowerfulShip() {
	mostPowerfulShip->printInfo();
	cout << endl;
}

void Starfleets::printWeakestShip() {
	weakestShip->printInfo();
	cout << endl;
}

void Starfleets::printUnarmedShips() {
	for (unsigned int i = 0; i < numFiles; i++) {
		for (unsigned int j = 0; j < files[i]->unarmedShips.size(); j++) {
			files[i]->unarmedShips[j]->printInfo();
			cout << endl;
		}
	}
}

/*==== DESTRUCTOR ====*/
Starfleets::~Starfleets() {
	for (unsigned int i = 0; i < files.size(); i++) {
		delete files[i];
	}
}