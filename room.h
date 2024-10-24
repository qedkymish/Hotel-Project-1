//Qusay Edkymish
//Oct/27th/2024
//Room class for hotel reservation sys.

#ifndef ROOM_H
#define ROOM_H

#include<iostream>
#include<string>

using namespace std;

/*The Room class serves as the base class for different room types in a hotel.
It provides common attributes and methods for managing room availability, reservations, and pricing.*/

class Room
{
protected:
	string name;	//Name of the room (type.)
	int available;	//Number of available rooms.
	int reserved;	//Number of reserved rooms.
	int price;		//Price per night for the room

public:
	//Constructor ro initialize the room attributes.
	Room(string roomName, int totalRooms, int roomPrice);

	//Getter for the name of the room.
	string getName() const;

	//Getter for total number of the rooms.
	int getAvailableRooms() const;

	//Getter for the number of reserved rooms.
	int getReservedRooms() const;

	//Getter for the price of a room per night.
	int getPrice() const;

	//Method to make a reservation.
	bool reserve();

	//Method to calculate the revenue.
	int calcRevenue() const;

	//Virtual destructor
	virtual ~Room();
};


//Classes derivation. Each room type is derived from the base class Room.
class Standard : public Room
{
public:
	//Constructor
	Standard() : Room("Courtyard", 70, 125) {}
};

class Scenic : public Room
{
public:
	//Constructor
	Scenic() : Room("Scenic", 35, 145) {}
};

class Deluxe : public Room
{
public:
	//Constructor
	Deluxe() : Room("Deluxe Suite", 15, 350) {}
};

class Penthouse : public Room
{
public:
	//Constructor
	Penthouse() : Room("Penthouse", 2, 1135) {}
};

#endif // !ROOM_H