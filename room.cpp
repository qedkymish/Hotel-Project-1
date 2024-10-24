//Qusay Edkymish
//Oct/27th/2024
//Room class for hotel reservation sys.


#include "Room.h"

//Constructor definition
Room::Room(string roomName, int totalRooms, int roomPrice)
    : name(roomName), available(totalRooms), reserved(0), price(roomPrice) {}

//Getter returns the name/type of the room.
string Room::getName() const
{
    return name;
}

//Getter returns the number of rooms available.
int Room::getAvailableRooms() const
{
    return available;
}

//Getter returns the number of rooms reserved.
int Room::getReservedRooms() const
{
    return reserved;
}

//Getter returns the price per night for the room.
int Room::getPrice() const
{
    return price;
}

//Method to reserve one room. Decrements the available count and increments the reserved count if successful.
bool Room::reserve()
{
    if (available > 0)  //Ensure there are rooms available to reserve.
    {
        available--;
        reserved++;
        return true;    //Reservation successful.
    }
    return false;       //No rooms available.
}

//Method to calculates and returns the total revenue
int Room::calcRevenue() const
{
    return reserved * price;
}

//Virtual destructor definition to allow proper cleanup in derived classes.
Room::~Room() {}