#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include <ctime>
#include <iomanip> // For fixed and setprecision

using namespace std;
using namespace chrono;

class SensorDataLogger {
private:
    ofstream fileStream;
    double temperature = 0.00;
    double humidity = 0.00;
    double co2 = 0.00;
    string timeStamp;

public:
    // Constructor: Opens the CSV file for appending
    SensorDataLogger(string fileName, bool writeHeader = false) {
        fileStream.open(fileName, ios::app);
        if (!fileStream.is_open()) {
            throw runtime_error("Unable to open file for writing");
        }

        // Write header if the file is empty
        if (writeHeader && fileStream.tellp() == 0) { // Check if the file is empty
            fileStream << "LoopCount,Timestamp,Temperature,Humidity,CO2\n";
        }
    }

    // Destructor: Closes the file when the object is destroyed
    ~SensorDataLogger() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

    // Read sensor data - Simulates sensor readings
    void readSensors() {
        timeStamp = getCurrentTimestamp();
        temperature = generateRandomNumber();
        humidity = generateRandomNumber();
        co2 = generateRandomNumber();
    }

    // Generate random numbers for sensor values
    double generateRandomNumber() {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> distr(0, 100); // Generate double values between 0 and 100
        return distr(gen);
    }

    // Logs the sensor values to the file in a single line with reduced decimals
    void logData(int loopCount) {
        if (fileStream.is_open()) {
            fileStream << loopCount << ","
                << timeStamp << ","
                << fixed << setprecision(0) // Reduce to 2 decimal places
                << temperature << ","
                << humidity << ","
                << co2 << "\n";
        }
        else {
            cerr << "Failed to write data to the file." << endl;
        }
    }

    // Combines reading sensors and logging data
    void run(int loopCount) {
        readSensors();
        logData(loopCount);
        cout << "Data logged successfully!" << endl;
    }

    // Get current timestamp as a formatted string
    string getCurrentTimestamp() {
        auto now = system_clock::now();
        time_t now_time = system_clock::to_time_t(now);
        string timeStr = ctime(&now_time); // Convert to local time
        timeStr.pop_back();               // Remove trailing newline
        return timeStr;
    }
};

int main() {
    try {
        int loopCount = 0;
        int i = 1;

        cout << "Enter the Loop Counter Value: (Enter -1 to STOP Program)" << endl;
        cin >> loopCount;

        // Initialize the logger with a .csv file
        SensorDataLogger logger("C:\\File\\sensor_dataa.csv", true); // Write header if needed

        while (loopCount != -1) {
            logger.run(i); // Log data
            loopCount--;

            if (loopCount > 0) {
                cout << "Remaining iterations: " << loopCount << endl;
            }
            else {
                cout << "Enter the Loop Counter Value: (Enter -1 to STOP Program)" << endl;
                cin >> loopCount;
            }
            i++;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
