#include <iostream>
// File handling operation in C++
#include <fstream>
// lib for string manipulation
#include <string>
// lib for random number generartion 
#include <random>
// lib for timestamp
#include <chrono>
#include <ctime>
#include <vector>
using namespace std;
using namespace chrono;


// Class initiated 
class SensorDataLogger {
	// data encapsulation : information hiding
private:
	fstream fileStream;
	double temperature = 0.00;
	double humidity = 0.00;
	double co2 = 0.00;
	string timeStamp = {};

public:
	//Constructor : Opens the file for logging.
	SensorDataLogger(string fileName) {
		fileStream.open(fileName, ios::out | ios::app);
		if (!fileStream.is_open()) {
			throw runtime_error("Unable to open file for writing and appending");
		}		
	}

	// Destructor - Closes the file when the object is destroyed.
	~SensorDataLogger() {
		if (fileStream.is_open()) {
			fileStream.close();
		}
	}
	// Read sensor data - Simulates reading sensor values.
	void readSensors() {		
		timeStamp = getCurrentTimestamp();
		temperature = RandomNumberGeneratorbetween1to100();
		humidity = RandomNumberGeneratorbetween1to100();
		co2 = RandomNumberGeneratorbetween1to100();
	}
	// Randomly Generate Number
	int RandomNumberGeneratorbetween1to100() {
		// Create a random device and seed the random number generator
		// srandom_device is used to seed the random number generator, ensuring a different
		// seed each time the program runs.
		random_device rd;

		//mt19937 is a Mersenne Twister engine, which is a good choice for generating random numbers.
		mt19937 gen(rd());
		
		 //uniform_int_distribution<> ensures the numbers are uniformly distributed within
		 // the specified range(0 to 100).Define the range
		 uniform_int_distribution<> distr(0, 100);

		// Generate the random number
		int random_number = distr(gen);

		// program output
		return random_number;
	}
	// Logs the sensor values to the file.
	void logData(int loopCount) {		
		// // Error handling - always check if the file opened successfully
		if (fileStream.is_open()) {
			//fileStream << "-----------------------------------" << endl;			
			/*fileStream << "TimeStamp: " << timeStamp << endl;
			fileStream << "Count no: " << loopCount << endl;
			fileStream << "Temperature: " << temperature << endl;
			fileStream << "Humidity: " << humidity << endl;
			fileStream << "CO2: " << co2 << endl;*/
			fileStream << loopCount << "," << timeStamp << "," << temperature << ","
				<< humidity << "," << co2 << "\n";
			fileStream << "-----------------------------------"<< endl;
			fileStream.close();			
		}
		else
		{
			cerr << "Failed to open the file." << endl;
		}
	}
	// Combines reading sensors and logging data, and prints a success message.
	void run(int loopCount) {
		readSensors();
		logData(loopCount);
		cout << "Data logged successfully!" << endl;
	}
	// This method gets the current time using <chrono> and formats it as a string.
	string getCurrentTimestamp() {
		// Get the current time using system_clock
		auto now = system_clock::now();
		// converts this time point to a time_t object, 
		// which represents the time in seconds since the epoch.
		time_t now_time = system_clock::to_time_t(now);
		// return the local time
		return ctime(&now_time);
	}
}; // Class end

// Main method
int main() {
	try 
	{
		int loopCount = 0;
		int i = 1;
		cout << "Enter the Loop Counter Value: (Enter -1 for STOP Program)" << endl;
		cin >> loopCount ; // Take input from keyboard (User insert data)
		while (loopCount != -1) {
			SensorDataLogger logger("C:\\File\\sensor_data.csv");
			logger.run(i);
			loopCount--;
			if (loopCount == 1) {
				cout << "Enter the Loop Counter Value: (Enter -1 for STOP Program)" << endl;
				cin >> loopCount; // Take input from keyboard (User insert data)
			}
			i++;
		}	
	}
	catch (exception e) {
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}

/*
Key Points:

Unbuffered Output: Unlike std::cout, std::cerr is unbuffered, meaning it outputs messages immediately without storing them in a buffer. This is useful for error messages that need to be displayed right away12.
Flushing: Since std::cerr is unbuffered, it automatically flushes the output stream after each insertion operation2.
Usage: It's a good practice to use std::cerr for error messages and std::cout for regular output. This way, you can easily redirect error messages to a different output stream if needed3.

*/

/*
he code snippet #include <chrono> and #include <ctime> includes two C++ standard library headers that provide functionality for working with time and date.

#include <chrono>:

This header is part of the C++11 standard and provides a set of utilities to deal with time durations, clocks, and time points.
It includes classes like std::chrono::duration, std::chrono::time_point, and various clocks such as std::chrono::system_clock, std::chrono::steady_clock, and std::chrono::high_resolution_clock.
#include <ctime>:

This header is part of the C standard library and provides functions to manipulate and format calendar time and clock time.
It includes functions like std::time, std::difftime, std::mktime, and structures like std::tm.
*/