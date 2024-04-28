#define STR_MAX 50
#define PHONE_LEN 20
#define PASSWORD_MAX 20
typedef struct contact
{
	char name[STR_MAX];
	char phoneNum[PHONE_LEN];
	char coolMessage[STR_MAX];
	char mail[STR_MAX];
	char password[PASSWORD_MAX];
	int isAdmin;
} contact;
void deleteContact();
char* passwordDecrypt(char* password);
char* passwordEncryption(char* password);
void search();
void updateContact();
void createContact(contact* contact);
