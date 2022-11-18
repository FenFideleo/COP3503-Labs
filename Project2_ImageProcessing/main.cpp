/* Project 2: Image Processing
*
*  Student: Erik Meurrens
*
* 
*  Notes:
*	- Overview 
*		- (1) read number of .TGA files in binary, 
*		- (2) process image data within those files,
*		- (3) write new .TGA files in same binary format
*	
*	- Input file names:
*		- car.tga
*		- circles.tga
*		- layer_blue.tga
*		- layer_green.tga
*		- layer_red.tga
*		- layer1.tga
*		- layer2.tga
*		- pattern1.tga
*		- pattern2.tga
*		- text.tga
*		- text2.tga
*/

#include "TGA.h"
using namespace std;

//void testDeprecated() {
//	// Test TGA read data functions
//	TGA test1("car.tga");
//	test1.printData();
//
//	TGA test2("circles.tga");
//	test2.printData();
//
//	TGA test3("layer_blue.tga");
//	test3.printData();
//
//	TGA test4("layer1.tga");
//	test4.printData();
//
//	// Test TGA write data functions
//	test1.writeData("output/", "car_test.tga");
//	test2.writeData("output/", "circles_test.tga");
//	test3.writeData("output/", "layer_blue_test.tga");
//	test4.writeData("output/", "layer1_test.tga");
//
//	// Test TGA overwrite functions
//	test1.overwrite(0, test1.getHeight(), 0, test1.getWidth(), TGA::preset::RED);
//	test1.writeData("output/", "overwriteRED.tga");
//	test1.overwrite(0, test1.getHeight(), 0, test1.getWidth(), TGA::preset::BLUE);
//	test1.writeData("output/", "overwriteBLUE.tga");
//	test1.overwrite(0, test1.getHeight(), 0, test1.getWidth(), TGA::preset::GREEN);
//	test1.writeData("output/", "overwriteGREEN.tga");
//	test1.overwrite(0, test1.getHeight(), 0, test1.getWidth(), TGA::preset::RAND);
//	test1.writeData("output/", "overwriteRAND.tga");
//
//	// Test writing new TGA file
//	TGA test5(512, 512);
//	test5.writeData("output/", test5.getFilename());
//	test5.overwrite(0, test5.getHeight(), 0, test5.getWidth(), TGA::preset::RAND);
//	test5.writeData("output/", "new_" + test5.getFilename());
//
//	// Testing colorAdjust and colorScale on TGA objects
//	TGA test6("car.tga");
//	cout << "Print \"car.tga\" data before" << endl;
//	test6.printData();
//	test6.colorAdjust(50, 50, 50);
//	test6.writeData("output/", "car_test_adjusted.tga");
//	cout << "Print \"car.tga\" data after adjust of 50, 50, 50" << endl;
//	test6.printData();
//	test6.colorScale(0.25, 0.5, 4);
//	test6.writeData("output/", "car_test_adjusted_scaled.tga");
//	cout << "Print \"car.tga\" data after adjust AND scale of 0.25, 0.5, 4" << endl;
//	test6.printData();
//
//	// Testing multiply function
//	TGA* temp1 = new TGA("pattern1.tga");
//	test4.multiply(*temp1);
//	test4.writeData("output/", "multiply_test.tga");
//	delete temp1;
//
//	// Test subtract function
//	temp1 = new TGA("layer2.tga");
//	TGA* temp2 = new TGA("car.tga");
//	temp2->subtract(*temp1);
//	temp2->writeData("output/", "subtract_test.tga");
//	delete temp1;
//	delete temp2;
//
//	// Test screen function
//	temp1 = new TGA("layer1.tga");
//	temp2 = new TGA("pattern2.tga");
//	temp1->multiply(*temp2);
//
//	TGA* temp3 = new TGA("text.tga");
//
//	temp3->screen(*temp1);
//	temp3->writeData("output/", "screen_test.tga");
//
//	delete temp1;
//	delete temp2;
//	delete temp3;
//
//	// Problem 4 test
//	temp1 = new TGA("layer2.tga");
//	temp2 = new TGA("circles.tga");
//	temp1->multiply(*temp2);
//
//	temp3 = new TGA("pattern2.tga");
//	temp1->subtract(*temp3);
//	temp1->writeData("output/", "problem4_test.tga");
//
//	delete temp1;
//	delete temp2;
//	delete temp3;
//
//	// Test overlay function
//	temp1 = new TGA("layer1.tga");
//	temp2 = new TGA("pattern1.tga");
//	temp1->overlay(*temp2);
//	temp1->writeData("output/", "overlay_test.tga");
//
//	delete temp1;
//	delete temp2;
//
//	// Test colorAdjust again with problem 6
//	temp1 = new TGA("car.tga");
//	temp1->colorAdjust(0, 200, 0);
//	temp1->writeData("output/", "problem6_test.tga");
//	delete temp1;
//
//	// Test colorScale again with problem 7
//	temp1 = new TGA("car.tga");
//	temp1->colorScale(0, 1, 4);
//	temp1->writeData("output/", "problem7_test.tga");
//	delete temp1;
//
//	// Test copyChannels() with problem 8
//	TGA* temp4;
//	temp1 = new TGA("car.tga");
//	temp2 = temp1->splitChannel(TGA::preset::BLUE);
//	temp3 = temp1->splitChannel(TGA::preset::GREEN);
//	temp4 = temp1->splitChannel(TGA::preset::RED);
//
//	temp2->writeData("output/", "problem8_b_test.tga");
//	temp3->writeData("output/", "problem8_g_test.tga");
//	temp4->writeData("output/", "problem8_r_test.tga");
//
//	delete temp1, temp2, temp3, temp4;
//
//	// Test addChannels() with problem 9
//	temp2 = new TGA("layer_blue.tga");
//	temp3 = new TGA("layer_green.tga");
//	temp4 = new TGA("layer_red.tga");
//	temp1 = new TGA(temp2->getWidth(), temp2->getHeight());
//
//	temp1->addChannels(*temp2, *temp3, *temp4);
//	temp1->writeData("output/", "problem9_test.tga");
//	delete temp1, temp2, temp3, temp4;
//
//	// Test rotate180() with problem 10
//	temp1 = new TGA("text2.tga");
//
//	temp1->rotate180();
//	temp1->writeData("output/", "problem10_test.tga");
//
//	delete temp1;
//
//	// Test extra credit
//	temp1 = new TGA("car.tga");
//	temp2 = new TGA("circles.tga");
//	temp3 = new TGA("pattern1.tga");
//	temp4 = new TGA("text.tga");
//	TGA* temp5 = new TGA(temp1->getWidth() * 2, temp1->getHeight() * 2);
//
//	temp5->overwrite(0, temp1->getHeight(), 0, temp1->getWidth(), *temp4);
//	temp5->overwrite(0, temp1->getHeight(), temp1->getWidth(), temp1->getWidth() * 2, *temp3);
//	temp5->overwrite(temp1->getHeight(), temp1->getHeight() * 2, 0, temp1->getWidth(), *temp1);
//	temp5->overwrite(temp1->getHeight(), temp1->getHeight() * 2, temp1->getWidth(), temp1->getWidth() * 2, *temp2);
//
//	temp5->writeData("output/", "extracredit_test.tga");
//	
//	delete temp1, temp2, temp3, temp4, temp5;
//}

unsigned int test(unsigned int count, string exampleName, string actualName) {
	TGA actual(actualName, "output/");
	TGA example(exampleName, "examples/");

	if (actual.getHeight() != example.getHeight() && actual.getWidth() != example.getWidth()) {
		cout << "Test #" << count << "...... Failed!" << endl << endl;
		return 0;
	}
	for (unsigned int i = 0; i < actual.pixels.size(); i++) {
		for (unsigned int j = 0; j < actual.pixels[i]->size(); j++) {
			TGA::Pixel& actualPixel = *(actual.pixels[i]->at(j));
			TGA::Pixel& examplePixel = *(example.pixels[i]->at(j));

			if (actualPixel.blue != examplePixel.blue ||
				actualPixel.green != examplePixel.green ||
				actualPixel.red != examplePixel.red) 
			{
				cout << "Test #" << count << "...... Failed!" << endl << endl;
				return 0;
			}
		}
	}
	cout << "Test #" << count << "...... Passed!" << endl << endl;
	return 1;
}

int main() {
	// Task 1
	TGA* temp1 = new TGA("layer1.tga");
	TGA* temp2 = new TGA("pattern1.tga");
	temp2->multiply(*temp1);
	temp2->writeData("output/", "part1.tga");
	delete temp1, temp2;

	// Task 2
	temp1 = new TGA("layer2.tga");
	temp2 = new TGA("car.tga");
	temp2->subtract(*temp1);
	temp2->writeData("output/", "part2.tga");
	delete temp1, temp2;

	// Task 3
	temp1 = new TGA("layer1.tga");
	temp2 = new TGA("pattern2.tga");
	temp1->multiply(*temp2);

	TGA* temp3 = new TGA("text.tga");

	temp3->screen(*temp1);
	temp3->writeData("output/", "part3.tga");

	delete temp1, temp2, temp3;

	// Task 4
	temp1 = new TGA("layer2.tga");
	temp2 = new TGA("circles.tga");
	temp1->multiply(*temp2);

	temp3 = new TGA("pattern2.tga");
	temp1->subtract(*temp3);
	temp1->writeData("output/", "part4.tga");

	delete temp1, temp2, temp3;

	// Task 5
	temp1 = new TGA("layer1.tga");
	temp2 = new TGA("pattern1.tga");
	temp1->overlay(*temp2);
	temp1->writeData("output/", "part5.tga");

	delete temp1, temp2;

	// Task 6
	temp1 = new TGA("car.tga");
	temp1->colorAdjust(0, 200, 0);
	temp1->writeData("output/", "part6.tga");
	delete temp1;

	// Task 7
	temp1 = new TGA("car.tga");
	temp1->colorScale(0, 1, 4);
	temp1->writeData("output/", "part7.tga");
	delete temp1;

	// Task 8
	TGA* temp4;
	temp1 = new TGA("car.tga");
	temp2 = temp1->splitChannel(TGA::preset::BLUE);
	temp3 = temp1->splitChannel(TGA::preset::GREEN);
	temp4 = temp1->splitChannel(TGA::preset::RED);

	temp2->writeData("output/", "part8_b.tga");
	temp3->writeData("output/", "part8_g.tga");
	temp4->writeData("output/", "part8_r.tga");

	delete temp1, temp2, temp3, temp4;

	// Task 9
	temp2 = new TGA("layer_blue.tga");
	temp3 = new TGA("layer_green.tga");
	temp4 = new TGA("layer_red.tga");
	temp1 = new TGA(temp2->getWidth(), temp2->getHeight());

	temp1->addChannels(*temp2, *temp3, *temp4);
	temp1->writeData("output/", "part9.tga");
	delete temp1, temp2, temp3, temp4;

	// Task 10
	temp1 = new TGA("text2.tga");

	temp1->rotate180();
	temp1->writeData("output/", "part10.tga");

	delete temp1;

	// Extra credit
	temp1 = new TGA("car.tga");
	temp2 = new TGA("circles.tga");
	temp3 = new TGA("pattern1.tga");
	temp4 = new TGA("text.tga");
	TGA* temp5 = new TGA(temp1->getWidth() * 2, temp1->getHeight() * 2);

	temp5->overwrite(0, temp1->getHeight(), 0, temp1->getWidth(), *temp4);
	temp5->overwrite(0, temp1->getHeight(), temp1->getWidth(), temp1->getWidth() * 2, *temp3);
	temp5->overwrite(temp1->getHeight(), temp1->getHeight() * 2, 0, temp1->getWidth(), *temp1);
	temp5->overwrite(temp1->getHeight(), temp1->getHeight() * 2, temp1->getWidth(), temp1->getWidth() * 2, *temp2);

	temp5->writeData("output/", "extracredit.tga");

	delete temp1, temp2, temp3, temp4, temp5;

	unsigned int successCount = 0;
	successCount += test(1, "EXAMPLE_part1.tga", "part1.tga");
	successCount += test(2, "EXAMPLE_part2.tga", "part2.tga");
	successCount += test(3, "EXAMPLE_part3.tga", "part3.tga");
	successCount += test(4, "EXAMPLE_part4.tga", "part4.tga");
	successCount += test(5, "EXAMPLE_part5.tga", "part5.tga");
	successCount += test(6, "EXAMPLE_part6.tga", "part6.tga");
	successCount += test(7, "EXAMPLE_part7.tga", "part7.tga");
	successCount += test(8, "EXAMPLE_part8_b.tga", "part8_b.tga");
	successCount += test(9, "EXAMPLE_part8_g.tga", "part8_g.tga");
	successCount += test(8, "EXAMPLE_part8_r.tga", "part8_r.tga");
	successCount += test(11, "EXAMPLE_part9.tga", "part9.tga");
	successCount += test(12, "EXAMPLE_part10.tga", "part10.tga");
	successCount += test(13, "EXAMPLE_extracredit.tga", "extracredit.tga");
	
	cout << "Test results: " << successCount << " / 13" << endl;

	return 0;
}