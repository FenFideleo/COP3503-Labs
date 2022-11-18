/* Lab 3: Array-Based Stack and Queue
*
*  Student: Erik Meurrens
*
*
*  Notes:
*	- Queues have two general behaviors: Enqueue and Dequeue
*		- Enqueue adds to end, as if someone was entering a queue
*		- Dequeue removes from front, so first in queue leaves the queue
*	- Make sure to add Big Three (copy constructor, copy assignment, destructor)
*		- Perhaps add a private copy() function to contain shared statements of
*			copy and copy assignment
*	- Use dynamically allocated array
*	- Default scale factor 2.0f (to be stored as class variable)
*		- i.e. enqueueing to full array will resize array by current_capacity * scale_factor
*		- if current size / max cap < 1 / scale_factor, resize array to current_cap / scale_factor
*	- Will throw exceptions of type runtime_error
*		- Syntax: throw type_of_exception("Message");
*		- e.g. throw runtime_error("An error has occurred.");
*	- Queue functions on .pdf
*/

#pragma once
#include <stdexcept>
using std::runtime_error;

template <typename T>
class ABQ
{
	// Private member declarations
	unsigned int size;
	unsigned int capacity;
	float scaleFactor;
	T* array;
	void copy(const ABQ& other);
	void resize(int state);

	// Public member declarations
public:
	// Constructors
	ABQ(unsigned int capacity = 1);	// Default constructor

	// Big Three
	ABQ(const ABQ& d);				// Copy constructor 
	ABQ& operator=(const ABQ& d);	// Copy assignment operator
	~ABQ();

	// Behaviors
	void enqueue(T data);				// Add new item
	T dequeue();						// Remove item and return

	// Accessors
	T peek();						// Return item at front without removing
	unsigned int getSize();			// Returns number of items
	unsigned int getMaxCapacity();	// Returns max capacity
	T* getData();					// Return array representing queue
};

template <typename T>
ABQ<T>::ABQ(unsigned int capacity) {	// Default constructor
	this->size = 0;
	this->capacity = capacity;
	this->scaleFactor = 2.0f;

	this->array = new T[capacity];
}

// Performs copy of other's variables to current object
template <typename T>
void ABQ<T>::copy(const ABQ& other) {
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
ABQ<T>::ABQ(const ABQ& d) {
	copy(d);
}

template <typename T>					// Copy assignment operator
ABQ<T>& ABQ<T>::operator=(const ABQ& d) {
	delete[] array;
	copy(d);

	return *this;
}

template <typename T>					// Resizes current ABQ
void ABQ<T>::resize(int state) {
	if (state < 0) {	// If size is too low (size < capacity / scaleFactor)
		// Divides capacity by scaleFactor
		capacity = capacity / scaleFactor;
	}
	else if (state > 0) {	// If size it too high (size >= capacity)
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

// Add new item to end of queue
// Resize if necessary
template <typename T>
void ABQ<T>::enqueue(T data) {
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


// Remove item at front of queue (first in array)
// Resize if necessary
// Return value removed
// Throws runtime error if queue is empty
template <typename T>
T ABQ<T>::dequeue() {
	if (size <= 0) {
		throw runtime_error("Array-based queue is empty");
	}
	else {
		// Remove element from array and store in temporary variable and decrement size
		T data = array[0];
		size--;

		// Move rest of elements to front, overwriting array[0]
		for (int i = 0; i < (int)size; i++) {
			array[i] = array[i + 1];
		}

		// Check to see if size <= (capacity / scaleFactor)
		// If so, downsize array
		if (size < (capacity / scaleFactor)) {
			resize(-1);
		}

		// Return array element
		return data;
	}
}

// Returns value of item at front of queue w/o removing
// Throws runtime_error if queue is empty
template <typename T>
T ABQ<T>::peek() {
	if (size <= 0) {
		throw runtime_error("Array-based queue is empty");
	}
	else {
		return array[0];
	}
}

template <typename T>					// Returns current number of items in ABQ
unsigned int ABQ<T>::getSize() {
	return size;
}

template <typename T>					// Returns the current max capacity of ABQ
unsigned int ABQ<T>::getMaxCapacity() {
	return capacity;
}

template <typename T>					// Returns array representing queue
T* ABQ<T>::getData() {
	return array;
}

template <typename T>					// Destructor
ABQ<T>::~ABQ() {
	delete[] array;
}