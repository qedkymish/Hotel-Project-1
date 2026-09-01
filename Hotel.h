//Qusay Edkymish
//Nov/17th/2024
//Hotel class for hotel reservation sys.

//Hotel.h
#ifndef HOTEL_H
#define HOTEL_H

#include "Customer.h"
#include "Room.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

//The Hotel class manages the different types of rooms and provides methods for reservations, inventory, and revenue.

class Hotel
{
private:
    //Room instances
    Standard standardRoom;  //Courtyard Room
    Scenic scenicRoom;      //Sceinc Room
    Deluxe deluxeSuite;     //Deluxe Suite
    Penthouse penthouse;    //Penthouse

private:
    string date;                        //Variable to store the date entered by the user
    vector<string> todaysLogEntries;    //In-memory log for today's operations

public:
    //Constructor
    Hotel();

    //Date handling
    void setDate();         //Setter for current date
    string getDate() const; //Getter for current date

    //Menus handling user interactions
    void menuName(const string& name) const;    //Printout menu name
    void mainMenu();                            //Main menu
    void reservationMenu();                     //Reservation menu
    void displayReportsMenu() const;            //Reports menu
    void displayAbout() const;                  //About menu         

    //Reservation handling
    void reserve(Room* selectedRoom);           //Make reservation for a specific type of room
    void cancelReservation();                   //Cancel reservation for a specific type of room
    int getRevenue() const;                     //Getter for the total revenue for the day.
    Customer collectCustomerInfo();             //Collect customer information

    //Display and Reports
    void displayHeader() const;                       //Display program header
    void displayRoomAvailable(const string& roomType, //Display available rooms for a single Room instance
        const Room& room) const;
    void displayRoomReserved(const string& roomType,  //Display reserved rooms for a single Room instance
        const Room& room) const;
    void displayInventory() const;                    //Display the inventory of all room types.
    void displayRevenue() const;                      //Display the revenue

    //Logging
    void initializeLog();                        //Load logs from file if available
    void logEntry(const string& action,          //Log the data
        const string& roomType, int roomNumber, 
        const string& status, double revenue,
        const Customer& customer);
    void archiveDailyLog();                     //Archive the current session's log
    void viewArchivedLogs() const;              //View archived logs
    void displayLogs(ifstream& logFile) const;  //Display logs

    //Virtual destructor
    virtual ~Hotel();    
};

#endif //!HOTEL_H
