//These lines include necessary header files for input/output operations, manipulating the output format,
//and file input/output.
#include <iostream>
#include <iomanip>
#include <fstream>

//Constants are defined to represent the number of rows and columns in the theater.
const int NUM_ROWS = 5;
const int NUM_COLS = 10;

//A 2D array theater is declared to represent the seating arrangement in the theater.
char theater[NUM_ROWS][NUM_COLS];


//A function initializeTheater is defined to set all seats in the theater to
// an available state, represented by the character 'A'.
void initializeTheater() {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            theater[i][j] = 'A';
        }
    }
}

//The displayTheater function is responsible for showing the current seating
//arrangement in the theater, including row and column numbers and the status of each seat.
void displayTheater() {
    std::cout << "  ";
    for (int j = 0; j < NUM_COLS; j++) {
        std::cout << std::setw(3) << j + 1;
    }
    std::cout << "\n";

    for (int i = 0; i < NUM_ROWS; i++) {
        std::cout << char('A' + i) << " ";
        for (int j = 0; j < NUM_COLS; j++) {
            std::cout << "[" << theater[i][j] << "]";
        }
        std::cout << "\n";
    }
}

//A function bookTicket is defined to book a ticket for a
//specified seat if it's valid and available. It returns true if the booking is successful.
bool bookTicket(int row, int col) {
    if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) {
        std::cout << "Invalid seat selection.\n";
        return false;
    }
    if (theater[row][col] == 'X') {
        std::cout << "Seat already booked.\n";
        return false;
    }

    theater[row][col] = 'X';
    std::cout << "Ticket booked successfully!\n";
    return true;
}

//A function readTheaterFromFile is defined to read the theater data from a file named "theater_data.txt" if the
//file exists.If the file doesn't exist or there is an error opening it, the theater is initialized to default 
//values.
void readTheaterFromFile() {
    std::ifstream inFile("theater_data.txt");
    if (inFile.is_open()) {
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                // Read characters and ignore the space
                inFile >> theater[i][j];
                inFile.ignore();  // Ignore the space
            }
        }
        inFile.close();
    } else {
        std::cout << "Error opening file. Initializing theater to default values.\n";
        initializeTheater();
    }
}

//A function writeTheaterToFile is defined to write the current theater data to the file "theater_data.txt".
void writeTheaterToFile() {
    std::ofstream outFile("theater_data.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                outFile << theater[i][j] << " ";
            }
            outFile << "\n";
        }
        outFile.close();
    } else {
        std::cout << "Error opening file for writing.\n";
    }
}

int main() {
    readTheaterFromFile();
    int choice;

    while (true) {
        std::cout << "\nMovie Ticket Booking System\n";
        std::cout << "1. Show Available Seats\n";
        std::cout << "2. Book a Ticket\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayTheater();
                break;
            case 2:
                char row;
                int col;
                std::cout << "Enter the row (A-E) and seat number (1-10): ";
                std::cin >> row >> col;
                row = toupper(row) - 'A';
                col--;
                if (bookTicket(row, col)) {
                    std::cout << "Enjoy the movie!\n";
                    writeTheaterToFile(); // Save the updated data to the file
                }
                break;
            case 3:
                std::cout << "Thank you for using the Movie Ticket Booking System.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
