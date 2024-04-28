#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#define MAX_EXTRACT 50
#define ADMIN 2
//, char* phoneNum, char* coolMessage, char* mail, char* password
void fileWrite(char* name, char* phoneNum, char* coolMessage, char* mail, char* password, int isAdmin)
{
    FILE* filePointer = NULL;
    filePointer = fopen("contacts.json", "a");
    if (filePointer == NULL)
    {
        printf("Error opening file!\n");
        return; // Exit the function if file opening failed
    }
    if (isFileContent())
    {

        fprintf(filePointer, ",\n\{\"name\": \"%s\", \"phoneNum\": \"%s\", \"coolMessage\": \"%s\", \"mail\": \"%s\", \"password\": \"%s\", \"length\": %d, \"isAdmin\": %d}", name, phoneNum, coolMessage, mail, passwordEncryption(password), strlen(name), isAdmin); // Write data to file with newline
    }
    else
    {
        fprintf(filePointer, "  {\"name\": \"%s\", \"phoneNum\": \"%s\", \"coolMessage\": \"%s\", \"mail\": \"%s\", \"password\": \"%s\", \"length\": %d, \"isAdmin\": %d}", name, phoneNum, coolMessage, mail, passwordEncryption(password), strlen(name), isAdmin); // Write data to file with newline
    }
    fclose(filePointer); // Close file
}
void fileRead() 
{
    FILE* filePointer = NULL;
    char buffer[1000] = { 0 };
    filePointer = fopen("contacts.json", "r"); // Open file in read mode
    if (filePointer == NULL)
    {
        printf("Error opening file!\n");
        return; // Exit the function if file opening failed
    }

    // Read and print each line in the file
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(filePointer); // Close file
}

int isUsernameInFile(char* username)
{
    FILE* filePointer = NULL;
    char buffer[200] = { 0 };
    char storedUsername[MAX_EXTRACT] = { 0 };
    int nameLength = 0;
    int foundUser = 0;

    filePointer = fopen("contacts.json", "r");
    if (filePointer == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        char* nameStart = strstr(buffer, "\"name\": \"");
        if (nameStart != NULL)
        {
            nameStart += strlen("\"name\": \"");
            char* nameEnd = strstr(nameStart, "\"");
            if (nameEnd != NULL)
            {
                strncpy(storedUsername, nameStart, nameEnd - nameStart);
                storedUsername[nameEnd - nameStart] = '\0';
                nameLength = nameEnd - nameStart;
            }
        }

        if (nameLength == strlen(username) && strcmp(storedUsername, username) == 0)
        {
            foundUser = 1;
            break;
        }
    }

    fclose(filePointer);
    return foundUser;
}

int isMailInFile(char* mail)
{
    FILE* filePointer = NULL;
    char buffer[200] = { 0 };
    char storedUsername[MAX_EXTRACT] = { 0 };
    int nameLength = 0;
    int foundUser = 0;

    filePointer = fopen("contacts.json", "r");
    if (filePointer == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        char* nameStart = strstr(buffer, "\"mail\": \"");
        if (nameStart != NULL)
        {
            nameStart += strlen("\"mail\": \"");
            char* nameEnd = strstr(nameStart, "\"");
            if (nameEnd != NULL)
            {
                strncpy(storedUsername, nameStart, nameEnd - nameStart);
                storedUsername[nameEnd - nameStart] = '\0';
                nameLength = nameEnd - nameStart;
            }
        }

        if (nameLength == strlen(mail) && strcmp(storedUsername, mail) == 0)
        {
            foundUser = 1;
            break;
        }
    }

    fclose(filePointer);
    return foundUser;
}
int isPhoneNumberInFile(char* phone)
{
    FILE* filePointer = NULL;
    char buffer[200] = { 0 };
    char storedUsername[MAX_EXTRACT] = { 0 };
    int nameLength = 0;
    int foundUser = 0;

    filePointer = fopen("contacts.json", "r");
    if (filePointer == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        char* nameStart = strstr(buffer, "\"phoneNum\": \"");
        if (nameStart != NULL)
        {
            nameStart += strlen("\"phoneNum\": \"");
            char* nameEnd = strstr(nameStart, "\"");
            if (nameEnd != NULL)
            {
                strncpy(storedUsername, nameStart, nameEnd - nameStart);
                storedUsername[nameEnd - nameStart] = '\0';
                nameLength = nameEnd - nameStart;
            }
        }

        if (nameLength == strlen(phone) && strcmp(storedUsername, phone) == 0)
        {
            foundUser = 1;
            break;
        }
    }

    fclose(filePointer);
    return foundUser;
}
int isFileContent()
{
    FILE* filePointer;
    char buffer[2] = { 0 };
    filePointer = fopen("contacts.json", "r");  // Open the file in read mode
    if (filePointer == NULL)
    {
        printf("Error opening file!\n");
        return 0;  // Return 0 indicating error
    }
    if (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        fclose(filePointer); // Close file
        return 1;
    }
    fclose(filePointer); // Close file
    return 0;
}

int isUserAdmin(char* username)
{
    FILE* filePointer = NULL;
    char isAdmin[ADMIN] = { 0 };
    char buffer[180] = { 0 };
    char storedUsername[MAX_EXTRACT] = { 0 };
    int nameLength = 0;
    filePointer = fopen("contacts.json", "r");  // Open the file in read mode
    if (filePointer == NULL)
    {
        printf("Error opening file!\n");
        return 0;  // Return 0 indicating error
    }
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        char* nameStart = strstr(buffer, "\"name\": \"");
        if (nameStart != NULL)
        {
            nameStart += strlen("\"name\": \"");
            char* nameEnd = strstr(nameStart, "\"");
            if (nameEnd != NULL)
            {
                strncpy(storedUsername, nameStart, nameEnd - nameStart);
                storedUsername[nameEnd - nameStart] = '\0';
                nameLength = nameEnd - nameStart;
            }
        }
        if (nameLength == strlen(username) && strcmp(storedUsername, username) == 0)
        {
            strncpy(isAdmin, buffer + strlen(buffer) - 4, 1);
            isAdmin[1] = '\0';
            if (strcmp(isAdmin, "1") == 0)
            {
                fclose(filePointer);  // Close the file
                return 1;  // Return 1 indicating username found in file and is admin
            }
        }
    }
    fclose(filePointer);  // Close the file
    return 0;  // Return 0 indicating either username not found or not an admin
}


int isPassword(char* password, char* username)
{
    FILE* filePointer = NULL;
    char buffer[200] = { 0 };
    char storedUsername[MAX_EXTRACT] = { 0 };
    char storedPassword[MAX_EXTRACT] = { 0 };
    int nameLength = 0, passwordLength = 0;
    int foundUser = 0;
    
    filePointer = fopen("contacts.json", "r");
    if (filePointer == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        if (strstr(buffer, username) != NULL)
        {
            // Extract username and password manually
            char* nameStart = strstr(buffer, "\"name\": \"");
            if (nameStart != NULL)
            {
                nameStart += strlen("\"name\": \"");
                char* nameEnd = strstr(nameStart, "\"");
                if (nameEnd != NULL)
                {
                    strncpy(storedUsername, nameStart, nameEnd - nameStart);
                    storedUsername[nameEnd - nameStart] = '\0';
                    nameLength = nameEnd - nameStart;
                }
            }

            char* passStart = strstr(buffer, "\"password\": \"");
            if (passStart != NULL)
            {
                passStart += strlen("\"password\": \"");
                char* passEnd = strstr(passStart, "\"");
                if (passEnd != NULL)
                {
                    strncpy(storedPassword, passStart, passEnd - passStart);
                    storedPassword[passEnd - passStart] = '\0';
                    passwordLength = passEnd - passStart;
                }
            }

            if (nameLength == strlen(username) && passwordLength == strlen(password) && strcmp(storedPassword, password) == 0)
            {
                foundUser = 1;
                break;
            }
        }
    }

    fclose(filePointer);
    return foundUser;
}

int deleteFile(char* username)
{
    FILE* originalFile, *tempFile = NULL;
    char fileName[] = "contacts.json";
    char line[200] = { 0 };
    int found = 0, deleted = 0;  // Added a flag to track if any deletion occurred

    // Open the original file in read mode
    originalFile = fopen(fileName, "r");
    if (originalFile == NULL)
    {
        printf("Error opening file!");
        return 1;
    }

    // Open the temporary file in write mode
    tempFile = fopen("temp.json", "w");
    if (tempFile == NULL)
    {
        printf("Error creating temporary file!");
        fclose(originalFile);
        return 1;
    }

    // Read each line from the original file
    while (fgets(line, sizeof(line), originalFile) != NULL)
    {
        char storedUsername[MAX_EXTRACT] = { 0 };
        int nameLength = 0;
        char* nameStart = strstr(line, "\"name\": \"");
        if (nameStart != NULL)
        {
            nameStart += strlen("\"name\": \"");
            char* nameEnd = strstr(nameStart, "\"");
            if (nameEnd != NULL)
            {
                strncpy(storedUsername, nameStart, nameEnd - nameStart);
                storedUsername[nameEnd - nameStart] = '\0';
                nameLength = nameEnd - nameStart;
            }
        }

        if (nameLength == strlen(username) && strcmp(storedUsername, username) == 0)
        {
            found = 1;
            deleted = 1;  // Set deletion flag
            continue;  // Skip writing this line to the temporary file
        }

        // Write lines that do not contain the username to the temporary file
        fputs(line, tempFile);
    }

    // Close both files
    fclose(originalFile);
    fclose(tempFile);

    if (!found)
    {
        printf("Username not found in file!");
        return 1;
    }

    // Delete the original file only if deletion occurred
    if (deleted && remove(fileName) != 0)
    {
        printf("Error deleting original file!");
        return 1;
    }

    // Rename the temporary file to the original filename
    if (rename("temp.json", fileName) != 0)
    {
        printf("Error renaming file!");
        return 1;
    }

    printf("Line deleted successfully!\n");
    return 0; // Success
}

void duplicateFile()
{
    FILE* sourceFile, *destFile = NULL;
    char sourceFileName[] = "contacts.json";  // Replace with your source file name
    char destFileName[] = "contactsBackup.json";  // Replace with your destination file name
    char ch = "";

    // Open the source file in read mode
    sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL) 
    {
        printf("Error opening source file");
        return 1;
    }

    // Open the destination file in write mode (create if not exists, overwrite if exists)
    destFile = fopen(destFileName, "w");
    if (destFile == NULL) 
    {
        printf("Error opening destination file");
        fclose(sourceFile);
        return 1;
    }

    // Read from the source file and write to the destination file
    while ((ch = fgetc(sourceFile)) != EOF) 
    {
        fputc(ch, destFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destFile);

    return 0;
}

void deleteAndRename() {
    char sourceFileName[] = "contactsBackup.json";  // Replace with your source file name
    char destFileName[] = "contacts.json";  // Replace with your destination file name
    char ch = ' ';
    FILE* sourceFile, * destFile = NULL;

    // Attempt to delete the destination file first

    // Open the source file in read mode
    sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL) 
    {
        printf("Error opening source file");
        return;  // Exit the function if source file cannot be opened
    }

    // Open the destination file in write mode
    destFile = fopen(destFileName, "w");
    if (destFile == NULL) 
    {
        printf("Error opening destination file");
        fclose(sourceFile);  // Close the source file before returning
        return;  // Exit the function if destination file cannot be opened
    }

    // Copy contents from source file to destination file
    while ((ch = fgetc(sourceFile)) != EOF) 
    {
        fputc(ch, destFile);
    }
    // Close both files
    fclose(sourceFile);
    fclose(destFile);

    printf("File renamed and contents copied successfully.\n");
}
void printUserInfo(char* username, char* phone, char* email, char* coolMessage) 
{
    printf("Name: %s\n", username);
    printf("Phone: %s\n", phone);
    printf("Cool Message: %s\n", coolMessage);
    printf("Email: %s\n", email);
}
void getUserInfo(char* inputUsername) 
{
    FILE* filePointer = fopen("contacts.json", "r");
    if (filePointer == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    char buffer[1024];  // Buffer to read lines from the file
    char storedUsername[50];  // Buffer to store the extracted username
    char phone[50];
    char email[50];
    char coolMessage[100];

    int nameLength = 0;  // Length of the extracted username

    while (fgets(buffer, sizeof(buffer), filePointer) != NULL) 
    {
        char* nameStart = strstr(buffer, "\"name\": \"");
        if (nameStart != NULL) {
            nameStart += strlen("\"name\": \"");
            char* nameEnd = strstr(nameStart, "\"");
            if (nameEnd != NULL) 
            {
                strncpy(storedUsername, nameStart, nameEnd - nameStart);
                storedUsername[nameEnd - nameStart] = '\0';
                nameLength = nameEnd - nameStart;
            }
        }

        if (nameLength == strlen(inputUsername) && strcmp(storedUsername, inputUsername) == 0) 
        {
            char* phoneStart = strstr(buffer, "\"phoneNum\": \"");
            if (phoneStart != NULL) 
            {
                phoneStart += strlen("\"phoneNum\": \"");
                char* phoneEnd = strstr(phoneStart, "\"");
                if (phoneEnd != NULL) 
                {
                    strncpy(phone, phoneStart, phoneEnd - phoneStart);
                    phone[phoneEnd - phoneStart] = '\0';
                }
            }

            char* emailStart = strstr(buffer, "\"mail\": \"");
            if (emailStart != NULL) 
            {
                emailStart += strlen("\"mail\": \"");
                char* emailEnd = strstr(emailStart, "\"");
                if (emailEnd != NULL) 
                {
                    strncpy(email, emailStart, emailEnd - emailStart);
                    email[emailEnd - emailStart] = '\0';
                }
            }

            char* coolMsgStart = strstr(buffer, "\"coolMessage\": \"");
            if (coolMsgStart != NULL) 
            {
                coolMsgStart += strlen("\"coolMessage\": \"");
                char* coolMsgEnd = strstr(coolMsgStart, "\"");
                if (coolMsgEnd != NULL) 
                {
                    strncpy(coolMessage, coolMsgStart, coolMsgEnd - coolMsgStart);
                    coolMessage[coolMsgEnd - coolMsgStart] = '\0';
                }
            }

            printUserInfo(storedUsername, phone, email, coolMessage);
            fclose(filePointer);
            return;
        }
    }

    fclose(filePointer);
    printf("Username not found!\n");
}
void insertTextIntoFile() 
{
    FILE* filePointer = fopen("contacts.json", "r+");
    if (filePointer == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    // Move the file pointer to the end of the file
    fseek(filePointer, 0, SEEK_END);

    // Insert the text
    fprintf(filePointer, "\n]");
    fclose(filePointer);
}
void modifyFile() 
{
    FILE* originalFile = fopen("contacts.json", "r");
    if (originalFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(originalFile);
        return;
    }

    char prevLine[200] = ""; // Buffer for the previous line
    char line[200];

    // Read each line from the original file
    while (fgets(line, sizeof(line), originalFile) != NULL) {
        // Check if this is not the last line
        if (!feof(originalFile)) {
            strcpy(prevLine, line); // Store the current line as the previous line
            fputs(line, tempFile);  // Write the line to the temp file
        }
    }

    fclose(originalFile);
    fclose(tempFile);

    // Remove the original file
    remove("contacts.json");

    // Rename the temporary file to the original filename
    rename("temp.txt", "contacts.json");
}