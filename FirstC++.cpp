#include <iostream>
#include <array>
#include <string>
#include <cstdlib> 
using namespace std; // TO SELF - AVOID USING NAMESPACE IN LARGE PROJECTS (naming conflicts)

/// <summary>
/// Print gathered information
/// </summary>
/// <param name="Info">Array of info</param>
void PrintInfo(const array<string, 3>& Info) {
	system("cls");
	for (int i = 0; i < 3; i++)
	{
		cout << Info[i] << endl; // print each instance of info on a new line
	}
}
/// <summary>
/// Simple verification of information based on formatting criteria
/// </summary>
/// <param name="Info">Array of information gathered</param>
/// <returns>All informations verification</returns>
bool VerifyInfo(const array<string, 3>& Info) {
	short Addresses = 0; // Amount of @ symbols 
	short Domains = 0; // Amount of periods after the @
	short Errors = 0; // Non email ralated errors (does not return on error for testing purposes)
	system("cls");
	for (const char& c : Info[0]) { // Checks the name for out of place digits
		if (isdigit(c)) {
			cerr << "Error: Name Invalid" << endl;
			Errors++;
			break;
		}
	}
	for (const char& digits : Info[1]) { // Checks phone number for size, verifies all chars are digits
		if (!isdigit(digits) || Info[1].size() != 10) {
			cerr << "Error: Invalid number (format - 1234567890)" << endl;
			Errors++;
			break;
		}
	}
	for (const char& c : Info[2]) { // Checks email for validity issues
		
		if (c == '@') { // Checks for an @ symbol (MUST HAVE 1)
			if (Addresses > 1) {
				cerr << "Error: Invalid Email (format - email@address.com)" << endl;
				return false;
			}
			Addresses++;
		}
		else if (c == '.' && Addresses > 0) { // Checks for periods after the @ (must only be one)
			if (Domains > 1) {
				cerr << "Error: Invalid Email (format - email@address.com)" << endl;
				return false;
			}
			Domains++;
		}
	}
	size_t found = Info[2].find(".com"); // Searches for the keyword ".com"
	if (Addresses < 1 || Domains < 1 || found == std::string::npos){
		cerr << "Error: Invalid Email (format - email@address.com)" << endl;
		return false;
	}
	else if (Errors > 0) { // Returns at the end so each error can be printed
		return false;
	}
	return true;
}
/// <summary>
/// Asks questions to gather contact information
/// </summary>
/// <returns>Array of contact information gathered</returns>
array<string, 3> GetContactInfo() {
	array<string, 3> questions = { "Name", "Phone Number", "Email" };
	array<string, 3> Info;
	for (int i = 0; i < questions.size(); i++) { // asks a question for each question in array
		cout << "What is your " << questions[i] << endl;
		getline(cin, Info[i]); // retrieve information
	}
	return Info;
}

int main() {
	const array<string, 3> GatheredInfo = GetContactInfo();
	if (VerifyInfo(GatheredInfo)) {
		PrintInfo(GatheredInfo);
	}
}

/*
		* Notes to self
	* C++ only does a ONE PASS PRECOMPILE - functions must be declared above any function calls
	* << and >> are used to "pass" information ex: cout << "string" << endl;
	* cout is used for common console prints is buffered
	* cerr is used for important info/errors - is unbuffered (it is not delayed)
	* cin is in ralation to user keyboard input ex: cin.ignore() will ignore inputs into the console/wait for specific input
	* C++ does not auto manage memory/system resources (study how to use class destructors effectively)
	* C++ foreach loops are formatted as: for (var : collection) {}
	* Arrays are fixed size - Vectors are unfixed
	* C style strings are char arrays ex: char[] String;
	* C++ does not come with many built in librarys
	* C++ is a "low-level" language - is not as user friendly to code in as C#
	* switch does not work with anything except int/enums
	* looks deceptivly similar to C#
*/