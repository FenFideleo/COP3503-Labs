/* COP3503C Lab 6: Inheritance
*
*  Student: Erik Meurrens
*
*  Notes:
*
*/

#include <iostream>
#include "Shapes.h"
using namespace std;

/*============================ Shape Class Functions ============================*/
// Very important function that I think I need
Shape::~Shape() {

}

/*============================ Shape2D Class Functions ============================*/
void Shape2D::ShowArea() const {
	cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
}

// Operators overloaded to compare Area() of Shape2D objects
bool Shape2D::operator<(const Shape2D& rhs) const {
	if (this->Area() < rhs.Area()) {
		return true;
	}
	else {
		return false;
	}
}

bool Shape2D::operator>(const Shape2D& rhs) const {
	if (this->Area() > rhs.Area()) {
		return true;
	}
	else {
		return false;
	}
}

bool Shape2D::operator==(const Shape2D& rhs) const {
	const float EQUALITY_THRESHOLD = 1e-4;

	if (abs(this->Area() - rhs.Area()) < EQUALITY_THRESHOLD) {
		return true;
	}
	else {
		return false;
	}
}

Shape2D::~Shape2D() {
	
}

/*============================ Square Class Functions ============================*/
// Default constructor
// Takes parameter and initializes data fields to that parameter value
Square::Square(float sideLength) {
	this->sideLength = sideLength;
}

void Square::Scale(float scaleFactor) {
	sideLength = sideLength * scaleFactor;
}

void Square::Display() const {
	cout << "The area of the Square is : " << Area() << endl
		<< "Length of a side: " << sideLength << endl
		<< endl;
}

float Square::Area() const {
	float area = sideLength * sideLength;
	return area;
}

string Square::GetName2D() const {
	return name;
}

Square::~Square() {
	// I don't know. I needed to do this so it would work.
}

/*============================ Triangle Class Functions ============================*/
// Default constructor
// Takes parameter and initializes data fields to that parameter value
Triangle::Triangle(float baseLength, float height) {
	this->baseLength = baseLength;
	this->height = height;
}

void Triangle::Scale(float scaleFactor) {
	baseLength = baseLength * scaleFactor;
	height = height * scaleFactor;
}

void Triangle::Display() const {
	cout << "The area of the Triangle is : " << Area() << endl
		<< "Base: " << baseLength << endl
		<< "Height: " << height << endl
		<< endl;
}

float Triangle::Area() const {
	float area = (1.0 / 2.0) * baseLength * height;
	return area;
}

string Triangle::GetName2D() const {
	return name;
}

Triangle::~Triangle() {
	// I don't know. I needed to do this so it would work.
}

/*============================ Circle Class Functions ============================*/
// Default constructor
// Takes parameter and initializes data fields to that parameter value
Circle::Circle(float radius) {
	this->radius = radius;
}

void Circle::Scale(float scaleFactor) {
	radius = radius * scaleFactor;
}

void Circle::Display() const {
	cout << "The area of the Circle is : " << Area() << endl
		<< "Radius: " << radius << endl
		<< endl;
}

float Circle::Area() const {
	float area = PI * radius * radius;
	return area;
}

string Circle::GetName2D() const {
	return name;
}

Circle::~Circle() {
	// I don't know. I needed to do this so it would work.
}

/*============================ Shape3D Class Functions ============================*/
void Shape3D::ShowVolume() const {
	cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
}

// Operators overloaded to compare Volume() of Shape3D objects
bool Shape3D::operator<(const Shape3D& rhs) const {
	if (this->Volume() < rhs.Volume()) {
		return true;
	}
	else {
		return false;
	}
}

bool Shape3D::operator>(const Shape3D& rhs) const {
	if (this->Volume() > rhs.Volume()) {
		return true;
	}
	else {
		return false;
	}
}

bool Shape3D::operator==(const Shape3D& rhs) const {
	const float EQUALITY_THRESHOLD = 1e-4;

	if (abs(this->Volume() - rhs.Volume()) < EQUALITY_THRESHOLD) {
		return true;
	}
	else {
		return false;
	}
}

Shape3D::~Shape3D() {

}

/*============================ TriangularPyramid Class Functions ============================*/
// Default constructor
// Takes parameter and initializes data fields to that parameter value
TriangularPyramid::TriangularPyramid(float height, float baseLength, float baseHeight) :
	Triangle(baseLength, baseHeight)
{
	this->height = height;
}

void TriangularPyramid::Scale(float scaleFactor) {
	Triangle::Scale(scaleFactor);
	height = height * scaleFactor;
}

void TriangularPyramid::Display() const {
	cout << "The volume of the Triangular Pyramid is : " << Volume() << endl
		<< "The height is: " << height << endl;
	Triangle::Display();
}

float TriangularPyramid::Volume() const {
	float volume = (1.0 / 3.0) * Triangle::Area() * height;
	return volume;
}

string TriangularPyramid::GetName3D() const {
	return name;
}

TriangularPyramid::~TriangularPyramid() {
	// I don't know. I needed to do this so it would work.
}

/*============================ Cylinder Class Functions ============================*/
// Default constructor
// Takes parameter and initializes data fields to that parameter value
Cylinder::Cylinder(float height, float radius) : Circle(radius) {
	this->height = height;
}

void Cylinder::Scale(float scaleFactor) {
	Circle::Scale(scaleFactor);
	height = height * scaleFactor;
}

void Cylinder::Display() const {
	cout << "The volume of the Cylinder is : " << Volume() << endl
		<< "The height is: " << height << endl;
	Circle::Display();
}

float Cylinder::Volume() const {
	float volume = Circle::Area() * height;
	return volume;
}

string Cylinder::GetName3D() const {
	return name;
}

Cylinder::~Cylinder() {
	// I don't know. I needed to do this so it would work.
}

/*============================ Sphere Class Functions ============================*/
// Default constructor
// Takes parameter and initializes data fields to that parameter value
Sphere::Sphere(float radius) : Circle(radius) {
	this->radius = radius;
}

void Sphere::Scale(float scaleFactor) {
	Circle::Scale(scaleFactor);
	radius = radius * scaleFactor;
}

void Sphere::Display() const {
	cout << "The volume of the Sphere is : " << Volume() << endl;
	Circle::Display();
}

float Sphere::Volume() const {
	float volume = (4.0 / 3.0) * Circle::Area() * radius;
	return volume;
}

string Sphere::GetName3D() const {
	return name;
}

Sphere::~Sphere() {
	// I don't know. I needed to do this so it would work.
}