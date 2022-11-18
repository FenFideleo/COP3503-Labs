/* Project 2: Image Processing
*
*  Student: Erik Meurrens
*
*
*  Notes:
*	- TGA header takes up 18 bytes total
*	- Header characteristics
*		- 24-bit true color, uncompressed images
*		- Need particularly image width and image height (12 byte offset, 14 byte offset)
*	- Image data pixel count is equivalent to image width * image height (data in header)
*	- Image data size is equivalent to pixel count * 3
*	- TGA pixel format
*		- BGR (blue first, green second, red third)
*		- Order of pixels
*			- First pixel is bottom left, last pixel top right
*			- Requires special algorithm to copy pixels into location (see p.5)
*	- Writing files
*		- Write header, follow with image data according to format
* 
*	- Blending modes to implement
*		- Multiply, Subtract, Screen, and Overlay	(May require 0-1 normalizing)
*		- Addition to individual channels	(+20 blue)	(Has limits at 0 and 255)
*		- Scaling individual channels	(50% green)	(May require 0-1 normalizing)
*/

#pragma once
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;


// TGA class represents TGA image file
class TGA
{
public: 
	// Nested Pixel struct contains pixel BGR values for 24-bit color TGA file
	struct Pixel
	{
		unsigned char blue;
		unsigned char green;
		unsigned char red;

		// Default Pixel constructor
		Pixel(unsigned char blue = 0, unsigned char green = 0, unsigned char red = 0);

		// Accessor(s)
		void printPixelData() const;

		// Mutator(s)
		void setValues(unsigned char blue, unsigned char green, unsigned char red);
	};

	// Nested Header struct contains file header info
	struct Header
	{
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;

		// Constructor(s)
		Header(short width = 0, short height = 0);				// Initializes to "default" values
		Header(ifstream& in);									// Uses referenced ifstream from TGA object to read data values

		// Accessor(s)
		void printHeaderData() const;
	};

/*=== PRIVATE MEMBERS === */
private:
	// Private member fields
	string filename;					// Stores name of TGA file
	ifstream in;						// Stores the file stream to read data
	ofstream out;						// Stores file stream to write data
	Header* header;						// Contains Header object to store header values
	unsigned int numPixels;				// Number of pixels in image
	unsigned int numPixelsPerRow;		// Number of pixels per row
	unsigned short numRows;				// Number of rows of pixels in image
	unsigned int fileSize;				// Returns size of file in bytes
	
	// Helper functions
	ifstream& openInputFileStream(string subDirectory);						// Ensures file can be opened and read
	void loadFileData(short width, short height);							// Loads default file data into data members for new file
	void loadFileData(ifstream& in);										// Loads file data into data members from file
	void openOutputFileStream(string& fileDirectory, string newFilename);	// Ensures filestream can be opened and written into

/*=== PUBLIC MEMBERS === */
public:
	vector<vector<Pixel*>*> pixels;		// Vector to store vectors(rows) of pixels from file (moved to public for personal convenience)

	/*=== CONSTRUCTOR(S) ===*/
	TGA(short width = 0, short height = 0, string filename = "a.tga");	// Default
	TGA(string filename);
	TGA(string filename, string subDirectory);							// Intended to open files from different directory than "input/"

	/*=== ACCESSORS ===*/
	string getFilename() const;						// Returns filename as string
	short getWidth() const;							// Returns width of image from header
	short getHeight() const;						// Returns height of image from header
	void printData() const;							// Prints image data for debugging

	/*=== MUTATORS ===*/
	void setFilename(string newFilename);									// Allows renaming of TGA object
	enum class preset { RED, GREEN, BLUE, RAND};							// Presets for overwrite function
	void overwrite(short h1, short h2, short w1, short w2, TGA& image);		// Completely overwrites pixel values in given region with new image
	void overwrite(short h1, short h2, short w1, short w2, preset value);	// Completely overwrites pixel values in given region using presets
	void rotate180();														// Rotates invoking TGA image by 180 degrees

	//=== SCALING, ADDITION, and other color manipulation
	void colorAdjust(int bAdjust, int gAdjust, int rAdjust);	// Adjusts channel values by addition/subtraction
	void colorScale(float bScale, float gScale, float rScale);	// Adjust channel values according to scale (multiply)
	TGA* splitChannel(preset color);							// Creates new TGA object from color channels of invoking TGA object
	void addChannels(TGA& blueChannel, TGA& greenChannel, TGA& redChannel);	// Adds channels together to form new image

	//=== BLENDING FUNCTIONS
	TGA& multiply(TGA& layer2);
	TGA& screen(TGA& layer2);
	TGA& subtract(TGA& source);
	TGA& overlay(TGA& layer2);

	/*=== BEHAVIORS ===*/
	void writeData(string fileDirectory, string filename);			// Writes stored image to file in given directory

	/*=== DESTRUCTOR ===*/
	~TGA();
};
