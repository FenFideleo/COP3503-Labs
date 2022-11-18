/* Lab 2: Classes
* 
*  Student: Erik Meurrens
* 
*/

#include <iostream>
#include "Vehicle.h"
using namespace std;

Vehicle::Vehicle() {	// default constructor
	this->make = "COP3503";
	this->model = "Rust Bucket";
	this->year = 1900;
	this->price = 0;
	this->mileage = 0;
}

Vehicle::Vehicle(string make, string model, 
					int year, float price, int mileage) {	
	this->make = make;
	this->model = model;
	this->year = year;
	this->price = price;
	this->mileage = mileage;
}

void Vehicle::Display() {	// Print vehicle details on single line
	cout << year << " " << make << " " << model << " "
			<< '$' << price << " " << mileage << endl;
}

string Vehicle::GetYearMakeModel() {	// Returns string of form "YEAR MAKE MODEL"
	string YearMakeModel = to_string(year) + " " + make + " " + model;
	return YearMakeModel;
}

float Vehicle::GetPrice() {	// Returns price of vehicle
	return price;
}