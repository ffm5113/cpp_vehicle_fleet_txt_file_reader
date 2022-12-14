// Vehicle IDs were randomly generated for academic purposes 
// Source(s) of logic assistance:  
// Gaddis, T. (2018). Starting out with C++: From control structures through objects. Pearson. 
//
// https://docs.microsoft.com/en-us/troubleshoot/developer/visualstudio/cpp/libraries/stl-sqrt-pow-functions
// https://docs.microsoft.com/en-us/cpp/standard-library/iomanip-functions?view=msvc-170

#include <iostream> // To use cin/cout
#include <iomanip>  // To access setw for output width
#include <string>   // To implement to_string() & length() functions
#include <fstream>  // To utilize ifstream, ofstream, fstream
using namespace std;

// Constant Variable Initialization
const string TITLE = "Fleet TXT File Input Program", AUTHOR_LINE = "By Forrest Moulin";

const string TABLE_TITLE = "Forrest's Green Vehicle Fleet Report";
const string TABLE_HEAD1 = "Vehicle ID", TABLE_HEAD2 = "Miles";
const string TABLE_HEAD3 = "Gallons", TABLE_HEAD4 = "MPG ";

const string COUNT_STR = "Fleet Count:", MILES_STR = "Total Miles:", MPG_STR = "Average MPG:";
const string BEST_STR = "Vehicle ID - Best MPG:";
const string WORST_STR = "Vehicle ID - Worst MPG:";

const int COL_GAP = 3;
// COL1: Vehicle ID, COL2: Miles, COL3: Gallons, COL4: MPG, COL5: WORST_STR
const int COL1_WIDTH = TABLE_HEAD1.length() + COL_GAP, COL2_WIDTH = TABLE_HEAD2.length() + COL_GAP;
const int COL3_WIDTH = TABLE_HEAD3.length() + COL_GAP, COL4_WIDTH = TABLE_HEAD4.length() + COL_GAP;
const int COL5_WIDTH = WORST_STR.length() + COL_GAP;
const int TABLE_WIDTH = COL1_WIDTH + COL4_WIDTH + COL5_WIDTH;

int main()
{
	// Dynamic Variable Initialization
	int fleetCount = 0;
	double miles, gal, avgMPG, worstMPG = 0.0, bestMPG = 0.0,
		 totalMiles = 0.0, totalGal = 0.0, fleetAvgMPG;
	string vehicleID, worstMPGStr, bestMPGStr, rowDivider = "-";

	string filePath = "C:\\Users\\UserName\\Path\\To\\File.txt";
	// Create ifstream object to read the text file
	ifstream inputFile;

	inputFile.open(filePath);
	if (inputFile.fail())
	{
		cout << "File open failure:" << endl
			<< filePath << endl;
		// Redudant measure to ensure file is closed
		inputFile.close();
		// End program in the event of file loading failure
		return 0;
	}

	// Format the row dividers to the proper width
	while (rowDivider.length() < TABLE_WIDTH)
	{
		rowDivider += "-";
	}
	// Program Logic/Output with double precision fixed to 1 decimal
	cout << fixed << setprecision(1)
		<< TITLE << endl << AUTHOR_LINE << endl << endl
		// Table output
		<< right << setw((TABLE_WIDTH - TABLE_TITLE.length()) / 2 + TABLE_TITLE.length())
		<< TABLE_TITLE << endl << rowDivider << endl 
		<< left << setw(COL1_WIDTH) << TABLE_HEAD1 
		<< left << setw(COL2_WIDTH) << TABLE_HEAD2 
		<< left << setw(COL3_WIDTH) << TABLE_HEAD3
		<< left << setw(COL4_WIDTH) << TABLE_HEAD4 
		<< endl << rowDivider << endl;
	// While there are lines to read in the file,
	// set the variables to the read values.
	while (inputFile >> vehicleID >> miles >> gal)
	{
		// Calculate MPG and add values to totals
		avgMPG = miles / gal;
		totalGal += gal;
		totalMiles += miles;
		fleetCount++;
		
		// 1st iteration sets the floor for worst MPG
		if (fleetCount == 1)
		{
			worstMPG = avgMPG;
		}
		// Find worst MPG
		if (avgMPG < worstMPG)
		{
			worstMPG = avgMPG;
			worstMPGStr = vehicleID;
		}
		// Find best MPG
		if (avgMPG > bestMPG)
		{
			bestMPG = avgMPG;
			bestMPGStr = vehicleID;
		}
		// Print the read variables found on each line
		// as well as the calculated MPG
		cout << left << setw(COL1_WIDTH) << vehicleID
			<< left << setw(COL2_WIDTH) << miles
			<< left << setw(COL3_WIDTH) << gal
			<< left << setw(COL4_WIDTH) << avgMPG
			<< endl;
	}
	// Close the file once all lines are read
	inputFile.close();
	// Calculate average mpg of the fleet
	fleetAvgMPG = totalMiles / totalGal;

	// Print fleet summary to console
	cout  << rowDivider << endl
		<< left << setw(COL5_WIDTH) << COUNT_STR << fleetCount << endl
		<< left << setw(COL5_WIDTH) << MILES_STR << totalMiles << endl
		<< left << setw(COL5_WIDTH) << MPG_STR << fleetAvgMPG << endl
		
		<< left << setw(COL5_WIDTH) << WORST_STR 
		<< left << setw(COL1_WIDTH) << worstMPGStr
		<< left << setw(COL4_WIDTH) << worstMPG << endl
		
		<< left << setw(COL5_WIDTH) << BEST_STR
		<< left << setw(COL1_WIDTH) << bestMPGStr 
		<< left << setw(COL4_WIDTH) << bestMPG << endl
		<< rowDivider << endl;
}
/*
* CONSOLE OUTPUT
* By Forrest Moulin
*
*      Forrest's Green Vehicle Fleet Report
* ----------------------------------------------
* Vehicle ID   Miles   Gallons   MPG
* ----------------------------------------------
* 279BX6KY2Z   582.2   20.5      28.4
* 802MX8BZ4Q   723.6   25.1      28.8
* 671AY6DZ3N   756.9   27.5      27.5
* 845DH6AJ3B   660.2   25.4      26.0
* 566GJ6KV2U   510.2   30.8      16.6
* 109QW2RP2Y   301.2   8.3       36.3
* 135TR4YC6H   387.6   12.2      31.8
* 122AC6UG7P   228.9   14.7      15.6
* 136VW8TD2Z   331.2   19.1      17.3
* 448WQ2DX1M   543.9   33.6      16.2
* 721GZ1LJ5N   629.8   27.9      22.6
* 779FS3MB4Y   651.2   28.4      22.9
* 553SB5LK8O   444.4   26.8      16.6
* ----------------------------------------------
* Fleet Count:              13
* Total Miles:              6751.3
* Average MPG:              22.5
* Vehicle ID - Worst MPG:   122AC6UG7P   15.6
* Vehicle ID - Best MPG:    109QW2RP2Y   36.3
* ----------------------------------------------
*/
