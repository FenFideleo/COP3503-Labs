/* Lab 3: Array-Based Stack and Queue
*
*  Student: Erik Meurrens
*
*
*  Notes:
*	- Stacks have two general behaviors: Add to top of stack, and
*		remove from top of stack and return(push/pop)
*	- Make sure to add Big Three (copy constructor, copy assignment, destructor)
*		- Perhaps add a private copy() function to contain shared statements of
*			copy and copy assignment
*	- Use dynamically allocated array
*	- Default scale factor 2.0f (to be stored as class variable)
*		- i.e. pushing to full array will resize array by current_capacity * scale_factor
*		- if current size / max cap < 1 / scale_factor, resize array to current_cap / scale_factor
*	- Will throw exceptions of type runtime_error
*		- Syntax: throw type_of_exception("Message");
*		- e.g. throw runtime_error("An error has occurred.");
*	- Stack functions on .pdf
*/

#pragma once
#include <stdexcept>
using std::runtime_error;

template <typename T>
class ABS
{
	// Private member declarations
	unsigned int size;
	unsigned int capacity;
	float scaleFactor;
	T* array;
	void copy(const ABS& other);
	void resize(int state);

	// Public member declarations
public:
	// Constructors
	ABS(unsigned int capacity = 1);	// Default constructor

	// Big Three
	ABS(const ABS& d);				// Copy constructor 
	ABS& operator=(const ABS& d);	// Copy assignment operator
	~ABS();

	// Behaviors
	void push(T data);				// Add new item
	T pop();						// Remove item and return

	// Accessors
	T peek();						// Return item at top without removing
	unsigned int getSize();			// Returns number of items
	unsigned int getMaxCapacity();	// Returns max capacity
	T* getData();					// Return array representing stack
};

template <typename T>
ABS<T>::ABS(unsigned int capacity) {	// Default constructor
	this->size = 0;
	this->capacity = capacity;
	this->scaleFactor = 2.0f;

	this->array = new T[capacity];
}

// Performs copy of other's variables to current object
template <typename T>
void ABS<T>::copy(const ABS& other) {
	// Member-to-member copy
	this->size = other.size;
	this->capacity = other.capacity;
	this->scaleFactor = other.scaleFactor;

	// Deep copy of array
	array = new T[capacity];
	for (int i = 0; i < size; i++) {
		array[i] = other.array[i];
	}
}

template <typename T>					// Copy constructor
ABS<T>::ABS(const ABS& d) {
	copy(d);
}

template <typename T>					// Copy assignment operator
ABS<T>& ABS<T>::operator=(const ABS& d) {
	delete[] array;
	copy(d);

	return *this;
}

template <typename T>					// Resizes current ABS
void ABS<T>::resize(int state) {
	if (state == -1) {	// If size is too low (size < capacity / scaleFactor)
		// Divides capacity by scaleFactor
		capacity = capacity / scaleFactor;
	}
	else if (state == 1) {	// If size it too high (size >= capacity)
		// Multiply capacity by scaleFactor
		capacity = capacity * scaleFactor;
	}

	// Create new array of new capacity
	T* newArray = new T[capacity];

	// Add old elements to new array
	for (int i = 0; i < (int)size; i++) {
		newArray[i] = array[i];
	}

	// Delete old array's data and set pointer to that of the new array
	delete[] array;
	array = newArray;
}

// Add new item to top of stack
// Resize if necessary
template <typename T>
void ABS<T>::push(T data) {
	// Check to see if size >= capacity
	// If size >= capacity, upsize array
	if (size >= capacity) {
		resize(1);
	}

	// Add element to array
	array[size] = data;

	// Increment size
	size++;
}


// Remove item at top of stack (end of array)
// Resize if necessary
// Return value removed
// Throws runtime error if stack is empty
template <typename T>
T ABS<T>::pop() {
	if (size <= 0) {
		throw runtime_error("Array-based stack is empty");
	}
	else  {
		// Remove element from array and store in temporary variable and decrement size
		T data = array[size - 1];
		size--;

		// Return array element
		return data;

		// Check to see if size <= (capacity / scaleFactor)
		// If so, downsize array
		if (size < (capacity / scaleFactor)) {
			resize(-1);
		}

	}
}

// Returns value of item at top of stack w/o removing
// Throws runtime_error if stack is empty
template <typename T>
T ABS<T>::peek() {
	if (size <= 0) {
		throw runtime_error("Array-based stack is empty");
	}
	else {
		return array[size - 1];
	}
}

template <typename T>					// Returns current number of items in ABS
unsigned int ABS<T>::getSize() {
	return size;
}

template <typename T>					// Returns the current max capacity of ABS
unsigned int ABS<T>::getMaxCapacity() {
	return capacity;
}

template <typename T>					// Returns array representing stack
T* ABS<T>::getData() {
	return array;
}

template <typename T>					// Destructor
ABS<T>::~ABS() {
	delete[] array;
}