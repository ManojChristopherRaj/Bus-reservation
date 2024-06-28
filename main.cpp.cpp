#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

static int t = 0;
bool isLoggedIn = false;
bool isAdmin = false;

class BusReservation {
    char bus_number[5], bus_driver[10], bus_arrival[5], bus_depart[5], b_from[10], b_to[10], bus_seat[8][4][10];

public:
    void add_new_number_of_bus();
    void reservation();
    void cancel();
    void empty();
    void view();
    void avail();
    void position(int i);
    void login();
    void logout();
};

BusReservation bus[5];

void bus_line(char ch) {
    for (int x = 80; x > 0; x--)
        cout << ch;
}

void BusReservation::add_new_number_of_bus() {
    if (!isAdmin) {
        cout << "You don't have permission to access this feature!\n";
        return;
    }
    cout << "Enter Bus Number: ";
    cin >> bus[t].bus_number;
    cout << "\nEnter Driver's Name: ";
    cin >> bus[t].bus_driver;
    cout << "\nArrival Time: ";
    cin >> bus[t].bus_arrival;
    cout << "\nDeparture: ";
    cin >> bus[t].bus_depart;
    cout << "\nFrom: \t\t\t";
    cin >> bus[t].b_from;
    cout << "\nTo: \t\t\t";
    cin >> bus[t].b_to;
    bus[t].empty();
    cout << "\nNew Bus Added Successfully \t\t\t";
    t++;
}

void BusReservation::reservation() {
    if (isAdmin) {
        cout << "You don't have permission to access this feature!\n";
        return;
    }
    char no[5];
    cout << "Enter Bus Number: ";
    cin >> no;
    int y;
    for (y = 0; y < t; y++) {
        if (strcmp(bus[y].bus_number, no) == 0)
            break;
    }
    if (y == t) {
        cout << "Bus Number not found!\n";
        return;
    }
    cout << "Number of seats to reserve: ";
    int number_of_seats;
    cin >> number_of_seats;

    for (int i = 0; i < number_of_seats; i++) {
        int bus_seat;
        cout << "\nSeat Number: ";
        cin >> bus_seat;
        if (bus_seat > 32) {
            cout << "\nThere are only 32 Seats Available in this Bus.";
            continue;
        }
        if (strcmp(bus[y].bus_seat[bus_seat / 4][(bus_seat % 4) - 1], "Empty") == 0) {
            cout << "Enter Passenger's Name: ";
            cin >> bus[y].bus_seat[bus_seat / 4][(bus_seat % 4) - 1];
        } else {
            cout << "The Seat Number is Already Reserved.\n";
            i--; // Decrement the counter to re-ask for the seat number
        }
    }
}

void BusReservation::cancel() {
    if (isAdmin) {
        cout << "You don't have permission to access this feature!\n";
        return;
    }
    char no[5];
    cout << "Enter Bus Number: ";
    cin >> no;
    int y;
    for (y = 0; y < t; y++) {
        if (strcmp(bus[y].bus_number, no) == 0)
            break;
    }
    if (y == t) {
        cout << "Bus Number not found!\n";
        return;
    }
    cout << "Seat Number to Cancel: ";
    int bus_seat;
    cin >> bus_seat;
    if (bus_seat > 32) {
        cout << "\nThere are only 32 Seats Available in this Bus.";
        return;
    }
    if (strcmp(bus[y].bus_seat[bus_seat / 4][(bus_seat % 4) - 1], "Empty") != 0) {
        strcpy(bus[y].bus_seat[bus_seat / 4][(bus_seat % 4) - 1], "Empty");
        cout << "Reservation Cancelled Successfully.";
    } else {
        cout << "The Seat Number is Already Empty.\n";
    }
}

void BusReservation::empty() {
    for (int x = 0; x < 8; x++) {
        for (int z = 0; z < 4; z++) {
            strcpy(bus[t].bus_seat[x][z], "Empty");
        }
    }
}

void BusReservation::view() {
    char number[5];
    cout << "Enter Bus Number: ";
    cin >> number;
    for (int m = 0; m < t; m++) {
        if (strcmp(bus[m].bus_number, number) == 0) {
            bus_line('*');
            cout << "Bus Number: \t" << bus[m].bus_number
                 << "\nDriver: \t" << bus[m].bus_driver << "\t\tArrival Time: \t"
                 << bus[m].bus_arrival << "\tDeparture Time:" << bus[m].bus_depart
                 << "\nFrom: \t\t" << bus[m].b_from << "\t\tTo: \t\t" <<
                 bus[m].b_to << "\n";
            bus_line('*');
            position(m);
            int d = 1;
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 4; y++) {
                    d++;
                    if (strcmp(bus[m].bus_seat[x][y], "Empty") != 0)
                        cout << "\nThe Seat no " << (d - 1) << " is Reserved for " << bus[m].bus_seat[x][y] << ".";
                }
            }
            return;
        }
    }
    cout << "Bus Number not found!\n";
}

void BusReservation::position(int l) {
    int r = 0, t = 0;
    for (int x = 0; x < 8; x++) {
        cout << "\n";
        for (int z = 0; z < 4; z++) {
            r++;
            if (strcmp(bus[l].bus_seat[x][z], "Empty") == 0) {
                cout.width(5);
                cout.fill(' ');
                cout << r << ".";
                cout.width(10);
                cout.fill(' ');
                cout << bus[l].bus_seat[x][z];
                t++;
            } else {
                cout.width(5);
                cout.fill(' ');
                cout << r << ".";
                cout.width(10);
                cout.fill(' ');
                cout << bus[l].bus_seat[x][z];
            }
        }
    }
    cout << "\n\nThere are " << t << " Seats Empty in Bus Number: " << bus[l].bus_number;
}

void BusReservation::avail() {
    for (int y = 0; y < t; y++) {
        bus_line('*');
        cout << "Bus Number: \t" << bus[y].bus_number << "\nDriver: \t" << bus[y].bus_driver
             << "\t\tArrival Time: \t" << bus[y].bus_arrival << "\tDeparture Time: \t"
             << bus[y].bus_depart << "\nFrom: \t\t" << bus[y].b_from << "\t\tTo: \t\t\t"
             << bus[y].b_to << "\n";
        bus_line('*');
        bus_line('_');
    }
}

void BusReservation::login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    // Perform authentication logic here
    if (username == "Guhan" && password == "123456789") {
        isAdmin = true;
        isLoggedIn = true;
        cout << "Admin Login successful!\n";
    } else if (username == "user" && password == "user") {
        isLoggedIn = true;
        cout << "User Login successful!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

void BusReservation::logout() {
    isAdmin = false;
    isLoggedIn = false;
    cout << "Logged out successfully.\n";
}

int main() {
    system("cls");
    int w;
    while (1) {
        cout << "\n\n";
        cout << "\t\t***SIMPLE BUS RESERVATION SYSTEM***";
        cout << "\n\n";
        cout << "\t\t\t1. Admin Login\n\t\t\t"
             << "2. User Login\n\t\t\t"
             << "3. Exit";
        cout << "\n\t\t\tEnter your Choice:- ";
        cin >> w;
        switch (w) {
            case 1:  bus[t].login();
                break;
            case 2:  bus[t].login();
                break;
            case 3:  exit(0);
        }
        if (isLoggedIn) {
            if (isAdmin) {
                while (1) {
                    cout << "\n\n";
                    cout << "\t\t***ADMIN MENU***";
                    cout << "\n\n";
                    cout << "\t\t\t1. Add New Bus Number\n\t\t\t"
                         << "2. Show Reservations\n\t\t\t"
                         << "3. Logout\n\t\t\t"
                         << "4. Exit";
                    cout << "\n\t\t\tEnter your Choice:- ";
                    cin >> w;
                    switch (w) {
                        case 1:  bus[t].add_new_number_of_bus();
                            break;
                        case 2:  bus[t].view();
                            break;
                        case 3:  bus[t].logout();
                            break;
                        case 4:  exit(0);
                    }
                    if (!isAdmin) {
                        break;
                    }
                }
            } else {
                while (1) {
                    cout << "\n\n";
                    cout << "\t\t***USER MENU***";
                    cout << "\n\n";
                    cout << "\t\t\t1. Reservation\n\t\t\t"
                         << "2. Cancel Reservation\n\t\t\t"
                         << "3. Show Available Buses\n\t\t\t"
                         << "4. Logout\n\t\t\t"
                         << "5. Exit";
                    cout << "\n\t\t\tEnter your Choice:- ";
                    cin >> w;
                    switch (w) {
                        case 1:  bus[t].reservation();
                            break;
                        case 2:  bus[t].cancel();
                            break;
                        case 3:  bus[t].avail();
                            break;
                        case 4:  bus[t].logout();
                            break;
                        case 5:  exit(0);
                    }
                    if (!isLoggedIn) {
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
