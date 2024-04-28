#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file_helper.h"

#define MAX_ASCII 122
#define MIN_ASCII 96
#define STR_MAX 50
#define PHONE_LEN 10
#define PASSWORD_MAX 20
void getInput(char* prompt, char* input, int minLen, int maxLen)
{
    do
    {
        printf("%s (%d-%d characters): ", prompt, minLen, maxLen);
        fgets(input, maxLen + 1, stdin);
        input[strcspn(input, "\n")] = '\0'; 
        if (!(strlen(input) < minLen || strlen(input) > maxLen))
        {
            getchar();
        }
    } while (strlen(input) < minLen || strlen(input) > maxLen);
}
void getInputMail(char* prompt, char* input, int minLen, int maxLen)
{
    do
    {

        printf("%s (%d-%d characters): ", prompt, minLen, maxLen);
        fgets(input, maxLen + 1, stdin);
        input[strcspn(input, "\n")] = '\0';
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    } while (strlen(input) < minLen || strlen(input) > maxLen);
}
void createContact(contact* conta)
{
    do
    {
        getInput("Name", conta->name, 4, 12);
    } while (isUsernameInFile(conta->name));
    getInput("Phone Number", conta->phoneNum, PHONE_LEN, PHONE_LEN);
    getInput("Email", conta->mail, 10, 20);
    getInput("Cool Message", conta->coolMessage, 4, 16);
    getInput("Password", conta->password, 4, 12);
    conta->isAdmin = 0;  // Assuming new contacts are not admins by default
}

void search()
{
    char input[PASSWORD_MAX] = { 0 };
    int option = 0;
    printf("--Search By Name--\n");
    printf("Enter Name: ");
    fgets(input, PASSWORD_MAX, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (isUsernameInFile(input))
    {
        getUserInfo(input);
    }
    else
    {
        printf("No User In File");
    }
    _getch();
}
void deleteContact()
{
    char username[STR_MAX] = { 0 };
    printf("Which Username to delete:");
    fgets(username, PHONE_LEN + 3, stdin);
    username[strcspn(username, "\n")] = '\0';
    if (username != NULL)
    {
        if (isUsernameInFile(username) && !isUserAdmin(username))
        {
            deleteFile(username);
            _getch();
        }
        else
        {
            printf("No Username in file!");
            _getch();
        }
    }
}

char* passwordEncryption(char* password)
{
    int i = 0;
    int string_length = strlen(password);
    char saved_letter = "";
    int saved_ascii_value = 0;
    char* encryptPass = malloc((string_length + 1) * sizeof(char)); // Allocate memory for decryptedPass
    if (encryptPass == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (i = 0; i < string_length; i++)
    {
        saved_ascii_value = (int)password[i] + 4; // Decrypt by subtracting 4 from ASCII value
        if (!(saved_ascii_value == 48 || saved_ascii_value == 49 || saved_ascii_value == 50 || saved_ascii_value == 51 || saved_ascii_value == 52 || saved_ascii_value == 53 || saved_ascii_value == 54 || saved_ascii_value == 55 || saved_ascii_value == 56 || saved_ascii_value == 57))
        {
            if (saved_ascii_value < MIN_ASCII)
            {
                saved_ascii_value = MAX_ASCII - (MIN_ASCII - saved_ascii_value);
            }
        }
        encryptPass[i] = (char)saved_ascii_value;
    }
    encryptPass[string_length] = '\0'; // Null-terminate the decrypted string

    // Reverse the decryptedPass string
    for (i = 0; i < string_length / 2; i++)
    {
        saved_letter = encryptPass[i];
        encryptPass[i] = encryptPass[string_length - i - 1];
        encryptPass[string_length - i - 1] = saved_letter;
    }
    return encryptPass;
}

char* passwordDecrypt(char* password) 
{
    int i = 0;
    int string_length = strlen(password);
    char saved_letter = "";
    int saved_ascii_value = 0;
    char* decryptedPass = malloc((string_length + 1) * sizeof(char)); // Allocate memory for decryptedPass
    if (decryptedPass == NULL) 
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (i = 0; i < string_length; i++) 
    {
        saved_ascii_value = (int)password[i] - 4; // Decrypt by subtracting 4 from ASCII value
        if (saved_ascii_value < MIN_ASCII) 
        {
            saved_ascii_value = MAX_ASCII - (MIN_ASCII - saved_ascii_value);
        }
        decryptedPass[i] = (char)saved_ascii_value;
    }
    decryptedPass[string_length] = '\0'; // Null-terminate the decrypted string

    // Reverse the decryptedPass string
    for (i = 0; i < string_length / 2; i++) 
    {
        saved_letter = decryptedPass[i];
        decryptedPass[i] = decryptedPass[string_length - i - 1];
        decryptedPass[string_length - i - 1] = saved_letter;
    }
    return decryptedPass;
}