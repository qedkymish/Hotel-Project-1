//Qusay Edkymish
//Nov/17th/2024
//Customer class for hotel reservation sys.

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

using namespace std;

//The Customer class represents a hotel customer and contains their personal information.
class Customer
{
private:
    string name;          //Customer's name.
    string phoneNumber;   //Customer's phone number.
    string email;         //Customer's email address.

public:
    // Default constructor
    Customer() : name("Unknown"), phoneNumber("N/A"), email("N/A") {}

    // Parameterized constructor
    Customer(const string& name, const string& phoneNumber, const string& email)
        : name(name), phoneNumber(phoneNumber), email(email) {}

    //Getters
    string getName() const;         //Customer's name.
    string getPhoneNumber() const;  //Customer's phone number.
    string getEmail() const;        //Customer's email.
};

#endif // !CUSTOMER_H
