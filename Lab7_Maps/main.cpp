/* Lab 7: Maps
*
*  Student: Erik Meurrens
*
*
*  Notes:
*		- Create function that has signature:
*			- void RollDice(int numberOfRolls, int numberOfSides);
*		- Create map<key, value> object to store results of these rolls
*			- number rolled is key
*			- # times a number is value
* 
*		- Load states via CSV file
*			- State class fields
*				- string name
*				- int perCapitaIncome
*				- unsigned int population
*				- int medianHouseIncome
*				- unsigned int numHouseholds
*/

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <string>
using namespace std;

mt19937 random_mt;

struct State {
	string name;
	int perCapitaIncome;
	unsigned int population;
	int medianHouseIncome;
	unsigned int numHouseholds;

	// Construtor
	State() {
		name = "null";
		perCapitaIncome = 0;
		population = 0;
		medianHouseIncome = 0;
		numHouseholds = 0;
	}

	// Print info
	void printInfo() {
		cout << name << endl
			<< "Population: " << population << endl
			<< "Per Capita Income: " << perCapitaIncome << endl
			<< "Median Household Income: " << medianHouseIncome << endl
			<< "Number of Households: " << numHouseholds << endl;
	}
};

// Instantiate map object to store dice roll info
map<unsigned int, unsigned int> diceRolls;
// Instantiate map object to store state info
map<string, State> stateInfo;


int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int numberOfRolls, int numberOfSides) {
	for (int i = 0; i < numberOfRolls; i++) {
		diceRolls[Random(1, numberOfSides)]++;
	}

	for (int i = 1; i <= numberOfSides; i++) {
		cout <<  i << ": " << diceRolls[i] << endl;
	}
}

void loadStateInfo() {
	ifstream in("F:/UF/COP3503C/Lab and Project files/Lab 7 - Maps/states.csv");
	if (!in.is_open()) {
		in.open("states.csv");
	}

	if (in.is_open()) {
		string dataRow;

		getline(in, dataRow);
		while (getline(in, dataRow)) {

			istringstream data(dataRow);
			string temp[5];

			for (unsigned int i = 0; i < sizeof(temp) / sizeof(temp[0]); i++) {
				getline(data, temp[i], ',');
			}

			State nextState;			
			nextState.name = temp[0];
			nextState.perCapitaIncome = stoi(temp[1]);
			nextState.population = (unsigned int)stoi(temp[2]);
			nextState.medianHouseIncome = stoi(temp[3]);
			nextState.numHouseholds = (unsigned int)stoi(temp[4]);

			stateInfo[nextState.name] = nextState;

		}

		in.close();
	}
	else {
		cout << "Could not open states.csv file!" << endl;
	}

}

int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);


		cout << "Number of times to roll the die: ";
		int timesToRoll;
		cin >> timesToRoll;	// user input

		cout << "Number of sides on this die: ";
		int numSides;
		cin >> numSides; // user input

		  // Roll Dice
		RollDice(timesToRoll, numSides);
	}
	else if (option == 2)
	{
		// Load the states
		loadStateInfo();

		// Get input for option 1 (show all states) or 2 (do a search for a particular state)
		cout << "1. Print all states" << endl
			<< "2. Search for a state" << endl;
		
		int userInput;
		cin >> userInput;

		map<string, State>::iterator iter;
		switch (userInput) {
			case 1: {				// Show all states
				for (iter = stateInfo.begin(); iter != stateInfo.end(); iter++) {
					iter->second.printInfo();
				}
				break;
			}
			case 2: {				// Search for particular state
				string state;
				cin >> state;
				iter = stateInfo.find(state);
				if (iter == stateInfo.end()) {
					cout << "No match found for " << state << endl;
				}
				else {
					iter->second.printInfo();
				}
				break;
			}
			default: {
				cout << "Invalid selection" << endl;
			}
		}

	}

	return 0;
}
