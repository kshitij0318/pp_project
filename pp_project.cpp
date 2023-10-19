#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
class Vehicle {
public:
    Vehicle(string make, string model, int year, double dailyRate)
        : make(make), model(model), year(year), dailyRate(dailyRate) {}
    virtual double calculateRentalCost(int days) {
        return days * dailyRate;
    }
    void displayInfo() {
        cout << "Make: " << make << ", Model: " << model << ", Year: " << year << endl;
    }
    virtual string getName() const {
        return make + " " + model;
    }
private:
    string make;
    string model;
    int year;
    double dailyRate;
};
class Car : public Vehicle {
public:
    Car(string make, string model, int year)
        : Vehicle(make, model, year, 500.0) {}
    string getName() const override {
        return "Car: " + Vehicle::getName();
    }
};
class Bike : public Vehicle {
public:
    Bike(string make, string model, int year)
        : Vehicle(make, model, year, 350.0) {}
    string getName() const override {
        return "Bike: " + Vehicle::getName();
    }
};
class Truck : public Vehicle {
public:
    Truck(string make, string model, int year)
        : Vehicle(make, model, year, 1000.0) {}
    string getName() const override {
        return "Truck: " + Vehicle::getName();
    }
};
class Customer {
public:
    Customer(string name) : name(name) {}
    string getName() const { return name; }
private:
    string name;
};
class RentalTransaction {
public:
    RentalTransaction(Vehicle* vehicle, int days, const Customer& customer)
        : vehicle(vehicle), days(days), customer(customer) {}
    double calculateTotalCost() const {
        return vehicle->calculateRentalCost(days);
    }
    void displayTransaction() const {
        cout << "Customer: " << customer.getName() << endl;
        vehicle->displayInfo();
        cout << "Rental Days: " << days << endl;
        cout << "Total Cost: Rupees: " << calculateTotalCost() << endl;
    }
    Vehicle* getVehicle() const {
        return vehicle;
    }
    int getDays() const {
        return days;
    }
    Customer getCustomer() const {
        return customer;
    }
private:
    Vehicle* vehicle;
    int days;
    Customer customer;
};
// Function to save booking information to a CSV file
void saveBookingToCSV(const RentalTransaction& rental, const string& filename) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << rental.calculateTotalCost() << "," << rental.getVehicle()->calculateRentalCost(rental.getDays()) << ","
             << rental.getCustomer().getName() << "," << rental.getVehicle()->getName() << "," << rental.getDays() << endl;
        file.close();
        cout << "Booking information saved to " << filename << endl;
    } else {
        cerr << "Failed to open the file: " << filename << endl;
    }
}
int main() {
    string make, model, customerName;
    int year, days;
    char choice;
    vector<RentalTransaction> rentalHistory;
    while (true) {
        cout << "\n--- Vehicle Rental System Menu ---" << endl;
        cout << "1. Rent a Car" << endl;
        cout << "2. Rent a Bike" << endl;
        cout << "3. Rent a Truck" << endl;
        cout << "4. View Rental History" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1/2/3/4/5): ";
        cin >> choice;
        switch (choice) {
            case '1': {
                cout << "Enter make: ";
                cin >> make;
                cout << "Enter model: ";
                cin >> model;
                cout << "Enter year: ";
                cin >> year;
                Car car(make, model, year);
                cout << "Enter rental days: ";
                cin >> days;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, customerName);
                Customer customer(customerName);
                RentalTransaction rental(&car, days, customer);
                rentalHistory.push_back(rental);
                rental.displayTransaction();
                saveBookingToCSV(rental, "car_bookings.csv");
                break;
            }
            case '2': {
                cout << "Enter make: ";
                cin >> make;
                cout << "Enter model: ";
                cin >> model;
                cout << "Enter year: ";
                cin >> year;
                Bike bike(make, model, year);
                cout << "Enter rental days: ";
                cin >> days;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, customerName);
                Customer customer(customerName);
                RentalTransaction rental(&bike, days, customer);
                rentalHistory.push_back(rental);
                rental.displayTransaction();
                saveBookingToCSV(rental, "bike_bookings.csv");
                break;
            }
            case '3': {
                cout << "Enter make: ";
                cin >> make;
                cout << "Enter model: ";
                cin >> model;
                cout << "Enter year: ";
                cin >> year;
                Truck truck(make, model, year);
                cout << "Enter rental days: ";
                cin >> days;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, customerName);
                Customer customer(customerName);
                RentalTransaction rental(&truck, days, customer);
                rentalHistory.push_back(rental);
                rental.displayTransaction();
                saveBookingToCSV(rental, "truck_bookings.csv");
                break;
            }
            case '4': {
                cout << "\n--- Rental History ---" << endl;
                for (const auto& rental : rentalHistory) {
                    rental.displayTransaction();
                    cout << endl;
                }
                break;
            }
            case '5':
                cout << "Exiting the program. Thank you for using our application!\nCome again :)" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
