/* Lab 2: Classes
*
*  Student: Erik Meurrens
*
*/

#include <iostream>
#include "Dealership.h"
using namespace std;

Dealership::Dealership(string name, unsigned int capacity) {
	this->name = name;
	this->capacity = capacity;
}

void Dealership::AddShowroom(Showroom& s) {	// Adds new showroom to dealership
	if (showrooms.size() == capacity) {	// If dealership is full
		cout << "Dealership is full, can't add another showroom!" << endl;
	}
	else {	// Room for new showroom; Adds new showroom
		showrooms.push_back(s);
	}
}


float Dealership::GetAveragePrice() {	// Loops through all vehicles in dealership and gets average price
	float sumPrices = 0.00f;
	unsigned int totalVehicles = 0;

	for (int i = 0; i < showrooms.size(); i++) {
		sumPrices += showrooms.at(i).GetInventoryValue();
		totalVehicles += showrooms.at(i).GetVehicleList().size();
	}

	float averagePrice = 0.00f;
	if (totalVehicles > 0) {
		averagePrice = sumPrices / totalVehicles;
	}

	return averagePrice;
}

void Dealership::ShowInventory() {	// Shows inventory of all showrooms in dealership
	if (showrooms.size() == 0) {	// No showsrooms; nothing to display
		cout << name << " is empty!" << endl;
	}
	else {
		for (int i = 0; i < showrooms.size(); i++) {
			showrooms.at(i).ShowInventory();
			cout << endl;
		}
	}
	cout << "Average car price: $" << GetAveragePrice();
}
