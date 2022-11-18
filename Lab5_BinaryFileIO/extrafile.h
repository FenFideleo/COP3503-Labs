/* COP3503C Lab 5: Binary IO
*
*  Student: Erik Meurrens
*
*  Notes:
*	- Solely functions for reading data; no writing
*	- Starfleets will have three nested classes/structs: 
*		-1) StarfleetFile which manages filestream and reads data,
*		-2) and Starship, which creates objects related to particular starships,
*		-3) and Weapons for the Starship
*	- May be more effective to perform ALL main functions and store info after set is loaded to file stream
*		as part of loading process
*	- Remember to read/write in bytes (char*) and cast accordingly
*/	

#pragma once
#include <vector>
#include <fstream>
using namespace std;

class Starfleets 
{
public:	// Public nested classes

	// Nested Starship struct
	struct Starship {
		// Nested Weapons class to store starship weapons
		struct Weapon {
			string type;		// Type of weapon available
			int power;			// Power of weapon
			float efficiency;	// Power consumption of weapon

			// Weapon constructor
			Weapon(string type = "", int power = 0, float efficiency = 0.0);	
		};

		// Startship member variables
		string name;						
		string shipClass;					
		short length;								
		int shieldCapacity;			
		float maxWarpSpeed;	
		int totalFirepower;
		bool hasWeapon;
		vector<Weapon*> weapons;	

		// Default constructor
		Starship();

		// Accessors
		void printInfo();		// Prints formatted information of ship
		int	strongestWeaponPower();		// Returns power of strongest weapon

		// Destructor
		~Starship();
	};
	
	// Nested File struct
	struct StarfleetFile {
		string filename;						// File's name
		ifstream in;							// File stream for reading
		unsigned int numShips;					// Number of starships in file
		vector<Starship*> ships;				// Vector to store Starship objects
		Starship* mostPowerfulWeapon;			// Starship with most powerful weapon in file
		Starship* mostPowerfulShip;				// Starship with most cumulative power in file
		Starship* weakestShip;					// Starship with least cumulative power among ships with weapons in file
		vector<Starship*> unarmedShips;			// Vector to store all unarmed ships in file
		
		// Default constructor
		StarfleetFile(string filename);

		// Destructor
		~StarfleetFile();

	private:
		// Mutators
		void openFileStream(string filename);	// Ensures file is opened to be read
		void loadData();						// Loads data from file into struct members
	};

private:
/*=== PRIVATE MEMBERS === */
	// Private member fields
	unsigned int numFiles;						// Stores number of files loaded
	vector<StarfleetFile*> files;				// Stores StarfleetFile objects for currently loaded files
	unsigned int numShips;						// Stores total number of ships (just in case)
	Starship* mostPowerfulWeapon;				// Starship with most powerful weapon among currently loaded files
	Starship* mostPowerfulShip;					// Starship with most cumulative power among currently loaded files
	Starship* weakestShip;						// Starship with least cumulative power among ships with weapons among currently loaded files
	
	// Private member functions
	void loadFiles(int input);					// Loads files into files vector according to user input
	void calculateDataFields();					// Fills in Starfleets data fields according to data from files

/*=== PUBLIC MEMBERS === */
public:
	/*=== CONSTRUCTORS ===*/
	Starfleets(int input = 0);					// Loads files according to user input from main

	/*=== ACCESSORS ===*/
	void printAllShips();						// Print info of all Starships from currently loaded files
	void printMostPowerfulWeapon();				// Print info of Starship with most powerful weapon
	void printMostPowerfulShip();				// Print info of Starship with most cumulative power
	void printWeakestShip();					// Print info of Starship with least cumulative power among ships with weapons
	void printUnarmedShips();					// Print info of all Starships with no weapons

	/*=== DESTRUCTOR ===*/
	~Starfleets();
};

