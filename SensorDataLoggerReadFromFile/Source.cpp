#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
	fstream myFile;
	myFile.open("C:\\File\\sensor_data.txt", ios::in);
	// Error handling - always check if the file opened successfully
	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			cout << line << endl;
		}
		myFile.close();
	}
	else
	{
		cerr << "Failed to open the file." << endl;
	}
	system("pause>0");

}