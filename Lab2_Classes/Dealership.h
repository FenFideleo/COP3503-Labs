/* Lab 2: Classes
*
*  Student: Erik Meurrens
*
*/

#pragma once
#include "Showroom.h"

class Dealership
{
// Private member declarations
	// Variables
	string name;
	unsigned int capacity;
	vector<Showroom> showrooms;

// Public member declarations
public:
	// Constructor(s)
	Dealership(string name = "Generic Dealership", unsigned int capacity = 0);

	// Behaviors
	void AddShowroom(Showroom& s);
	float GetAveragePrice();
	void ShowInventory();

};

