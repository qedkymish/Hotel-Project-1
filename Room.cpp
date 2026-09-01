//Qusay Edkymish
//Nov/17th/2024
//Room class for hotel reservation sys.


#include "Room.h"


//Constructor definition
Room::Room(string roomName, int totalRooms, int roomPrice, int startRoom, int endRoom)
    : name(roomName), available(totalRooms), reserved(0), price(roomPrice)
{
    //Generate room numbers within the specified range and populate the available rooms
    for (int i = startRoom; i <= endRoom; ++i)
    {
        roomNumbers.push_back(i);
        availableRooms.push_back(i);
    }
}

//Getter returns the name/type of the room.
string Room::getName() const
{
    return name;
}

//Getter returns the total number of rooms available.
int Room::getAvailable() const
{
    return available;
}

//Getter returns the total number of rooms reserved.
int Room::getReserved() const
{
    return reserved;
}

//Getter returns the price per night for the room.
int Room::getPrice() const
{
    return price;
}

//Getter for available rooms numbers
vector<int> Room::getAvailableRooms() const
{
    return availableRooms;
}

//Getter for reserved rooms numbers with customer information
const map<int, Customer> Room::getReservedRooms() const
{
    return reservedRooms;
}

//Method to reserve one room. Decrements the available count and increments the reserved count if successful.
bool Room::reserve(int roomNumber, Customer& customer)
{
    //Check if the room is available
    auto it = find(availableRooms.begin(), availableRooms.end(), roomNumber);
    
    //If available, remove it from the list and update counts
    if (it != availableRooms.end())
    {
        availableRooms.erase(it);               //Remove from available list
        reservedRooms[roomNumber] = customer;   //Add customer information and room number
        reserved++;
        available--;
        return true;
    }

    return false; //Room not available
}

//Reserve a random room
int Room::reserveRandom(Customer& customer)
{
    //Check if there are rooms available
    if (availableRooms.empty()) return -1;

    //Select a random room and reserve it
    int index = rand() % availableRooms.size();
    int roomNumber = availableRooms[index];

    //Remove room from availableRooms and add it to reservedRooms
    availableRooms.erase(availableRooms.begin() + index);

    //Track in reservedRooms
    reservedRooms[roomNumber] = customer;
    
    //Update counts
    reserved++;
    available--;

    return roomNumber;
}

//Method to reserve one room. Decrements the reserved count and increments the available  count if successful.
bool Room::cancelReservation(int roomNumber, Customer& customer)
{
    //Check if the room is currently reserved by looking it up in the reservedRooms map
    auto it = reservedRooms.find(roomNumber);
    if (it != reservedRooms.end()) //If found, the room is reserved
    {
        //Retrieve customer information before erasing
        customer = it->second;

        //Remove the room and associated customer data from the reservedRooms map
        reservedRooms.erase(it);

        //Add the room back to the availableRooms vector
        availableRooms.push_back(roomNumber);

        //Sort the availableRooms vector to maintain numerical order
        sort(availableRooms.begin(), availableRooms.end());

        //Update the reservation counts
        reserved--;  
        available++;

        return true; //Cancellation successful
    }

    //Room was not reserved or the room number was invalid
    return false;
}


//Method to calculates and returns the total revenue
int Room::calcRevenue() const
{
    return reserved * price;
}

//Virtual destructor definition to allow proper cleanup in derived classes.
Room::~Room() {}
