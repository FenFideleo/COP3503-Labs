/* COP3503C Lab 6: Inheritance
*
*  Student: Erik Meurrens
*
*  Notes:
*		- Shapes is the name of the file. The inherited base class/interface will be called Shape
*		- Satisfactory value for PI = 3.14159f
*		- Include math.h/cmath to get access to math functions
*		- Shape -> Shape2D -> Square, Triangle, Circle
*		- Shape -> Shape3D -> Triangular Pyramid, Cylinder, Volume
*/
#pragma once
#include <cmath>
#include <string>
using namespace std;

// ====== Abstract base class Shape, declares functions to be defined in other child classes
class Shape
{
// Public members
public:
	const float PI = 3.14159f;		// Need value for PI

	virtual void Scale(float scaleFactor) = 0;	
	virtual void Display() const = 0;

	// Very important virtual destructor
	virtual ~Shape();
};

// ====== Shape2D is an abstract base class derived from Shape
class Shape2D : virtual public Shape 
{
// Public members
public:
	virtual float Area() const = 0;
	void ShowArea() const;
	virtual string GetName2D() const = 0;

	// Overloaded operators compare Area() of "this" to Area() of rhs
	bool operator>(const Shape2D& rhs) const;
	bool operator<(const Shape2D& rhs) const;
	bool operator==(const Shape2D& rhs) const;

	// Destructor
	~Shape2D();
};

// ====== Square is a derived class of Shape2D
class Square : public Shape2D
{
// Private members
	string name = "Square";
	float sideLength;

// Public members
public:
	// Constructor(s)					
	Square(float sideLength = 0.0f);	// Sets member variables to 0 if parameter not given
	
	// Overloaded parent class functions
	void Scale(float scaleFactor);
	void Display() const;
	float Area() const;
	string GetName2D() const;

	// Destructor
	~Square();
};

// ====== Triangle is a derived class of Shape2D
class Triangle : public Shape2D
{
// Private members
	string name = "Triangle";
	float baseLength;
	float height;

// Public members
public:
	// Constructor(s)					
	Triangle(float baseLength = 0.0f, float height = 0.0f);	// Sets member variables to 0 if parameters not given

	// Overloaded parent class functions
	void Scale(float scaleFactor);
	void Display() const;
	float Area() const;
	string GetName2D() const;

	// Destructor
	~Triangle();
};

// ====== Circle is a derived class of Shape2D
class Circle : public Shape2D
{
// Private members
	string name = "Circle";
	float radius;

// Public members
public:
	// Constructor(s)						
	Circle(float radius = 0.0f);	// Sets member variables to 0 if parameter not given

	// Overloaded parent class functions
	void Scale(float scaleFactor);
	void Display() const;
	float Area() const;
	string GetName2D() const;

	// Destructor
	~Circle();
};

// ====== Shape3D is an abstract base class derived from Shape
class Shape3D : virtual public Shape
{
// Public members
public:
	virtual float Volume() const = 0;
	void ShowVolume() const;
	virtual string GetName3D() const = 0;

	// Overloaded operators compare Volume() of "this" to Volume() of rhs
	bool operator>(const Shape3D& rhs) const;
	bool operator<(const Shape3D& rhs) const;
	bool operator==(const Shape3D& rhs) const;

	// Destructor
	~Shape3D();
};

// ====== TriangularPyramid is a derived class of Shape3D and has Triangle class object(?) via private inheritance
class TriangularPyramid : public Shape3D, private Triangle
{
// Private members
	string name = "TriangularPyramid";
	float baseArea = Triangle::Area();
	float height;

// Public members
public:
	// Constructor(s)
	// Sets member variables to 0 if parameters not given
	TriangularPyramid(float height = 0, float baseLength = 0, float baseHeight = 0);	

	// Overloaded parent class functions
	void Scale(float scaleFactor);
	void Display() const;
	float Volume() const;
	string GetName3D() const;

	// Destructor
	~TriangularPyramid();
};

// ====== Cylinder is a derived class of Shape3D and has Circle class object(?) via private inheritance
class Cylinder : public Shape3D, private Circle
{
// Private members
	string name = "Cylinder";
	float baseArea = Circle::Area();
	float height;

// Public members
public:
	// Constructor(s)
	// Sets member variables to 0 if parameters not given
	Cylinder(float height = 0, float radius = 0);

	// Overloaded parent class functions
	void Scale(float scaleFactor);
	void Display() const;
	float Volume() const;
	string GetName3D() const;

	// Destructor
	~Cylinder();
};

// ====== Sphere is a derived class of Shape3D and has Circle class object(?) via private inheritance
class Sphere : public Shape3D, private Circle
{
// Private members
	string name = "Sphere";
	float radius;

// Public members
public:
	// Constructor(s)
	// Sets member variables to 0 if parameters not given
	Sphere(float radius = 0);

	// Overloaded parent class functions
	void Scale(float scaleFactor);
	void Display() const;
	float Volume() const;
	string GetName3D() const;

	// Destructor
	~Sphere();
};