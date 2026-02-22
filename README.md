# Hotel Reservation System (C++)

A console-based hotel reservation system built in C++ using object-oriented design principles.

## Overview

This project models a hotel with multiple room types and allows users to:

- Reserve different types of rooms
- View room inventory
- View total revenue generated

The system is implemented using inheritance to represent different room types.

## Room Types

- Standard
- Scenic
- Deluxe
- Penthouse

Each room type has:
- A name
- A price per night
- A total number of rooms available

## Features

- Menu-driven interface
- Input validation
- Room availability tracking
- Revenue calculation
- Object-oriented structure

## Technologies

- C++
- Standard Library (iostream, string, limits)

## Build & Run

Compile using g++:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic Hotel_Project_1.cpp Hotel.cpp Room.cpp -o hotel
