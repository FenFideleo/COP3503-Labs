/* COP3503C Lab 4: File IO
*
*  Student: Erik Meurrens
*
*  Notes:
*	- Class with file manipulation functions?
*	- Consider an additional class to store all files in program
*	- May be more effective to perform ALL main functions and store info after set is loaded to file stream
*		as part of loading process
*/	

#pragma once
#include <vector>
#include <fstream>
using namespace std;

class extrafile
{
public:
	// Nested struct File contains file data
	struct File {

		

		// Nested struct Set contains set data
		struct Set {		
			unsigned int setNumber;			
			string theme;
			string name;
			unsigned int numPieces;
			unsigned int numMinifigures;
			double price;

			// Set constructor
			Set(string input);

			// Accessor
			void printInfo();
			void printLine();

		};

		// Data fields
		string name;
		ifstream in;						// Stores respective file's input stream
		vector<Set*> sets;					// Stores file's sets
		unsigned int numSets;				// Stores number of sets in file
		Set* mostExpensiveSet;				// Stores most expensive set in file
		Set* leastExpensiveSet;				// Stores least expensive set in file
		Set* mostPiecesSet;					// Stores set with most pieces in file
		Set* mostMinifiguresSet;			// Stores set with most minifigures in file
		unsigned int totalPiecesCount;		// Stores total parts of sets in file
		unsigned int totalMinifiguresCount;	// Stores total minifigures of sets in file
		double totalPrice;					// Stores total price of all sets in file

		// File Constructor
		File(string filename);

		// File Destructor
		~File();	// Make sure to delete heap memory for Sets

	private:
		// Mutators
		void openFileStream(string filename);
		void calculateDataFields();
	};

private:
/*=== PRIVATE MEMBERS === */
	// Private member fields
	unsigned int numLoadedFiles;				// Stores number of files currently loaded
	vector<File*> files;						// Stores File objects for currently loaded files
	unsigned int numSets;						// Stores number of sets in currently loaded files
	File::Set* mostExpensiveSet;				// Stores most expensive set of all loaded files
	File::Set* leastExpensiveSet;				// Stores least expensive set of all loaded files
	File::Set* mostPiecesSet;					// Stores set with most pieces of all loaded files
	File::Set* mostMinifiguresSet;				// Stores set with most minifigures of all loaded files
	unsigned int averagePiecesCount;			// Stores average part count of all sets
	unsigned int averageMinifiguresCount;		// Stores average minifigure count of all sets
	double averagePrice;						// Stores average price of all sets
	unsigned int totalPiecesCount;				// Stores total part count of all sets
	unsigned int totalMinifiguresCount;			// Stores total minifugure count of all sets
	double totalPrice;							// Stores total price of all sets
	
	// Private member functions
	void loadFiles(int input);	// Loads files according to input
	void calculateDataFields();		// Calculates data fields of extrafile with data of all loaded sets
	const vector<File::Set*> searchForName(string name) const;	// Returns vector of sets with given name
	const vector<File::Set*> searchForTheme(string theme) const; // Returns vector of sets with given theme

/*=== PUBLIC MEMBERS === */
public:
	/*=== CONSTRUCTOR(S) ===*/
	extrafile(int input = 0);	// Constructs file according to user input in main

	/*=== ACCESSORS ===*/
	int getNumSets();
	void printMostExpensive();							// Prints most expensive set's info
	void printMostPieces();								// Prints set info for that with most pieces
	void printAllWithName(string name);					// Prints set info for sets with matching name 
	void printAllWithTheme(string theme);				// Prints set info for sets with matching theme
	void printAverageParts();							// Prints average parts of all sets
	void printPriceInfo();								// Prints price information of all sets
	void printMinifigureInfo();							// Prints average minifigures of sets and set with most minifigures
	void printSumOfEverything();						// Prints total cost, pieces, and minifigures

	/*=== DESTRUCTOR ===*/
	~extrafile();			// Make sure to delete heap memory for Files
};

