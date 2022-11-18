/* Lab 2: Classes
*
*  Student: Erik Meurrens
*
*/

#pragma once
#include <string>
using std::string;

class Vehicle
{
// Private member declarations
	// Variables
	string make;
	string model;
	unsigned int year;
	float price;
	unsigned int mileage;

// Public member declarations
public:
	// Constructors
	Vehicle();	// default
	Vehicle(string make, string model, int year, float price, int mileage);

	// Functions
	void Display();				// Prints vehicle details on single line
	string GetYearMakeModel();	// Returns string in form "YEAR MAKE MODEL"
	float GetPrice();			// Returns price
};

