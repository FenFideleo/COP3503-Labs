/*  Lab 1: Data Visualization
*   
*   Student: Erik Meurrens
*   
*   Notes:
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    string userInput = "";  // Stores all user input

    // Prompt user for title of data
    string titleTable = "";
    cout << "Enter a title for the data:" << endl;
    getline(cin, userInput);
    titleTable = userInput;
    cout << "You entered: " << titleTable << endl;

    // Prompt user for headers of two table columns
    string headers[2] = { "", "" }; // Create array for two column headers

    for (int i = 1; i <= 2; i++) {
        cout << "Enter the column " << i << " header:" << endl;
        getline(cin, userInput);
        headers[i - 1] = userInput;
        cout << "You entered: " << userInput << endl;
    }

    // Prompt user for data points until -1 for input
    // Use loop that continues iterating until -1 is received

    bool enteringData = true;   // Controls loop
    vector<string> stringData;  // Vector stores user string data
    vector<int> intData;    // Vector stores user int data

    {
        int i = 0;  // Want local variable to count loop iterations
        while (enteringData) {
            cout << "Enter a data point (-1 to stop input):" << endl;
            getline(cin, userInput);
            try {
                if (stoi(userInput) == -1) {
                    break;
                }
            }
            catch (invalid_argument& ignored) {}

            int commaCount = 0;         // Keeps track of comma count in user input
            int lastCommaIndex = -1;    // Tracks last comma index

            // Validate userInput string
                // Checks comma count in user input
                for (int index = 0; index < userInput.length(); index++) {
                    if (userInput.at(index) == ',') {
                        commaCount++;
                        lastCommaIndex = index;
                    }
                }
                // Checks for errors
                if (commaCount == 0) {
                    cout << "Error: No comma in string." << endl;
                    continue;
                }
                else if (commaCount > 1) {
                    cout << "Error: Too many commas in input." << endl;
                    continue;
                }
                else {
                    try {
                        stoi(userInput.substr(lastCommaIndex + 1, userInput.length()));
                    }
                    catch (invalid_argument e) {
                        cout << "Error: Comma not followed by an integer." << endl;
                        continue;
                    }
                }
            
            // Add vector spaces to fit data
            stringData.resize(i + 1);
            intData.resize(i + 1);
            // Store data into respective vectors
            stringData.at(i) = userInput.substr(0, lastCommaIndex);
            intData.at(i) = stoi(userInput.substr(lastCommaIndex + 1, userInput.length()));
            // Print data
            cout << "Data string: " << stringData.at(i) << endl;
            cout << "Data integer: " << intData.at(i) << endl;
            
            i++; // increment iterator
        }                                   // End local iterator scope

        cout << endl;

        // Print data table
            // Print title and headers
            cout << setw(33) << titleTable << endl;             // Prints table title
            cout << left << setw(20) << headers[0] << "|";      // Prints left column header
            cout << right << setw(23) << headers[1] << endl;    // Prints right column header
            cout << setfill('-') << setw(44) << "" << endl;     // Prints horizontal table divider
            cout << setfill(' ');

            // Prints data, iterating through data vectors
            for (int i = 0; i < stringData.size(); ++i) {
                cout << left << setw(20) << stringData.at(i) << "|";    // Print stringData element
                cout << right << setw(23) << intData.at(i) << endl;     // Prints intData element
            }

            cout << endl;   // Create space between table and histogram

        // Print formatted histogram
            for (int i = 0; i < stringData.size(); ++i) {
                cout << right << setw(20) << stringData.at(i) << " ";               // Print stringData element
                cout << left << setfill('*') << setw(intData.at(i)) << "";           // Print '*' intData(i) times
                if (i < stringData.size() - 1) {
                    cout << endl;
                }
                cout << setfill(' ');
            }
            cout << endl;

        return 0;   // End program
        
    }
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
