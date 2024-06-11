// iPhone 2G ID Tool v1.1
// This tool will provide info about an iPhone 2G based on serial number
// Idea credited to u/SilentHunterDEV
// Initial code developed by u/SilentHunterDEV & u/BJNFNE

#include <iostream>
#include <string>

using namespace std;

void importSerialNumber(char serialNumber[11]); // This function will write the desired serial number to the array "serialNumber"
void displaySerialNumber(char serialNumber[11]); // This function will print the serial number of the device
void displayInfo(char serialNumber[11], int prodWeek, int prodYear); // This function will print device info
int productionWeek(char serialNumber[11]); // This function will return the production week of an iPhone
int productionYear(char serialNumber[11]); // This function will return the production year of an iPhone
float distgunishBootLoader(int prodWeek, int prodYear); // This function wll return bootloader based on production week and year
string calcMinOS(int prodWeek, int prodYear); // This function will return minimum OS version
string prodWeekToMonth(int prodWeek); // This function will convert production week to month
	
	int main() {
	char serialNumber[11] = { '0' }; // 11 character long array to store iPhone 2G serial number
	int prodWeek = 0; // Create an int to store production week
	int prodYear = 0; // Create an int to store production year
		
	std::cout << "\b" << std::endl; // This Line is added for make space between Console before execution of 2GIDTool

	std::cout << "iPhone2G ID Tool - iPhone v1.1\n" << std::endl;
	std::cout << "This Utility will output basic information about an iPhone 2G based on its serial number\n" << std::endl;
	std::cout << "Please input your iPhone's Serial number.\n" << "" << std::endl;
	importSerialNumber(serialNumber); // Prompt the user for the Serial number

	prodWeek = productionWeek(serialNumber); // calculate the production week
	prodYear = productionYear(serialNumber); // calculate the production year

	std::cout << "\b" << std::endl; // This newline is for to between space for Device information and entered serial number

	std::cout << "Device information: \n" << std::endl;
	displayInfo(serialNumber, prodWeek, prodYear);

	std::cout << "Press enter to exit.\b" << std::endl;
	std::cin.get();
	std::cout << "Have a nice day!\n" << std::endl;
	std::cout << " - 2GIDTool Team\n" << std::endl;
	return 0;
}

void importSerialNumber(char serialNumber[11]) {
    bool validInput = false;
    while (!validInput) {
        std::cout << "Enter the serial number (11 characters): \b" << std::endl;
        string input_serialnumber;
        getline(cin, input_serialnumber);

        if (input_serialnumber.length() == 0) {
            std::cout << "Error: Serial number cannot be empty.\n" << std::endl;
        } else if (input_serialnumber.length() != 11) {
            std::cout << "Error: Serial number must be 11 characters long.\n" << std::endl;
        } else {
            for (int i = 0; i < 11; i++) {
                serialNumber[i] = input_serialnumber[i];
            }
            validInput = true;
        }
    }
}

void displaySerialNumber(char serialNumber[11]) { // This function will print the serial number of the device
    std::cout << "Serial Number: ";
    for (int i = 0; i < 11; i++) {
        std::cout << serialNumber[i];
    }
    std::cout << std::endl;
}

void InvalidErrorHandler() {
	std::cout << "Error: Invalid or unknown Serial number.\n " << std::endl;
	std::cout << "If you believe this is in error, Please contact SilentHunterDEV or BJNFNE on Discord over an Direct Message.\n";
	std::cout << "If the Desktop application don't work for you, Please consider then to try out our Web based application of 2GIDTool\n";
	return;
}

void displayInfo(char serialNumber[11], int prodWeek, int prodYear) { // This function will print device info
	displaySerialNumber(serialNumber); // Print the devices serial number
	cout << "\n";

	if (prodWeek == 0 || prodYear == 0) { // Check if serial is valid by making sure that productionWeek did not return 0
		InvalidErrorHandler();
		return;
	}
	else {
		std::cout << "Production Week: " << prodWeek << "\n" << std::endl; // print production week
		std::cout << "Production Month / Year: " << prodWeekToMonth(prodWeek) << " " << prodYear << "\n" << std::endl; // print production year
	}

	std::cout << "Original Bootloader Version: " << distgunishBootLoader(prodWeek, prodYear) << "\n" << std::endl;  // use distgunishBootLoader to distgunish bootloader version
	std::cout << "Minimum OS Version: " << calcMinOS(prodWeek, prodYear) << "\n" << std::endl; // use calcMinOS to determine minimum OS version
}

int productionWeek(char serialNumber[11]) { // This function will return the production week of an iPhone
	int week = 0; // integer to store production week

	// use static_cast int - 48 to convert from ascii character value to int
	week = ((static_cast <int> (serialNumber[3]) - 48) * 10) + (static_cast <int> (serialNumber[4]) - 48);
	
	if (week > 52 || week <= 0) {
		return 0;
	}
	else {

	return week;

	}
}

int productionYear(char serialNumber[11]) { // This function will return the production year of an iPhone
	switch ((static_cast <int> (serialNumber[2]) - 48)) // convert third digit in serial number from ascii character to int
	{
	
	case 7:
	return 2007; // if digit 3 is 7, production year is 2007
	
	case 8: 
	return 2008; // if digit 3 is 8, production year is 2008
	
	default:
	return 0; // if neither, return 0 causing an error
	}
}

float distgunishBootLoader(int prodWeek, int prodYear) { // This function wll return bootloader based on production week and year
	if ((prodWeek >= 45 && prodYear == 2007) || (prodYear == 2008)) { // If production week 45 or above and production year is 2007, or if production year is 2008, bootloader us 4.6
		return 4.6;
	}
	else {
	return 3.9;
	}
}

string calcMinOS(int prodWeek, int prodYear) { // This function will return minimum OS version
	if (prodWeek <= 48 && prodYear == 2007) {
		return "Firmware 1.0";
	}
	else {

	return "Firmware 1.1.1";
	
	}
}

string prodWeekToMonth(int prodWeek) { // This function will convert production week to month
	if (prodWeek <= 5) {
	return "January";
	}
	if (prodWeek <= 9) {
	return "February";
	}
	if (prodWeek <= 13) {
	return "March";
	}
	if (prodWeek <= 18) {
	return "April";
	}
	if (prodWeek <= 22) {
	return "May";
	}
	if (prodWeek <= 26) {
	return "June";
	}
	if (prodWeek <= 31) {
	return "July";
	}
	if (prodWeek <= 35) {
	return "August";
	}
	if (prodWeek <= 39) {
	return "September";
	}
	if (prodWeek <= 44) {
	return "October";
	}
	if (prodWeek <= 48) {
	return "November";
	}
	if (prodWeek <= 52) {
	return "December";
	}
	else {
	return "Unknown";
	}
	return 0;
} // End of namespace
