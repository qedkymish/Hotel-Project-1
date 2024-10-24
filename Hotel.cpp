//Qusay Edkymish
//Oct/27th/2024
//Hotel class for hotel reservation sys.

//Hotel.cpp
#include "Hotel.h"


//Constructor 
Hotel::Hotel() {}

//Method to display the program's header
void Hotel::displayHeader() const
{
	//Print program title
	cout << "========================================\n";
	cout << "   Grossmont Hotel Reservation System   \n";
	cout << "========================================\n";


	//Prompt user to start the program.
	cout << "Wellcome! Press any key to start...\n";
	cin.get();
}

//Method to display the main menu and handle user interactions.
void Hotel::mainMenu()
{
	int choice;				//Variable to store the user's menu selection.
	bool running = true;	//Variable to control loop to keep the menu running.


	//Main menu loop
	while (running)
	{

		//Display menu
		cout << "\n=====================\n";
		cout << "      Main Menu       \n";
		cout << "=====================\n\n";

		//Display main menu options
		cout << "1. Make a reservation\n";
		cout << "2. Get inventory\n";
		cout << "3. Show revenue for today\n";
		cout << "0. Quit\n";

		//Validate user's input.
		while (true)
		{
			cout << "Enter your choice: ";
			if (!(cin >> choice) || choice < 0 || choice > 3)
			{
				cin.clear(); //Clear the error state
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignore any remaining invalid input
				cout << "Invalid input. Please enter a number from 0 to 3.\n";
			}
			else
			{
				break; //Valid input received, exit the validation loop
			}
		}


		//Choices
		switch (choice)
		{
		case 1:
			//Navigate to reservation menu
			reservationMenu();
			break;

		case 2:
			//Display the inventory
			displayInventory();
			break;

		case 3:
			//Diplay the revenue for today
			cout << "\nThe total revenue for today is: $" << getRevenue() << "\n";
			break;

		case 0:
			//End the program
			running = false;
			cout << "\nGoodbye!\n";
			break;

		default:
			cout << "Invalid choice. Please try again.\n";
			break;
		}
	}
}

//Method to display the reservation menu and handle user interaction.
void Hotel::reservationMenu()
{
	int choice;				//Variable to store the user's menu selection
	bool subMenu = true;	//Variable to control loop to keep the menu running.

	while (subMenu)
	{
		//Display the menu name
		cout << "\n=====================\n";
		cout << "     Reservation      \n";
		cout << "=====================\n\n";

		//Display reservation menu options
		cout << "1. Standard Room, Courtyard\n";
		cout << "2. Standard Room, Scenic\n";
		cout << "3. Deluxe Suite\n";
		cout << "4. Penthouse\n";
		cout << "0. Return to main menu\n";

		//Validate user's input.
		while (true)
		{
			cout << "Enter your choice: ";
			if (!(cin >> choice) || choice < 0 || choice > 4)
			{
				cin.clear(); //Clear the error state
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignore any remaining invalid input
				cout << "Invalid input. Please enter a number from 0 to 4.\n";
			}
			else
			{
				break; //Valid input received, exit the validation loop
			}
		}

		//Choices
		switch (choice)
		{
		case 1:
			//Reserve a Courtyard
			if (standardRoom.reserve())
			{
				cout << "\nSuccessfully reserved a Courtyard room. Rooms left: " << standardRoom.getAvailableRooms() << "\n";
			}
			else
			{
				cout << "\nNo available Courtyard rooms to reserve.\n";
			}
			break;

		case 2:
			//Reserve a Scenic
			if (scenicRoom.reserve())
			{
				cout << "\nSuccessfully reserved a Scenic room. Rooms left: " << scenicRoom.getAvailableRooms() << "\n";
			}
			else
			{
				cout << "\nNo available Scenic rooms to reserve.\n";
			}
			break;

		case 3:
			//Reserve a Deluxe Suite
			if (deluxeSuite.reserve())
			{
				cout << "\nSuccessfully reserved a Deluxe Suite. Rooms left: " << deluxeSuite.getAvailableRooms() << "\n";
			}
			else
			{
				cout << "\nNo available Deluxe Suites to reserve.\n";
			}
			break;

		case 4:
			//Reserve a Penthouse
			if (penthouse.reserve())
			{
				cout << "\nSuccessfully reserved a Penthouse Rooms left: " << penthouse.getAvailableRooms() << "\n";
			}
			else
			{
				cout << "\nNo available Penthouses to reserve.\n";
			}
			break;

		case 0:
			//Exit the reservation menu
			subMenu = false;
			break;

		default:
			cout << "\nInvalid input! Please try again.\n";
			break;
		}
	}
}


//Method to display the inventory of all room types.
void Hotel::displayInventory() const 
{
	cout << "\n=====================\n";
	cout << "    The Inventory    \n";
	cout << "=====================\n\n";

	// Display the number of reserved and available rooms for each type:
	cout << left << setw(20) << "Courtyard" << left << setw(10) << "Reserved: " << right << setw(5) << standardRoom.getReservedRooms()
		<< "  Available: " << right << setw(5) << standardRoom.getAvailableRooms() << "\n";

	cout << left << setw(20) << "Scenic" << left << setw(10) << "Reserved: " << right << setw(5) << scenicRoom.getReservedRooms()
		<< "  Available: " << right << setw(5) << scenicRoom.getAvailableRooms() << "\n";

	cout << left << setw(20) << "Deluxe Suite" << left << setw(10) << "Reserved: " << right << setw(5) << deluxeSuite.getReservedRooms()
		<< "  Available: " << right << setw(5) << deluxeSuite.getAvailableRooms() << "\n";

	cout << left << setw(20) << "Penthouse" << left << setw(10) << "Reserved: " << right << setw(5) << penthouse.getReservedRooms()
		<< "  Available: " << right << setw(5) << penthouse.getAvailableRooms() << "\n\n";

	int totalReserved = standardRoom.getReservedRooms() + scenicRoom.getReservedRooms()
		+ deluxeSuite.getReservedRooms() + penthouse.getReservedRooms();

	int totalAvailable = standardRoom.getAvailableRooms() + scenicRoom.getAvailableRooms()
		+ deluxeSuite.getAvailableRooms() + penthouse.getAvailableRooms();

	cout << left << setw(20) << "Total reserved rooms: " << right << setw(5) << totalReserved << "\n";
	cout << left << setw(20) << "Total available rooms: " << right << setw(5) << totalAvailable << "\n\n";
}

//Getter for the total revenue for the day.
int Hotel::getRevenue() const
{
	//Calculate total revenue
	return standardRoom.calcRevenue() + scenicRoom.calcRevenue()
		+ deluxeSuite.calcRevenue() + penthouse.calcRevenue();
}

//Virtual destructor
Hotel::~Hotel() {}