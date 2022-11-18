/* COP3503C Lab 5: Binary IO
*
*  Student: Erik Meurrens
*
*  Notes:
*	- 
*/

#include <iostream>
#include <fstream>
#include "extrafile.h"
using namespace std;

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

	/* Load files here */
	Starfleets loadedData(option);	// creates Starfleets object which loads file according to option

	// Print info of all ships
	cout << "1. Print all ships" << endl;
	// Print the starship with most powerful weapon
	cout << "2. Starship with the strongest weapon" << endl;
	// Print the most powerful ship (highest combined power rating of all weapons)
	cout << "3. Strongest starship overall" << endl;
	// Print the weakest ship (out of ships that actually have weapons)
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	// Print unarmed ships
	cout << "5. Unarmed ships" << endl;

	cin >> option;

	/* Work your magic here */

	switch(option) {
		case 1: {	// Print info of all ships
			loadedData.printAllShips();
			break;
		}
		case 2: {	// Print info of Starship with most powerful weapon
			loadedData.printMostPowerfulWeapon();
			break;
		}
		case 3: {	// Print info of cumlatively most powerful Starship
			loadedData.printMostPowerfulShip();
			break;
		}
		case 4: {	// Print info of weakest Starship
			loadedData.printWeakestShip();
			break;
		}
		case 5: {	// Print info of all unarmed ships
			loadedData.printUnarmedShips();
			break;
		}
		default: {

			break;
		}
	}

	return 0;
}