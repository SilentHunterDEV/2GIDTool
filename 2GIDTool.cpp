// iPhone 2G ID Tool v1.0
// This tool will provide info about an iPhone 2G based on serial number
// Idea credited to u/random_user_online
// Initial code credited to u/randomNinja64

#include <iostream>
#include <string>

using namespace std;

void importSerial(char serialNumber[11]); // This function will write the desired serial number to the array "serialNumber"
void displaySerial(char serialNumber[11]); // This function will print the serial number of the device
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

	std::cout << "iPhone2G ID Tool - iPhone v1.0\n" << std::endl;
	std::cout << "This utility will output basic information about an iPhone 2G based on its serial number\n" << std::endl;
	std::cout << "Please input your iPhone's Serial number.\n" << "Serial: \n" << std::endl;
	importSerial(serialNumber); // Prompt the user for the Serial number

	prodWeek = productionWeek(serialNumber); // calculate the production week
	prodYear = productionYear(serialNumber); // calculate the production year

	std::cout << "Device information:\n" << std::endl;
	displayInfo(serialNumber, prodWeek, prodYear);

	std::cout << "Press enter to exit.\n" << std::endl;
	cin.get();
	return 0;
}

void importSerial(char serialNumber[11]) {  // This function will write the desired serial number to the array "serialNumber"
	for (int i = 0; i < 11; i++) { // For loop to fill character array with serial number
		cin >> serialNumber[i];
	}
}

void displaySerial(char serialNumber[11]) { // This function will print the serial number of the device
	std::cout << "Serial Number: " << std::endl;
	for (int i = 0; i < 11; i++) { // For loop to print serial number
		std::cout << serialNumber[i] << std::endl;
	}
}

void displayInfo(char serialNumber[11], int prodWeek, int prodYear) { // This function will print device info
	displaySerial(serialNumber); // Print the devices serial number
	cout << "\n";

	if (prodWeek == 0 || prodYear == 0) { // Check if serial is valid by making sure that productionWeek did not return 0
		std::cout << "Error: Invalid or Unknown Serial number. If you believe this is in error, please contact u/randomNinja64\n " << std::endl;
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
		return 0; // Program will return an error
	}
	else {

	return week;

	}
}

int productionYear(char serialNumber[11]) { //This function will return the production year of an iPhone
	switch ((static_cast <int> (serialNumber[2]) - 48)) //convert third digit in serial number from ascii character to int
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
	if ((prodWeek >= 45 && prodYear == 2007) || (prodYear == 2008)) { //if production week 45 or above and production year is 2007, or if production year is 2008, bootloader us 4.6
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
