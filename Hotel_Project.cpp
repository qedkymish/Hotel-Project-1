//Qusay Edkymish
//Nov/17th/2024
//Hotel Project 2

#include "Hotel.h"

int main()
{
	//Create instence
	Hotel hotel;

	//Display the program Header
	hotel.displayHeader();

	//Set today's date
	hotel.setDate();

	//Initialize the log for the entered date
	hotel.initializeLog();

	//Display the main Menu
	hotel.mainMenu();

	//Archive the current data
	hotel.archiveDailyLog();

	//Exit the program.
	return 0;
}
