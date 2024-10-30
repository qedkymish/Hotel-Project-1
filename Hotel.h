//Qusay Edkymish
//Oct/27th/2024
//Hotel class for hotel reservation sys.

//Hotel.h
#ifndef HOTEL_H
#define HOTEL_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Room.h"

using namespace std;

//The Hotel class manages the different types of rooms and provides methods for reservations, inventory, and revenue.
class Hotel
{
private:
    //Room instances are private members of the Hotel class.
    Standard standardRoom;
    Scenic scenicRoom;
    Deluxe deluxeSuite;
    Penthouse penthouse;

public:
    //Constructor
    Hotel();

    //Display the header information.
    void displayHeader() const;

    //Method to display the main menu and handle user interactions.
    void mainMenu();

    //Method to display the reservation menu and handle user interaction.
    void reservationMenu();

    //Getter for the total revenue for the day.
    int getRevenue() const;


    void displayRevenue() const;

    //Method to display the inventory of all room types.
    void displayInventory() const;

    //Virtual destructor
    virtual ~Hotel();
};

#endif // !HOTEL_H
