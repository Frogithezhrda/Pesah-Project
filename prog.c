/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/
#include <stdio.h>
#include "menu.h"
#include "file_helper.h"
#include "contact.h"

#define STR_MAX 50
#define PHONE_LEN 10
#define PASSWORD_MAX 20

int main(void)
{
	//modifyFile();
	duplicateFile();
	//char password[] = "12345678";
	//char* decrypted = passwordDecrypt(password);
	//printf(passwordEncryption(password));
	//getchar();
	////if (decrypted != NULL) 
	//{
	//	printf("Decrypted Password: %s\n", decrypted);
	//	free(decrypted); // Free the dynamically allocated memory
	//}
	//getchar();
	fileMenu();
	// fileWrite("sholi", "0508818844", "Hello my brother is raviv", "Koral@gmail.com", "koral", 1);
	// fileRead();
	insertTextIntoFile();
	getchar();
	return 0;
}
