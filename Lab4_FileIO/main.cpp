/* COP3503C Lab 4: File IO
* 
*  Student: Erik Meurrens
*
*  Notes:
*	- Must implements search criteria listed below
*	- Must loop through second menu
*/

#include <iomanip>
#include <iostream>
#include <string>
#include "extrafile.h"
using namespace std;

int main()
{
	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;

	/*======= Load data from file(s) =======*/
	extrafile loadedData(option);	// creates extrafile object which loads file according to option

	/*======= Print out how many sets were loaded =======*/
	cout << "Total number of sets: " << loadedData.getNumSets() << endl;
	cout << endl;

	bool programRunning = true;
	while (programRunning) {
		//// From sets loaded, which is the most expensive?
		//cout << "1. Most Expensive set" << endl;
		//// From loaded sets, which has most parts?
		//cout << "2. Largest piece count" << endl;
		//// Get string as input from user, print matching set info
		//cout << "3. Search for set name containing..." << endl;
		//// Same as above, except for set themes
		//cout << "4. Search themes..." << endl;
		//// Show average parts for all loaded sets
		//cout << "5. Part count information" << endl;
		//// Show the average, minimum, and maximum prices
		//cout << "6. Price information" << endl;
		//// Show average number of minifigures and info of set with most minifigures
		//cout << "7. Minifigure information" << endl;
		//// How much would it all cost? How many parts and minifigures would you have?
		//cout << "8. If you bought one of everything..." << endl;
		//// Close program
		//cout << "0. Exit" << endl;

		int choice;
		cin >> choice;
		cin.get();  // Clear newline character for any later input

		/*======= Based on the choice, execute the appropriate task and show the results =======*/
		switch (choice) {
		case 1: {								// Displays most expensive set info
			loadedData.printMostExpensive();
			break;
		}
		case 2: {								// Display info of set with most parts
			loadedData.printMostPieces();
			break;
		}
		case 3: {								// Show all sets containing given name
			string userInput;
			getline(cin, userInput);
			loadedData.printAllWithName(userInput);
			break;
		}
		case 4: {								// Show all sets with given theme
			string userInput;
			getline(cin, userInput);
			loadedData.printAllWithTheme(userInput);
			break;
		}
		case 5: {								// Displays average piece count for all loaded sets
			loadedData.printAverageParts();
			break;
		}
		case 6: {								// Displays average price of all loaded sets, and least and most expensive set info
			loadedData.printPriceInfo();
			break;
		}
		case 7: {								// Displays average minifigure count for all loaded sets, and info of set with most minifigures
			loadedData.printMinifigureInfo();
			break;
		}
		case 8: {								// Prints stats if you bought one of everything
			cout << "If you bought one of everything..." << endl;
			loadedData.printSumOfEverything();
			break;
		}
		case 0: {								// Exits program by setting programRunning to false
			programRunning = false;
			break;
		}
		default: 								// Invalid input from choice
			cout << "Invalid input" << endl;
			break;
		}

		cout << endl;
		programRunning = false;		// Zybooks doesn't like my loop, and it doesn't test the program with a loop
	}

	return 0;
}


