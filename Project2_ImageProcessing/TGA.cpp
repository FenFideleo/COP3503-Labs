/* Project 2: Image Processing
*
*  Student: Erik Meurrens
*
*
*  Notes:
*
*/

#include <cmath>
#include "TGA.h"
using namespace std;

/*========================================= TGA::PIXEL STRUCT FUNCTIONS =========================================*/

/*==== CONSTRUCTOR(S) ====*/
TGA::Pixel::Pixel(unsigned char blue, unsigned char green, unsigned char red){
	this->blue = blue;
	this->green = green;
	this->red = red;
}

/*==== ACCESSOR(S) ====*/
void TGA::Pixel::printPixelData() const{
	cout << "Red Value: " << (int)red << "	"
		<< "Green Value: " << (int)green << "  "
		<< "Blue Value: " << (int)blue << endl;
}

/*==== MUTATOR(S) ====*/
void TGA::Pixel::setValues(unsigned char blue, unsigned char green, unsigned char red) {
	this->blue = blue;
	this->green = green;
	this->red = red;
}

/*========================================= TGA::HEADER STRUCT FUNCTIONS =========================================*/

/*==== CONSTRUCTOR(S) ====*/
// Default constructor (Sets to project defaults, except width and height are 0)
TGA::Header::Header(short width, short height) {

	idLength = 0;
	colorMapType = 0;
	dataTypeCode = 2;
	colorMapOrigin = 0;
	colorMapLength = 0;
	colorMapDepth = 0;
	xOrigin = 0;
	yOrigin = 0;
	this->width = width;
	this->height = height;
	bitsPerPixel = 24;
	imageDescriptor = 0;

}

// Preferred constructor uses filestream to read data and place into data fields
TGA::Header::Header(ifstream& in) {
	
	in.read(&idLength, sizeof(idLength));
	in.read(&colorMapType, sizeof(colorMapType));
	in.read(&dataTypeCode, sizeof(dataTypeCode));
	in.read((char*)&colorMapOrigin, sizeof(colorMapOrigin));
	in.read((char*)&colorMapLength, sizeof(colorMapLength));
	in.read(&colorMapDepth, sizeof(colorMapDepth));
	in.read((char*)&xOrigin, sizeof(xOrigin));
	in.read((char*)&yOrigin, sizeof(yOrigin));
	in.read((char*)&width, sizeof(width));
	in.read((char*)&height, sizeof(height));
	in.read(&bitsPerPixel, sizeof(bitsPerPixel));
	in.read(&imageDescriptor, sizeof(imageDescriptor));

}

/*==== ACCESSORS(S) ====*/
void TGA::Header::printHeaderData() const {
	cout << "========= HEADER DATA ===========" << endl
		<< "ID Length: " << (int)idLength << endl
		<< "Color Map Type: " << (int)colorMapType << endl
		<< "Data Type Code: " << (int)dataTypeCode << endl
		<< "Color Map Origin: " << (int)colorMapOrigin << endl
		<< "Color Map Length: " << (int)colorMapLength << endl
		<< "Color Map Depth: " << (int)colorMapDepth << endl
		<< "X Origin: " << (int)xOrigin << endl
		<< "Y Origin: " << (int)yOrigin << endl
		<< "Width: " << (int)width << endl
		<< "Height: " << (int)height << endl
		<< "Bits per Pixel: " << (int)bitsPerPixel << endl
		<< "Image Descriptor: " << (int)imageDescriptor << endl
		<< endl;
}

/*========================================= TGA CLASS FUNCTIONS =========================================*/

/*==== CONSTRUCTOR(S) ====*/
// Default constructor
TGA::TGA(short width, short height, string filename) {
	this->filename = filename;
	
	loadFileData(width, height);
}

void TGA::loadFileData(short width, short height) {
	// Constructs header according to default values + width & height inputs
	header = new Header(width, height);

	// Determine pixel count and, by extension, theoretical file size
	// Image data pixel count is equivalent to image width* image height(data in header)
	//  -Image data size is equivalent to pixel count * pixel data size(==3)
	numPixels = header->width * header->height;
	numPixelsPerRow = header->width;
	numRows = header->height;
	fileSize = numPixels * sizeof(Pixel);

	// Load pixel data into pixels vector using zero-default BGR values
	for (unsigned int i = 0; i < numRows; i++) {
		pixels.push_back(new vector<Pixel*>);
		for (unsigned int j = 0; j < numPixelsPerRow; j++) {
			unsigned char blueVal = 0, greenVal = 0, redVal = 0;

			pixels[i]->push_back(new Pixel(blueVal, greenVal, redVal));
		}
	}
}

// Constructor initializes data members by initializing filestream
// and loading data from respective TGA file
TGA::TGA(string filename) {
	this->filename = filename;
	
	// Ensures filestream is opened and loads image data into data fields
	loadFileData(openInputFileStream("input/"));

}

TGA::TGA(string filename, string subDirectory) {
	this->filename = filename;

	// Ensures filestream is opened and loads image data into data fields
	loadFileData(openInputFileStream(subDirectory));
}

/*==== CONSTRUCTOR HELPER FUNCTIONS ==== */
ifstream& TGA::openInputFileStream(string subDirectory) {
	// Attempt to open from program-relative directory
	in.open(subDirectory + filename, ios_base::binary);

	// Check if file is open
	// If not, program-relative directory does not exist; try test directory
	if (!in.is_open()) {
		in.close();		// Just in case
		// Attempt to open file from test directory
		string fileDirectory = "F:/UF/COP3503C/Lab and Project files/Project 2 - Image Processing/Project2_ImageProcessing/" + subDirectory;
		fileDirectory = fileDirectory + filename;
		in.open(fileDirectory, ios_base::binary);
	}
	else {
		cout << "Opened \"" << filename << "\" from program-relative directory" << endl << endl;
		return in;
	}

	// Check if file is open again; if not, tough luck
	if (!in.is_open()) {
		in.close();
		cout << "Unable to open \"" << filename << "\"" << endl;
	}
	else {
		cout << "Opened \"" << filename << "\" from test directory" << endl << endl;
		return in;
	}

	return in;
}
void TGA::loadFileData(ifstream& in) {
	// Load data into header file from ifstream
	header = new Header(in);

	// Determine pixel count and, by extension, theoretical file size
	// Image data pixel count is equivalent to image width* image height(data in header)
	//  -Image data size is equivalent to pixel count * pixel data size(==3)
	numPixels = header->width * header->height;
	numPixelsPerRow = header->width;
	numRows = header->height;
	fileSize = numPixels * sizeof(Pixel);

	// Load pixel data into pixels vector using BGR values
	for (unsigned int i = 0; i < numRows; i++) {
		pixels.push_back(new vector<Pixel*>);
		for (unsigned int j = 0; j < numPixelsPerRow; j++) {
			unsigned char blueVal, greenVal, redVal;
			in.read((char*)&blueVal, sizeof(blueVal));
			in.read((char*)&greenVal, sizeof(greenVal));
			in.read((char*)&redVal, sizeof(redVal));

			pixels[i]->push_back(new Pixel(blueVal, greenVal, redVal));
		}
	}
	
	in.close();	// Done reading
}
void TGA::openOutputFileStream(string& fileDirectory, string newFilename) {
	// Attempts to open file stream to given directory
	out.open(fileDirectory + newFilename, ios_base::binary);
	//  if doesn't work attempt to open file in test directory
	if (!out.is_open()) {
		out.close();
		fileDirectory = "F:/UF/COP3503C/Lab and Project files/Project 2 - Image Processing/Project2_ImageProcessing/output/";
		out.open(fileDirectory + newFilename, ios_base::binary);

		// if that doesn't work, tough luck, can't write
		if (!out.is_open()) {
			out.close();
			cout << "Unable to open \"" << newFilename << "\"" << endl;
			return;
		}
		else {
			cout << "Able to write \"" << newFilename << "\" to test directory" << endl << endl;
		}
	}
	else {
		cout << "Able to write \"" << newFilename << "\" to program-relative directory" << endl << endl;
	}
}

/*==== ACCESSORS ====*/
string TGA::getFilename() const {
	return filename;
}
short TGA::getWidth() const {
	return header->width;
}
short TGA::getHeight() const {
	return header->height;
}
void TGA::printData() const {
	cout << "Printing data for \"" << filename << "\" . . ." << endl;
	header->printHeaderData();
	cout << "Printing data for first pixel . . . " << endl;
	pixels[0]->at(0)->printPixelData();
	cout << "Printing data for last pixel . . . " << endl;
	pixels[numRows - 1]->at(numPixelsPerRow - 1)->printPixelData();
	cout << endl;
}

/*==== MUTATORS ====*/
void TGA::setFilename(string newFilename) {
	filename = newFilename;
}

void TGA::overwrite(short h1, short h2, short w1, short w2, TGA& image) {
	for (unsigned int i = h1; i < h2; i++) {
		for (unsigned int j = w1; j < w2; j++) {
			pixels[i]->at(j) = image.pixels[i - h1]->at(j - w1);
		}
	}
}
void TGA::overwrite(short h1, short h2, short w1, short w2, preset value) {
	// Overwrites values from h1 to h2-1, and w1 to w2-1
	switch (value) {
		case preset::RED: {
			for (short i = h1; i < h2; i++) {
				for (short j = w1; j < w2; j++) {
					pixels[i]->at(j)->setValues(0, 0, 255);
				}
			}
			break;
		}
		case preset::GREEN: {
			for (short i = h1; i < h2; i++) {
				for (short j = w1; j < w2; j++) {
					pixels[i]->at(j)->setValues(0, 255, 0);
				}
			}
			break;
		}
		case preset::BLUE: {
			for (short i = h1; i < h2; i++) {
				for (short j = w1; j < w2; j++) {
					pixels[i]->at(j)->setValues(255, 0, 0);
				}
			}
			break;
		}
		case preset::RAND: {
			for (short i = h1; i < h2; i++) {
				for (short j = w1; j < w2; j++) {
					pixels[i]->at(j)->setValues(rand()%256, rand()%256, rand()%256);
				}
			}
			break;
		}
		default: {
			break;
		}
	}
}

void TGA::rotate180() {
	for (unsigned int i = 0, j = numRows - 1; i <= j; i++, j--) {
		for (unsigned int m = 0, n = numPixelsPerRow - 1; m < numPixelsPerRow; m++, n--) {
			if (i == j && m == n) {
				break;
			}
			Pixel* mPixel = pixels[i]->at(m);
			pixels[i]->at(m) = pixels[j]->at(n);
			pixels[j]->at(n) = mPixel;
		}
	}
}

//=== ADDITION AND SCALING and other color manipulation
void TGA::colorAdjust(int bAdjust, int gAdjust, int rAdjust) {
	// Create temporary variables to store resultant value in case of overflow
	int blue, green, red;

	// Loop through pixels in image, adjusting them according to the adjustment parameters
	// If blue, green, or red values are less than 0 or greater than 255, set them to min/max to avoid overflow
	for (unsigned int i = 0; i < pixels.size(); i++) {
		for (unsigned int j = 0; j < pixels[i]->size(); j++) {
			Pixel& currentPixel = *(pixels[i]->at(j));
			blue = currentPixel.blue + bAdjust;
			green = currentPixel.green + gAdjust;
			red = currentPixel.red + rAdjust;

			if (blue < 0) {
				blue = 0;
			}
			else if (blue > 255) {
				blue = 255;
			}
			currentPixel.blue = (unsigned char)blue;

			if (green < 0) {
				green = 0;
			}
			else if (green > 255) {
				green = 255;
			}
			currentPixel.green = (unsigned char)green;

			if (red < 0) {
				red = 0;
			}
			else if (red > 255) {
				red = 255;
			}
			currentPixel.red = (unsigned char)red;
		}
	}
}
void TGA::colorScale(float bScale, float gScale, float rScale) {
	const float ROUNDING_OFFSET = 0.5f;

	// Declare variables for normalized values, and values to store resultant values
	float bNormal/*I wish*/, gNormal, rNormal;
	float blue, green, red;

	// Loop through all pixels and adjust their values according to the scale
	// Make sure to normalize color channel values
	// If value exceeds 1, set value to 1
	for (unsigned int i = 0; i < pixels.size(); i++) {
		for (unsigned int j = 0; j < pixels[i]->size(); j++) {
			Pixel& currentPixel = *(pixels[i]->at(j));
			bNormal = currentPixel.blue / (float)(pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT)  - 1.0);
			gNormal = currentPixel.green / (float)(pow(2.0, sizeof(currentPixel.green) * CHAR_BIT)  - 1.0);
			rNormal = currentPixel.red / (float)(pow(2.0, sizeof(currentPixel.red) * CHAR_BIT)  - 1.0);

			blue = bNormal * bScale;
			green = gNormal * gScale;
			red = rNormal * rScale;

			if (blue > 1.0) {
				blue = 1.0;
			}
			currentPixel.blue = (unsigned char)(blue * (pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT) - 1) + ROUNDING_OFFSET);

			if (green > 1.0) {
				green = 1.0;
			}
			currentPixel.green = (unsigned char)(green * (pow(2.0, sizeof(currentPixel.green) * CHAR_BIT) - 1) + ROUNDING_OFFSET);

			if (red > 1.0) {
				red = 1.0;
			}
			currentPixel.red = (unsigned char)(red * (pow(2.0, sizeof(currentPixel.red) * CHAR_BIT) - 1) + ROUNDING_OFFSET);
		}
	}
}
TGA* TGA::splitChannel(preset color) {
	// Make blank TGA file using this TGA data values
	TGA* result = new TGA(header->width, header->height);
	
	// Loop through current TGA and add selected channels into new TGA
	for (unsigned int i = 0; i < pixels.size(); i++) {
		for (unsigned int j = 0; j < pixels[i]->size(); j++) {
			Pixel& currentPixel = *(pixels[i]->at(j));
			Pixel& newPixel = *(result->pixels[i]->at(j));

			if (color == preset::BLUE) {
				newPixel.blue = currentPixel.blue;
				newPixel.green = currentPixel.blue;
				newPixel.red = currentPixel.blue;
			}
			if (color == preset::GREEN) {
				newPixel.blue = currentPixel.green;
				newPixel.green = currentPixel.green;
				newPixel.red = currentPixel.green;
			}
			if (color == preset::RED) {
				newPixel.blue = currentPixel.red;
				newPixel.green = currentPixel.red;
				newPixel.red = currentPixel.red;
			}
		}
	}

	return result;
}
void TGA::addChannels(TGA& blueChannel, TGA& greenChannel, TGA& redChannel) {
	//// Check to see which layer has greater dimensions
	//// If one has greater width AND height value, set this TGA's header's width and height value to same
	//if (blueChannel.header->height > header->height
	//	&& blueChannel.header->width > header->width) {
	//	header->height = blueChannel.header->height;
	//	header->width = blueChannel.header->width;

	//	numRows = header->height;
	//	numPixelsPerRow = header->width;
	//	numPixels = numRows * numPixelsPerRow;
	//	fileSize = numPixels * sizeof(Pixel);
	//}

	//// Expand current pixels vector to fit additional pixels, if needed
	//for (unsigned int i = numRows; i < header->height; i++) {
	//	pixels.push_back(new vector<Pixel*>);
	//	for (unsigned int j = numPixelsPerRow; j < header->width; j++) {
	//		unsigned char blueVal = 0, greenVal = 0, redVal = 0;

	//		pixels[i]->push_back(new Pixel(blueVal, greenVal, redVal));
	//	}
	//}

	for (unsigned int i = 0; i < pixels.size(); i++) {
		for (unsigned int j = 0; j < pixels[i]->size(); j++) {
			Pixel& currentPixel = *(pixels[i]->at(j));
			unsigned char blue = blueChannel.pixels[i]->at(j)->blue;
			unsigned char green = greenChannel.pixels[i]->at(j)->green;
			unsigned char red = redChannel.pixels[i]->at(j)->red;

			currentPixel.blue = blue;
			currentPixel.green = green;
			currentPixel.red = red;
		}
	}
}

//=== BLENDING METHODS
// Multiplies color values of current TGA and other TGA, pixel-by-pixel, and overwrites current TGA file
TGA& TGA::multiply(TGA& layer2) {
	const float ROUNDING_OFFSET = 0.5f;

	// Declare variables to store normalized values and resultant values
	float b1Normal, b2Normal, g1Normal, g2Normal, r1Normal, r2Normal;
	float blue, green, red;
	
	//// Check to see which layer has greater dimensions
	//// If one has greater width AND height value, set this TGA's header's width and height value to same
	//if (layer2.header->height > header->height 
	//	&& layer2.header->width > header->width) {
	//	header->height = layer2.header->height;
	//	header->width = layer2.header->width;

	//	numRows = header->height;
	//	numPixelsPerRow = header->width;
	//	numPixels = numRows * numPixelsPerRow;
	//	fileSize = numPixels * sizeof(Pixel);
	//}

	//// Expand current pixels vector to fit additional pixels, if needed
	//for (unsigned int i = numRows; i < header->height; i++) {
	//	pixels.push_back(new vector<Pixel*>);
	//	for (unsigned int j = numPixelsPerRow; j < header->width; j++) {
	//		unsigned char blueVal = 0, greenVal = 0, redVal = 0;

	//		pixels[i]->push_back(new Pixel(blueVal, greenVal, redVal));
	//	}
	//}

	// Loop through pixels of TGA parameters and multiply normalized pixel values together
	// Store product in this TGA
	// Make sure to normalize color channel values
	for (unsigned int i = 0; i < pixels.size(); i++) {
		for (unsigned int j = 0; j < pixels[i]->size(); j++) {
			Pixel& currentPixel = *(pixels[i]->at(j));
			Pixel& layer2Pixel = *(layer2.pixels[i]->at(j));
			b1Normal = currentPixel.blue / (float)(pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT) - 1.0);
			g1Normal = currentPixel.green / (float)(pow(2.0, sizeof(currentPixel.green) * CHAR_BIT) - 1.0);
			r1Normal = currentPixel.red / (float)(pow(2.0, sizeof(currentPixel.red) * CHAR_BIT) - 1.0);
			b2Normal = layer2Pixel.blue / (float)(pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT) - 1.0);
			g2Normal = layer2Pixel.green / (float)(pow(2.0, sizeof(currentPixel.green) * CHAR_BIT) - 1.0);
			r2Normal = layer2Pixel.red / (float)(pow(2.0, sizeof(currentPixel.red) * CHAR_BIT) - 1.0);

			blue = b1Normal * b2Normal;
			green = g1Normal * g2Normal;
			red = r1Normal * r2Normal;

			currentPixel.blue = (unsigned char)(blue * (pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT) - 1.0) + ROUNDING_OFFSET);
			currentPixel.green = (unsigned char)(green * (pow(2.0, sizeof(currentPixel.green) * CHAR_BIT) - 1.0) + ROUNDING_OFFSET);
			currentPixel.red = (unsigned char)(red * (pow(2.0, sizeof(currentPixel.red) * CHAR_BIT) - 1.0) + ROUNDING_OFFSET);
		}
	}

	return *this;
}

// I honestly have no clue what this is supposed to do, I'm just following the equation, C = 1 - (1-A)*(1-B)
TGA& TGA::screen(TGA& layer2) {
	const float ROUNDING_OFFSET = 0.5f;

	// Declare variables to store normalized values and resultant values
	float b1Normal, b2Normal, g1Normal, g2Normal, r1Normal, r2Normal;
	float blue, green, red;

	//// Check to see which layer has greater dimensions
	//// If one has greater width AND height value, set this TGA's header's width and height value to same
	//if (layer2.header->height > header->height
	//	&& layer2.header->width > header->width) {
	//	header->height = layer2.header->height;
	//	header->width = layer2.header->width;

	//	numRows = header->height;
	//	numPixelsPerRow = header->width;
	//	numPixels = numRows * numPixelsPerRow;
	//	fileSize = numPixels * sizeof(Pixel);
	//}

	//// Expand current pixels vector to fit additional pixels, if needed
	//for (unsigned int i = numRows; i < header->height; i++) {
	//	pixels.push_back(new vector<Pixel*>);
	//	for (unsigned int j = numPixelsPerRow; j < header->width; j++) {
	//		unsigned char blueVal = 0, greenVal = 0, redVal = 0;

	//		pixels[i]->push_back(new Pixel(blueVal, greenVal, redVal));
	//	}
	//}

	// Loop through pixels of this TGA and layer2 and multiply normalized pixel values together
	//		according to equation C = 1 - (1-A) * (1-B)
	// Store product in this TGA
	for (unsigned int i = 0; i < pixels.size(); i++) {
		for (unsigned int j = 0; j < pixels[i]->size(); j++) {
			Pixel& currentPixel = *(pixels[i]->at(j));
			Pixel& layer2Pixel = *(layer2.pixels[i]->at(j));

			b1Normal = currentPixel.blue / (float)(pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT) - 1.0);
			g1Normal = currentPixel.green / (float)(pow(2.0, sizeof(currentPixel.green) * CHAR_BIT) - 1.0);
			r1Normal = currentPixel.red / (float)(pow(2.0, sizeof(currentPixel.red) * CHAR_BIT) - 1.0);
			b2Normal = layer2Pixel.blue / (float)(pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT) - 1.0);
			g2Normal = layer2Pixel.green / (float)(pow(2.0, sizeof(currentPixel.green) * CHAR_BIT) - 1.0);
			r2Normal = layer2Pixel.red / (float)(pow(2.0, sizeof(currentPixel.red) * CHAR_BIT) - 1.0);

			blue = 1 - (1 - b1Normal) * (1 - b2Normal);
			green = 1 - (1 - g1Normal) * (1 - g2Normal);
			red = 1 - (1 - r1Normal) * (1 - r2Normal);

			currentPixel.blue = (unsigned char)(blue * (pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT) - 1.0) + ROUNDING_OFFSET);
			currentPixel.green = (unsigned char)(green * (pow(2.0, sizeof(currentPixel.green) * CHAR_BIT) - 1.0) + ROUNDING_OFFSET);
			currentPixel.red = (unsigned char)(red * (pow(2.0, sizeof(currentPixel.red) * CHAR_BIT) - 1.0) + ROUNDING_OFFSET);
		}
	}

	return *this;
}

TGA& TGA::overlay(TGA& layer2) {
	const float ROUNDING_OFFSET = 0.5f;

	// Declare variables to store normalized values and resultant values
	float b1Normal, b2Normal, g1Normal, g2Normal, r1Normal, r2Normal;
	float blue, green, red;

	//// Check to see which layer has greater dimensions
	//// If one has greater width AND height value, set this TGA's header's width and height value to same
	//if (layer2.header->height > header->height
	//	&& layer2.header->width > header->width) {
	//	header->height = layer2.header->height;
	//	header->width = layer2.header->width;

	//	numRows = header->height;
	//	numPixelsPerRow = header->width;
	//	numPixels = numRows * numPixelsPerRow;
	//	fileSize = numPixels * sizeof(Pixel);
	//}

	//// Expand current pixels vector to fit additional pixels, if needed
	//for (unsigned int i = numRows; i < header->height; i++) {
	//	pixels.push_back(new vector<Pixel*>);
	//	for (unsigned int j = numPixelsPerRow; j < header->width; j++) {
	//		unsigned char blueVal = 0, greenVal = 0, redVal = 0;

	//		pixels[i]->push_back(new Pixel(blueVal, greenVal, redVal));
	//	}
	//}

	// Loop through pixels of this TGA and layer2 and multiply normalized pixel values together
	// If layer2 pixel saturation is <= 0.5, use equation C = 2*A*B;
	// If layer2 pixel saturation is > 0m5, use equation C = 1 - 2*(1-A)*(1-B)
	// Store product in this TGA
	for (unsigned int i = 0; i < pixels.size(); i++) {
		for (unsigned int j = 0; j < pixels[i]->size(); j++) {
			Pixel& currentPixel = *(pixels[i]->at(j));
			Pixel& layer2Pixel = *(layer2.pixels[i]->at(j));

			b1Normal = currentPixel.blue / (float)(pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT) - 1.0);
			g1Normal = currentPixel.green / (float)(pow(2.0, sizeof(currentPixel.green) * CHAR_BIT) - 1.0);
			r1Normal = currentPixel.red / (float)(pow(2.0, sizeof(currentPixel.red) * CHAR_BIT) - 1.0);
			b2Normal = layer2Pixel.blue / (float)(pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT) - 1.0);
			g2Normal = layer2Pixel.green / (float)(pow(2.0, sizeof(currentPixel.green) * CHAR_BIT) - 1.0);
			r2Normal = layer2Pixel.red / (float)(pow(2.0, sizeof(currentPixel.red) * CHAR_BIT) - 1.0);

			if (b2Normal <= 0.5f) {
				blue = 2 * b1Normal * b2Normal;
			}
			else {
				blue = 1 - 2 * (1 - b1Normal) * (1 - b2Normal);
			}

			if (g2Normal <= 0.5f) {
				green = 2 * g1Normal * g2Normal;
			}
			else {
				green = 1 - 2 * (1 - g1Normal) * (1 - g2Normal);
			}

			if (r2Normal <= 0.5f) {
				red = 2 * r1Normal * r2Normal;
			}
			else {
				red = 1 - 2 * (1 - r1Normal) * (1 - r2Normal);
			}

			currentPixel.blue = (unsigned char)(blue * (pow(2.0, sizeof(currentPixel.blue) * CHAR_BIT) - 1.0) + ROUNDING_OFFSET);
			currentPixel.green = (unsigned char)(green * (pow(2.0, sizeof(currentPixel.green) * CHAR_BIT) - 1.0) + ROUNDING_OFFSET);
			currentPixel.red = (unsigned char)(red * (pow(2.0, sizeof(currentPixel.red) * CHAR_BIT) - 1.0) + ROUNDING_OFFSET);
		}
	}

	return *this;
}

// Subtracts colors of pixels in source from color of pixels in target; overwrites this TGA file
TGA& TGA::subtract(TGA& source) {
	// Create temporary variables to store resultant value in case of overflow
	int blue, green, red;

	//// Check to see which layer has greater dimensions
	//// If one has greater width AND height value, set this TGA's header's width and height value to same
	//if (source.header->height > header->height
	//	&& source.header->width > header->width) {
	//	header->height = source.header->height;
	//	header->width = source.header->width;

	//	numRows = header->height;
	//	numPixelsPerRow = header->width;
	//	numPixels = numRows * numPixelsPerRow;
	//	fileSize = numPixels * sizeof(Pixel);
	//}

	//// Expand current pixels vector to fit additional pixels, if needed
	//for (unsigned int i = numRows; i < header->height; i++) {
	//	pixels.push_back(new vector<Pixel*>);
	//	for (unsigned int j = numPixelsPerRow; j < header->width; j++) {
	//		unsigned char blueVal = 0, greenVal = 0, redVal = 0;

	//		pixels[i]->push_back(new Pixel(blueVal, greenVal, redVal));
	//	}
	//}

	// Loop through pixels in this TGA subtracting source TGA's pixel values from them
	// If blue, green, or red values are less than 0 set them to min (== 0) to avoid overflow
	for (unsigned int i = 0; i < pixels.size(); i++) {
		for (unsigned int j = 0; j < pixels[i]->size(); j++) {
			Pixel& currentPixel = *(pixels[i]->at(j));
			Pixel& sourcePixel = *(source.pixels[i]->at(j));

			blue = currentPixel.blue - sourcePixel.blue;
			green = currentPixel.green - sourcePixel.green;
			red = currentPixel.red - sourcePixel.red;

			if (blue < 0) {
				blue = 0;
			}
			currentPixel.blue = (unsigned char)blue;

			if (green < 0) {
				green = 0;
			}
			currentPixel.green = (unsigned char)green;

			if (red < 0) {
				red = 0;
			}
			currentPixel.red = (unsigned char)red;
		}
	}

	return *this;
}

/*==== BEHAVIORS ====*/
void TGA::writeData(string fileDirectory, string filename) {
	openOutputFileStream(fileDirectory, filename);
	
	// Write header data
	out.write(&(header->idLength), sizeof(header->idLength));
	out.write(&(header->colorMapType), sizeof(header->colorMapType));
	out.write(&(header->dataTypeCode), sizeof(header->dataTypeCode));
	out.write((char*)&(header->colorMapOrigin), sizeof(header->colorMapOrigin));
	out.write((char*)&(header->colorMapLength), sizeof(header->colorMapLength));
	out.write(&(header->colorMapDepth), sizeof(header->colorMapDepth));
	out.write((char*)&(header->xOrigin), sizeof(header->xOrigin));
	out.write((char*)&(header->yOrigin), sizeof(header->yOrigin));
	out.write((char*)&(header->width), sizeof(header->width));
	out.write((char*)&(header->height), sizeof(header->height));
	out.write(&(header->bitsPerPixel), sizeof(header->bitsPerPixel));
	out.write(&(header->imageDescriptor), sizeof(header->imageDescriptor));

	// Write pixel data
	for (unsigned int i = 0; i < pixels.size(); i++) {
		for (unsigned int j = 0; j < pixels[i]->size(); j++) {
			Pixel& currentPixel = *(pixels[i]->at(j));
			out.write((char*)&(currentPixel.blue), sizeof(currentPixel.blue));
			out.write((char*)&(currentPixel.green), sizeof(currentPixel.green));
			out.write((char*)&(currentPixel.red), sizeof(currentPixel.red));
		}
	}

	out.close(); // Close for safety
}

/*==== DESTRUCTOR ====*/
TGA::~TGA() {
	delete header;
	for (unsigned int i = 0; i < pixels.size(); i++) {
		for (unsigned int j = 0; j < pixels[i]->size(); j++) {
			delete pixels[i]->at(j);
		}
		delete pixels[i];
	}
}
