#include "202411078_lab_project.h"
#include <cctype>

bool isValidFlightNo(const string& flightNo)
{
    // TK and PG have 2 characters and "th"e number can be at most 4 characters long. So the sum must be between 3 and 7
    if (flightNo.length() < 3 || flightNo.length() > 7)
        return false;

    // get the first two characters as 'prefix' and control it
    string prefix = flightNo.substr(0, 2);
    if (prefix != "TK" && prefix != "PG")
        return false;

    // Find where the number part starts (3 if there is a space and 2 if there is not)
    int startIndex = (flightNo[2] == ' ') ? 3 : 2;

    string numberPart = flightNo.substr(startIndex);
    // check if number part is between 1 and 4
    if (numberPart.length() < 1 || numberPart.length() > 4)
        return false;

    // check if all characters are digits
    for (int i = 0; i < numberPart.length(); i++)
    {
        if (!isdigit(numberPart[i]))
            return false;
    }

    return true;
}

bool isValidName(const string& name)
{
    // if name is empty, it's not valid
    if (name.empty())
        return false;

    // check if name only has letters and not symbols or numbers
    for (int i = 0; i < name.length(); i++)
    {
        if (!isalpha(name[i]))
            return false;
    }

    return true;
}

void displayPassengerMenu(Flight& selectedFlight)
{
    int choice = 0;
    while (choice != 4)
    {
        cout << "\n--- Passenger Management (Flight: " << selectedFlight.getFlightNo() << ") ---\n";
        cout << "1. Reserve a Seat\n2. Cancel a Reservation\n3. View Passenger List\n4. Back to Flight Management Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                string name, surname;
                char gender;

                do
                {
                    cout << "Enter a valid name: ";
                    cin >> name;
                    if (!isValidName(name))
                        cout << "Error: Name must contain only letters." << endl;
                } while (!isValidName(name));

                do
                {
                    cout << "Enter a valid surname: ";
                    cin >> surname;
                    if (!isValidName(surname))
                        cout << "Error: Surname must contain only letters." << endl;
                } while (!isValidName(surname));

                do
                {
                    cout << "Enter a valid gender (M/F): ";
                    cin >> gender;
                    gender = toupper(gender);
                    if (gender != 'M' && gender != 'F')
                        cout << "Error: Gender must be M or F." << endl;
                } while (gender != 'M' && gender != 'F');

                Passenger p(name, surname, gender);
                selectedFlight.reserveSeat(p);

                break;
            }

            case 2:
            {
                string name, surname;
                char gender;

                cout << "Enter details for verification\nName: ";
                cin >> name;
                cout << "Surname: ";
                cin >> surname;
                cout << "Gender (M/F): ";
                cin >> gender;

                Passenger p(name, surname, gender);
                selectedFlight.cancelReservation(p);

                break;
            }

            case 3:
            {
                selectedFlight.printPassengers();
                break;
            }
        }
    }
}

void displayMainMenu(FlightManager& manager)
{
    int choice = 0;
    while (choice != 5)
    {
        cout << "\n--- Flight Management Menu ---\n";
        cout << "1. Add a Flight\n2. Remove a Flight\n3. List All Flights\n4. Select a Flight and Manage the Passengers\n5. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                string fNo, dest;
                int seats;

                do
                {
                    cout << "Flight Number (TK/PG xxxx): ";
                    getline(cin >> ws, fNo);
                } while (!isValidFlightNo(fNo));

                cout << "Destination: ";
                cin >> dest;
                cout << "Max Seats (Even, 2-80, Default 40): ";
                cin >> seats;

                Flight newFlight(fNo, dest, seats);
                manager.addFlight(newFlight);

                break;
            }

            case 2:
            {
                string fNo;

                cout << "Enter flight number to remove: ";
                getline(cin >> ws, fNo);

                manager.removeFlight(fNo);
                break;
            }

            case 3:
            {
                manager.listAllFlights();
                break;
            }

            case 4:
            {
                string fNo;

                cout << "Enter flight number: ";
                getline(cin >> ws, fNo);

                try
                {
                    Flight& selected = manager.getFlightByNumber(fNo);
                    displayPassengerMenu(selected);
                }

                catch (string& msg)
                {
                    cerr << msg << endl;
                }
                break;
            }
        }
    }
}

int main()
{
    FlightManager myManager;
    displayMainMenu(myManager);
    cout << "Thank you for using our Flight Management System. Hope you have a great day!" << endl;
    cout << "Now exiting..." << endl;
    return 0;
}