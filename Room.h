//Qusay Edkymish
//Nov/17th/2024
//Room class for hotel reservation sys.

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>
#include "Customer.h"

using namespace std;

/*The Room class serves as the base class for different room types in a hotel.
It provides common attributes and methods for managing room availability, reservations, and pricing.*/

class Room
{
protected:
	string name;								//Name of the room (type.)
	int available;								//Number of available rooms.
	int reserved;								//Number of reserved rooms.
	int price;									//Price per night for the room
	vector<int> roomNumbers;					//All room numbers for this type
	vector<int> availableRooms;					//Currently available rooms
	map<int, Customer> reservedRooms;	//Room number to customer info

public:
	//Constructor ro initialize the room attributes.
	Room(string roomName, int totalRooms, int roomPrice, int startRoom, int endRoom);

	//Getters
	string getName() const;								//Room name
	int getAvailable() const;							//Total number of the rooms.
	int getReserved() const;							//Total number of reserved rooms.
	int getPrice() const;								//Price of a room per night.
	vector<int> getAvailableRooms() const;				//Available rooms numbers
	const map<int, Customer> getReservedRooms() const;	//Reserved rooms numbers

	//Reservation and cancelation
	virtual bool reserve(int roomNumber, Customer& customer);	//Reserve a specific room
	virtual int reserveRandom(Customer& customer);				//Reserve a random room
	virtual bool cancelReservation(int roomNubmer,						//Cancel a reservation
		Customer& customer);						

	//Method to calculate the revenue.
	int calcRevenue() const;

	//Virtual destructor
	virtual ~Room();
};


//Classes derivation. Each room type is derived from the base class Room. (This was asked in the assignment)
class Standard : public Room
{
public:
	//Constructor
	Standard() : Room("Courtyard", 70, 125, 101, 170) {}
};

class Scenic : public Room
{
public:
	//Constructor
	Scenic() : Room("Scenic", 35, 145, 201, 235) {}
};

class Deluxe : public Room
{
public:
	//Constructor
	Deluxe() : Room("Deluxe Suite", 15, 350, 236, 250) {}
};

class Penthouse : public Room
{
public:
	//Constructor
	Penthouse() : Room("Penthouse", 2, 1135, 301, 302) {}
};

#endif //!ROOM_H
