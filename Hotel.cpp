//Qusay Edkymish
//Nov/17th/2024
//Hotel class for hotel reservation sys.

//Hotel.cpp
#include "Hotel.h"


//Constructor 
Hotel::Hotel()
{
	//Seeds random number generation for random room assignment.
	srand(static_cast<unsigned int>(time(0)));
}

//Setter for the date
void Hotel::setDate()
{
	//Variable to store user input
	string inputDate;

	//Pattern for input validation
	regex datePattern("^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/20\\d{2}$");

	//Loop to validate the input
	while (true)
	{
		//Prompt the user to enter the date
		cout << "Please enter today's date (MM/DD/YYYY): ";
		cin >> inputDate;

		//Validate the input
		if (regex_match(inputDate, datePattern))
		{
			int month = stoi(inputDate.substr(0, 2));
			int day = stoi(inputDate.substr(3, 2));

			//Validate the date to ensure its valid calendar
			if ((month == 2 && day <= 29) ||
				((month == 4 || month == 6 || month == 9 || month == 11) && day <= 30) ||
				((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day <= 31))
			{
				date = inputDate; //Valid date
				replace(date.begin(), date.end(), '/', '-'); //Replace '/' with '-'
				break;
			}
		}

		//WIP, add option to let users quit if they want
		
		//Inform the user about invalid input.
		cout << "Invalid date. Ensure it's in MM/DD/YYYY format and a valid calendar date.\n";
	}
}

//Getter for the date
string Hotel::getDate() const
{
	return date;
}

//Initialize log for the current date
void Hotel::initializeLog()
{
	// Replace '/' with '-' in the date
	string formattedDate = date;
	replace(formattedDate.begin(), formattedDate.end(), '/', '-');

	// Today's log file name
	string logFilename = "reservations_log_" + formattedDate + ".csv";
	ifstream logFile(logFilename);

	// If the log file doesn't exist, start fresh and inform the user
	if (!logFile.is_open())
	{
		cout << "\nNo log file found for today (" << date << "). Starting fresh.\n";
		return;
	}

	// Inform the user that the log is loading
	cout << "\nLoading previous session's log from " << logFilename << "\n";

	string line;
	getline(logFile, line); // Skip the header line (Date, Action, ...)

	while (getline(logFile, line))
	{
		// Parse the line using a stringstream
		stringstream ss(line);
		string logDate, action, roomType, status, customerName, customerPhone, customerEmail;
		int roomNumber = 0;
		double revenue = 0.0;

		// Extract individual fields from the log entry
		getline(ss, logDate, ',');
		getline(ss, action, ',');
		getline(ss, roomType, ',');
		ss >> roomNumber;
		ss.ignore(); // Skip comma
		getline(ss, status, ',');
		ss >> revenue;
		ss.ignore(); // Skip comma
		getline(ss, customerName, ',');
		getline(ss, customerPhone, ',');
		getline(ss, customerEmail, ',');

		// Skip invalid input, such as failed attempts
		if (ss.fail() || roomNumber <= 0)
		{
			cerr << "Skipping invalid log entry: " << line << "\n";
			continue;
		}

		//Create a Customer object
		Customer customer(customerName, customerPhone, customerEmail);

		// Update room states based on the log
		if (action == "Reservation" && status == "Confirmed")
		{
			if (roomType == "Courtyard")
				standardRoom.reserve(roomNumber, customer);
			else if (roomType == "Scenic")
				scenicRoom.reserve(roomNumber, customer);
			else if (roomType == "Deluxe Suite")
				deluxeSuite.reserve(roomNumber, customer);
			else if (roomType == "Penthouse")
				penthouse.reserve(roomNumber, customer);
		}
		else if (action == "Cancellation" && status == "Cancelled")
		{
			if (roomType == "Courtyard")
				standardRoom.cancelReservation(roomNumber, customer);
			else if (roomType == "Scenic")
				scenicRoom.cancelReservation(roomNumber, customer);
			else if (roomType == "Deluxe Suite")
				deluxeSuite.cancelReservation(roomNumber, customer);
			else if (roomType == "Penthouse")
				penthouse.cancelReservation(roomNumber, customer);
		}

		// Add the valid log entry to the in-memory log
		todaysLogEntries.push_back(line);
	}

	// Close the file after reading
	logFile.close();

	// Inform the user that the log is successfully loaded
	cout << "Log for " << date << " loaded successfully.\n";
}

//Method to printout menu name
void Hotel::menuName(const string& name) const
{
	//Define a minimum width for the title box
	int minWidth = 30;  //Set a minimum width to keep borders wide enough
	int totalWidth = max(static_cast<int>(name.size()) + 8, minWidth);  //Ensure padding, minimum width

	//Calculate padding on each side for centering
	int padding = (totalWidth - static_cast<int>(name.size())) / 2;

	//Top border
	cout << "\n" << string(totalWidth, '=') << "\n";

	//Centered title with padding
	cout << string(padding, ' ') << name << string(padding, ' ');

	//If the title length is odd, add one extra space for alignment
	if (static_cast<int>(name.size()) % 2 != 0)
	{
		cout << " ";
	}

	cout << "\n";

	//Bottom border
	cout << string(totalWidth, '=') << "\n\n";
}

//Method to display the program's header
void Hotel::displayHeader() const
{
	//Print program title
	menuName("Grossmont Hotel Reservation System");

	//Prompt user to start the program.
	cout << "Welcome! Press any key to start...\n";
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
		menuName("Main Menu");

		//Display main menu options
		cout << "1. Reservations\n";
		cout << "2. Reports\n";
		cout << "3. About\n";
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
			//Display reports menu
			displayReportsMenu();
			break;

		case 3:
			//Display About
			displayAbout();
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
	int choice;              //Variable to store the user's menu selection
	bool subMenu = true;     //Variable to control loop to keep the menu running.

	while (subMenu)
	{
		//Print menu name
		menuName("Reservation");

		//Display menu options
		cout << "1. Standard Room, Courtyard\n";
		cout << "2. Standard Room, Scenic\n";
		cout << "3. Deluxe Suite\n";
		cout << "4. Penthouse\n";
		cout << "5. Cancel Reservation\n";
		cout << "0. Return to main menu\n";

		//Validate user's input.
		while (true)
		{
			cout << "Enter your choice: ";
			if (!(cin >> choice) || choice < 0 || choice > 5)
			{
				cin.clear(); //Clear the error state
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignore any remaining invalid input
				cout << "Invalid input. Please enter a number from 0 to 5.\n";
			}
			else
			{
				break; //Valid input received, exit the validation loop
			}
		}

		//Pointer to the selected room type based on user choice
		Room* selectedRoom = nullptr;

		switch (choice)
		{
		case 1:
			selectedRoom = &standardRoom;
			break;
		case 2:
			selectedRoom = &scenicRoom;
			break;
		case 3:
			selectedRoom = &deluxeSuite;
			break;
		case 4:
			selectedRoom = &penthouse;
			break;
		case 5:
			cancelReservation();
			continue;
		case 0:
			subMenu = false;
			continue;
		default:
			cout << "\nInvalid input! Please try again.\n";
			continue;
		}


		reserve(selectedRoom);


	}
}

// Method to make reservation for a specific type of room
void Hotel::reserve(Room* selectedRoom)
{
	// If a valid room type was selected, proceed with reservation options
	if (selectedRoom)
	{
		cout << "Do you want to pick a specific room? (1 = Yes, 0 = Random): ";
		bool pickRoom;
		cin >> pickRoom;
		cin.ignore(); // Clear the newline character after input

		// Get customer information
		Customer customer = collectCustomerInfo();

		while (true)
		{
			if (pickRoom)
			{
				// Display available rooms and let the user pick one
				displayRoomAvailable(selectedRoom->getName(), *selectedRoom);
				int roomNumber;
				cout << "Enter room number: ";
				cin >> roomNumber;
				cin.ignore(); // Clear the newline character after input

				if (selectedRoom->reserve(roomNumber, customer))
				{
					// Successful reservation for the chosen room
					cout << "\nRoom " << roomNumber << " reserved successfully. Rooms left: "
						<< selectedRoom->getAvailable() << "\n";

					// Log reservation with revenue
					logEntry("Reservation", selectedRoom->getName(), roomNumber, "Confirmed", selectedRoom->getPrice(), customer);

					break; // Exit loop after successful reservation
				}
				else
				{
					// Failed to reserve the chosen room (room not available)
					cout << "\nRoom " << roomNumber << " is not available. Please try another room.\n\n";
					logEntry("Reservation Attempt", selectedRoom->getName(), roomNumber, "Failed", 0.0, customer);
					continue;
				}
			}
			else
			{
				// Randomly assign a room
				int roomNumber = selectedRoom->reserveRandom(customer);
				if (roomNumber != -1)
				{
					// Successful reservation for a randomly chosen room
					cout << "\nRoom " << roomNumber << " reserved successfully. Rooms left: "
						<< selectedRoom->getAvailable() << "\n";
					logEntry("Reservation", selectedRoom->getName(), roomNumber, "Confirmed", selectedRoom->getPrice(), customer);
					break;
				}
				else
				{
					// No rooms available in this type
					cout << "\nNo available rooms in " << selectedRoom->getName() << ".\n\n";
					logEntry("Reservation Attempt", selectedRoom->getName(), -1, "Failed", 0.0, customer);
					break;
				}
			}
		}
	}
}

//Method to collect customer information
Customer Hotel::collectCustomerInfo()
{
	string name, phone, email;

	//Collect customer name (required)
	cout << "\nEnter Customer Name: ";
	getline(cin, name);
	while (name.empty()) 
	{
		cout << "Customer name cannot be empty. Please enter a valid name: ";
		getline(cin, name);
	}

	//Collect phone number (optional)
	cout << "Enter Phone Number (optional, press Enter to skip): ";
	getline(cin, phone);

	// Collect email address (optional)
	cout << "Enter Email Address (optional, press Enter to skip): ";
	getline(cin, email);

	//Return a Customer object with the provided information
	return Customer(name, phone, email);
}

//  Method to cancel reservation
void Hotel::cancelReservation()
{
	// Cancellation process. Ask for room number to cancel
	int roomNumber;
	cout << "Enter the room number you want to cancel: ";
	cin >> roomNumber;

	Customer customer;

	// Attempt to cancel the reservation. Check each room type to cancel the reservation
	if (standardRoom.cancelReservation(roomNumber, customer))
	{
		logEntry("Cancellation", standardRoom.getName(), roomNumber, "Cancelled", -standardRoom.getPrice(), customer);
		cout << "\nSuccessfully canceled the reservation for room " << roomNumber << " (Courtyard).\n";
	}
	else if (scenicRoom.cancelReservation(roomNumber, customer))
	{
		logEntry("Cancellation", scenicRoom.getName(), roomNumber, "Cancelled", -scenicRoom.getPrice(), customer);
		cout << "\nSuccessfully canceled the reservation for room " << roomNumber << " (Scenic).\n";
	}
	else if (deluxeSuite.cancelReservation(roomNumber, customer))
	{
		logEntry("Cancellation", deluxeSuite.getName(), roomNumber, "Cancelled", -deluxeSuite.getPrice(), customer);
		cout << "\nSuccessfully canceled the reservation for room " << roomNumber << " (Deluxe Suite).\n";
	}
	else if (penthouse.cancelReservation(roomNumber, customer))
	{
		logEntry("Cancellation", penthouse.getName(), roomNumber, "Cancelled", -penthouse.getPrice(), customer);
		cout << "\nSuccessfully canceled the reservation for room " << roomNumber << " (Penthouse).\n";
	}
	else
	{
		logEntry("Cancellation Attempt", "Unknown", roomNumber, "Failed", 0.0, customer);
		cout << "\nCancellation failed. The room number is invalid or not reserved.\n";
	}
}

//Method to display available rooms for a single Room instance
void Hotel::displayRoomAvailable(const string& roomType, const Room& room) const
{
	cout << left << setw(25) << ("Available rooms for " + roomType + ":\n");

	//Fetch available rooms using the getter
	for (int roomNumber : room.getAvailableRooms())
	{
		cout << setw(5) << roomNumber;
	}
	cout << endl;
}

//Method to display reserved rooms for a single Room instance
void Hotel::displayRoomReserved(const string& roomType, const Room& room) const {
	// Define column widths
	const int widthRoomType = 20, widthReservedCount = 15;

	// Print row with room type and reserved count
	cout << left << setw(widthRoomType) << roomType
		<< right << setw(widthReservedCount) << room.getReservedRooms().size()
		<< " | ";

	const auto& reservedRooms = room.getReservedRooms();

	// Check if there are reserved rooms
	if (reservedRooms.empty()) {
		cout << "None\n"; // Display "None" for no reservations
	}
	else 
	{
		// Loop through reserved rooms and display details
		for (const auto& entry : reservedRooms) {
			int roomNumber = entry.first;
			const Customer& customer = entry.second;

			// Indent customer details below the header
			cout << "Room " <<  roomNumber << ": " << customer.getName()
				<< " (" << customer.getPhoneNumber() << ", " << customer.getEmail() << ")\n";
		}
	}
}



//Method to display the reports menu and handle user interaction.
void Hotel::displayReportsMenu() const
{
	int choice;              // Variable to store the user's menu selection
	bool subMenu = true;     // Variable to control loop to keep the menu running.

	while (subMenu)
	{
		//Print menu name
		menuName("Reports");


		cout << "1. Inventory Report for Today\n";
		cout << "2. Revenue Report for Today\n";
		cout << "3. View Archived Logs\n";
		cout << "0. Return to main menu\n";
		cout << "Enter your choice: ";

		//Input validation for user choice
		if (!(cin >> choice) || choice < 0 || choice > 3)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number from 0 to 2.\n";
			continue;
		}

		switch (choice)
		{
		case 1:
			displayInventory();
			break;
		case 2:
			displayRevenue();
			break;
		case 3:
			viewArchivedLogs();
			break;
		case 0:
			subMenu = false;
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
			break;
		}
	}

}

//Method to display the inventory of all room types (today).
void Hotel::displayInventory() const
{
	//Main heading using menuName for the report title
	menuName("The Inventory");

	//Subsection for Available Rooms
	cout << "=== Current Available Rooms ===\n";
	cout << left << setw(20) << "Room Type"
		<< right << setw(15) << "Available Count\n";
	cout << "---------------------------------------------\n";

	//Display available rooms for each type
	cout << left << setw(20) << "Courtyard"
		<< right << setw(15) << standardRoom.getAvailable() << "\n";

	cout << left << setw(20) << "Scenic"
		<< right << setw(15) << scenicRoom.getAvailable() << "\n";

	cout << left << setw(20) << "Deluxe Suite"
		<< right << setw(15) << deluxeSuite.getAvailable() << "\n";

	cout << left << setw(20) << "Penthouse"
		<< right << setw(15) << penthouse.getAvailable() << "\n";

	//Divider line
	cout << "---------------------------------------------\n";

	//Subsection for Reserved Rooms
	cout << "\n=== Current Reserved Rooms ===\n";
	cout << left << setw(20) << "Room Type"
		<< right << setw(15) << "Reserved Count"
		<< " | Room Numbers\n";
	cout << "--------------------------------------------------------\n";

	//Display reserved rooms for each room type
	displayRoomReserved(standardRoom.getName(), standardRoom);
	displayRoomReserved(scenicRoom.getName(), scenicRoom);
	displayRoomReserved(deluxeSuite.getName(), deluxeSuite);
	displayRoomReserved(penthouse.getName(), penthouse);

	//Divider line
	cout << "--------------------------------------------------------\n";


	//Calculate the total counts 
	int totalReserved = standardRoom.getReserved() + scenicRoom.getReserved()
		+ deluxeSuite.getReserved() + penthouse.getReserved();
	int totalAvailable = standardRoom.getAvailable() + scenicRoom.getAvailable()
		+ deluxeSuite.getAvailable() + penthouse.getAvailable();

	//Subsection for Total Count
	cout << "\n=== Total Rooms Count ===\n";
	cout << left << setw(25) << "Total reserved rooms:"
		<< right << setw(10) << totalReserved << "\n";
	cout << left << setw(25) << "Total available rooms:"
		<< right << setw(10) << totalAvailable << "\n";
}

//Getter for the total revenue for the day.
int Hotel::getRevenue() const
{
	//Calculate total revenue
	return standardRoom.calcRevenue() + scenicRoom.calcRevenue()
		+ deluxeSuite.calcRevenue() + penthouse.calcRevenue();
}

//Method to display revenue menu
void Hotel::displayRevenue() const
{
	//Print menu name
	menuName("Revenue");

	//Diplay the revenue for each type of room
	cout << left << setw(20) << "Courtyard: " 
		<< right << setw(10) << "$" << standardRoom.calcRevenue() << "\n";
	cout << left << setw(20) << "Scenic: " 
		<< right << setw(10) << "$" << scenicRoom.calcRevenue() << "\n";
	cout << left << setw(20) << "Deluxe Suite: " 
		<< right << setw(10) << "$" << deluxeSuite.calcRevenue() << "\n";
	cout << left << setw(20) << "Penthouse: " 
		<< right << setw(10) << "$" << penthouse.calcRevenue() << "\n";

	//Display the total revenue
	cout << "\n--------------------------------\n";
	cout << left << setw(20) << "Total revenue:" 
		<< right << setw(10) << "$" << getRevenue() << "\n\n";
}

//Method to display About menu
void Hotel::displayAbout() const
{
	//Print Menu name
	menuName("About This Program");

	//Program information 
	cout << "Program Name: Grossmont Hotel reservation System\n";
	cout << "Version: 0.2.0\n";
	cout << "Developer: Qusay Edkymish\n";

	//Purpose of the program
	cout << "\nPurpose:\n";
	cout << "This project was developed for the CSIS-297 Intermediate C++ Programming course\n";
	cout << "at Grossmont College. It is designed to demonstrate proficiency in object-oriented\n";
	cout << "programming and data management. The hotel reservation system allows users to\n";
	cout << "view available rooms, make reservations, and view detailed reports. Key project\n";
	cout << "goals include applying OOP principles, managing complex data structures, and\n";
	cout << "creating a user-friendly interface.\n";

	//Features of the program
	cout << "\nFeatures:\n";
	cout << "- View and manage available rooms by type, with real-time updates for each category.\n";
	cout << "- Make or cancel reservations, with options for specific room selection or random assignment.\n";
	cout << "- Collect and store customer information during reservations, such as name, phone, and email.\n";
	cout << "- Generate detailed inventory reports, tracking reserved and available rooms.\n";
	cout << "- Generate revenue reports, calculating earnings from reservations and cancellations.\n";
	cout << "- Log all reservation and cancellation activities, including timestamps and revenues.\n";
	cout << "- Archive logs daily into organized files for future reference and retrieval.\n";
	cout << "- Display archived logs by date or view all logs in a well-aligned format.\n";
	cout << "- Input and validate dates to ensure correct format and prevent errors.\n";
	cout << "- Enjoy a user-friendly, formatted interface with clear sections and intuitive navigation.\n";
	cout << "- Benefit from a modular, expandable design, enabling future enhancements and features.\n";

	//Upcoming features for program
	cout << "\nUpcoming Features:\n";
	cout << "- Add a colorful, visually appealing interface to enhance user experience.\n";
	cout << "- Implement advanced filtering options in reports for better data insights.\n";
	cout << "- Provide an option to export reports and logs into PDF formats.\n";
	cout << "- Integrate an option menu for better controling.\n";
	cout << "- And more.....\n";



}

//Log a new entry to both memory and the master log file.
void Hotel::logEntry(const string& action, const string& roomType, int roomNumber,
	const string& status, double revenue, const Customer& customer)
{
	// Create the log entry
	string entry = date + "," + action + "," + roomType + "," + to_string(roomNumber) + "," +
		status + "," + to_string(revenue) + "," + customer.getName() + "," +
		customer.getPhoneNumber() + "," + customer.getEmail();

	// Add the entry to the in-memory log
	todaysLogEntries.push_back(entry);

	// Append to the master log file
	ofstream masterLogFile("master_log.csv", ios::app);
	if (masterLogFile.is_open()) 
	{
		masterLogFile << entry << "\n";
		masterLogFile.close();
	}
	else 
	{
		cerr << "Unable to open master log file.\n";
	}
}

//Archive the current day's log to a dedicated file.
void Hotel::archiveDailyLog()
{
	//Format the archive file name
	string formattedDate = date;
	replace(formattedDate.begin(), formattedDate.end(), '/', '-'); // Replace '/' with '-'
	string archiveFilename = "reservations_log_" + formattedDate + ".csv";

	// Open the archive file
	ofstream archiveFile(archiveFilename, ios::trunc); // Overwrite the file if it exists
	if (archiveFile.is_open()) {
		// Write the header line
		archiveFile << "Date,Action,RoomType,RoomNumber,Status,Revenue,CustomerName,CustomerPhone,CustomerEmail\n";

		// Write all log entries from the current day
		for (const auto& entry : todaysLogEntries) {
			archiveFile << entry << "\n";
		}

		archiveFile.close(); // Close the file
		cout << "Logs for " << date << " archived successfully to " << archiveFilename << ".\n";
	}
	else {
		cerr << "Error: Unable to archive logs.\n";
	}
}


//View archived logs, either for a specific date or all logs.
void Hotel::viewArchivedLogs() const
{
	//Print out the header
	menuName("Hotel's Archive");
	
	//Open the master log file for viewing all logs.
	ifstream logFile;
	logFile.open("master_log.csv");
	
	if (logFile.is_open()) 
	{
		displayLogs(logFile); //Call helper method to display the logs in a formatted way.
		logFile.close();
	}
	else 
	{
		cerr << "No archived logs found." << "\n"; //Inform the user if no log file exists.
	}
}

//Display logs from a given input file stream.
void Hotel::displayLogs(ifstream& logFile) const
{
	//Column widths
	const int widthDate = 12, widthAction = 15, widthRoomType = 15,
		widthRoomNumber = 10, widthStatus = 12, widthRevenue = 8,
		widthName = 12, widthPhone = 12, widthEmail = 20;

	//Summary variables
	double totalRevenue = 0.0;
	int totalReservedRooms = 0;

	//Header
	cout << string(115, '-') << "\n";
	cout << left << setw(widthDate) << "Date"
		<< setw(widthAction) << "Action"
		<< setw(widthRoomType) << "Room Type"
		<< setw(widthRoomNumber) << "Room #"
		<< setw(widthStatus) << "Status"
		<< setw(widthRevenue) << "Revenue"
		<< setw(widthName) << "Name"
		<< setw(widthPhone) << "Phone"
		<< setw(widthEmail) << "Email" << "\n";
	cout << string(115, '-') << "\n";

	string line;
	while (getline(logFile, line)) {
		stringstream ss(line);
		string logDate, action, roomType, status, customerName, customerPhone, customerEmail;
		int roomNumber;
		double revenue;

		//Parse log entry
		getline(ss, logDate, ',');
		getline(ss, action, ',');
		getline(ss, roomType, ',');
		ss >> roomNumber;
		ss.ignore();
		getline(ss, status, ',');
		ss >> revenue;
		ss.ignore();
		getline(ss, customerName, ',');
		getline(ss, customerPhone, ',');
		getline(ss, customerEmail, ',');

		//Print row
		cout << left << setw(widthDate) << logDate
			<< setw(widthAction) << action
			<< setw(widthRoomType) << roomType
			<< setw(widthRoomNumber) << roomNumber
			<< setw(widthStatus) << status
			<< "$" << setw(widthRevenue - 1) << revenue
			<< setw(widthName) << customerName
			<< setw(widthPhone) << customerPhone
			<< setw(widthEmail) << customerEmail << "\n";
	}
	cout << string(115, '-') << "\n";

	//Display summary
	cout << left << setw(20) << "Total Reserved Rooms:" << right << setw(5) << totalReservedRooms << "\n";
	cout << left << setw(20) << "Total Revenue:" << right << setw(5) << "$" << totalRevenue << "\n";
}


//Virtual destructor
Hotel::~Hotel() {}
