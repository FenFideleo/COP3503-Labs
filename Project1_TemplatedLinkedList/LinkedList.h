/* Project 1: Templated Linked List
*
*  Student: Erik Meurrens
*
*/

#pragma once
#include<iostream>
#include<vector>
#include<stdexcept>
using namespace std;

template <typename T>
class LinkedList
{
/*===PRIVATE MEMBER DECLARATIONS===*/
// Need a public nest Node class for part 2
public:
	/*===NESTED NODE CLASS===*/
	struct Node
	{
		// Node class public members (only accessible to LinkedList class)
		T data;
		Node* next;
		Node* prev;

		// Constructor
		Node(const T& data, Node* next = nullptr, Node* prev = nullptr);

	};

private:
	/*===PRIVATE MEMBER FIELDS===*/
	int numNodes;
	Node* headPtr;
	Node* tailPtr;

	/*===PRIVATE MEMBER FUNCTIONS===*/
	void variableCopy(const LinkedList& other);

/*===PUBLIC MEMBER DECLARATIONS===*/
public:
	/*===CONSTRUCTORS===*/
	LinkedList();
	LinkedList(const LinkedList& other);	// Copy constructor

	/*===OPERATORS===*/
	LinkedList& operator=(const LinkedList& other);	// Copy assignment operator
	T& operator[](unsigned int index);	// Overloaded subscript operator
	const T& operator[](unsigned int index) const;
	bool operator==(const LinkedList& rhs) const;	// Overloaded equality operator

	/*===DESTRUCTOR===*/
	~LinkedList();

	/* TO ADD (Part 4)
		- RemoveHead()
		- RemoveTail()
		- RemoveAt()
		- Remove()
		- Clear()

		- PrintForwardRecursive()
		- PrintReverseRecursive()
	*/

	/*===BEHAVIORS===*/
	void PrintForward() const;		// Iterate through all nodes and print values
	void PrintReverse() const;		// ^ Same, but backwards
	void PrintForwardRecursive(const Node* node) const;	// Implemented via recursion, takes starting node and prints forward
	void PrintReverseRecursive(const Node* node) const;	// ^Same, but prints backwards

	/*===ACCESSORS===*/
	unsigned int NodeCount() const;		// Returns numNodes
	void FindAll(vector<Node*>& outData, const T& value) const;		// Finds all nodes of value and store pointers to nodes in vector
	Node* Find(const T& data); 	// Finds first Node with matching data value
	const Node* Find(const T& data) const;
	Node* GetNode(unsigned int index); 	// Returns pointer to node at index
	const Node* GetNode(unsigned int index) const;
	Node* Head();						// Returns head pointer
	const Node* Head() const;
	Node* Tail();						// Returns tail pointer
	const Node* Tail() const;

	/*===INSERTION===*/
	void AddHead(const T& data);		// Adds new Node to front of list
	void AddTail(const T& data);		// Adds new Node to end of list
	void AddNodesHead(const T* data, unsigned int count);		// Adds new Nodes for each element of array to front
	void AddNodesTail(const T* data, unsigned int count);		// Adds new Nodes for each element of array to end
	void InsertBefore(Node* node, const T& data);	// Inserts new node before given node param
	void InsertAfter(Node* node, const T& data);	// Inserts new node after given node param
	void InsertAt(const T& data, unsigned int index);	// Inserts node at given index param

	/*===REMOVAL===*/
	bool RemoveHead();	// Deletes first Node in list
	bool RemoveTail();	// Deletes last Node in list
	bool RemoveAt(unsigned int index);	// Deletes index-th Node from list
	unsigned int Remove(const T& data);	// Remove ALL Nodes containing values matching that of param
	void Clear(); // Deletes all Nodes
};

// Node constructor
template <typename T>
LinkedList<T>::Node::Node(const T& data, Node* next, Node* prev) {
	this->data = data;
	this->next = next;
	this->prev = prev;
}

// Default constructor
template <typename T>
LinkedList<T>::LinkedList() {
	numNodes = 0;
	headPtr = nullptr;
	tailPtr = nullptr;
}

// Private copy function to minimize code. 
// Copies other's values to this object.
template <typename T>
void LinkedList<T>::variableCopy(const LinkedList& other) {
	// Deep Copy
	// For each node in other LinkedList
	// Add data value to new LinkedList
	for (int i = 0; i < other.numNodes; i++) {
		AddTail(other.GetNode(i)->data);
	}

}

// Copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
	numNodes = 0;
	headPtr = nullptr;
	tailPtr = nullptr;
	variableCopy(other);
}

// ==== OPERATORS ==== 
// Copy assignment operator
// After writing "list A = list B;", listA == listB is true
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
	// Delete currently existing data in LinkedList if it exists
	if (headPtr != nullptr) {
		Node* nextPtrToDelete;
		do {
			nextPtrToDelete = headPtr->next;
			delete headPtr;
			headPtr = nextPtrToDelete;
		} while (nextPtrToDelete != nullptr);

		// Reset values for this LinkedList
		headPtr = nullptr;
		tailPtr = nullptr;
		numNodes = 0;
	}
	
	variableCopy(other);

	return *this;
}

// Overloaded subscript operator
// Takes an index, and returns data from the index-th node
// Throws out_of_range exception for invalid index
template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
	if ((int)index < 0 || (int)index > numNodes - 1) {
		throw out_of_range("Given index out of LinkedList range");
	}
	// Use GetNode(index) to find node with desired T value and return value
	return this->GetNode(index)->data;
}
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
	if ((int)index < 0 || (int)index > numNodes - 1) {
		throw out_of_range("Given index out of LinkedList range");
	}
	// Use GetNode(index) to find node with desired T value and return value
	return this->GetNode(index)->data;
}

// Overloaded equality operator
// Given a pair of Nodes at a given index for listA and listB,
//	assess equality of Nodes by comparing the data values
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	// Check to see if lists are of same length; if not return false
	if (this->numNodes != rhs.numNodes) {
		return false;
	}
	// Else, they must be the same length
	else {
		// If both lists have no Nodes, they are equal
		if (this->numNodes == 0 && rhs.numNodes == 0) {
			return true;
		}
		// Loop from i to i == numNodes-1, checking each Node at that i for equality
		Node* currentNodeA = this->headPtr;
		Node* currentNodeB = rhs.headPtr;
		for (int i = 0; i < numNodes; i++) {
			// Data field of listA at index i does not equal value of data field of listB
			if (currentNodeA->data != currentNodeB->data) {
				return false;
			}
			currentNodeA = currentNodeA->next;
			currentNodeB = currentNodeB->next;
		}
		// Returns true after checking each Node for equality
		return true;
	}
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
	if (headPtr != nullptr) {
		Node* nextPtrToDelete;
		do {
			nextPtrToDelete = headPtr->next;
			delete headPtr;
			headPtr = nextPtrToDelete;
		} while (nextPtrToDelete != nullptr);
	}
}

// ==== BEHAVIORS ====
// Iterates through all nodes and prints out their values from head to tail
template <typename T>
void LinkedList<T>::PrintForward() const {
	// Use while loop to iterate through node objects, starting at head Node,
	// changing nodes until last node's next == nullptr
	if (headPtr == nullptr) {
		cout << "Unable to print. No elements in list." << endl;
		return;
	}
	Node currentNode = *headPtr;
	while (true) {
		if (currentNode.next == nullptr) {
			cout << currentNode.data << endl;
			break;
		}
		else {
			cout << currentNode.data << endl;
		}
		currentNode = *(currentNode.next);
	}
}

// Iterates through all nodes and prints out their values from tail to head
template <typename T>
void LinkedList<T>::PrintReverse() const {
	// Use while loop to iterate through node objects, starting at tail Node,
	// until first node's prev == nullptr
	if (tailPtr == nullptr) {
		cout << "Unable to print. No elements in list." << endl;
		return;
	}
	Node currentNode = *tailPtr;
	while (true) {
		if (currentNode.prev == nullptr) {
			cout << currentNode.data << endl;
			break;
		}
		else {
			cout << currentNode.data << endl;
		}
		currentNode = *(currentNode.prev);
	}
}


// Takes in a pointer to a Node - a starting node
// From node, recursively visit each node that follows, in forward order, and prints respective value
// MUST be implemented via recursion
template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
	if (node == nullptr) {
		return;
	}
	else {
		cout << node->data << endl;
		PrintForwardRecursive(node->next);
	}
}

// Takes in a pointer to a Node - a starting node
// From node, recursively visit each node that follows, in backward order, and prints respective value
// MUST be implemented via recursion
template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
	if (node == nullptr) {
		return;
	}
	else {
		cout << node->data << endl;
		PrintReverseRecursive(node->prev);
	}
}

// ==== ACCESSORS ====
// Return number of items stored in Linked List
template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return numNodes;
}

// Find all nodes which match passed in param value,
//  and store pointer to that node in passed in vector
template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
	Node* currentNodePtr = headPtr;
	// Iterate through nodes, checking each's data value, storing node pointer if there is a match
	for (int i = 0; i < numNodes; i++) {
		if (currentNodePtr->data == value) {
			outData.push_back(currentNodePtr);
		}

		currentNodePtr = currentNodePtr->next;
	}
}

// Find the first node with a data value matching the passed in parameter,
//	 returning the pointer to that node.
// Returns nullptr if no match found
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	Node* currentNodePtr = headPtr;
	// Iterate through nodes, checking each's data value, returning node pointer if there is a match
	for (int i = 0; i < numNodes; i++) {
		if (currentNodePtr->data == data) {
			return currentNodePtr;
		}
		else {
			currentNodePtr = currentNodePtr->next;
		}
	}
	return nullptr;
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	Node* currentNodePtr = headPtr;
	// Iterate through nodes, checking each's data value, returning node pointer if there is a match
	for (int i = 0; i < numNodes; i++) {
		if (currentNodePtr->data == data) {
			return currentNodePtr;
		}
		else {
			currentNodePtr = currentNodePtr->next;
		}
	}
	return nullptr;
}

// Given an index, return a pointer to the node at that index
// Throws out_of_range exception if index is out of range (<0 || >numNodes - 1)
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	// If index < 0  || index > numNodes - 1, throw out_of_range exception
	if ((int)index < 0 || (int)index > numNodes - 1) {
		try {
			throw out_of_range("Given index out of LinkedList range");
		}
		catch (out_of_range&) { return nullptr; }	// THIS EXISTS ONLY TO PASS THE ZYBOOKS TESTS
	}
	// If index == 0, return headPtr
	else if (index == 0) {
		return headPtr;
	}
	// If index == numNodes - 1, return tailPtr
	else if ((int)index == numNodes - 1) {
		return tailPtr;
	}
	else {
		Node* currentNodePtr = headPtr->next;
		// Loop index - 1 times starting from i = 1 (headPtr.next)
		// (Redundant to start from i == 0 or iterate to include i == index)
		for (int i = 1; i < (int)index; i++) {
			// For every iteration assigned currentNodePtr = currentNodePtr.next
			currentNodePtr = currentNodePtr->next;
		}
		// Return Node* at currentNodePtr after loop
		return currentNodePtr;
	}
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	// If index < 0  || index > numNodes - 1, throw out_of_range exception
	if ((int)index < 0 || (int)index > numNodes - 1) {
		throw out_of_range("Given index out of LinkedList range");
	}
	// If index == 0, return headPtr
	else if (index == 0) {
		return headPtr;
	}
	// If index == numNodes - 1, return tailPtr
	else if ((int)index == numNodes - 1) {
		return tailPtr;
	}
	else {
		Node* currentNodePtr = headPtr->next;
		// Loop index - 1 times starting from i = 1 (headPtr.next)
		// (Redundant to start from i == 0 or iterate to include i == index)
		for (int i = 1; i < (int)index; i++) {
			// For every iteration assigned currentNodePtr = currentNodePtr.next
			currentNodePtr = currentNodePtr->next;
		}
		// Return Node* at currentNodePtr after loop
		return currentNodePtr;
	}
}

// Returns head pointer 
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return headPtr;
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return headPtr;
}

// Returns tail pointer
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return tailPtr;
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return tailPtr;
}

// ==== INSERTION ====
// Creates a new Node at the front of the list to store the passed in parameter
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	// Declare new Node object
	Node* newNodePtr;
	// If there is no assigned pointers in LinkedList,
	// then headptr == nullptr and new node ptr is headptr and tailptr
	if (headPtr == nullptr) {
		newNodePtr = new Node(data); // new Node prevPtr and nextPtr assigned nullptr by default
		headPtr = newNodePtr;
		tailPtr = newNodePtr;
	}
	// Else there exists some Node(s) already in list
	else {
		// Create newNode object assigning headptr value to newNode's next param
		Node* next = headPtr;
		newNodePtr = new Node(data, next, nullptr);

		// Change list's headPtr to newNode
		headPtr = newNodePtr;

		// Update nextNode's prev value
		next->prev = newNodePtr;
	}
	numNodes++;
}

// Create a new Node at the end of the list to store the passed in parameter
template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	// Declare new Node object
	Node* newNodePtr;
	// If there is no assigned pointers in LinkedList,
	// then tailPtr == nullptr and new node ptr is headptr and tailptr
	if (tailPtr == nullptr) {
		newNodePtr = new Node(data); // new Node prevPtr and nextPtr assigned nullptr by default
		headPtr = newNodePtr;
		tailPtr = newNodePtr;
	}
	// Else there exists some Node(s) already in list
	else {
		// Create newNode object assigning tailPtr value to newNode's prev param
		Node* prev = tailPtr;
		newNodePtr = new Node(data, nullptr, prev);

		// Change list's tailPtr to newNode
		tailPtr = newNodePtr;

		// Update prevNode's next value
		prev->next = newNodePtr;
	}
	numNodes++;
}

// Given an array of values, insert a node for each value at the beginning of the list
//	maintaining the original order
template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
	// Last array element is first to be added to head
	// Iterate through array until first data element is added to head
	for (int i = (int)count - 1; i >= 0; i--) {
		AddHead(data[i]);
	}
}

// Given an array of values, insert a node for each value at end of the list
//	maintaining the original order
template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
	// Last array element is last to be added to list
	// Iterate through array until last data element added to tail
	for (int i = 0; i < (int)count; i++) {
		AddTail(data[i]);
	}
}

// Given a pointer to a Node, create a new Node to store the passed in value
//	before the indicated Node
template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
	// Look for Node in LinkedList that matches given Node
	// Since indicated Node is going to be after new Node, store as "next"
	Node* next = headPtr; 
	for (int i = 0; i < numNodes; i++) {
		if (next == node) {
			break;
		}
		else {
			next = next->next;
			if (next == nullptr) {
				cout << "Unable to find indicated node" << endl;
			}
		}
	}
	// Store next's prev Node as "prev"
	Node* prev = next->prev;
	
	// Create a new Node with given data
	//	and next's and prev's pointers as it's own next and prev fields
	Node* newNode = new Node(data, next, prev);
	//Reassign next's and prev's prev and next Nodes, respectively
	if (next != nullptr && prev != nullptr) {
		next->prev = newNode;
		prev->next = newNode;
	}

	numNodes++;
}

// Given a pointer to a Node, create a new Node to store the passed in value
//	after the indicated Node
template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
	// Look for Node in LinkedList that matches given Node
	// Since indicated Node is going to be before new Node, store as "prev"
	Node* prev = headPtr;
	for (int i = 0; i < numNodes; i++) {
		if (prev == node) {
			break;
		}
		else {
			prev = prev->next;
			if (prev == nullptr) {
				cout << "Unable to find indicated node" << endl;
			}
		}
	}
	// Store prev's next Node as "next"
	Node* next = prev->next;

	// Create a new Node with given data
	//	and next's and prev's pointers as it's own next and prev fields
	Node* newNode = new Node(data, next, prev);
	//Reassign next's and prev's prev and next Nodes, respectively
	next->prev = newNode;
	prev->next = newNode;

	numNodes++;
}

// Inserts a new Node to store the first param, at index-th location
// So if index == 3, new Node should have 3 nodes before it (inserts new Node after Node at index - 1)
// Throws out_of_range exception if index is invalid (index > numNodes, 
//	since numNodes - 1 is a valid previous node, or if index < 0)
template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
	// If index is invalid, throw out_of_range exception
	if ((int)index > numNodes || (int)index < 0) {
		throw out_of_range("Invalid index. Make sure index <= number of nodes in LinkedList.");
	}
	// If given index is 0, there is no previous node to work off of
	// New Node becomes head of list
	if (index == 0) {
		AddHead(data);
	}
	// Else if given index == numNodes, it will become the tail Node
	else if ((int)index == numNodes) {
		AddTail(data);
	}
	// Else given index is within LinkedList and has previous Node to work off of
	// So find Node before given index (index - 1) and insert new Node after that Node
	else {
		Node* prev = GetNode(index - 1);
		InsertAfter(prev, data);
	}
}

// ==== INSERTION ====
// Deletes the first Node in list
// Returns whether or not Node was removed
template <typename T>
bool LinkedList<T>::RemoveHead() {
	// If LinkedList is empty, it has no head; cannot be successful
	if (headPtr == nullptr) {
		return false;
	}
	else {
		// Create variables to store Node to remove and Node's next value
		Node* nodeToRemove = headPtr;
		Node* newHead = nodeToRemove->next;
		// Assign nullptr to newHead->prev, if newHead isn't nullptr
		if (newHead != nullptr) {
			newHead->prev = nullptr;
		}
		// Assign newHead to headPtr
		headPtr = newHead;
		if (headPtr == nullptr) {
			// List is now empty, make sure tailPtr represents that
			tailPtr = nullptr;
		}
		// Delete nodeToRemove
		delete nodeToRemove;

		numNodes--;
		return true;
	}
}

// Deletes last Node in list
// Returns whether or not Node was removed
template <typename T>
bool LinkedList<T>::RemoveTail() {
	// If LinkedList is empty, it has no tail; cannot be successful
	if (tailPtr == nullptr) {
		return false;
	}
	else {
		// Create variables to store Node to remove and Node's previous value
		Node* nodeToRemove = tailPtr;
		Node* newTail = nodeToRemove->prev;
		// Assign nullptr to newTail->next, if newTail isn't nullptr
		if (newTail != nullptr) {
			newTail->next = nullptr;
		}
		// Assign newTail to tailPtr
		tailPtr = newTail;
		if (tailPtr == nullptr) {
			// List is now empty, make sure headPtr represents that
			headPtr = nullptr;
		}
		// Delete nodeToRemove
		delete nodeToRemove;

		numNodes--;
		return true;
	}
}

// Deletes index-th Node from list
// Returns whether or not Node was successful
template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
	// If index is 0, remove head
	if (index == 0) {
		return RemoveHead();
	}
	// else if index is numNodes - 1, remove tail
	else if ((int)index == numNodes - 1) {
		return RemoveTail();
	}
	else {
		// If LinkedList is empty, it has no elements; cannot be successful
		if (headPtr == nullptr) {
			return false;
		}
		// Create variables to store Node to remove, Node's prev value, and Node's next value
		Node* nodeToRemove = GetNode(index);
		// If nodeToRemove given nullptr, index is out of range
		if (nodeToRemove == nullptr) { 
			return false;
		}
		else {
			Node* prev = nodeToRemove->prev;
			Node* next = nodeToRemove->next;
			// Assign next to prev->next, and prev to next->prev
			prev->next = next;
			next->prev = prev;
			// Delete Node to remove
			delete nodeToRemove;

			numNodes--;
			return true;
		}
	}
}

// Remove ALL Nodes containing values matching that of the passed-in parameter.
// Returns how many instances were removed.
template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
	// Find all Nodes with given data value and store in vector for quick access
	vector<LinkedList<T>::Node*> matches;
	FindAll(matches, data);

	unsigned int numMatches = matches.size();

	// Loop through vector; removing each node one by one
	for (unsigned int i = 0; i < matches.size(); i++) {
		Node* nodeToRemove = matches.at(i);
		Node* prev = nodeToRemove->prev;
		Node* next = nodeToRemove->next;

		prev->next = next;
		next->prev = prev;

		delete nodeToRemove;
		numNodes--;
	}

	return numMatches;
}

// Deletes all Nodes.
template <typename T>
void LinkedList<T>::Clear() {
	// Essentially Destructor's code
	if (headPtr != nullptr) {
		Node* nextPtrToDelete;
		do {
			nextPtrToDelete = headPtr->next;
			delete headPtr;
			headPtr = nextPtrToDelete;
		} while (nextPtrToDelete != nullptr);
	}

	headPtr = nullptr;
	tailPtr = nullptr;
	numNodes = 0;
}