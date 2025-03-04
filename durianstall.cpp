
//Include library header file
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>

// Library header file for decoration and displaying purpose 
#include <windows.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <conio.h>
#include <ctime>
#include <chrono>

//Global Constant int
#define SIZE 100

using namespace std;

// Function prototype
void color(DWORD);
void print(string, int, int);
void printART(string, int);
void printWord(string);
void loading(int, int, int);
void welcome();
void exit();
void mainmenu();
void menuhandling();
void validation(string message, void(function()));
void menuPrint();
void writeToFile();
void checkFile(string, string);
void storeDurian();
void addMenu();
void updateMenu();
void deleteMenu();
void storeHistory(string, string, double, double);
void viewMenuHistory();
void restoreMenu();
void displaySpace(int, int);
void transactionHandling();
void viewTransaction();
void addTransaction();
void storeTransaction();
void readTransaction();
void deleteTransaction();
void dateFilter();
void customerNoFilter();
void durianTypeFilter();
void totalPriceFilter();
void dateTime(int&, int&, int&);

// Global variables
int totalDurian = 0;	// To count total durian in array
int space = 0;			// For non-string printing to the centre
int background = 0;		// To change background colour
int actionCounter = 0;	// To count the number of menu handling action
int addCounter = 0;
int customerCounter = 0;
int readCounter = 0;
int index = 0;
double grandTotal = 0;
char check = 'Y';
bool blank = true;		// Check whether the file is blank
bool absent = true;		// Check whether the file is absent
bool cont = false;		// To identify whether the addTransaction function is looped

// Global array
string historyList[1000][5];

// Declaration of structs
struct Durian
{
	string name;
	double minPrice;
	double maxPrice;
};

struct transactionInfo
{
	int durianType;
	double price;
	int customerNo;
	double weight;
	double totalPrice;
	string date;
};

// Declaration and initialisation of struct array
Durian durian[SIZE] = { {"", 0, 0} };
transactionInfo transaction[SIZE] = { {0, 0, 0, 0, 0, ""} };

// Main function
int main()
{
	welcome();
	mainmenu();
	exit();
	return 0;
}


//Welcome function page
void welcome()
{
	// Loading page
	system("Color 02");	// Set the background colour of console to black and text colour to green
	background = 1;	// To print the spaces before the content in black

	// Print the ASCII durian picture and message
	print(" ", 3, 1);
	printART("Durian Picture", 1);
	cout << endl << endl;
	print("=====================================================================", 1, 6);
	print("| * NOTE: Maximise / Enlarge your screen for better experience :) * |", 1, 6);
	print("=====================================================================", 2, 6);
	print("Please wait while we are fetching your information ...", 2, 1);

	// Loading progress bar section
	print("LOADING...", 1, 1);
	loading(23, 7, 1);

	// Welcome page 
	system("cls"); // Clear the screen
	system("Color F0");	// Set the background colour of console to white and text colour to black
	background = 0;	 //To print the space before the content in white
	print("", 2, 0);
	printART("Welcome", -1);  // To print the ASCII art from text file
	return;
}


// Exit program page
void exit()
{
	system("cls");	// Clear the screen
	print("", 2, 0);
	printART("Exit", 1); // To print the ASCII art from text file
	Sleep(3000);  // To let the program sleep for 3 seconds
}


// Main menu page
void mainmenu()
{
	// Clear the screen
	system("cls");

	// Declaration of variable
	string choice;

	// Display title heading and menu choices
	cout << endl;
	printART("StoreName", 1);
	print("                                                                                                     ", 3, 7);
	printWord("MAIN MENU");
	print("===================================================================", 1, 0);
	print("A.  Menu Handling        ", 1, 0);
	print("B.  Transaction Handling ", 1, 0);
	print("C.  Exit the Program     ", 1, 0);
	print("===================================================================", 2, 0);

	// Verification and prompt the user to enter the choice
	do {
		print("Please select your choice >> ", 0, 0);
		cin >> choice;

		//Execute the code inside if statement only if the user key in one character
		if (choice.length() == 1)
		{
			//Validation: lower case and upper case for the first letter
			check = (char)toupper(choice[0]);
			switch (check)
			{
			case'A':	// Navigate to menu handling page
				menuhandling();
				return;
			case 'B':	// Navigate to transaction handling page
				transactionHandling();
				return;
			case 'C':	// Exit the program
				return;
			default:	// Prompt again for correct output if wrong input is detected
				check = '-';
				print("Invalid input! Please enter again.", 2, 4);
				break;
			}
		}
		else
		{
			// Prompt again for correct output if wrong input is detected
			check = '-';
			print("Invalid input! Please enter again.", 2, 4);
		}
	} while (check == '-');
}


//Menu handling page
void menuhandling()
{
	// Clear the screen
	system("cls");

	// Display title heading
	cout << endl;
	printART("StoreName", 1);
	print("                                                                                                  ", 3, 6);
	printWord("MENU HANDLING");

	// Declaration of variable
	int choice = 0, verification = 0;;

	// Verification and prompt the user to enter the choice
	while (verification == 0)
	{
		print("Please select your choice >> ", 0, 0);
		cin >> choice;

		// Validation: only accept integer from 1 to 7
		if (cin.fail())
		{
			cin.clear();// Clear the input
			cin.ignore(1000, '\n'); // Ignore previous 1000 unknown character until next line
			print("Invalid input! Please enter a valid number (1-7).", 2, 4);
			continue;// Proceed to the next iteration
		}
		else
		{
			switch (choice)
			{
			case 1:	// Navigate to add new durian page
				addMenu();
				return;

			case 2:	// Navigate to edit durian page
				updateMenu();
				return;

			case 3:	// Navigate to delete durian page
				deleteMenu();
				return;

			case 4:	// Navigate to restore durian page
				restoreMenu();
				return;

			case 5:	// Navigate to view menu page

				// Clear the screen
				system("cls");

				// Display title heading and menu
				print(" ", 2, 0);
				printART("StoreName", 1);
				print("                                                                                                     ", 3, 7);// for colour
				print("Here is the MENU:", 2, 7);
				menuPrint();
				
				if (totalDurian > 1)
					print("There are total "+to_string(totalDurian)+" types of durian available in JKJT durian stall.", 2, 3);
				else if (totalDurian == 1)
					print("There is only 1 type of durian available in JKJT durian stall.", 2, 3);
				else
					print("There is no durian available in JKJT durian stall.", 2, 3);
				
				// Wait for the user to press ENTER
				print("Press ENTER to exit...", 0, 0);
				cin.ignore();
				cin.get();

				// Navigate back to menu handling page
				menuhandling();
				return;

			case 6:	// Navigate to view menu handling history page
				viewMenuHistory();
				return;

			case 7:	// Navigate back to main menu page
				mainmenu();
				return;

			default:
				// Error message, prompt the user to enter the choice again
				print("Invalid input! Please enter a valid number (1-7).", 2, 4);
				verification = 0;
				break;
			}
		}
	}
}



// Verification: to continue or exit the function
void validation(string message, void(function()))
{
	//Declaration of variable
	string choice;

	// Prompt user to input
	cout << endl;
	print("================================================================", 1, 0);
	print(message, 1, 0);
	print("================================================================", 1, 0);
	print("Y - YES", 1, 3);
	print("N - NO ", 1, 4);
	print("----------------------------------------------------------------", 1, 0);
	print("(Y/N) >> ", 0, 0);
	cin >> choice;

	// To exit to menu handling
	if (choice == "-1")
	{
		print("EXITING! You will proceed to menu handling page...", 0, 11);
		Sleep(1300);
		menuhandling();
		return;
	}

	// Validation: lower case and upper case for the first letter
	check = (char)toupper(choice[0]);

	// Execute the code inside if statement only if the user key in one character
	if (choice.length() == 1)
	{
		switch (check)
		{
		case 'Y':	// Execute the function again if yes
			cout << endl << endl;
			function();
			return;
		case 'N':	// Navigate back to menu handling page if no
			menuhandling();
			return;
		default:	// Prompt again for correct output if wrong input is detected
			print("Invalid input! Please enter again.", 2, 4);
			validation(message, function);
			return;
		}
	}
	else
	{
		print("Invalid input! Please enter again.", 2, 4);
		validation(message, function);
		return;
	}

}


//To check wheteher the file exists or is the file empty
void checkFile(string fileName, string message)
{
	//Open file
	ifstream inFile(fileName.c_str());

	//Check if file is open
	if (inFile.is_open())
	{
		blank = true;
		absent = false;		// The file exists
		string line;
		while (getline(inFile, line))
		{
			blank = false;	// The file is not empty
			break;
		}

		if (blank == true)
		{
			cout << endl;
			print(message, 1, 4);	// Print message when the file is empty
		}
	}
	else
		absent = true;	// The file does not exist

	inFile.close();
}


// To store the content of durian.txt file into durian struct
void storeDurian()
{
	//Declaration of variable
	string discard;

	//Open file 
	ifstream inFile("durian.txt");

	// Check if file is open
	if (inFile.is_open())
	{
		totalDurian = 0;	//Initialise counter for total number of durian
		while (getline(inFile, durian[totalDurian].name))
		{
			// If total number of durian equals to 99(SIZE), stop reading
			if (totalDurian >= SIZE - 1)
			{
				cout << endl << endl;
				print("Warning!", 1, 4);
				print("There are too many durian type in the menu!", 1, 4);
				print("The durian type that are above maximum index " + to_string(SIZE - 1) + " will not be printed...", 1, 4);
				print("Please delete some durian type in the delete function to ensure smooth operation...", 1, 3);
				displaySpace(29, 84);  // Display spaces for alignment purpose
				system("Pause");
				break;
			}

			// Store durian, price into Struct
			inFile >> durian[totalDurian].minPrice;
			inFile >> discard;
			inFile >> durian[totalDurian].maxPrice;
			inFile.ignore();
			totalDurian++;	// Increment total number of durian
		}
	}
	inFile.close();
	return;
}


void writeToFile()
{
	//Open the file for printing
	ofstream outFile("durian.txt");

	// Write to file
	for (int j = 0; j < totalDurian; j++)
	{
		// If not the last durian, print the content with new line
		if (j != totalDurian - 1)
		{
			outFile << durian[j].name << endl;
			outFile << fixed << showpoint << setprecision(2) << durian[j].minPrice << " - " << durian[j].maxPrice << endl;
		}
		// Last durian, print the content without new line
		else if (j == totalDurian - 1)
		{
			outFile << durian[j].name << endl;
			outFile << fixed << showpoint << setprecision(2) << durian[j].minPrice << " - " << durian[j].maxPrice;
		}
	}
	outFile.close();
}


// To print the menu on the user screen 
void menuPrint()
{
	// Call function to check file
	checkFile("durian.txt", "* Please note that the menu is empty! *");

	// Call function to store file content into durian struct
	storeDurian();

	// Display table
	cout << endl;
	printWord("MENU");
	print("===================================================================================================", 1, 0);
	print("|   No.  |                Durian Type                     |             Price Range(RM)           |", 1, 6);
	print("===================================================================================================", 1, 0);
	for (int j = 0; j < totalDurian; j++)
	{
		displaySpace(0, 0);  // Print space before content for alignment purpose

		cout << "|" << setw(5) << right << j + 1 << ".  |      "
			<< setw(42) << left << durian[j].name
			<< setw(8) << left << "|"
			<< setw(11) << left << fixed << setprecision(2) << durian[j].minPrice << " - "
			<< setw(11) << right << durian[j].maxPrice
			<< setw(8) << right << "|" << endl;

		// Display divider if it is not the end of the table
		if (j != totalDurian - 1)
			print("---------------------------------------------------------------------------------------------------", 1, 0);
	}

	// Print  | only when the menu is blank
	if (blank == true)
	{
		for (int i = 0; i < 3; i++)
		{
			displaySpace(0, 0);	// Print space before content for alignment purpose
			cout << "|        |      " << setw(43) << right << "|" << setw(40) << right << "|" << endl;
		}
	}
	print("===================================================================================================", 2, 0);
	return;
}

//============================================================================================================
// Function to for ADDING, UPDATING, and DELETING MENU
//============================================================================================================

// Function to add new durian type and price range 
void addMenu()
{
	//Clear the screen
	system("cls");

	// Call function to print the menu
	menuPrint();

	// Declaration of variables
	double max, min;
	string type;

	//Check if the file exists
	if (absent == true)
	{
		print("The file \"durian.txt\" do not exist!", 1, 4);
		print("To continue, \"durian.txt\" will be created...", 2, 3);
	}

	// Print header
	print("////////////////////////////////////////", 1, 5);
	printWord("Adding...");
	print("////////////////////////////////////////", 1, 5);

	// Option to return to menu handling sub-menu
	print("-------------------------------", 1, 11);
	print("Enter \"-1\" anywhere to exit!", 1, 11);
	print("-------------------------------", 2, 11);

	// Check if the total number of durian exeed the maximum list for struct
	if (totalDurian >= SIZE - 1)
	{
		// Print error message
		print("Warning!", 1, 4);
		print("The total number of durian type has reached the maximum number of durian type in the menu! (" + to_string(SIZE - 1) + ")", 1, 4);
		print("Please delete some of the durian type in the menu if you wish to add a new type of durian...", 1, 2);
		print("Press ENTER to exit...", 0, 0);	// Wait for the user to press ENTER
		cin.ignore();
		cin.get();
		menuhandling();	// Navigate back to menu handling page
		return;
	}
	else
	{
		//Prompt for the user to key in value
		print("  Please enter the information that you would like to add below:  ", 1, 7);
		print("--------------------------------------------------------------------", 1, 0);
		print("New Durian Type        >> ", 0, 0);
		cin.ignore();
		getline(cin, type);

		// To exit to menu handling
		if (type == "-1")
		{
			print("EXITING! The durian type will not be added...", 0, 11);
			Sleep(1000);
			menuhandling();
			return;
		}

		// To check if the durianType entered already existed in the menu
		bool exist = false;
		for (int i = 0; i < totalDurian; i++)
		{
			if (type == durian[i].name)
			{
				print("Durian type existed! Please enter another durian type that you would like to add. ", 1, 4);
				print("*NOTE: You can modify the durian type in Modify section.*", 2, 9);
				exist = true;
				break;
			}
			else
				exist = false;
		}

		// If the durianType entered do not exist in the menu, proceed; else, prompt the user to enter again
		if (exist == false)
		{
			// Initialise verification
			bool verify = false;
			while (verify == false)
			{
				print("New Minimum Price (RM) >> ", 0, 0);
				cin >> min;

				// To exit to menu handling
				if (min == -1)
				{
					print("EXITING! The durian type and price range will not be added...", 0, 11);
					Sleep(1300);
					menuhandling();
					return;
				}

				// Validation: only accept integer/double value
				else if (cin.fail())
				{
					cin.clear();	// Clear the input
					cin.ignore(1000, '\n');  // Ignore previous 1000 unknown character until next line
					print("Invalid input! Please enter again.", 2, 4);
					continue;  // Proceed to the next iteration
				}
				else
				{
					print("New Maximum Price (RM) >> ", 0, 0);
					cin >> max;
					cin.ignore();

					// To exit to menu handling
					if (max == -1)
					{
						print("EXITING! The durian type and price range will not be added...", 0, 11);
						Sleep(1300);
						menuhandling();
						return;
					}

					// Validation: only accept integer/double value
					else if (cin.fail())
					{
						cin.clear();	// Clear the input
						cin.ignore(1000, '\n');  // Ignore previous 1000 unknown character until next line
						print("Invalid input! Please enter again.", 2, 4);
						continue;  // Proceed to the next iteration
					}

					// Check if the minimum price is less than maximum price, if not, prompt for user input again
					else if (min < max)
					{
						verify = true;

						//Write to the file with new line if it is not empty
						if (blank == false)
						{
							ofstream outFile("durian.txt", ios::app);
							outFile << endl;
							outFile.close();
						}

						//Write the new content to the file
						ofstream outFile("durian.txt", ios::app);
						outFile << type << endl;
						outFile << fixed << showpoint << setprecision(2) << min << " - " << max;
						outFile.close();

						// Update Menu Handling History
						storeHistory("ADDED", type, min, max);

						// Print message to screen
						system("cls");	// Clear the screen
						print(" ", 4, 0);
						printWord("Adding...");
						loading(1, 7, 0);	// Display loading progress bar
						cout << endl;
						print("Durian type has been successfully added as follows: ", 1, 2);
						menuPrint();	// Display menu
						cout << endl << endl;
					}
					else
					{
						// Wrong input message, prompt the user to enter again
						print("Invalid input! The maximum price should be greater than minimum price. ", 1, 4);
						print("Please enter again.", 2, 4);
					}
				}
			} 
		}

		// Validation to continue or exit
		validation("Do you want to add another type of durian? ", addMenu);
		return;
	}
	return;
}


// To update durian type and price range
void updateMenu()
{
	// Clear the screen
	system("cls");

	// Call function to display the menu
	menuPrint();

	// Display update header
	print("/////////////////////////////////////////////////////////", 1, 5);// for colour
	printWord("Updating...");
	print("/////////////////////////////////////////////////////////", 1, 5);// for colour

	// Declaration of variables
	int updateInfo;
	bool num = false;
	string type;
	int verification = 0, choiceInt = 0;

	// Check if there is content in the file to update
	if (blank == true)
	{
		// Navigate back to menu handling page if the menu is empty
		print("The menu is empty! There is no durian type to update. ", 1, 4);
		print("Please proceed to ADD function to add durian type into the menu... ", 2, 2);
		print("Press ENTER to return to MENU HANDLING... ", 0, 0);
		cin.ignore();
		cin.get();  // Wait for the user to press ENTER
		menuhandling();
		return;
	}
	else
	{
		// Option to return to menu handling sub-menu
		print("-------------------------------", 1, 11);
		print("Enter \"-1\" anywhere to exit!", 1, 11);
		print("-------------------------------", 2, 11);
		
		//Prompt for user to enter the no. of durian type
		print("  Please select the number of the durian that you would like to update  ", 1, 7);
		print("-------------------------------------------------------------------------", 1, 0);
		print("No. of Durian Type >> ", 0, 0);
		cin >> choiceInt;

		// To exit to menu handling
		if (choiceInt == -1)
		{
			print("EXITING! The menu will not be updated...", 0, 11);
			Sleep(1300);
			menuhandling();
			return;
		}

		// Validation: only accept integer value 
		else if (cin.fail())
		{
			cin.clear();// Clear input
			cin.ignore(1000, '\n');// Ignore previous 1000 unknown character until next line
			print("Invalid input! Please enter again.", 2, 4);
		}

		//	Validation: only accept within number of total durian
		else if (choiceInt <= totalDurian && choiceInt > 0)
		{
			// Find index of matched durian
			index = choiceInt - 1;
			num = true;
			cout << endl << endl;

			// Display found durian and price range
			print("  Found as below :  ", 1, 7);
			print("----------------------------------------------------", 1, 0);
			print("Durian Type: " + durian[index].name + "           ", 1, 0);
			displaySpace(0, 0);
			cout << "Price Range: " << fixed << showpoint << setprecision(2) << "RM " << durian[index].minPrice << " - " << "RM " << durian[index].maxPrice << endl;
			print("----------------------------------------------------", 2, 0);

			//To prompt for the user to enter what information that need to be updated
			do
			{
				print("  UPDATE OPTION  ", 0, 7);
				print(" ", -1, 0);
				cout << endl;
				print("----------------------------------------------------", 1, 0);
				print("1: Durian type ", 1, 0);
				print("2: Price range ", 1, 0);
				print("----------------------------------------------------", 1, 0);
				print("Please enter the option that you would like to update >> ", 0, 0);
				cin >> updateInfo;

				// To exit to menu handling
				if (updateInfo == -1)
				{
					print("EXITING! The menu will not be updated...", 0, 11);
					Sleep(1300);
					menuhandling();
					return;
				}

				// Validation: only accept integer value 
				else if (cin.fail())
				{
					cin.clear();// Clear input
					cin.ignore(1000, '\n');// Ignore previous 1000 unknown character until next line
					print("Invalid input! Please enter a valid number (1 or 2).", 2, 4);
					continue;// Proceed to the next iteration
				}

				// Update new durian type
				else if (updateInfo == 1)
				{
					cout << endl;
					print("  UPDATE DURIAN TYPE  ", 0, 7);
					print(" ", -1, 0);
					cout << endl;
					print("----------------------------------------------------", 1, 0);
					print("New Durian type  >>  ", 0, 0);
					cin.ignore();
					getline(cin, type);

					// To exit to menu handling
					if (type == "-1")
					{
						print("EXITING! The durian type will not be updated...", 0, 11);
						Sleep(1300);
						menuhandling();
						return;
					}

					// To check if the durian type exist, if exist , the user need to update another durian to avoid 2 durian with same type 
					int exist = 0;
					for (int i = 0; i < totalDurian; i++)
					{
						if (type == durian[i].name)
							exist++;
					}

					// If the durian type do not exist, proceed; else prompt the user to update another durian type
					if (exist == 0)
					{
						// Update History
						storeHistory("UPDATED Durian Type", durian[index].name + " --> " + type, durian[index].minPrice, durian[index].maxPrice);

						// Update durian type in the durian struct
						durian[index].name = type;
						cout << endl << endl;
						verification = 1;
					}

					// Invalid input Message, prompt the user to enter again
					else
					{
						print("Durian type \"" + type + "\" existed !", 1, 4);
						print("Please update to another type of durian to avoid conflict.", 1, 4);
						print("* NOTE: OR update its price range instead... *", 2, 9);
						verification = 0;
					}
				}

				// Update new price range
				else if (updateInfo == 2)
				{
					cout << endl;
					print("  UPDATE PRICE RANGE  ", 0, 7);
					print(" ", -1, 0);
					cout << endl;
					print("----------------------------------------------------", 1, 0);

					// To prompt for the user to enter the new price range
					bool input = false;
					while (input == false)
					{
						print("New Minimum price >> ", 0, 0);
						cin >> durian[index].minPrice;

						// To exit to menu handling
						if (durian[index].minPrice == -1)
						{
							print("EXITING! The price range will not be updated...", 0, 11);
							Sleep(1300);
							menuhandling();
							return;
						}

						// Validation: only accept integer value
						else if (cin.fail())
						{
							cin.clear();  // Clear input
							cin.ignore(1000, '\n');  // Ignore previous 1000 unknown character until next line
							print("Invalid input! Please enter a valid price.", 2, 4);
							continue;  // Proceed to the next iteration
						}

						print("New Maximum price >> ", 0, 0);
						cin >> durian[index].maxPrice;

						// To exit to menu handling
						if (durian[index].maxPrice == -1)
						{
							print("EXITING! The price range will not be updated...", 0, 11);
							Sleep(1300);
							menuhandling();
							return;
						}

						// Validation: only accept integer value
						else if (cin.fail())
						{
							cin.clear();  // Clear input
							cin.ignore(1000, '\n');  // Ignore previous 1000 unknown character until next line
							print("Invalid input! Please enter a valid price.", 2, 4);
							continue;  // Proceed to the next iteration
						}

						//Check if minumum price is less than maximum price
						else if (durian[index].minPrice < durian[index].maxPrice)
						{
							input = true;

							// Update History
							storeHistory("UPDATED Price Range", durian[index].name, durian[index].minPrice, durian[index].maxPrice);
						}
						else
						{
							// Invalid input Message, prompt the user to enter again
							print("Invalid input! The maximum price should be greater than minimum price.", 1, 4);
							print("Please enter again.", 2, 4);
							input = false;
						}
					}
					verification = 1;
				}
				else
				{
					// Invalid input Message, prompt the user to enter again
					print("Invalid input! Please enter a valid number (1 or 2).", 2, 4);
					verification = 0;
				}
			} while (verification == 0);

			// Call function to write the durian struct to file
			writeToFile();

			// Clear the screen and display updated message
			system("cls");
			print(" ", 4, 0);
			printWord("Updating...");
			loading(1, 7, 0);	// Display loading animation
			cout << endl;
			print("Menu has been successfully updated as followed: ", 1, 2);
			menuPrint();	//Display menu
		}
		else
		{
			// Wrong input validation
			print("Unable to find!", 1, 4);
			print("Please enter the correct no. of durian type to update, from 1 to " + to_string(totalDurian) + " inclusive .", 2, 4);
		}

		// Validation to continue or exit
		validation("Do you want to update another type of durian? ", updateMenu);
		return;	
		
	}
	return;
}


// To delete unwanted durian type and price range 
void deleteMenu()
{
	//Clear the screen
	system("cls");

	// Call function to print the menu
	menuPrint();

	// Declaration of variable
	int choiceInt = 0, selection = 0;

	// Call function to print title header
	print("//////////////////////////////////////////////////////", 1, 5);
	printWord("Deleting...");
	print("//////////////////////////////////////////////////////", 1, 5);

	// To check if there is content in the file to delete
	if (blank == true)
	{
		// Navigate back to menu handling page if the menu is empty (prompt the user to add the durian)
		print("The menu is empty! There is no durian type to delete. ", 1, 4);
		print("Please proceed to ADD function to add durian type into the menu... ", 2, 2);
		print("Press ENTER to return to MENU HANDLING... ", 0, 0);
		cin.ignore();
		cin.get();// Wait for the user to press ENTER
		menuhandling();	// Return to menu handling
		return;
	}
	else
	{		
		// Option to return to menu handling sub-menu
		print("-------------------------------", 1, 11);
		print("Enter \"-1\" anywhere to exit!", 1, 11);
		print("-------------------------------", 2, 11);

		// Display option for delete
		print("  DELETE OPTION  ", 1, 7);
		print("----------------------------------------------------------------", 1, 0);
		print("1: Delete 1 type of durian                             ", 1, 0);
		print("2: Delete all durian type and price range (Clear menu) ", 1, 0);
		print("----------------------------------------------------------------", 2, 0);

		// To prompt for the user to enter the choice
		bool option = false;
		while (option == false)
		{
			print("Please enter the option that you would like to delete >> ", 0, 0);
			cin >> selection;

			// To exit to menu handling
			if (selection == -1)
			{
				print("EXITING! The durian type will not be deleted...", 0, 11);
				Sleep(1300);
				menuhandling();
				return;
			}

			// Validation: only accept integer value
			else if (cin.fail())
			{
				cin.clear();// Clear input
				cin.ignore(1000, '\n');// Ignore previous 1000 unknown character until next line
				print("Invalid input! Please enter again.", 2, 4);
				continue;// Proceed to the next iteration
			}

			// Valid input --> break the while loop
			else if (selection == 1 || selection == 2)
				option = true;

			// Invalid input message, prompt the user to enter again
			else
			{
				option = false;
				print("Invalid input! Please enter a valid number (1 or 2).", 2, 4);
			}
		}

		// Delete 1 durian type
		if (selection == 1)
		{
			//Prompt for user to enter the durian type and store
			cout << endl;
			print("  DELETE 1 DURIAN TYPE  ", 0, 7);
			print(" ", -1, 0);
			cout << endl;
			print("----------------------------------------------------------------", 1, 0);
			print("Please enter the no. of durian type to delete, from 1 to " + to_string(totalDurian) + " inclusive:", 1, 0);

			bool num = false;
			while (num == false)
			{

				print("No. of Durian Type >> ", 0, 0);
				cin >> choiceInt;

				// To exit to menu handling
				if (choiceInt == -1)
				{
					print("EXITING! The durian type will not be deleted...", 0, 11);
					Sleep(1300);
					menuhandling();
					return;
				}

				// Validation: only accept integer value
				else if (cin.fail())
				{
					cin.clear();// Clear input
					cin.ignore(1000, '\n');// Ignore previous 1000 unknown character until next line
					print("Invalid input! Please enter again.", 2, 4);
					continue;// Proceed to the next iteration
				}

				// Check if the no. of durianType is within the range 
				else if (choiceInt <= totalDurian && choiceInt > 0)
				{
					//Find index of matched durian
					index = choiceInt - 1;
					num = true;

					// Update Menu Handling History
					storeHistory("DELETED", durian[index].name, durian[index].minPrice, durian[index].maxPrice);

					// Delete durian from the struct
					for (int i = index; i < SIZE - 1; i++)
					{
						// Replace the durian entered and move all elements on space ahead
						durian[i].name = durian[i + 1].name;
						durian[i].minPrice = durian[i + 1].minPrice;
						durian[i].maxPrice = durian[i + 1].maxPrice;
					}

					// Reduce the number of durian (deleted)
					totalDurian--;

					//Call the function to write durian struct to the file
					writeToFile();

					// Clear the screen
					system("cls");

					// Display the deleted successfully messages
					cout << endl << endl << endl << endl;
					printWord("Deleting...");
					loading(1, 7, 0);	// Display loading progress bar
					Sleep(900);
					cout << endl;
					print("Successfully deleted!!", 2, 2);

					// Display the latest menu
					print("Here is the latest menu: ", 1, 0);
					menuPrint();
				}
				else
				{
					// Invalid input message, prompt the user to enter again
					print("Unable to find!", 1, 4);
					print("Please enter the correct no. of durian type to delete, from 1 to " + to_string(totalDurian) + " inclusive.", 2, 4);
				}

			}

			// Validation to continue or exit
			validation("Do you want to delete another type of durian? ", deleteMenu);
			return;
		}

		// Delete all durian types and price ranges
		else
		{
			string choice;
			cout << endl;
			print("  DELETE ALL DURIAN TYPES  ", 0, 7);
			print(" ", -1, 0);
			cout << endl;
			print("----------------------------------------------------------------", 1, 0);

			// Prompt for user to confirm the deletion
			do {
				print("Are you sure you want to delete all durian types? The menu will be empty...", 1, 2);
				print("Y - YES", 1, 3);
				print("N - NO ", 1, 4);
				print("(Y/N) >> ", 0, 0);
				cin >> choice;

				// To exit to menu handling
				if (choice == "-1")
				{
					print("EXITING! All the durian types will not be deleted...", 0, 11);
					Sleep(1300);
					menuhandling();
					return;
				}

				// Validation: lower case and upper case for the first letter
				check = (char)toupper(choice[0]);// character 

				// Execute the code inside if statement only if the user key in one character
				if (choice.length() == 1)
				{
					switch (check)
					{
					case 'Y':	// Break the loop to delete all durian types and price ranges
						break;
					case 'N':	// Validation to continue or exit	
						cout << endl;
						validation("Do you still want to delete durian type(s)? ", deleteMenu);
						return;
					default:	//Prompt again for correct output if wrong input is detected
						check = '-';
						print("Invalid input! Please enter again.", 2, 4);
						break;
					}
				}
				else
				{
					//Prompt again for correct output if wrong input is detected
					check = '-';
					print("Invalid input! Please enter again.", 2, 4);
				}
			} while (check == '-');

			// Update Menu Handling History
			for (int i = 0; i < totalDurian; i++)
			{
				storeHistory("DELETED ALL (" + to_string(i + 1) + ")", durian[i].name, durian[i].minPrice, durian[i].maxPrice);
			}

			// Delete all the content in the file
			ofstream outFile("durian.txt", ios::trunc);
			outFile.close();

			//Clear the screen
			system("cls");

			// Print successfully deleted message
			print(" ", 5, 0);
			printWord("Deleting...");
			loading(1, 7, 0);
			Sleep(900);
			print(" ", 2, 0);
			print("Successfully deleted all durian types and price range!!", 2, 2);

			// Print menu
			print("The menu has been cleared as follows: ", 1, 0);
			menuPrint();

			// Wait for the user to press ENTER to exit to MENU HANDLING
			print("Press ENTER to exit: ", 0, 0);
			cin.ignore();
			cin.get();
			menuhandling();
			return;
		}
	}
	return;
}



//============================================================================================================
// Extra : ADD/UPDATE/DELETE HISTORY + RESTORE function
//============================================================================================================
// To store menu handling history into global array: historyList[][]
void storeHistory(string action, string durian, double min, double max)
{
	// Declaration of variable
	string dateTime;

	// Update actionCounter
	actionCounter++;

	// Store new info into nested array
	historyList[actionCounter][0] = action;
	historyList[actionCounter][1] = durian;
	historyList[actionCounter][2] = to_string(min).erase(to_string(min).find(".") + 3, 100);
	historyList[actionCounter][3] = to_string(max).erase(to_string(max).find(".") + 3, 100);

	// Access system time
	auto nowtime = chrono::system_clock::to_time_t(chrono::system_clock::now());
	dateTime = ctime(&nowtime);
	dateTime[dateTime.length() - 1] = '\0';  // Remove \n to prevent printing new line
	
	// Store dateTime into historyList array
	historyList[actionCounter][4] = dateTime;
}

// To print menu handling history
void viewMenuHistory()
{
	// Clear the screen
	system("cls");

	// Print Header
	printART("StoreName", 1);
	print("                                                                                                     ", 3, 7);
	printWord("MENU HANDLING HISTORY");

	// Print Table
	print("===========================================================================================================================================", 1, 0);
	print("|  No. |       Action Taken       |              Durian Type                 |       Price Range(RM)      |              Time             |", 1, 6);
	print("===========================================================================================================================================", 1, 0);

	for (int i = 1; i <= actionCounter; i++)
	{
		displaySpace(0, 0);		// Print spaces before content for alignment purpose
		// Display content in historyList array
		cout << "|" << setw(4) << right << to_string(i) << ". |   "
			<< setw(23) << left << historyList[i][0]
			<< setw(4) << left << "|"
			<< setw(39) << left << historyList[i][1]
			<< setw(4) << left << "|"
			<< setw(10) << left << fixed << setprecision(2) << historyList[i][2] << " - "
			<< setw(10) << right << fixed << setprecision(2) << historyList[i][3] << "  "
			<< setw(4) << left << "|"
			<< setw(29) << left << historyList[i][4] << "|" << endl;

		// Display divider if it is not the end of the table
		if (i != actionCounter)
			print("-------------------------------------------------------------------------------------------------------------------------------------------", 1, 0);
	}

	// Print only | when the history is blank
	if (actionCounter == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			displaySpace(0, 0);	// Display spaces for alignment purpose
			cout << "|      |" << setw(27) << right << "|" << setw(43) << right << "|" << setw(29) << right << "|" << setw(32) << right << "|" << endl;
		}
	}
	print("===========================================================================================================================================", 1, 0);

	// Display message if the history is blank
	if (actionCounter == 0)
		print("No action taken yet! The menu hasn't been edited.", 1, 3);

	// Wait for the user to press ENTER to exit to MENU HANDLING
	print("Press ENTER to exit... ", 0, 0);
	cin.ignore();
	cin.get();
	menuhandling();
	return;
}

// To restore deleted durian type and price range from menu handling history
void restoreMenu()
{
	// Clear the screen
	system("cls");

	// Check the content of the file and store to durian struct
	storeDurian();

	// Print title header
	printART("StoreName", 1);
	print("                                                                                                     ", 3, 7);
	printWord("Restoring...");
	cout << endl;
	print("Here is a list of previously DELETED DURIAN TYPE and PRICE RANGE to be restored: ", 1, 0);

	// Declaration of array and variables
	string restoreList[1000][3];
	int numDurian = 0;
	int choiceInt = 0;

	// Store deleted durian types and price ranges into array
	for (int i = 1; i <= actionCounter; i++)
	{
		if (historyList[i][0][0] == 'D')
		{
			restoreList[numDurian][0] = historyList[i][1];
			restoreList[numDurian][1] = historyList[i][2];
			restoreList[numDurian][2] = historyList[i][3];
			numDurian++;	// Update number of durian deleted
		}
	}

	// Print table
	print("===================================================================================================", 1, 0);
	print("|   No.  |                Durian Type                     |             Price Range(RM)           |", 1, 6);
	print("===================================================================================================", 1, 0);

	for (int i = 0; i < numDurian; i++)
	{
		displaySpace(0, 0);	 // Print space before content for alignment purpose

		// Display content in restoreList array
		cout << "|" << setw(5) << right << i + 1 << ".  |      "
			<< setw(42) << left << restoreList[i][0]
			<< setw(8) << left << "|"
			<< setw(11) << left << restoreList[i][1] << " - "
			<< setw(11) << right << restoreList[i][2]
			<< setw(8) << right << "|" << endl;

		// Display divider if it is not the end of the table
		if (i != numDurian - 1)
			print("---------------------------------------------------------------------------------------------------", 1, 0);
	}

	// Print only | when there is no deleted durian
	if (numDurian == 0)
		for (int i = 0; i < 3; i++)
		{
			displaySpace(0, 0);
			cout << "|        |      " << setw(43) << right << "|" << setw(40) << right << "|" << endl;

		}
	print("===================================================================================================", 2, 0);

	// Display message if there is no deleted durian and return to menu handling page
	if (numDurian == 0)
	{
		print("There is no deleted durian to restore!", 1, 3);
		print("Press ENTER to exit... ", 0, 0);
		cin.ignore();
		cin.get();// Wait for the user to press ENTER
		menuhandling();
		return;
	}

	// Check if the total number of durian exceed the maximum list for struct (SIZE)
	else if (totalDurian >= SIZE - 1)
	{
		// Display warning message and return to menu handling page
		print("Warning!", 1, 4);
		print("The total number of durian type has reached the maximum number of durian type in the menu! (" + to_string(SIZE - 1) + ")", 1, 4);
		print("Please delete some of the durian type in the menu if you wish to restore a deleted durian...", 1, 4);
		print("Press ENTER to exit...", 0, 4);
		cin.ignore();
		cin.get();  // Wait for the user to press ENTER
		menuhandling();
		return;
	}
	else
	{
		// Option to return to menu handling sub-menu
		print("-------------------------------", 1, 11);
		print("Enter \"-1\" anywhere to exit!", 1, 11);
		print("-------------------------------", 2, 11);

		// Prompt the user to enter the number of the durian to be restored
		bool num = false;
		while (num == false)
		{
			print("Please enter the no. of durian type that you would like to restore: ", 1, 7);
			print("------------------------------------------------------------------", 1, 0);
			print("No. of Durian Type >> ", 0, 0);
			cin >> choiceInt;

			// To exit to menu handling
			if (choiceInt == -1)
			{
				print("EXITING! The durian type and price range will not be restored...", 0, 11);
				Sleep(1300);
				menuhandling();
				return;
			}

			// Validation: only accept when the input is integer value
			else if (cin.fail())
			{
				cin.clear();  // Clear the input
				cin.ignore(1000, '\n');  // Ignore previous 1000 unknown character until next line
				print("Invalid input! Please enter a valid number.", 2, 4);
				continue;  // Proceed to the next iteration
			}

			// Check if the no. of durian type is within the range
			else if (choiceInt <= numDurian && choiceInt > 0)
			{
				// To check if the durianType entered already existed in durian array
				bool exist = false;
				for (int i = 0; i < totalDurian; i++)
				{
					index = choiceInt - 1;
					if (restoreList[index][0] == durian[i].name)
					{
						print("Durian type existed in the menu! Please enter another no. of durian type that you would like to restore. ", 1, 4);
						print("*NOTE: You can view the menu in VIEW MENU section.*", 2, 4);
						exist = true;
						break;
					}
					else
						exist = false;
				}

				// Proceed if the durian type don't exist in the menu
				if (exist == false)
				{
					num = true;

					// Update Menu Handling History
					storeHistory("RESTORED", restoreList[index][0], stod(restoreList[index][1]), stod(restoreList[index][2]));

					// Write to the file with new line if it is not empty
					if (blank == false)
					{
						ofstream outFile("durian.txt", ios::app);
						outFile << endl;
						outFile.close();
					}

					// Write the new content to the file
					ofstream outFile("durian.txt", ios::app);
					outFile << restoreList[index][0] << endl;
					outFile << fixed << showpoint << setprecision(2) << restoreList[index][1] << " - " << restoreList[index][2];
					outFile.close();

					// Clear the screen
					system("cls");

					// Print successful resotred message
					cout << endl << endl << endl << endl;
					printWord("Restoring...");
					loading(1, 7, 0);	// Display loading progress bar 
					Sleep(900);
					cout << endl;
					print("Successfully restored from bin!!", 2, 2);

					// Print menu
					print("Here is the latest menu: ", 1, 0);
					menuPrint();
				}

				//Verification
				validation("Do you want to restore more deleted durian from bin? ", restoreMenu);
				return;
			}
			else
			{
				// Display error message if the input is not in the range
				print("Unable to find!", 1, 4);
				print("Please enter the correct no. of durian type to restore", 2, 4);
			}
		}
	}
}


//============================================================================================================
// Function to for transaction handling
//============================================================================================================

void dateTime(int& year, int& month, int& day)
{
	// Current date and time based on current system
	time_t now = time(0);

	tm* ltm = localtime(&now);

	// Date
	year = 1900 + ltm->tm_year;
	month = 1 + ltm->tm_mon;
	day = ltm->tm_mday;

	return;
}

void transactionHandling()
{
	// Declaration and initialisation of variable
	string option;
	bool valid = true;

	// Clear screen
	system("cls");

	// Sub-menu header
	cout << endl;
	printART("StoreName", 1);
	print("                                                                                                  ", 3, 7);

	printWord("TRANSACTION HANDLING");

	// Choices
	print("===================================================================", 1, 0);
	print("                    1. View Transaction History                    ", 1, 0);
	print("                    2. Add Transaction                             ", 1, 0);
	print("                    3. Delete Transaction                          ", 1, 0);
	print("                    4. Back to Main Menu                           ", 1, 0);
	print("===================================================================", 1, 0);
	cout << endl;

	// Input validation
	do
	{
		valid = true;

		// Prompt for user to enter choice
		print("Please select your choice: ", 0, 0);
		cin >> option;

		if (option.length() == 1)
		{
			check = option[0];

			// Selection
			if (check == '1')
			{
				viewTransaction();
				return;
			}
			else if (check == '2')
			{
				addTransaction();
				return;
			}
			else if (check == '3')
			{
				deleteTransaction();
				return;
			}
			else if (check == '4')
			{
				mainmenu();
				return;
			}
			else
			{
				valid = false;
			}
		}
		else
		{
			valid = false;
		}

		if (valid == false)
		{
			print("Invalid input. Available choices: 1 - 4", 2, 4);
		}

	} while (valid == false);

	return;
}


void viewTransaction()
{
	// Declaration and initialisation of variables
	string transactionNo;
	string customerNo;
	string date;
	string name;
	string price;
	string weight;
	string totalPrice;
	string response;
	bool valid = true;

	// Clear screen
	system("cls");

	// Sub-menu header
	print("", 1, 0);
	printWord("TRANSACTION HISTORY");
	print("", 1, 0);
	print("(Displaying All)", 2, 0);

	// Check whether transaction.txt exists or is the file empty
	checkFile("transaction.txt", "");

	if (absent == true)  // If transaction.txt does not exist
	{
		print("", 5, 0);
		print("The file \"transaction.txt\" cannot be found", 1, 4);
		print("Please go to Add Transaction to create the file", 1, 4);
		print("", 1, 0);
		displaySpace(32, 0);  // Display spaces for alignment purpose
		system("pause");

		// Navigate back to transaction handling sub-menu
		transactionHandling();
		return;
	}
	else if (blank == true)  // If transaction.txt is empty
	{

		print("", 5, 0);
		print("There is no transaction history", 1, 4);
		print("", 1, 0);
		displaySpace(32, 0);  // Display spaces for alignment purpose
		system("pause");

		// Navigate back to transaction handling sub-menu
		transactionHandling();
		return;
	}

	// Calling of readTransaction() to read the content of transaction history
	readTransaction();

	// Display all transaction history
	for (int i = 0; i < readCounter; i++)
	{
		transactionNo = "Transaction No." + to_string(i + 1);
		customerNo = "Customer No.       : " + to_string(transaction[i].customerNo);
		date = "Date               : " + transaction[i].date;
		name = "Durian Type        : " + durian[i].name;
		price = "Price per kg       : RM " + to_string(transaction[i].price).erase(to_string(transaction[i].price).find(".") + 3, 100);
		weight = "Weight             : " + to_string(transaction[i].weight).erase(to_string(transaction[i].weight).find(".") + 3, 100) + " kg";
		totalPrice = "Total Price        : RM " + to_string(transaction[i].totalPrice).erase(to_string(transaction[i].totalPrice).find(".") + 3, 100);

		print("", 1, 0);
		print("=====================================================================", 1, 0);
		print(transactionNo, 1, 3);
		print("=====================================================================", 1, 0);
		print(customerNo, 1, 0);
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << date << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << name << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << price << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << weight << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << totalPrice << endl;
	}

	// Prompt the user to select filter to view
	print("", 2, 0);
	print("==========================================================", 1, 11);
	print("Enter \"-1\" to go back to Transaction Handling sub-menu", 1, 11);
	print("==========================================================", 3, 11);
	cin.ignore();

	do
	{
		valid = true;

		print("=======================================", 1, 0);
		print("Do you want to apply a filter", 1, 0);
		print("=======================================", 1, 0);
		print("Y - YES", 1, 3);
		print("N - NO ", 1, 4);
		print("---------------------------------------", 1, 0);
		displaySpace(10, 40);  // Display spaces for alignment purpose
		cout << "(Y/N) >> ";

		getline(cin, response);
		check = toupper(response[0]);

		if (response == "-1")
		{
			// Navigate back to transaction handling sub-menu
			transactionHandling();
			return;
		}
		else if ((check == 'Y') && (response.length() == 1))
		{
			do
			{
				cout << endl;
				print("=======================================", 1, 0);
				print("Please select the attrubute to filter", 1, 0);
				print("=======================================", 1, 0);
				print("1. Date        ", 1, 0);
				print("2. Customer No.", 1, 0);
				print("3. Durian type ", 1, 0);
				print("4. Total price ", 1, 0);
				print("---------------------------------------", 1, 0);
				displaySpace(9, 40);  // Display spaces for alignment purpose
				cout << "Filter: ";

				getline(cin, response);
				check = toupper(response[0]);

				if (response == "-1")
				{
					// Navigate back to transaction handling sub-menu
					transactionHandling();
					return;
				}
				else if ((check == '1') && (response.length() == 1))
				{
					// Calling of dateFilter() to filter the transaction history by date
					dateFilter();
					return;

				}
				else if ((check == '2') && (response.length() == 1))
				{
					// Calling of customerNoFilter() to filter the transaction history by customer no.
					customerNoFilter();
					return;
				}
				else if ((check == '3') && (response.length() == 1))
				{
					// Calling of durianTypeFilter() to filter the transaction history by durian type
					durianTypeFilter();
					return;
				}
				else if ((check == '4') && (response.length() == 1))
				{
					// Calling of totalPriceFilter() to filter the transaction history by total price
					totalPriceFilter();
					return;
				}
				else
				{
					print("", 1, 0);
					print("Invalid input. Available filters: 1 - 4", 1, 4);
					valid = false;
					continue;
				}

			} while (valid == false);
		}
		else if ((check == 'N') && (response.length() == 1))
		{
			print("", 1, 0);
			displaySpace(32, 0);  // Display spaces for alignment purpose

			system("pause");

			transactionHandling();  // Navigate back to transaction handling sub-menu
			return;
		}
		else
		{
			valid = false;
			print("Invalid input! Please enter again.", 2, 4);
			continue;  // Proceed to the next iteration
		}

	} while (valid == false);

	// Navigate back to transaction handling sub-menu
	transactionHandling();
	return;
}


void addTransaction()
{
	// Declaration and initialisation of variables
	int year;
	int month;
	int day;
	bool valid;
	string inputYear;
	string inputMonth;
	string inputDay;
	string response;
	string customerNo;
	string outOfRange;
	string totalPrice;
	string grand;

	int addCounter = 0;

	// Clear screen
	system("cls");

	// Display header
	print("", 1, 0);
	printWord("ADD TRANSACTION");
	print("", 1, 0);

	// Display date
	int displayYear, displayMonth, displayDay;
	dateTime(displayYear, displayMonth, displayDay);
	string displayDate = to_string(displayDay) + "/" + to_string(displayMonth) + "/" + to_string(displayYear);
	print("", 1, 0);
	print("===================", 1, 0);
	print("DATE:", 1, 0);
	print(displayDate, 1, 7);
	print("===================", 1, 0);

	// Calling of storeDurian() function to update the struct array
	storeDurian();

	// Display menu
	menuPrint();

	// Direct the user back to the transaction handling sub-menu if durian.txt is empty
	if (blank == true)
	{
		print("", 1, 0);
		print("The menu is empty! Please proceed to add durian details into the menu... ", 2, 4);
		print("", 1, 0);
		displaySpace(32, 0);
		system("pause");

		// Navigate back to transaction handling sub-menu
		transactionHandling();
		return;
	}

	// Check whether transaction.txt exists or is the file empty
	checkFile("transaction.txt", "");

	// Read the content of transaction.txt
	if (absent == false)
	{
		readTransaction();
	}

	// Display message
	print("", 2, 0);
	print("=================================================================", 1, 11);
	print("Enter \"-1\" to exit to Transaction Handling sub-menu", 1, 11);
	print("=================================================================", 3, 11);

	// Calculate the customer no.
	if (blank == true)
	{
		// Customer no. starts from 1 if there is no transaction history
		transaction[addCounter].customerNo = 1;
	}
	else if ((blank == false) && (cont == false))	// The first loop of addTransaction function
	{
		// Display the next customer no. with reference to the transaction history
		transaction[addCounter].customerNo = transaction[readCounter - 1].customerNo + 1;
	}
	else if ((blank == false) && (cont == true))	// Not the first loop of addTransaction function
	{
		transaction[addCounter].customerNo = transaction[readCounter - 1].customerNo;
	}

	// Display customer no.
	customerNo = "Customer " + to_string(transaction[addCounter].customerNo);
	print("=================================================================", 1, 0);
	print(customerNo, 1, 2);
	print("=================================================================", 1, 0);

	// Prompt the user to enter the durian type
	do
	{
		displaySpace(50, 50);	// Display spaces for alignment purpose
		cout << "Please choose the durian type (no.)            : ";
		cin >> transaction[addCounter].durianType;

		if (cin.fail())  // Incompatible data type input
		{
			cin.clear();  // Clear input
			cin.ignore(1000, '\n');  // Ignore previous 1000 (unknown) characters until next line
			print("", 1, 0);
			print("Invalid durian type! Please try again.", 1, 4);
			print("                                                                 ", 1, 0);
			continue;  // Proceed to the next iteration
		}
		else if (transaction[addCounter].durianType == -1)
		{
			grandTotal = 0;  // Reinitialise the grand total back to 0
			transaction[addCounter].durianType = 0;
			cont = false;

			print("", 1, 0);
			print("The transaction will not be stored!", 1, 4);
			Sleep(1500);
			transactionHandling();
			return;
		}
		else if ((transaction[addCounter].durianType <= 0) || (transaction[addCounter].durianType > totalDurian))
		{
			print("", 1, 0);
			print("Invalid durian type! Please try again.", 1, 4);
			print("                                                                 ", 1, 0);
		}

	} while ((transaction[addCounter].durianType <= 0) || (transaction[addCounter].durianType > totalDurian));

	// Prompt the user to enter the price
	do
	{
		displaySpace(50, 50);	// Display spaces for alignment purpose
		cout << "Price per kg (RM)                              : ";
		cin >> transaction[addCounter].price;

		if (cin.fail())  // Incompatible data type input
		{
			cin.clear();  // Clear input
			cin.ignore(1000, '\n');  // Ignore previous 1000 (unknown) characters until next line
			print("", 1, 0);
			print("Invalid price! Please try again.", 1, 4);
			print("                                                                 ", 1, 0);
			continue;  // Proceed to the next iteration
		}
		else if (transaction[addCounter].price == -1)
		{
			grandTotal = 0;  // Reinitialise the grand total back to 0
			transaction[addCounter].price = 0;
			cont = false;

			print("", 1, 0);
			print("The transaction will not be stored!", 1, 4);
			Sleep(1500);
			transactionHandling();
			return;
		}
		else if ((transaction[addCounter].price < durian[transaction[addCounter].durianType - 1].minPrice) || (transaction[addCounter].price > durian[transaction[addCounter].durianType - 1].maxPrice))
		{
			// Display error message if price is out of range
			outOfRange = "Please enter the price in the range of RM " +
				to_string(durian[transaction[addCounter].durianType - 1].minPrice).erase(to_string(durian[transaction[addCounter].durianType - 1].minPrice).find(".") + 3, 100) +
				" - RM " +
				to_string(durian[transaction[addCounter].durianType - 1].maxPrice).erase(to_string(durian[transaction[addCounter].durianType - 1].maxPrice).find(".") + 3, 100);

			print("", 1, 0);
			print(outOfRange, 1, 4);
			print("                                                                 ", 1, 0);
		}

	} while ((transaction[addCounter].price < durian[transaction[addCounter].durianType - 1].minPrice) || (transaction[addCounter].price > durian[transaction[addCounter].durianType - 1].maxPrice));

	// Prompt the user to enter the weight
	do
	{
		displaySpace(50, 50);	// Display spaces for alignment purpose
		cout << "Weight (kg)                                    : ";
		cin >> transaction[addCounter].weight;

		if (cin.fail())  // Incompatible data type input
		{
			cin.clear();  // Clear input
			cin.ignore(1000, '\n');  // Ignore previous 1000 (unknown) characters until next line
			print("", 1, 0);
			print("Invalid weight! Please try again.", 1, 4);
			print("                                                                 ", 1, 0);
			continue;  // Proceed to the next iteration
		}
		else if (transaction[addCounter].weight == -1)
		{
			grandTotal = 0;  // Reinitialise the grand total back to 0
			transaction[addCounter].weight = 0;
			cont = false;

			print("", 1, 0);
			print("The transaction will not be stored!", 1, 4);
			Sleep(1500);
			transactionHandling();
			return;
		}
		else if (transaction[addCounter].weight <= 0)
		{
			print("", 1, 0);
			print("Invalid weight! Please try again.", 1, 4);
			print("                                                                 ", 1, 0);
		}

	} while (transaction[addCounter].weight <= 0);

	// Prompt the user to enter the date
	do
	{
		valid = true;

		displaySpace(50, 50);	// Display spaces for alignment purpose
		cout << "Date (dd/mm/yyyy)                              : ";
		cin >> transaction[addCounter].date;

		if (transaction[addCounter].date == "-1")
		{
			grandTotal = 0;  // Reinitialise the grand total back to 0
			transaction[addCounter].date = "";
			cont = false;

			print("", 1, 0);
			print("The transaction will not be stored!", 1, 4);
			Sleep(1500);
			transactionHandling();
			return;
		}
		else if (transaction[addCounter].date.length() == 10)
		{
			inputYear = transaction[addCounter].date.substr(6, 4);
			inputMonth = transaction[addCounter].date.substr(3, 2);
			inputDay = transaction[addCounter].date.substr(0, 2);

			if ((inputYear.length() == 4) && (inputMonth.length() == 2) && (inputDay.length() == 2))
			{
				for (int i = 0; i < 2; i++)
				{
					if (!isdigit(inputMonth[i]) || !isdigit(inputDay[i]))
					{
						valid = false;
						break;
					}
				}
				for (int j = 0; j < 4; j++)
				{
					if (!isdigit(inputYear[j]))
					{
						valid = false;
						break;
					}
				}
			}
			else
				valid = false;

			if (valid == true)
			{
				year = stoi(inputYear);
				month = stoi(inputMonth);
				day = stoi(inputDay);

				if ((year >= 1900) && (year <= 2099))
				{
					if ((month >= 1) && (month <= 12))  // 12 months
					{
						if ((day >= 1) && (day <= 31))  // Maximum 31 days in a month
						{
							if (month == 2)  // The month is February
							{
								if ((year % 4) == 0)  // The year is a leap year
								{
									if (day > 29)  // Maximum 29 days for February in a leap year
										valid = false;
								}
								else
								{
									if (day > 28)  // Maximum 28 days for February in a non-leap year
										valid = false;
								}
							}
							else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
							{
								if (day > 30)
									valid = false;
							}
						}
						else
							valid = false;
					}
					else
						valid = false;
				}
				else
					valid = false;
			}
		}
		else
			valid = false;

		if (valid == false)
		{
			print("", 1, 0);
			print("Invalid date format! Please try again.", 1, 4);
			print("                                                                 ", 1, 0);
		}

	} while (valid == false);

	// Calculate the total price for a type of durian
	transaction[addCounter].totalPrice = transaction[addCounter].price * transaction[addCounter].weight;

	// Reinitialise the struct array
	storeDurian();

	// Display the total price for a type of durian
	totalPrice = "Total price for " +
		to_string(transaction[addCounter].weight).erase(to_string(transaction[addCounter].weight).find(".") + 3, 100) +
		" kg of " + durian[transaction[addCounter].durianType - 1].name + " is RM " +
		to_string(transaction[addCounter].totalPrice).erase(to_string(transaction[addCounter].totalPrice).find(".") + 3, 100);

	print("                                                                 ", 1, 0);
	print(totalPrice, 1, 3);
	print("                                                                 ", 2, 0);

	// Calculate the grand total for the transaction
	grandTotal += transaction[addCounter].totalPrice;

	// Prompt for user to add another type of durian or exit the function
	cin.ignore();
	do
	{
		valid = true;

		print("=================================================================", 1, 0);
		print("Do you want to enter another type of durian?", 1, 0);
		print("=================================================================", 1, 0);
		print("Y - YES", 1, 3);
		print("N - NO", 1, 4);
		print("-----------------------------------------------------------------", 1, 0);
		print("(Y/N) >> ", 0, 0);

		getline(cin, response);
		check = toupper(response[0]);

		if (response == "-1")  // Exit to transaction handling sub-menu without saving
		{
			grandTotal = 0;  // Reinitialise the grand total back to 0
			cont = false;

			print("", 1, 0);
			print("The transaction will not be stored!", 1, 4);
			Sleep(1500);
			transactionHandling();
			return;
		}
		else if (check == 'Y')  // Continue to add another transaction details
		{
			valid = true;
			cont = true;

			// Store the transaction details into transaction.txt
			storeTransaction();

			// Execute the addTransaction function again
			addTransaction();
			return;
		}
		else if (check == 'N')  // Store the transaction details into transaction.txt and exit to transaction handling sub-menu
		{
			valid = true;
			cont = false;

			// Store the transaction details into transaction.txt
			storeTransaction();

			// Display the grand total for the transaction
			grand = "The grand total for this transaction is RM " + to_string(grandTotal).erase(to_string(grandTotal).find(".") + 3, 100);
			print("", 2, 0);
			print(grand, 1, 3);
			print("                                                                 ", 1, 0);

			// Display reminder message if transaction.txt does not exist
			if (absent == true)
			{
				print("", 1, 0);
				print("transaction.txt cannot be found!", 1, 4);
				print("transaction.txt will be created instead...", 2, 4);
				Sleep(1000);
				print("transaction.txt is created", 1, 4);
				print("Transaction details are stored", 1, 4);
				Sleep(1000);
			}

			grandTotal = 0;  // Reinitialise the grand total back to 0

			print("", 1, 0);
			displaySpace(32, 0);	// Display spaces for alignment purpose
			system("pause");
			transactionHandling();
			return;
		}
		else
		{
			valid = false;

			print("Invalid input. Please try again!", 1, 4);
			print("", 1, 0);
		}

	} while (valid == false);

}


void storeTransaction()
{
	// Declaration and initialisation of variables
	ofstream outFile;

	// Calling of function to check whether transaction.txt exists or is the file empty
	checkFile("transaction.txt", "");

	// Open transaction.txt for appending
	outFile.open("transaction.txt", ios::app);

	if (blank == false)  // transaction.txt is not empty
	{
		outFile << endl;
	}

	outFile << transaction[addCounter].customerNo << endl;
	outFile << transaction[addCounter].date << endl;
	outFile << durian[transaction[addCounter].durianType - 1].name << endl;
	outFile << transaction[addCounter].price << " " << transaction[addCounter].weight << endl;
	outFile << transaction[addCounter].totalPrice;

	outFile.close();
}


void readTransaction()
{
	// Declaration and initialisation of variables
	readCounter = 0;
	ifstream inFile;

	// Open transaction.txt for reading
	inFile.open("transaction.txt");

	while (!inFile.eof())
	{
		inFile >> transaction[readCounter].customerNo;
		inFile >> transaction[readCounter].date;
		inFile.ignore();
		getline(inFile, durian[readCounter].name);
		inFile >> transaction[readCounter].price >> transaction[readCounter].weight;
		inFile >> transaction[readCounter].totalPrice;

		readCounter++;
	}

	inFile.close();
}


void deleteTransaction()
{
	// Declaration and initialisation of variables
	ofstream outFile;
	bool valid = true;
	string response;

	// Clear screen
	system("cls");

	// Display header
	print("", 1, 0);
	print("//////////////////////////////////////////////////////", 1, 5);
	printWord("Deleting...");
	print("//////////////////////////////////////////////////////", 1, 5);

	// Check whether transaction.txt exists or is the file empty
	checkFile("transaction.txt", "");

	if (absent == true)  // If transaction.txt does not exist
	{
		print("", 5, 0);
		print("transaction.txt cannot be found", 1, 4);
		print("Please go to Add Transaction to create the file", 1, 4);
		print("", 1, 0);
		displaySpace(32, 0);  // Display spaces for alignment purpose
		system("pause");

		// Navigate back to transactio handling sub-menu
		transactionHandling();
		return;
	}
	else if (blank == true)  // If transaction.txt is empty
	{

		print("", 5, 0);
		print("There is no transaction history", 1, 4);
		print("", 1, 0);
		displaySpace(32, 0);  // Display spaces for alignment purpose
		system("pause");

		// Navigate back to transaction handling sub-menu
		transactionHandling();
		return;
	}

	// Prompt the user to decide whether to delete all the content in transaction.txt
	print("", 5, 0);
	cin.ignore();

	do
	{
		valid = true;

		print("===========================================================", 1, 0);
		print("Do you want to delete all transaction history: ", 1, 0);
		print("===========================================================", 1, 0);
		print("Y - YES", 1, 3);
		print("N - NO", 1, 4);
		print("-----------------------------------------------------------", 1, 0);
		print("(Y/N) >> ", 0, 0);

		getline(cin, response);
		check = toupper(response[0]);

		if (check == 'Y')  // Delete all the transaction details and exit to transaction handling sub-menu
		{
			valid = true;
			outFile.open("transaction.txt", ios::trunc);
			outFile.close();

			// Display message
			print("", 1, 0);
			printWord("Deleting...");
			loading(1, 7, 0);
			Sleep(1000);
			print("", 1, 0);
			print("The transaction history has been cleared!", 1, 4);
			print("", 1, 0);
			displaySpace(32, 0);	// Display spaces for alignment purpose
			system("pause");

			// Navigate back to transaction handling sub-menu
			transactionHandling();
			return;
		}
		else if (check == 'N')  // Exit to transaction handling sub-menu
		{
			valid = true;

			// Navigate back to transaction handling sub-menu
			transactionHandling();
			return;
		}
		else
		{
			valid = false;
			cout << endl;
			print("Invalid input. Please try again!", 1, 4);
			print("", 1, 0);
		}

	} while (valid == false);

}


void dateFilter()
{
	// Declaration and initialisation of variables
	int year;
	int month;
	int day;
	string transactionNo;
	string customerNo;
	string date;
	string name;
	string price;
	string weight;
	string totalPrice;
	bool valid = true;
	bool displayYear = true;
	bool displayMonth = true;
	bool displayDay = true;
	bool leapYear = true;

	// Calling of storeDurian() function to update the struct array
	storeDurian();

	// Calling of readTransaction() to read the content of transaction history
	readTransaction();

	// Clear screen
	system("cls");

	// Display all transaction history
	print("", 1, 0);
	printWord("TRANSACTION HISTORY");
	print("", 1, 0);
	print("(Displaying All)", 2, 0);

	for (int i = 0; i < readCounter; i++)
	{
		transactionNo = "Transaction No." + to_string(i + 1);
		customerNo = "Customer No.       : " + to_string(transaction[i].customerNo);
		date = "Date               : " + transaction[i].date;
		name = "Durian Type        : " + durian[i].name;
		price = "Price per kg       : RM " + to_string(transaction[i].price).erase(to_string(transaction[i].price).find(".") + 3, 100);
		weight = "Weight             : " + to_string(transaction[i].weight).erase(to_string(transaction[i].weight).find(".") + 3, 100) + " kg";
		totalPrice = "Total Price        : RM " + to_string(transaction[i].totalPrice).erase(to_string(transaction[i].totalPrice).find(".") + 3, 100);

		print("", 1, 0);
		print("=====================================================================", 1, 0);
		print(transactionNo, 1, 3);
		print("=====================================================================", 1, 0);
		print(customerNo, 1, 0);
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << date << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << name << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << price << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << weight << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << totalPrice << endl;
	}

	// Prompt the user to enter the date to filter
	print("", 2, 0);
	print("=================================================================", 1, 11);
	print("Enter \"-1\" to exit to the Transaction Handling sub-menu", 1, 11);
	print("Enter \"0\" if you do not want to apply the specific filter field", 1, 11);
	print("=================================================================", 3, 11);

	do  // Prompt the user to enter the year
	{
		valid = true;

		print("Enter the year    : ", 0, 0);
		cin >> year;

		if (cin.fail())
		{
			valid = false;

			cin.clear();  // Clear input
			cin.ignore(1000, '\n');  // Ignore previous 1000 (unknown number) characters until next line
			print("", 1, 0);
			print("Invalid input. Please enter a valid year", 2, 4);
		}
		else if ((year >= 1900) && (year <= 2099))
		{
			valid = true;
		}
		else if (year == -1)
		{
			// Navigate back to transaction handling sub-menu
			transactionHandling();
			return;
		}
		else if (year == 0)
		{
			displayYear = true;
		}
		else
		{
			cout << endl;
			print("Invalid input. Please enter a valid year", 2, 4);

			valid = false;
		}

	} while (valid == false);

	do  // Prompt the user to enter the month
	{
		valid = true;

		print("Enter the month   : ", 0, 0);
		cin >> month;

		if (cin.fail())
		{
			valid = false;

			cin.clear();  // Clear input
			cin.ignore(1000, '\n');  // Ignore previous 1000 (unknown number) characters until next line
			print("", 1, 0);
			print("Invalid input. Please enter a valid month", 2, 4);
		}
		else if ((month >= 1) && (month <= 12))
		{
			valid = true;
		}
		else if (month == -1)
		{
			// Navigate back to transaction handling sub-menu
			transactionHandling();
			return;
		}
		else if (month == 0)
		{
			displayMonth = true;
		}
		else
		{
			cout << endl;
			print("Invalid input. Please enter a valid month", 2, 4);

			valid = false;
		}

	} while (valid == false);

	if ((year % 4) == 0)  // Check if the year entered is a leap year
	{
		leapYear = true;
	}
	else
	{
		leapYear = false;
	}

	do  // Prompt the user to enter the day
	{
		valid = true;

		print("Enter the day     : ", 0, 0);
		cin >> day;

		if (cin.fail())
		{
			valid = false;

			cin.clear();  // Clear input
			cin.ignore(1000, '\n');  // Ignore previous 1000 (unknown number) characters until next line
			print("", 1, 0);
			print("Invalid input. Please enter a valid day", 2, 4);
		}
		else if ((day >= 1) && (day <= 31))
		{
			if ((month == 2) && (leapYear == true))  // February of leap year
			{
				if (day > 29)
				{
					cout << endl;
					print("Invalid input. Please enter a valid day", 2, 4);

					valid = false;
				}
				else
				{
					valid = true;
				}
			}
			else if ((month == 2) && (leapYear == false))  // February of non-leap year
			{
				if (day > 28)
				{
					cout << endl;
					print("Invalid input. Please enter a valid day", 2, 4);

					valid = false;
				}
				else
				{
					valid = true;
				}
			}
			else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
			{
				if (day > 30)
				{
					cout << endl;
					print("Invalid input. Please enter a valid day", 2, 4);

					valid = false;
				}
				else
				{
					valid = true;
				}
			}
		}
		else if (day == -1)
		{
			// Navigate back to transaction handling sub-menu
			transactionHandling();
			return;
		}
		else if (day == 0)
		{
			displayDay = true;
		}
		else
		{
			cout << endl;
			print("Invalid input. Please enter a valid day", 2, 4);

			valid = false;
		}

	} while (valid == false);

	// Display filtered transaction history
	system("cls");
	print("", 1, 0);
	printWord("RESULT");
	print("", 1, 0);

	for (int i = 0; i < readCounter; i++)
	{
		if (stoi(transaction[i].date.substr(0, 2)) == day)  // Matched day
		{
			displayDay = true;
		}
		else if (day == 0)
		{
			displayDay = true;
		}
		else
		{
			displayDay = false;
		}

		if (stoi(transaction[i].date.substr(3, 2)) == month)  // Matched month
		{
			displayMonth = true;
		}
		else if (month == 0)
		{
			displayMonth = true;
		}
		else
		{
			displayMonth = false;
		}

		if (stoi(transaction[i].date.substr(6, 4)) == year)  // Matched year
		{
			displayYear = true;
		}
		else if (year == 0)
		{
			displayYear = true;
		}
		else
		{
			displayYear = false;
		}

		if ((displayYear == true) && (displayMonth == true) && (displayDay == true))
		{
			transactionNo = "Transaction No." + to_string(i + 1);
			customerNo = "Customer No.       : " + to_string(transaction[i].customerNo);
			date = "Date               : " + transaction[i].date;
			name = "Durian Type        : " + durian[i].name;
			price = "Price per kg       : RM " + to_string(transaction[i].price).erase(to_string(transaction[i].price).find(".") + 3, 100);
			weight = "Weight             : " + to_string(transaction[i].weight).erase(to_string(transaction[i].weight).find(".") + 3, 100) + " kg";
			totalPrice = "Total Price        : RM " + to_string(transaction[i].totalPrice).erase(to_string(transaction[i].totalPrice).find(".") + 3, 100);

			print("", 1, 0);
			print("=====================================================================", 1, 0);
			print(transactionNo, 1, 3);
			print("=====================================================================", 1, 0);
			print(customerNo, 1, 0);
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << date << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << name << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << price << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << weight << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << totalPrice << endl;
		}
	}

	// Navigate back to the View Transaction page
	print("", 5, 0);

	for (int i = 0; i < space - 16; i++)
	{
		cout << " ";
	}

	system("pause");
	viewTransaction();
	return;

}


void customerNoFilter()
{
	// Declaration and initialisation of variables
	string transactionNo;
	string customerNo;
	string date;
	string name;
	string price;
	string weight;
	string totalPrice;
	int largest;
	int smallest;
	bool valid = true;

	// Calling of storeDurian() function to update the struct array
	storeDurian();

	// Calling of readTransaction() to read the content of transaction history
	readTransaction();

	// Clear screen
	system("cls");

	// Display all transaction history
	print("", 1, 0);
	printWord("TRANSACTION HISTORY");
	print("", 1, 0);
	print("(Displaying All)", 2, 0);

	for (int i = 0; i < readCounter; i++)
	{
		transactionNo = "Transaction No." + to_string(i + 1);
		customerNo = "Customer No.       : " + to_string(transaction[i].customerNo);
		date = "Date               : " + transaction[i].date;
		name = "Durian Type        : " + durian[i].name;
		price = "Price per kg       : RM " + to_string(transaction[i].price).erase(to_string(transaction[i].price).find(".") + 3, 100);
		weight = "Weight             : " + to_string(transaction[i].weight).erase(to_string(transaction[i].weight).find(".") + 3, 100) + " kg";
		totalPrice = "Total Price        : RM " + to_string(transaction[i].totalPrice).erase(to_string(transaction[i].totalPrice).find(".") + 3, 100);

		print("", 1, 0);
		print("=====================================================================", 1, 0);
		print(transactionNo, 1, 3);
		print("=====================================================================", 1, 0);
		print(customerNo, 1, 0);
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << date << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << name << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << price << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << weight << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << totalPrice << endl;
	}

	// Display message
	print("", 2, 0);
	print("=================================================================", 1, 11);
	print("Enter \"-1\" to exit to Transaction Handling sub-menu", 1, 11);
	print("=================================================================", 3, 11);

	// Prompt the user to enter the range of customer no. to display
	print("=======================================", 1, 0);
	print("Enter the range of the customer no.", 1, 0);
	print("---------------------------------------", 1, 0);

	do
	{
		displaySpace(25, 40);	// Display spaces for alignment purpose

		cout << "Largest customer no.  : ";
		cin >> largest;

		if (cin.fail())
		{
			valid = false;

			cin.clear();  // Clear input
			cin.ignore(1000, '\n');  // Ignore previous 1000 (unknown number) characters until next line
			print("", 1, 0);
			print("Invalid input. Please try again!", 1, 4);
			print("                                       ", 1, 0);
		}
		else if (largest > 0)
		{
			valid = true;
		}
		else if (largest == -1)
		{
			valid = true;

			// Navigate back to Transaction Handling sub-menu
			transactionHandling();
			return;
		}
		else
		{
			valid = false;

			// Display error message
			cout << endl;
			print("Invalid input. Please try again!", 1, 4);
			print("                                       ", 1, 0);
		}

	} while (valid == false);

	do
	{
		displaySpace(25, 40);	// Display spaces for alignment purpose

		cout << "Smallest customer no. : ";
		cin >> smallest;

		if (cin.fail())
		{
			valid = false;

			cin.clear();  // Clear input
			cin.ignore(1000, '\n');  // Ignore previous 1000 (unknown number) characters until next line
			print("", 1, 0);
			print("Invalid input. Please try again!", 1, 4);
			print("                                       ", 1, 0);
		}
		else if ((smallest <= largest) && (smallest > 0))
		{
			valid = true;
		}
		else if (smallest == -1)
		{
			valid = true;

			// Navigate back to Transaction Handling sub-menu
			transactionHandling();
			return;
		}
		else
		{
			valid = false;

			// Display error message
			cout << endl;
			print("Invalid input. Please try again!", 1, 4);
			print("                                       ", 1, 0);
		}

	} while (valid == false);


	// Display filtered transaction history
	system("cls");
	print("", 1, 0);
	printWord("RESULT");
	print("", 1, 0);

	for (int i = 0; i < readCounter; i++)
	{

		if ((transaction[i].customerNo >= smallest) && (transaction[i].customerNo <= largest))
		{
			transactionNo = "Transaction No." + to_string(i + 1);
			customerNo = "Customer No.       : " + to_string(transaction[i].customerNo);
			date = "Date               : " + transaction[i].date;
			name = "Durian Type        : " + durian[i].name;
			price = "Price per kg       : RM " + to_string(transaction[i].price).erase(to_string(transaction[i].price).find(".") + 3, 100);
			weight = "Weight             : " + to_string(transaction[i].weight).erase(to_string(transaction[i].weight).find(".") + 3, 100) + " kg";
			totalPrice = "Total Price        : RM " + to_string(transaction[i].totalPrice).erase(to_string(transaction[i].totalPrice).find(".") + 3, 100);

			print("", 1, 0);
			print("=====================================================================", 1, 0);
			print(transactionNo, 1, 3);
			print("=====================================================================", 1, 0);
			print(customerNo, 1, 0);
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << date << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << name << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << price << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << weight << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << totalPrice << endl;
		}
	}

	// Navigate back to the View Transaction page
	print("", 5, 0);

	for (int i = 0; i < space - 16; i++)
	{
		cout << " ";
	}

	system("pause");
	viewTransaction();
	return;
}


void durianTypeFilter()
{
	// Declaration and initialisation of variables
	string transactionNo;
	string customerNo;
	string date;
	string name;
	string price;
	string weight;
	string totalPrice;
	string durianType;
	bool valid = true;

	// Calling of storeDurian() function to update the struct array
	storeDurian();

	// Calling of readTransaction() to read the content of transaction history
	readTransaction();

	// Clear screen
	system("cls");

	// Display all transaction history
	print("", 1, 0);
	printWord("TRANSACTION HISTORY");
	print("", 1, 0);
	print("(Displaying All)", 2, 0);

	for (int i = 0; i < readCounter; i++)
	{
		transactionNo = "Transaction No." + to_string(i + 1);
		customerNo = "Customer No.       : " + to_string(transaction[i].customerNo);
		date = "Date               : " + transaction[i].date;
		name = "Durian Type        : " + durian[i].name;
		price = "Price per kg       : RM " + to_string(transaction[i].price).erase(to_string(transaction[i].price).find(".") + 3, 100);
		weight = "Weight             : " + to_string(transaction[i].weight).erase(to_string(transaction[i].weight).find(".") + 3, 100) + " kg";
		totalPrice = "Total Price        : RM " + to_string(transaction[i].totalPrice).erase(to_string(transaction[i].totalPrice).find(".") + 3, 100);

		print("", 1, 0);
		print("=====================================================================", 1, 0);
		print(transactionNo, 1, 3);
		print("=====================================================================", 1, 0);
		print(customerNo, 1, 0);
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << date << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << name << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << price << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << weight << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << totalPrice << endl;
	}

	// Display message
	print("", 2, 0);
	print("=================================================================", 1, 11);
	print("Enter \"-1\" to exit to Transaction Handling sub-menu", 1, 11);
	print("The filter is case-sensitive and requires an exact input", 1, 11);
	print("=================================================================", 3, 11);

	// Prompt the user to enter the durian type to display
	do
	{
		print("=======================================", 1, 0);
		print("Enter the durian type", 1, 0);
		print("---------------------------------------", 1, 0);
		displaySpace(14, 14);	// Display spaces for alignment purpose
		cout << "Durian type: ";
		getline(cin, durianType);

		if (durianType == "-1")
		{
			valid = true;

			// Navigate back to Transaction Handling sub-menu
			transactionHandling();
			return;
		}
		else
		{
			valid = true;
		}

		// Display filtered transaction history
		system("cls");
		print("", 1, 0);
		printWord("RESULT");
		print("", 1, 0);

		for (int i = 0; i < readCounter; i++)
		{

			if (durianType == durian[i].name)
			{
				transactionNo = "Transaction No." + to_string(i + 1);
				customerNo = "Customer No.       : " + to_string(transaction[i].customerNo);
				date = "Date               : " + transaction[i].date;
				name = "Durian Type        : " + durian[i].name;
				price = "Price per kg       : RM " + to_string(transaction[i].price).erase(to_string(transaction[i].price).find(".") + 3, 100);
				weight = "Weight             : " + to_string(transaction[i].weight).erase(to_string(transaction[i].weight).find(".") + 3, 100) + " kg";
				totalPrice = "Total Price        : RM " + to_string(transaction[i].totalPrice).erase(to_string(transaction[i].totalPrice).find(".") + 3, 100);

				print("", 1, 0);
				print("=====================================================================", 1, 0);
				print(transactionNo, 1, 3);
				print("=====================================================================", 1, 0);
				print(customerNo, 1, 0);
				displaySpace(21, 21);  // Display spaces for alignment purpose
				cout << date << endl;
				displaySpace(21, 21);  // Display spaces for alignment purpose
				cout << name << endl;
				displaySpace(21, 21);  // Display spaces for alignment purpose
				cout << price << endl;
				displaySpace(21, 21);  // Display spaces for alignment purpose
				cout << weight << endl;
				displaySpace(21, 21);  // Display spaces for alignment purpose
				cout << totalPrice << endl;
			}
		}

	} while (valid == false);

	// Navigate back to the View Transaction page
	print("", 5, 0);
	displaySpace(32, 0);
	system("pause");
	viewTransaction();
	return;
}


void totalPriceFilter()
{
	// Declaration and initialisation of variables
	string transactionNo;
	string customerNo;
	string date;
	string name;
	string price;
	string weight;
	string totalPrice;
	int largest;
	int smallest;
	bool valid = true;

	// Calling of storeDurian() function to update the struct array
	storeDurian();

	// Calling of readTransaction() to read the content of transaction history
	readTransaction();

	// Clear screen
	system("cls");

	// Display all transaction history
	print("", 1, 0);
	printWord("TRANSACTION HISTORY");
	print("", 1, 0);
	print("(Displaying All)", 2, 0);

	for (int i = 0; i < readCounter; i++)
	{
		transactionNo = "Transaction No." + to_string(i + 1);
		customerNo = "Customer No.       : " + to_string(transaction[i].customerNo);
		date = "Date               : " + transaction[i].date;
		name = "Durian Type        : " + durian[i].name;
		price = "Price per kg       : RM " + to_string(transaction[i].price).erase(to_string(transaction[i].price).find(".") + 3, 100);
		weight = "Weight             : " + to_string(transaction[i].weight).erase(to_string(transaction[i].weight).find(".") + 3, 100) + " kg";
		totalPrice = "Total Price        : RM " + to_string(transaction[i].totalPrice).erase(to_string(transaction[i].totalPrice).find(".") + 3, 100);

		print("", 1, 0);
		print("=====================================================================", 1, 0);
		print(transactionNo, 1, 3);
		print("=====================================================================", 1, 0);
		print(customerNo, 1, 0);
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << date << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << name << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << price << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << weight << endl;
		displaySpace(21, 21);  // Display spaces for alignment purpose
		cout << totalPrice << endl;
	}

	// Display message
	print("", 2, 0);
	print("=================================================================", 1, 11);
	print("Enter \"-1\" to exit to Transaction Handling sub-menu", 1, 11);
	print("=================================================================", 3, 11);

	// Prompt the user to enter the range of total price to display
	print("=======================================", 1, 0);
	print("Enter the range of the customer no.", 1, 0);
	print("---------------------------------------", 1, 0);

	do
	{
		displaySpace(25, 40);	// Display spaces for alignment purpose
		cout << "Highest total price   : ";
		cin >> largest;

		if (cin.fail())
		{
			valid = false;

			cin.clear();  // Clear input
			cin.ignore(1000, '\n');  // Ignore previous 1000 (unknown number) characters until next line
			print("", 1, 0);
			print("Invalid input. Please try again!", 1, 4);
			print("                                       ", 1, 0);
		}
		else if (largest > 0)
		{
			valid = true;
		}
		else if (largest == -1)
		{
			valid = true;

			// Navigate back to Transaction Handling sub-menu
			transactionHandling();
			return;
		}
		else
		{
			valid = false;

			// Display error message
			cout << endl;
			print("Invalid input. Please try again!", 1, 4);
			print("                                       ", 1, 0);
		}

	} while (valid == false);

	do
	{
		displaySpace(25, 40);	// Display spaces for alignment purpose
		cout << "Lowest total price    : ";
		cin >> smallest;

		if (cin.fail())
		{
			valid = false;

			cin.clear();  // Clear input
			cin.ignore(1000, '\n');  // Ignore previous 1000 (unknown number) characters until next line
			print("", 1, 0);
			print("Invalid input. Please try again!", 1, 4);
			print("                                       ", 1, 0);
		}
		else if ((smallest <= largest) && (smallest > 0))
		{
			valid = true;
		}
		else if (smallest == -1)
		{
			valid = true;

			// Navigate back to Transaction Handling sub-menu
			transactionHandling();
			return;
		}
		else
		{
			valid = false;

			// Display error message
			cout << endl;
			print("Invalid input. Please try again!", 1, 4);
			print("                                       ", 1, 0);
		}

	} while (valid == false);


	// Display filtered transaction history
	system("cls");
	print("", 1, 0);
	printWord("RESULT");
	print("", 1, 0);

	for (int i = 0; i < readCounter; i++)
	{

		if ((transaction[i].totalPrice >= smallest) && (transaction[i].totalPrice <= largest))
		{
			transactionNo = "Transaction No." + to_string(i + 1);
			customerNo = "Customer No.       : " + to_string(transaction[i].customerNo);
			date = "Date               : " + transaction[i].date;
			name = "Durian Type        : " + durian[i].name;
			price = "Price per kg       : RM " + to_string(transaction[i].price).erase(to_string(transaction[i].price).find(".") + 3, 100);
			weight = "Weight             : " + to_string(transaction[i].weight).erase(to_string(transaction[i].weight).find(".") + 3, 100) + " kg";
			totalPrice = "Total Price        : RM " + to_string(transaction[i].totalPrice).erase(to_string(transaction[i].totalPrice).find(".") + 3, 100);

			print("", 1, 0);
			print("=====================================================================", 1, 0);
			print(transactionNo, 1, 3);
			print("=====================================================================", 1, 0);
			print(customerNo, 1, 0);
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << date << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << name << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << price << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << weight << endl;
			displaySpace(21, 21);  // Display spaces for alignment purpose
			cout << totalPrice << endl;
		}
	}

	// Navigate back to the View Transaction page
	print("", 5, 0);
	displaySpace(32, 0);
	system("pause");
	viewTransaction();
	return;
}


//===========================================================================================================
// Function for decoration
//===========================================================================================================

// To change the colour of the background and the text
void color(DWORD Colour)
{
	CONSOLE_SCREEN_BUFFER_INFO Info;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);	// Get the handle of the standard output
	GetConsoleScreenBufferInfo(hStdout, &Info);	// Get the current colour of the background and the text
	SetConsoleTextAttribute(hStdout, Colour);	// Set the colour of the background and the text
}


// To print text to the centre of console, control colour of the text and print new line
// print(text that need to be printed, the number of new line, the colour of the text)
void print(string text, int newline, int colour)
{
	// Get the console handle
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Create a pointer to the Screen Info pointing to a temporal screen info
	PCONSOLE_SCREEN_BUFFER_INFO pointScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO();

	// Save the console screen info into the pointScreenInfo pointer
	GetConsoleScreenBufferInfo(consoleHandle, pointScreenInfo);

	// Gets the size of the screen
	COORD newScreenSize = pointScreenInfo->dwSize;

	// Change the colour of the blank space
	if (background == 0)		// White
		color(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
	else if (background == 1)	// Black
		color(0);

	// Only print spaces before the text when newline is larger or equal to 0, else, just print the text
	if (newline >= 0)
	{
		// Print text to the centre of console (if the size of the console is more than the text length)
		if (newScreenSize.X > text.size())
		{
			// Calculate the number of spaces to center the text
			int newSpace = static_cast<int>((newScreenSize.X - text.size()) / 2);

			// Prints the spaces before the text
			space = 0;
			for (int i = 0; i < newSpace; i++)
			{
				cout << " ";
				space++;	// Update the space
			}
		}
	}

	// Change the colour of the text
	switch (colour)
	{
	case 1:	// Black Background, Dark Green text
		color(FOREGROUND_GREEN);
		break;
	case 2:	// White Background, Dark Green Text
		color(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_GREEN);
		break;
	case 3:	// White Background, Dark Cyan text
		color(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 4:	// White Background, Red text
		color(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED);
		break;
	case 5:	// White Background, Grey text
		color(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 6:	// Black background, White text 
		color(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 7:	// Grey Background, Black text
		color(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
		break;
	case 8:	// White background, Dark yellow text
		color(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case 9:	// White background, Dark blue text
		color(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 10: // Red background, Green text 
		color(BACKGROUND_RED | FOREGROUND_GREEN);
		break;
	case 11: // White background, Dark magenta text
		color(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		break;
	default: // White Background, Black Text
		color(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
		break;
	}

	// If >= 0, the program will print (how many) new line; newline = 0, centred but no new line
	cout << text;
	for (int i = 0; i < newline; i++)
		cout << endl;
}

// To display message at the centre of the console displaySpace(current line length, previous line length)
void displaySpace(int line, int linebefore)
{
	int total = (linebefore - line) / 2;
	for (int i = 0; i < space + total; i++)
		cout << " ";
}

void printART(string pic, int displayFunction)
{
	if (pic == "Durian Picture")
	{
		print("                           wuA?b1?S<\"\"?    \"\\'       ", 1, 1);
		print("                   r\\3A?&AEA!\"     'r#<RWEfk1Sv      ", 1, 1);
		print("                .\"Err'=.\"!w3      =\"!.A<AR@=wW\\      ", 1, 1);
		print("               bW\"            w&&rwA?u11\\R#<A        ", 1, 1);
		print("             'AE        r!\\1\\Eu,        WR%E?1=      ", 1, 1);
		print("          '13(\"!v,    3uAbwr=!1=        R<b @E       ", 1, 1);
		print("         A#\\      ' wRw     .'\" '      #SS' b@v      ", 1, 1);
		print("        u%u      =wAR     '       '  3S?%A  3#=      ", 1, 1);
		print("        &<!    =3w3!\"\"'. \"        3k\\1wRE=r!?kw      ", 1, 1);
		print("       wE<r   @S!        .       =kr 1<?'<wr<1       ", 1, 1);
		print("       &R<Au?<k         . '.   rAA 'S\  Ewf?@?       ", 1, 1);
		print("        <<w ?&        .r'  'r1vw!vW?=  vRrAR>>       ", 1, 1);
		print("       vW<?wb&S\"?w_'?uSE(vv13wb?b(!     R?!=         ", 1, 1);
		print("        r<wurw?S3&kEufr_r\"r\"3r3v     !@u%r           ", 1, 1);
		print("          uRw1  =1f\"vvrb3?!\"       uv#w              ", 1, 1);
		print("           !=(R!&v            'E!vkv=!               ", 1, 1);
		print("              \\=r<?&bb!3@\\\"@?(RA,w'                  ", 1, 1);
		print("                 ,v  (krr\\A, =\"                      ", 1, 1);
	}
	else if (pic == "StoreName")
	{
		print("", 2, 0);
		print("               |====|                                                                                 ", 1, 0);
		print("      _________|____|____________________________________________________________________________     ", 1, 0);
		print("     /===========================================================================================\\    ", 1, 0);
		print("    /=============================================================================================\\   ", 1, 0);
		print("   /===================================| BEST DURIAN IN KAMPAR |===================================\\  ", 1, 0);
		print("  /=================================================================================================\\ ", 1, 0);
		print(" /=++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-+=\\", 1, 0);
		print("   +      _  _  __   _  _____   ___   _   _  ___  ___    _    _  _   ___  _____  _    _     _      +  ", 1, 0);
		print("   |   _ | || |/ /_ | ||_   _| |   \\ | | | || _ \\|_ _|  /_\\  | \\| | / __||_   _|/_\\  | |   | |     |  ", 1, 0);
		print("   +  | || || ' <| || |  | |   | |) || |_| ||   / | |  / _ \\ | .` | \\__ \\  | | / _ \\ | |__ | |__   +  ", 1, 0);
		print("   |   \\__/ |_|\\_\\\\__/   |_|   |___/  \\___/ |_|_\\|___|/_/ \\_\\|_|\\_| |___/  |_|/_/ \\_\\|____||____|  |  ", 1, 0);
		print("   +                                                                                               +  ", 1, 0);
		print("   ++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-++-+  ", 1, 0);
	}
	else if (pic == "Welcome")
	{
		print("==================================================================================================================", 1, 0);
		print("", 1, 0);
		print("        /$$      /$$ /$$$$$$$$ /$$        /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$       /$$$$$$$$ /$$$$$$       ", 1, 0);
		print("       | $$  /$ | $$| $$_____/| $$       /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/      |__  $$__//$$__  $$      ", 1, 0);
		print("       | $$ /$$$| $$| $$      | $$      | $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$               | $$  | $$  \\ $$      ", 1, 0);
		print("       | $$/$$ $$ $$| $$$$$   | $$      | $$      | $$  | $$| $$ $$/$$ $$| $$$$$            | $$  | $$  | $$      ", 1, 0);
		print("       | $$$$_  $$$$| $$__/   | $$      | $$      | $$  | $$| $$  $$$| $$| $$__/            | $$  | $$  | $$      ", 1, 0);
		print("       | $$$/ \\  $$$| $$      | $$      | $$    $$| $$  | $$| $$\\  $ | $$| $$               | $$  | $$  | $$      ", 1, 0);
		print("       | $$/   \\  $$| $$$$$$$$| $$$$$$$$|  $$$$$$/|  $$$$$$/| $$ \\/  | $$| $$$$$$$$         | $$  |  $$$$$$/      ", 1, 0);
		print("       |__/     \\__/|________/|________/ \\______/  \\______/ |__/     |__/|________/         |__/   \\______/       ", 1, 0);
		print("", 2, 0);
		print("                           wuA?b1?S<\"\"?    \"\\'                                                                   ", 1, 0);
		print("                   r\\3A?&AEA!\"     'r#<RWEfk1Sv                                                                  ", 1, 0);
		print("                .\"Err'=.\"!w3      =\"!.A<AR@=wW\\                                                                  ", 1, 0);
		print("               bW\"            w&&rwA?u11\\R#<A                                                                    ", 1, 0);
		print("             'AE        r!\\1\\Eu,        WR%E?1=         /$$$$$ /$$   /$$    /$$$$$ /$$$$$$$$                     ", 1, 0);
		print("          '13(\"!v,    3uAbwr=!1=        R<b @E          |__  $$| $$  /$$/   |__  $$|__  $$__/                    ", 1, 0);
		print("         A#\\      ' wRw     .'\" '      #SS' b@v            | $$| $$ /$$/       | $$   | $$                       ", 1, 0);
		print("        u%u      =wAR     '       '  3S?%A  3#=            | $$| $$$$$/        | $$   | $$                       ", 1, 0);
		print("        &<!    =3w3!\"\"'. \"        3k\\1wRE=r!?kw       /$$  | $$| $$  $$   /$$  | $$   | $$                       ", 1, 0);
		print("       wE<r   @S!        .       =kr 1<?'<wr<1       | $$  | $$| $$\\  $$ | $$  | $$   | $$                       ", 1, 0);
		print("       &R<Au?<k         . '.   rAA 'S\  Ewf?@?>       |  $$$$$$/| $$ \\  $$|  $$$$$$/   | $$                       ", 1, 0);
		print("        <<w ?&        .r'  'r1vw!vW?=  vRrAR>>        \\______/ |__/  \\__/ \\______/    |__/                       ", 1, 0);
		print("       vW<?wb&S\"?w_'?uSE(vv13wb?b(!     R?!=                                                                     ", 1, 0);
		print("        r<wurw?S3&kEufr_r\"r\"3r3v     !@u%r                                                                       ", 1, 0);
		print("          uRw1  =1f\"vvrb3?!\"       uv#w                                                                          ", 1, 0);
		print("           !=(R!&v            'E!vkv=!                                                                           ", 1, 0);
		print("              \\=r<?&bb!3@\\\"@?(RA,w'                                                                              ", 1, 0);
		print("                 ,v  (krr\\A, =\"                                                                                  ", 1, 0);
		print("", 2, 0);
		print("  /$$$$$$$  /$$   /$$ /$$$$$$$  /$$$$$$  /$$$$$$  /$$   /$$        /$$$$$$  /$$$$$$$$ /$$$$$$  /$$       /$$      ", 1, 0);
		print(" | $$__  $$| $$  | $$| $$__  $$|_  $$_/ /$$__  $$| $$$ | $$       /$$__  $$|__  $$__//$$__  $$| $$      | $$      ", 1, 0);
		print(" | $$  \\ $$| $$  | $$| $$  \\ $$  | $$  | $$  \\ $$| $$$$| $$      | $$  \\__/   | $$  | $$  \\ $$| $$      | $$      ", 1, 0);
		print(" | $$  | $$| $$  | $$| $$$$$$$/  | $$  | $$$$$$$$| $$ $$ $$      |  $$$$$$    | $$  | $$$$$$$$| $$      | $$      ", 1, 0);
		print(" | $$  | $$| $$  | $$| $$__  $$  | $$  | $$__  $$| $$  $$$$       \\____  $$   | $$  | $$__  $$| $$      | $$      ", 1, 0);
		print(" | $$  | $$| $$  | $$| $$  \\ $$  | $$  | $$  | $$| $$\\  $$$       /$$  \\ $$   | $$  | $$  | $$| $$      | $$      ", 1, 0);
		print(" | $$  | $$| $$  | $$| $$  \\ $$  | $$  | $$  | $$| $$\\  $$$       /$$  \\ $$   | $$  | $$  | $$| $$      | $$      ", 1, 0);
		print(" | $$$$$$$/|  $$$$$$/| $$  | $$ /$$$$$$| $$  | $$| $$ \\  $$      |  $$$$$$/   | $$  | $$  | $$| $$$$$$$$| $$$$$$$$", 1, 0);
		print(" |_______/  \\______/ |__/  |__/|______/|__/  |__/|__/  \\__/       \\______/    |__/  |__/  |__/|________/|________/", 1, 0);
		print("", 1, 0);
		print("==================================================================================================================", 1, 0);
	}

	else if (pic == "Exit")
	{
		print("=====================================================================================================================", 1, 0);
		print("", 2, 0);
		print("         /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$        /$$$$$$$  /$$     /$$ /$$$$$$$$          /$$$                  ", 1, 0);
		print("        /$$__  $$ /$$__  $$ /$$__  $$| $$__  $$      | $$__  $$|  $$   /$$/| $$_____/         |_  $$                 ", 1, 0);
		print("       | $$  \\__/| $$  \\ $$| $$  \\ $$| $$  \\ $$      | $$  \\ $$ \\  $$ /$$/ | $$             /$$ \\  $$                ", 1, 0);
		print("       | $$ /$$$$| $$  | $$| $$  | $$| $$  | $$      | $$$$$$$   \\  $$$$/  | $$$$$         |__/  | $$                ", 1, 0);
		print("       | $$|_  $$| $$  | $$| $$  | $$| $$  | $$      | $$__  $$   \\  $$/   | $$__/               | $$                ", 1, 0);
		print("       | $$  \\ $$| $$  | $$| $$  | $$| $$  | $$      | $$  \\ $$    | $$    | $$             /$$  /$$/                ", 1, 0);
		print("       |  $$$$$$/|  $$$$$$/|  $$$$$$/| $$$$$$$/      | $$$$$$$/    | $$    | $$$$$$$$      |__//$$$/                 ", 1, 0);
		print("        \\______/  \\______/  \\______/ |_______/       |_______/     |__/    |________/         |___/                  ", 1, 0);
		print("", 2, 0);
		print("   /$$$$$$                                                                                              /$$          ", 1, 0);
		print("  /$$__  $$                                                                                            |__/          ", 1, 0);
		print(" | $$  \\__/  /$$$$$$   /$$$$$$        /$$   /$$  /$$$$$$  /$$   /$$        /$$$$$$   /$$$$$$   /$$$$$$  /$$ /$$$$$$$ ", 1, 0);
		print(" |  $$$$$$  /$$__  $$ /$$__  $$      | $$  | $$ /$$__  $$| $$  | $$       |____  $$ /$$__  $$ |____  $$| $$| $$__  $$", 1, 0);
		print("  \\____  $$| $$$$$$$$| $$$$$$$$      | $$  | $$| $$  \\ $$| $$  | $$        /$$$$$$$| $$  \\ $$  /$$$$$$$| $$| $$  \\ $$", 1, 0);
		print("  /$$  \\ $$| $$_____/| $$_____/      | $$  | $$| $$  | $$| $$  | $$       /$$__  $$| $$  | $$ /$$__  $$| $$| $$  | $$", 1, 0);
		print(" |  $$$$$$/|  $$$$$$$|  $$$$$$$      |  $$$$$$$|  $$$$$$/|  $$$$$$/      |  $$$$$$$|  $$$$$$$|  $$$$$$$| $$| $$  | $$", 1, 0);
		print("  \\______/  \\_______/ \\_______/       \\____  $$ \\______/  \\______/        \\_______/ \\____  $$ \\_______/|__/|__/  |__/", 1, 0);
		print("                                      /$$  | $$                                     /$$  \\ $$                        ", 1, 0);
		print("                                     |  $$$$$$/                                    |  $$$$$$/                        ", 1, 0);
		print("                                      \\______/                                      \\______/                         ", 1, 0);
		print("                                              /$$             /$$     /$$                               /$$          ", 1, 0);
		print("                                             | $$            | $$    |__/                              | $$          ", 1, 0);
		print("              /$$$$$$$   /$$$$$$  /$$   /$$ /$$$$$$         /$$$$$$   /$$ /$$$$$$/$$$$   /$$$$$$       | $$          ", 1, 0);
		print("             | $$__  $$ /$$__  $$|  $$ /$$/|_  $$_/        |_  $$_/  | $$| $$_  $$_  $$ /$$__  $$      | $$          ", 1, 0);
		print("             | $$  \\ $$| $$$$$$$$ \\  $$$$/   | $$            | $$    | $$| $$ \\ $$ \\ $$| $$$$$$$$      |__/          ", 1, 0);
		print("             | $$  | $$| $$_____/  >$$  $$   | $$ /$$        | $$ /$$| $$| $$ | $$ | $$| $$_____/                    ", 1, 0);
		print("             | $$  | $$|  $$$$$$$ /$$/\\  $$  |  $$$$/        |  $$$$/| $$| $$ | $$ | $$|  $$$$$$$       /$$          ", 1, 0);
		print("             |__/  |__/ \\_______/|__/  \\__/   \\___/           \\___/  |__/|__/ |__/ |__/ \\_______/      |__/          ", 1, 0);
		print("", 2, 0);
		print("=====================================================================================================================", 1, 0);
	}

	if (displayFunction == -1)
	{
		print("Press ENTER to continue... ", 0, 0);
		cin.get();// Wait for the user to press ENTER
	}
}


// To print title and word in ASCII art form
void printWord(string word)
{
	if (word == "MAIN MENU")
	{
		print("   __  __    _    ___  _  _    __  __  ___  _  _  _   _ ", 1, 4);
		print("  |  \\/  |  /_\\  |_ _|| \\| |  |  \\/  || __|| \\| || | | |", 1, 8);
		print("  | |\\/| | / _ \\  | | | .` |  | |\\/| || _| | .` || |_| |", 1, 2);
		print("  |_|  |_|/_/ \\_\\|___||_|\\_|  |_|  |_||___||_|\\_| \\___/ ", 1, 3);
	}
	if (word == "MENU")
	{
		print("  __  __  ___  _  _  _   _  ", 1, 4);
		print(" |  \\/  || __|| \\| || | | | ", 1, 8);
		print(" | |\\/| || _| | .` || |_| | ", 1, 2);
		print(" |_|  |_||___||_|\\_| \\___/  ", 1, 3);
	}
	else if (word == "MENU HANDLING")
	{
		print(" __  __  ___  _  _  _   _   _  _    _    _  _  ___   _     ___  _  _   ___ ", 1, 4);
		print("|  \\/  || __|| \\| || | | | | || |  /_\\  | \\| ||   \\ | |   |_ _|| \\| | / __|", 1, 8);
		print("| |\\/| || _| | .` || |_| | | __ | / _ \\ | .` || |) || |__  | | | .` || (_ |", 1, 2);
		print("|_|  |_||___||_|\\_| \\___/  |_||_|/_/ \\_\\|_|\\_||___/ |____||___||_|\\_| \\___|", 1, 3);
		print("//////////////////////////////////////////////////////////////////////////////", 1, 11);// for colour

		// Print bar
		print("==============================================================================", 1, 0);
		print("||                                                                          ||", 1, 0);
		print("||   .~~~~~~~~~~~~~~~~~~.    .~~~~~~~~~~~~~~~~~~.    .~~~~~~~~~~~~~~~~~~.   ||", 1, 0);

		// Print no. and name with different colour
		string printName[7];
		printName[0] = "     ADD      ", printName[1] = "    UPDATE    ",
			printName[2] = "    DELETE    ", printName[3] = "   RESTORE    ",
			printName[4] = "  VIEW MENU   ", printName[5] = " VIEW HISTORY ",
			printName[6] = "     EXIT     ";

		displaySpace(0, 0);
		print("||   |", -1, 0);
		for (int i = 0; i < 3; i++)
		{
			print(" " + to_string(i + 1) + " ", -1, 7);
			print("|", -1, 0);
			print(printName[i], -1, 7);
			if (i != 2)
				print("|    |", -1, 0);
			else
				print("|   ||", -1, 0);
		}
		cout << endl;
		print("||   '~~~~~~~~~~~~~~~~~~'    '~~~~~~~~~~~~~~~~~~'    '~~~~~~~~~~~~~~~~~~'   ||", 1, 0);
		print("||                                                                          ||", 1, 0);
		print("||   .~~~~~~~~~~~~~~~~~~.    .~~~~~~~~~~~~~~~~~~.    .~~~~~~~~~~~~~~~~~~.   ||", 1, 0);

		displaySpace(0, 0);	// Display spaces for alignment purpose
		print("||   |", -1, 0);
		for (int i = 3; i < 6; i++)
		{
			print(" " + to_string(i + 1) + " ", -1, 7);
			print("|", -1, 0);
			print(printName[i], -1, 7);
			if (i != 5)
				print("|    |", -1, 0);
			else
				print("|   ||", -1, 0);
		}
		cout << endl;

		print("||   '~~~~~~~~~~~~~~~~~~'    '~~~~~~~~~~~~~~~~~~'    '~~~~~~~~~~~~~~~~~~'   ||", 1, 0);
		print("||                                                                          ||", 1, 0);
		print("||                           .~~~~~~~~~~~~~~~~~~.                           ||", 1, 0);

		displaySpace(0, 0);	// Display spaces for alignment purpose
		print("||                           |", -1, 0);
		print(" 7 |", -1, 7);
		print(printName[6], -1, 7);
		print("|                           ||", -1, 0);
		cout << endl;

		print("||                           '~~~~~~~~~~~~~~~~~~'                           ||", 1, 0);
		print("==============================================================================", 2, 0);
	}
	else if (word == "Adding...")
	{
		print(" ___    _    _  _                    ", 1, 4);
		print("| . | _| | _| |<_>._ _  ___          ", 1, 8);
		print("|   |/ . |/ . || || ' |/ . | _  _  _ ", 1, 2);
		print("|_|_|\\___|\\___||_||_|_|\\_. |<_><_><_>", 1, 3);
		print("                       <___'         ", 1, 9);
	}
	else if (word == "Updating...")
	{
		print("  _   _           _        _    _                      ", 1, 4);
		print(" | | | | _ __  __| | __ _ | |_ (_) _ _   __ _          ", 1, 8);
		print(" | |_| || '_ \\/ _` |/ _` ||  _|| || ' \\ / _` | _  _  _ ", 1, 2);
		print("  \\___/ | .__/\\__,_|\\__,_| \\__||_||_||_|\\__, |(_)(_)(_)", 1, 3);
		print("        |_|                             |___/          ", 1, 9);
	}
	else if (word == "Deleting...")
	{
		print("   ___        _       _    _                      ", 1, 4);
		print("  |   \\  ___ | | ___ | |_ (_) _ _   __ _          ", 1, 8);
		print("  | |) |/ -_)| |/ -_)|  _|| || ' \\ / _` | _  _  _ ", 1, 2);
		print("  |___/ \\___||_|\\___| \\__||_||_||_|\\__, |(_)(_)(_)", 1, 3);
		print("                                   |___/          ", 1, 9);
	}
	else if (word == "MENU HANDLING HISTORY")
	{
		print(" __  __  ___  _  _  _   _   _  _    _    _  _  ___   _     ___  _  _   ___   _  _  ___  ___  _____  ___   ___ __   __", 1, 4);
		print("|  \\/  || __|| \\| || | | | | || |  /_\\  | \\| ||   \\ | |   |_ _|| \\| | / __| | || ||_ _|/ __||_   _|/ _ \\ | _ \\\\ \\ / /", 1, 8);
		print("| |\\/| || _| | .` || |_| | | __ | / _ \\ | .` || |) || |__  | | | .` || (_ | | __ | | | \\__ \\  | | | (_) ||   / \\ V / ", 1, 2);
		print("|_|  |_||___||_|\\_| \\___/  |_||_|/_/ \\_\\|_|\\_||___/ |____||___||_|\\_| \\___| |_||_||___||___/  |_|  \\___/ |_|_\\  |_|  ", 1, 3);
	}
	else if (word == "Restoring...")
	{
		print("  ___           _              _                      ", 1, 4);
		print(" | _ \\ ___  ___| |_  ___  _ _ (_) _ _   __ _          ", 1, 8);
		print(" |   // -_)(_-<|  _|/ _ \\| '_|| || ' \\ / _` | _  _  _ ", 1, 2);
		print(" |_|_\\\\___|/__/ \\__|\\___/|_|  |_||_||_|\\__, |(_)(_)(_)", 1, 3);
		print("                                       |___/          ", 1, 3);
	}
	else if (word == "TRANSACTION HANDLING")
	{
		print("  _____  ___    _    _  _  ___    _    ___  _____  ___  ___   _  _   _  _    _    _  _  ___   _     ___  _  _   ___ ", 1, 4);
		print(" |_   _|| _ \\  /_\\  | \\| |/ __|  /_\\  / __||_   _||_ _|/ _ \\ | \\| | | || |  /_\\  | \\| ||   \\ | |   |_ _|| \\| | / __|", 1, 8);
		print("   | |  |   / / _ \\ | .` |\\__ \\ / _ \\| (__   | |   | || (_) || .` | | __ | / _ \\ | .` || |) || |__  | | | .` || (_ |", 1, 2);
		print("   |_|  |_|_\\/_/ \\_\\|_|\\_||___//_/ \\_\\\\___|  |_|  |___|\\___/ |_|\\_| |_||_|/_/ \\_\\|_|\\_||___/ |____||___||_|\\_| \\___|", 1, 3);
	}
	else if (word == "TRANSACTION HISTORY")
	{
		print("  _____  ___    _    _  _  ___    _    ___  _____  ___  ___   _  _   _  _  ___  ___  _____  ___   ___ __   __", 1, 4);
		print(" |_   _|| _ \\  /_\\  | \\| |/ __|  /_\\  / __||_   _||_ _|/ _ \\ | \\| | | || ||_ _|/ __||_   _|/ _ \\ | _ \\\\ \\ / /", 1, 8);
		print("   | |  |   / / _ \\ | .` |\\__ \\ / _ \\| (__   | |   | || (_) || .` | | __ | | | \\__ \\  | | | (_) ||   / \\ V / ", 1, 2);
		print("   |_|  |_|_\\/_/ \\_\\|_|\\_||___//_/ \\_\\\\___|  |_|  |___|\\___/ |_|\\_| |_||_||___||___/  |_|  \\___/ |_|_\\  |_|  ", 1, 3);
	}
	else if (word == "RESULT")
	{
		print("  ___  ___  ___  _   _  _   _____ ", 1, 4);
		print(" | _ \\| __|/ __|| | | || | |_   _|", 1, 8);
		print(" |   /| _| \\__ \\| |_| || |__ | |  ", 1, 2);
		print(" |_|_\\|___||___/ \\___/ |____||_|  ", 1, 3);
	}
	else if (word == "ADD TRANSACTION")
	{
		print("    _    ___   ___    _____  ___    _    _  _  ___    _    ___  _____  ___  ___   _  _ ", 1, 4);
		print("   /_\\  |   \\ |   \\  |_   _|| _ \\  /_\\  | \\| |/ __|  /_\\  / __||_   _||_ _|/ _ \\ | \\| |", 1, 8);
		print("  / _ \\ | |) || |) |   | |  |   / / _ \\ | .` |\\__ \\ / _ \\| (__   | |   | || (_) || .` |", 1, 2);
		print(" /_/ \\_\\|___/ |___/    |_|  |_|_\\/_/ \\_\\|_|\\_||___//_/ \\_\\\\___|  |_|  |___|\\___/ |_|\\_|", 1, 3);
	}
}

// To print a loading progress bar
void loading(int time, int colour, int original)
{
	// Declaration of varaible
	int fillerAmount, barLength = 50, updateValue = 0;
	double currentProgress = 0, neededProgress = 100;
	string bar1stPart = "|", barLastPart = "|", filler = "_", updater = "_";

	// Print the loading bar
	print(" ___________________________________________________", 1, original);

	//Main loop for progress
	for (int i = 0; i < 100; i++)
	{
		//Update progress bar: How much new progress was added (only needed when new progress was added)
		currentProgress += 1;
		fillerAmount = (int)((currentProgress / neededProgress) * (double)barLength);

		//Print progress Bar:
		updateValue %= updater.length();
		cout << "\r";
		print(" ", -1, original);
		for (int i = 0; i < space - 1; i++)
			cout << " ";
		print(bar1stPart, -1, original);

		//Print out current progress
		for (int a = 0; a < fillerAmount; a++)
		{
			print(filler, -1, colour);
		}
		cout << updater[updateValue];

		// Print out spaces
		for (int b = 0; b < barLength - fillerAmount; b++)
		{
			print("_", -1, original);
		}

		// Print last part of progress bar 
		print(bar1stPart, -1, original);
		print(" ", -1, original);
		cout << "(" << (int)(100 * (currentProgress / neededProgress)) << "%)" << flush;

		updateValue++;	// Update value 
		Sleep(time);	// Control time for status bar
	}
	cout << endl;
}
