#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

class ReadCsv {
public:
    std::string file_path = "../../Data/Monza_raceline.csv";

private:
    float x_;
    float y_;
    float yaw_;
    std::ifstream fin_;

public:
    // Constructor
    ReadCsv() : x_(0.0f), y_(0.0f), yaw_(0.0f) {
        fin_.open(file_path);
        if (!fin_.is_open()) {
            std::cerr << "Error opening the file." << std::endl;
        }
    }

    // Destructor to close the file
    ~ReadCsv() {
        if (fin_.is_open()) {
            fin_.close();
        }
    }

    // Function to get the next line from the CSV file and parse the columns
        // Function to get the next valid data line from the CSV file and parse the columns
    bool getLine() {
        std::string line, element;
        while (std::getline(fin_, line)) {
            if (line.empty() || line[0] == '#') {
                // Skip empty lines and comment lines
                continue;
            }

            std::stringstream s(line);
            std::vector<std::string> row;

            while (std::getline(s, element, ',')) {
                row.push_back(element);
            }

            if (row.size() >= 3) { // Ensure that there are enough columns
                // Parse the columns and set member variables
                x_ = std::stof(row[1]);   // Assuming x_m is at index 1
                y_ = std::stof(row[2]);   // Assuming y_m is at index 2
                yaw_ = std::stof(row[3]); // Assuming psi_rad is at index 3

                return true; // Successfully read and parsed the line
            }
        }

        return false; // Failed to read or parse a valid data line
    }

    // Getter functions for x_, y_, and yaw_
    float getX() const { return x_; }
    float getY() const { return y_; }
    float getYaw() const { return yaw_; }
};

int main() {
    ReadCsv reader;

    // Read and print the values of x_, y_, and yaw_ for each valid data line in the CSV file
    while (reader.getLine()) {
        std::cout << "x: " << reader.getX() << ", y: " << reader.getY() << ", yaw: " << reader.getYaw() << std::endl;
        
    }

    return 0;
}