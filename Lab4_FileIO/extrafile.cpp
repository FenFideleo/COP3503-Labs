/* COP3503C Lab 4: File IO
* 
*  Student: Erik Meurrens
*
*  Notes:
*	- Will be loading LEGO set data (1. Set number, 2. Theme, 3. Name of set, 4. Number of parts, 5. Price (USD)
*	- Must read data, store data (Lego set class?), and search it
*	- Remember to convert to stored data type (e.g. stoi (string to integer), stof(string to float), etc.)
*		- Consider invalid arguments
*	
*		
*/
//This file is optional and here for your own use

#include <sstream>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <iostream>
#include "extrafile.h"
using namespace std;

/*========================================= SET STRUCT FUNCTIONS =========================================*/
// Set constructor
extrafile::File::Set::Set(string input) {
	// Each set object has six data fields to be filled
	string temp[6];
	istringstream data(input);
	// Loop through string until no more delimiters and put into array
	for (long unsigned int i = 0; i < sizeof(temp) / sizeof(temp[0]); i++) {
		getline(data, temp[i], ',');
	}
	// Throw array elements/tokens into respective fields, converting values when needed
	setNumber = stoi(temp[0]);
	theme = temp[1];
	name = temp[2];
	numMinifigures = (unsigned int)stoi(temp[3]);
	numPieces = (unsigned int)stoi(temp[4]);
	price = stod(temp[5]);
}

// Prints info of set
void extrafile::File::Set::printInfo() {
	cout << "Name: " << name << endl <<
			"Number: " << setNumber << endl <<
			"Theme: " << theme << endl <<
			"Price: $" << price << endl <<
			"Minifigures: " << numMinifigures << endl <<
			"Piece count: " << numPieces << endl;
}

// Prints setNumber, name, and price of set onto one line
void extrafile::File::Set::printLine() {
	cout << setNumber << " " << name << " $" << price << endl;
}

/*========================================= FILE STRUCT FUNCTIONS =========================================*/
/*=== CONSTRUCTOR ===*/
extrafile::File::File(string filename) {
	// Assign filename to name
	name = filename;
	
	// Open file stream
	openFileStream(filename);

	// Stores sets into vector and initialize data values
	calculateDataFields();
}

// File's open file stream function
// Attempts to open file from either my absolute directory or program's directory
void extrafile::File::openFileStream(string filename) {
	// Attempt to open file from my file directory
	string fileDirectory = "F:/UF/COP3503C/Lab and Project files/Lab 4 - File IO/";
	fileDirectory = fileDirectory + filename;
	in.open(fileDirectory);
	
	// Check if file is open; if not, try program directory
	if (!in.is_open()) {
		in.close();		// Just in case
		in.open(filename);		// Open file in program directory
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

// Initializes all File's data values
// Iterates through file stream; making a new set for each new line of data
// Adjusts data values according to Set values in vector
void extrafile::File::calculateDataFields() {
	// Set default values
	{
		numSets = 0;
		totalPiecesCount = 0;
		totalMinifiguresCount = 0;
		totalPrice = 0.0;
		mostExpensiveSet = nullptr;
		leastExpensiveSet = nullptr;
		mostPiecesSet = nullptr;
		mostMinifiguresSet = nullptr;
	}
	
	string data;
	getline(in, data); // Skip first list since it has no useful data
	// While getline(in, input)
	while (getline(in, data)) {
		// Add Set object to Set vector with given data
		sets.push_back(new Set(data));
		
		// Check Set's values and compare to File's Set type fields
		if (numSets == 0) {
			// Only existing Set in File; therefore, it is the superlative set
			mostExpensiveSet = sets[numSets];
			leastExpensiveSet = sets[numSets];
			mostPiecesSet = sets[numSets];
			mostMinifiguresSet = sets[numSets];
		}
		else {
			// Assign superlatives accordingly
			if (sets[numSets]->price > mostExpensiveSet->price) {	// Adjust mostExpensiveSet if applicable
				mostExpensiveSet = sets[numSets];
			}
			if (sets[numSets]->price < leastExpensiveSet->price) {	// Adjust leastExpensiveSet if applicable
				leastExpensiveSet = sets[numSets];
			}
			if (sets[numSets]->numPieces > mostPiecesSet->numPieces) {	// Adjust mostPiecesSet if applicable
				mostPiecesSet = sets[numSets];
			}
			if (sets[numSets]->numMinifigures > mostMinifiguresSet->numMinifigures) { // Adjust mostMinifiguresSet if appplicable
				mostMinifiguresSet = sets[numSets];
			}
		}
		
		// Add to file primitive fields
		totalPiecesCount += sets[numSets]->numPieces;
		totalMinifiguresCount += sets[numSets]->numMinifigures;
		totalPrice += sets[numSets]->price;
		numSets++;
	}
}

/*=== DESTRUCTOR ===*/
extrafile::File::~File() {
	in.close();

	for (unsigned int i = 0; i < sets.size(); i++) {
		delete sets[i];
	}
}

/*========================================= EXTRAFILE CLASS FUNCTIONS =========================================*/
/*=== CONSTRUCTOR ===*/
extrafile::extrafile(int input) {
	// Load files according to input
	loadFiles(input);

	// Initialize data values
	calculateDataFields();
}

// Creates new file objects according to input
// Adds file pointers to files vector
// Assigns numLoadedFiles files.size()
void extrafile::loadFiles(int input) {
	// Create array of all possible file names
	string possibleFiles[] = { "lego1.csv", "lego2.csv", "lego3.csv" };

	// Load files according to input value
	switch (input) {
		case 1: {	// Load lego1.csv
			files.push_back(new File("lego1.csv"));
			break;
		}
		case 2: {	// Load lego2.csv
			files.push_back(new File("lego2.csv"));
			break;
		}
		case 3: {	// Load lego3.csv
			files.push_back(new File("lego3.csv"));
			break;
		}
		case 4: {	// Load all possible files
			for (int i = 0; i < 3; i++) {
				files.push_back(new File(possibleFiles[i]));
			}
			break;
		}
		default: {	// Invalid input
			cout << "Invalid input" << endl;
			break;
		}
	}

	numLoadedFiles = files.size();
}

// Initializes all extrafile's data values
// Adjusts data values according to File values in vector
void extrafile::calculateDataFields() {
	// Initalize values to default
	{
		numSets = 0;
		totalPiecesCount = 0;
		totalMinifiguresCount = 0;
		totalPrice = 0.0;
		averagePiecesCount = 0;
		averageMinifiguresCount = 0;
		averagePrice = 0;

		mostExpensiveSet = nullptr;
		leastExpensiveSet = nullptr;
		mostPiecesSet = nullptr;
		mostMinifiguresSet = nullptr;
	}


	// Calculate values that require totals (e.g. numSets, totalPiecesCount, totalMinifiguresCount, totalPrice)
	//	and assign superlative sets accordingly
	for (unsigned int i = 0; i < files.size(); i++) {
		// Add each File's respective primitive values to extrafile's corresponding primitive fields
		numSets += files[i]->numSets;
		totalPiecesCount += files[i]->totalPiecesCount;
		totalMinifiguresCount += files[i]->totalMinifiguresCount;
		totalPrice += files[i]->totalPrice;

		// Assign superlative fields
		if (i == 0) {	// The first object in the vector acts as a reference to assign superlatives
			mostExpensiveSet = files[i]->mostExpensiveSet;
			leastExpensiveSet = files[i]->leastExpensiveSet;
			mostPiecesSet = files[i]->mostPiecesSet;
			mostMinifiguresSet = files[i]->mostMinifiguresSet;
		}
		else {	// With respective to the currently existing superlative values, adjust superlatives with new data
			if (files[i]->mostExpensiveSet->price > mostExpensiveSet->price) {	// Adjust mostExpensiveSet, if applicable
				mostExpensiveSet = files[i]->mostExpensiveSet;
			}
			if (files[i]->leastExpensiveSet->price < leastExpensiveSet->price) {	// Adjust leastExpensiveSet, if applicable
				leastExpensiveSet = files[i]->leastExpensiveSet;
			}
			if (files[i]->mostPiecesSet->numPieces > mostPiecesSet->numPieces) {	// Adjust mostPiecesSet, if applicable
				mostPiecesSet = files[i]->mostPiecesSet;
			}
			if (files[i]->mostMinifiguresSet->numMinifigures > mostMinifiguresSet->numMinifigures) { // Adjust mostMinifiguresSet, if applicable
				mostMinifiguresSet = files[i]->mostMinifiguresSet;
			}
		}
	}

	// Calculate average values (e.g. averagePiecesCount, averageMinifiguresCount, averagePrice)
	averagePiecesCount = totalPiecesCount / numSets;
	averageMinifiguresCount = totalMinifiguresCount / numSets;
	averagePrice = totalPrice / numSets;
}

/*=== ACCESSORS ===*/
int extrafile::getNumSets() {
	return numSets;
}

void extrafile::printMostExpensive() {
	cout << "The most expensive set is:" << endl;
	mostExpensiveSet->printInfo();
}

void extrafile::printMostPieces() {
	cout << "The set with the highest parts count:" << endl;;
	mostPiecesSet->printInfo();
}

void extrafile::printAllWithName(string name) {
	const vector<extrafile::File::Set*> matchingSets = searchForName(name);
	if (matchingSets.size() > 0) {
		cout << "Sets matching \"" << name << "\":" << endl;
		for (unsigned int i = 0; i < matchingSets.size(); i++) {
			matchingSets[i]->printLine();
		}
	}
	else {
		cout << "No sets found matching that search term" << endl;
	}
}

const vector<extrafile::File::Set*> extrafile::searchForName(string name) const {
	vector<extrafile::File::Set*> matchingSets;

	for (unsigned int i = 0; i < files.size(); i++) {
		for (unsigned int j = 0; j < files[i]->sets.size(); j++) {
			if (files[i]->sets[j]->name.find(name) != std::string::npos) {
				matchingSets.push_back(files[i]->sets[j]);
			}
		}
	}

	return matchingSets;
}

void extrafile::printAllWithTheme(string theme) {
	cout << "Sets matching \"" << theme << "\":" << endl;
	const vector<extrafile::File::Set*> matchingSets = searchForTheme(theme);
	for (unsigned int i = 0; i < matchingSets.size(); i++) {
		matchingSets[i]->printLine();
	}
}

const vector<extrafile::File::Set*> extrafile::searchForTheme(string theme) const {
	vector<extrafile::File::Set*> matchingSets;

	for (unsigned int i = 0; i < files.size(); i++) {
		for (unsigned int j = 0; j < files[i]->sets.size(); j++) {
			if (files[i]->sets[j]->theme.compare(theme) == 0) {
				matchingSets.push_back(files[i]->sets[j]);
			}
		}
	}

	return matchingSets;
}

void extrafile::printAverageParts() {
	cout << "Average part count for " << numSets << " sets: " << averagePiecesCount << endl;
}

void extrafile::printPriceInfo() {
	cout << "Average price for " << numSets << " sets: $" << averagePrice << endl;
	cout << endl;
	cout << "Least expensive set:" << endl;
	leastExpensiveSet->printInfo();
	cout << endl;
	cout << "Most expensive set:" << endl;
	mostExpensiveSet->printInfo();
}

void extrafile::printMinifigureInfo() {
	cout << "Average number of minifigures: " << averageMinifiguresCount << endl;
	cout << "Set with the most minifigures: " << endl;
	mostMinifiguresSet->printInfo();
}

void extrafile::printSumOfEverything() {
	cout << "It would cost: $" << totalPrice << endl;
	cout << "You would have " << totalPiecesCount << " pieces in your collection" << endl;
	cout << "You would have an army of " << totalMinifiguresCount << " minifigures!" << endl;
}


/*=== DESTRUCTOR ===*/
extrafile::~extrafile() {
	for (unsigned int i = 0; i < files.size(); i++) {
		delete files[i];
	}
}
