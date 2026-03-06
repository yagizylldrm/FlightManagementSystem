#ifndef LAB_PROJECT_H
#define LAB_PROJECT_H
#define ROW_SIZE 4
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class Passenger
{
private:
    string name;
    string surname;
    char gender;

public:
    // both default and parameterized constructor
    Passenger(const string n = "", const string s = "", const char g = '\0') : name(n), surname(s), gender(g) {}

    // getters and setters
    string getName() const { return name; }
    string getSurname() const { return surname; }
    char getGender() const { return gender; }
    void setName(const string& n) { name = n; }
    void setSurname(const string& s) { surname = s; }
    void setGender(const char g) { gender = g; }

    // operator overloading
    Passenger& operator=(const Passenger& other)
    {
        if (this != &other)
        {
            this->name = other.name;
            this->surname = other.surname;
            this->gender = other.gender;
        }
        return *this;
    }

    bool operator==(const Passenger& other) const
    {
        if ((other.name == this->name) && (other.surname == this->surname) && (other.gender == this->gender))
        {
            return true;
        }

        return false;
    }
};

class Flight
{
private:
    string flightNo;
    string destination;
    int maxSeats = 40;
    int numPassengers;
    vector<Passenger> passengers;

public:
    // both default and parameterized constructor
    Flight(const string& fn, const string& d, int ms) : flightNo(fn), destination(d), numPassengers(0)
    {
        setMaxSeats(ms);
        passengers.resize(maxSeats);
    }

    // getters and control mechanisms
    string getFlightNo() const { return flightNo; }
    string getDestination() const { return destination; }
    int getMaxSeats() const { return maxSeats; }
    int getNumPassengers() const { return numPassengers; }
    vector<Passenger>& getPassengers() { return passengers; }
    Passenger& getSpecificPassenger(const int index) { return passengers[index]; }

    bool isSeatTaken(int index)
    {
        if (passengers[index].getGender() != '\0')
            return true;

        return false;
    }

    // setters
    void setFlightNo(const string& n) { flightNo = n; }
    void setDestination(const string& d) { destination = d; }

    void setMaxSeats(const int ms)
    {
        try
        {
            if (ms % 2 == 0 && (ms <= 80 && ms > 0))
                maxSeats = ms;
            else if (ms % 2 != 0)
                throw string("Maximum number of seats must be even.");
            else if (!(ms <= 80 && ms > 0))
                throw string("Maximum number of seats must be between 1 and 80 (inclusive)");
        }

        catch (string& msg)
        {
            cerr << msg << endl;
        }
    }

    void setNumPassengers(const int np) { numPassengers = np; }
    void setPassengers(const vector<Passenger> p) { passengers = p; }
    void setSpecificPassenger(const int index, const Passenger& p) { passengers[index] = p; }

    // needed methods
    void displaySeatingPlan()
    {
        cout << "\nSeating Plan (O: Vacant, X: Occupied)\n";
        cout << "      A   B      C   D\n";

        int totalRows = maxSeats / ROW_SIZE;
        for (int i = 0; i < totalRows; ++i)
        {
            // Format row number with leading zero if needed
            int rowNum = i + 1;
            if (rowNum < 10)
                cout << "0" << rowNum << " ";
            else
                cout << rowNum << " ";

            for (int j = 0; j < ROW_SIZE; ++j)
            {
                int currentIndex = i * ROW_SIZE + j;

                if (isSeatTaken(currentIndex))
                {
                    cout << "| X ";
                }
                else
                {
                    cout << "| O ";
                }

                // simulate the plane corridor
                if (j == 1)
                    cout << "    ";
            }
            cout << "|\n";
        }
    }

    void reserveSeat(const Passenger& passenger)
    {
        /* A = 0, B = 1, C = 2, D = 3
         * needed formula is: (Row - 1) * 4 + Row Offset
         */

        // display the flight plan here
        displaySeatingPlan();

        // get the seat info from user
        int seatIndex, rowOffset;
        cout << "Enter the seat you want to reserve: ";
        int rowNumber;
        char seatLetter;
        cin >> rowNumber >> seatLetter;

        try
        {
            if (rowNumber < 1 || (rowNumber * ROW_SIZE) > maxSeats)
                throw string("Row number is not valid.");

            // assign rowOffset according to seatLetter
            switch (seatLetter)
            {
                case 'A':
                {
                    rowOffset = 0;
                    break;
                }

                case 'B':
                {
                    rowOffset = 1;
                    break;
                }

                case 'C':
                {
                    rowOffset = 2;
                    break;
                }

                case 'D':
                {
                    rowOffset = 3;
                    break;
                }

                default:
                {
                    throw string("Seat letter is not valid.");
                    break;
                }
            }
            // calculate seatIndex
            seatIndex = (rowNumber - 1) * ROW_SIZE + rowOffset;
            // check if seat is already taken
            if (isSeatTaken(seatIndex))
                throw string("The seat you've selected is full.");
            else
            {
                passengers[seatIndex] = passenger;
                numPassengers++;
            }
        }

        catch (string& msg)
        {
            cerr << msg << endl;
        }
    }

    void cancelReservation(const Passenger& passenger)
    {
        // checker for exception handling
        bool foundPassenger = false;
        try
        {
            // search all seats and if found, exit the loop
            for (int i = 0; i < maxSeats; i++)
            {
                if (passengers[i] == passenger)
                {
                    passengers[i] = Passenger();
                    numPassengers--;
                    foundPassenger = true;
                    cout << "Reservation cancelled successfully." << endl;
                    break;
                }
            }

            if (!foundPassenger)
                throw string("No reservation found for this passenger.");
        }

        catch (string& msg)
        {
            cerr << msg << endl;
        }
    }

    int numberOfPassengers()
    {
        return numPassengers;
    }

    void printPassengers()
    {
        cout << setfill(' '); // Ensure fill character is space
        cout << "\nPassenger List for Flight " << flightNo << ":\n";
        cout << left << setw(5) << "Seat" << " | "
             << setw(15) << "Passenger Name" << " | "
             << "Gender" << endl;

        for (int i = 0; i < maxSeats; ++i)
        {
            // calculate seat label for all seats
            string seatLabel = to_string((i / ROW_SIZE) + 1) + (char)('A' + (i % ROW_SIZE));

            if (isSeatTaken(i))
            {
                string fullName = passengers[i].getName() + " " + passengers[i].getSurname();

                // if name > 15 characters, cut and add '.'
                if (fullName.length() > 15)
                {
                    fullName = fullName.substr(0, 14) + ".";
                }

                cout << left << setw(5) << seatLabel << " | "
                     << setw(15) << fullName << " | "
                     << passengers[i].getGender() << endl;
            }
        }
    }

    bool isFlyingTo(const string& destination)
    {
        if (destination == this->getDestination())
            return true;

        return false;
    }
};

class FlightManager
{
private:
    vector<Flight> flights;

public:
    // constructor (just in case)
    FlightManager() {}
    // also no getters and setters is needed (I hope so!)
    // needed methods
    void addFlight(const Flight& flight)
    {
        // control for already existing flight number
        for (int i = 0; i < flights.size(); i++)
        {
            if (flights[i].getFlightNo() == flight.getFlightNo())
            {
                cerr << "Flight " + flight.getFlightNo() + " already exists." << endl;
                return;
            }
        }
        flights.push_back(flight);
        cout << "Flight added successfully." << endl;
    }

    void removeFlight(const string& flightNumber)
    {
        try
        {
            // checker for exception handling
            bool foundFlight = false;
            // search all flights and if found, exit the loop
            for (int i = 0; i < flights.size(); i++)
            {
                if (flights[i].getFlightNo() == flightNumber)
                {
                    // erase flight at index i
                    flights.erase(flights.begin() + i);
                    foundFlight = true;
                    cout << "Flight " << flightNumber << " is removed successfully." << endl;
                    break;
                }
            }

            if (!foundFlight)
                throw string("Flight not found.");
        }

        catch (string& msg)
        {
            cerr << msg << endl;
        }
    }

    void listAllFlights()
    {
        cout << "\n--- Current Flights ---" << endl;
        cout << left << setw(10) << "Flight No" << "|" << setw(15) << "Destination" << "|" << "Available Seats" << endl;
        for (int i = 0; i < flights.size(); i++)
        {
            int available = flights[i].getMaxSeats() - flights[i].getNumPassengers();
            cout << left << setw(10) << flights[i].getFlightNo() << "|"
                 << setw(15) << flights[i].getDestination() << "|"
                 << available << endl;
        }
    }

    Flight& getFlightByNumber(const string& flightNumber)
    {
        for (int i = 0; i < flights.size(); i++)
        {
            if (flights[i].getFlightNo() == flightNumber)
            {
                return flights[i];
            }
        }

        throw string("Flight " + flightNumber + " not found.");
    }

    Flight& getFlightByDestination(const string& destination)
    {
        for (int i = 0; i < flights.size(); i++)
        {
            if (flights[i].getDestination() == destination)
            {
                return flights[i];
            }
        }

        throw string("No flight found for destination " + destination + ".");
    }
};

#endif