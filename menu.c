#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "menu.h"
#include "file_helper.h"
#include "contact.h"

#define MAX_LENGTH 50
#define STR_MAX 50
#define PHONE_LEN 10
#define PASSWORD_MAX 20

void arrowLocation(int realPosition, int arrowPosition);
void loading();
void logout();
void addContact();
int posFolder = 0;
int buttonId = 0;
int pos = 1;

void fileMenu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	char username[MAX_LENGTH] = { 0 };
	char password[MAX_LENGTH] = { 0 };
	int exitNum = 0;
	int keyPressed = 0;
	int max_pos = 0;
	int min_pos = 0;
	const int keyEsc = 27;
	const int keyEnter = 13;
	const int keyDown = 72;
	const int keyUp = 80;
	system("cls");
	while (keyPressed != keyEsc && exitNum != 1)
	{
		system("cls");
		if (posFolder == 0)
		{
			SetConsoleTextAttribute(hConsole, 6);
			printf("%s", " _       ___    ____  ____  ____       ___ ___    ___  ____   __ __ \n");
			printf("%s", "| |     /   \\  /    ||    ||    \\     |   |   |  /  _]|    \\ |  |  |\n");
			printf("%s", "| |    |     ||   __| |  | |  _  |    | _   _ | /  [_ |  _  ||  |  |\n");
			printf("%s", "| |___ |  O  ||  |  | |  | |  |  |    |  \\_/  ||    _]|  |  ||  |  |\n");
			printf("%s", "|     ||     ||  |_ | |  | |  |  |    |   |   ||   [_ |  |  ||  :  |\n");
			printf("%s", "|     ||     ||     | |  | |  |  |    |   |   ||     ||  |  ||     |\n");
			printf("%s", "|_____| \\___/ |___,_||____||__|__|    |___|___||_____||__|__| \\__,_|\n");
			max_pos = 2;
			min_pos = 1;
			arrowLocation(1, pos);
			printf(" Login.\n");
			arrowLocation(2, pos);
			printf(" Exit.\n");
		}
		else if (posFolder == 1 && isUserAdmin(username))
		{
			SetConsoleTextAttribute(hConsole, 4);
			printf("%s", "  ____  ___    ___ ___  ____  ____       ___ ___    ___  ____   __ __ \n");
			printf("%s", " /    ||   \\  |   |   ||    ||    \\     |   |   |  /  _]|    \\ |  |  |\n");
			printf("%s", "|  o  ||    \\ | _   _ | |  | |  _  |    | _   _ | /  [_ |  _  ||  |  |\n");
			printf("%s", "|     ||  D  ||  \\_/  | |  | |  |  |    |  \\_/  ||    _]|  |  ||  |  |\n");
			printf("%s", "|  _  ||     ||   |   | |  | |  |  |    |   |   ||   [_ |  |  ||  :  |\n");
			printf("%s", "|  |  ||     ||   |   | |  | |  |  |    |   |   ||     ||  |  ||     |\n");
			printf("%s", "|__|__||_____||___|___||____||__|__|    |___|___||_____||__|__| \\__,_|\n");
			max_pos = 5;
			min_pos = 1;
			arrowLocation(1, pos);
			printf(" Add New Contacts.\n");
			arrowLocation(2, pos);
			printf(" Delete Contacts.\n");
			arrowLocation(3, pos);
			printf(" Search Contacts.\n");
			arrowLocation(4, pos);
			printf(" Bring Up Backup.\n");
			arrowLocation(5, pos);
			printf(" Logout.\n");
		}
		else if (posFolder == 1 && !isUserAdmin(username))
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			printf("%s", "    __  _      ____    ___  ____   ______      ___ ___    ___  ____   __ __ \n");
			printf("%s", "   /  ]| |    |    |  /  _]|    \\ |      |    |   |   |  /  _]|    \\ |  |  |\n");
			printf("%s", "  /  / | |     |  |  /  [_ |  _  ||      |    | _   _ | /  [_ |  _  ||  |  |\n");
			printf("%s", " /  /  | |___  |  | |    _]|  |  ||_|  |_|    |  \\_/  ||    _]|  |  ||  |  |\n");
			printf("%s", "/   \\_ |     | |  | |   [_ |  |  |  |  |      |   |   ||   [_ |  |  ||  :  |\n");
			printf("%s", "\\     ||     | |  | |     ||  |  |  |  |      |   |   ||     ||  |  ||     |\n");
			printf("%s", " \\____||_____||____||_____||__|__|  |__|      |___|___||_____||__|__| \\__,_|\n");
			max_pos = 2;
			min_pos = 1;
			arrowLocation(1, pos);
			printf(" Search Contacts.\n");
			arrowLocation(2, pos);
			printf(" Logout.\n");
		}
		keyPressed = _getch();
		if (keyPressed == keyUp && pos < max_pos)
		{
			buttonId++;
			pos++;
		}
		else if (keyPressed == keyDown && pos > min_pos)
		{
			buttonId--;
			pos--;
		}
		if (keyPressed == keyEnter)
		{
			switch (pos)
			{
			case 1:
				if (buttonId == 0)
				{
					do
					{
						printf("Name:");
						fgets(username, MAX_LENGTH, stdin);
						username[strcspn(username, "\n")] = 0;
					} while (strlen(username) < 3 || strlen(username) > 12 && !isUsernameInFile(username));
					do
					{
						printf("Password:");
						fgets(password, MAX_LENGTH, stdin);
						password[strcspn(password, "\n")] = 0;
					} while (strlen(password) < 3 || strlen(password) > 12);
					if (username[0] != '\0' && username != NULL && password[0] != '\0' && password != NULL)
					{
						if (isUsernameInFile(username) && isPassword(passwordEncryption(password), username))
						{
							printf("Welcome %s\n", username);
							loading();
							if (isUserAdmin(username))
							{
								buttonId = 2;
							}
							else
							{
								buttonId = 8;
							}
							posFolder = 1;
						}
						else
						{
							printf("No Name in the database");	
							_getch();
						}
					}
					else
					{
						printf("Not a valid name");
						_getch();  // Wait for any key press to continue
					}
					pos = 1;
				}
				else if (buttonId == 2)
				{
					addContact();
				}
				else if(buttonId == 8)
				{
					search();
				}
				break;
			case 2:
				if (buttonId == 1)
				{
					printf("Good Bye!");
					loading();
					exitNum = 1;
				}
				if (buttonId == 9)
				{
					logout();
				}
				if (buttonId == 3)
				{
					deleteContact();
				}
				break;
			case 3:
				if (buttonId == 4)
				{
					search();
					_getch();
				}
				break;
			case 4:
				if (buttonId == 5)
				{
					deleteAndRename();
					_getch();
				}
				break;
			case 5:
				if (buttonId == 6)
				{
					logout();
				}
				break;
			}
		}
	}
}
void arrowLocation(int realPosition, int arrowPosition)
{
	if (realPosition == arrowPosition)
	{
		printf("-->");
	}
	else
	{
		printf("   ");
	}
}

void logout()
{
	printf("GoodBye!");
	pos = 1;
	buttonId = 0;
	posFolder = 0;
	loading();
}

void addContact()
{
	contact newContact;
	createContact(&newContact);
	printf("\nNew Contact Details:\n");
	printf("Name: %s\n", newContact.name);
	printf("Phone Number: %s\n", newContact.phoneNum);
	printf("Cool Message: %s\n", newContact.coolMessage);
	printf("Email: %s\n", newContact.mail);
	printf("Password: %s\n", newContact.password);
	printf("isAdmin: %d\n", newContact.isAdmin);
	fileWrite(newContact.name, newContact.phoneNum, newContact.coolMessage, newContact.mail, newContact.password, newContact.isAdmin);
	_getch();  // Wait for any key press to continue

}

void loading()
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		printf(".");
		Sleep(100);
	}
}