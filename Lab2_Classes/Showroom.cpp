/* Lab 2: Classes
*
*  Student: Erik Meurrens
*
*/

#include <iostream>
#include "Showroom.h"
using namespace std;

Showroom::Showroom(string name, unsigned int capacity) {	// Default constuctor
	this->name = name;
	this->capacity = capacity;
}

vector<Vehicle> Showroom::GetVehicleList() {	// Returns vector<Vehicle> objects
	return vehicles;
}

void Showroom::AddVehicle(Vehicle& v) {	// Adds referenced vehicle to vector
	if (vehicles.size() == capacity) {	// Showroom at capacity
		cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << endl;
	}
	else {	// Showroom has space; add vehicle
		vehicles.push_back(v);
	}
}

void Showroom::ShowInventory() {	// Shows all vehicles in showroom
	if (vehicles.size() == 0) { // Showroom is empty; no vehicles to show
		cout << name << " is empty!" << endl;
	}
	else { // Otherwise display vehicles
		cout << "Vehicles in " << name << endl;
		for (Vehicle& v : vehicles) {
			v.Display();
		}
	}
}

float Showroom::GetInventoryValue() {			// Returns sum of prices of all vehicles in showroom
	float totalShowroomValue = 0;
	for (int i = 0; i < vehicles.size(); i++) {
		totalShowroomValue += vehicles.at(i).GetPrice();
	}
	
	return totalShowroomValue;
}

