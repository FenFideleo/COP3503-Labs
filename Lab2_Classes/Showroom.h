/* Lab 2: Classes
*
*  Student: Erik Meurrens
*
*/

#pragma once
#include <vector>
#include "Vehicle.h"
using std::vector;

class Showroom
{
// Private member declarations
	// Variables
	string name;
	vector<Vehicle> vehicles;
	unsigned int capacity;

// Public member declarations
public: 
	// Constructor(s)
	Showroom(string name = "Unnamed Showroom", unsigned int capacity = 0);	// default constructor

	// Accessors
	vector<Vehicle> GetVehicleList();

	// Behaviors
	void AddVehicle(Vehicle& v);
	void ShowInventory();
	float GetInventoryValue();
};

