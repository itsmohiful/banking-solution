// header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <conio.h>
//#include <windows.h>

// pre define fixed property
#define USERNAME_LENGTH 30
#define PASSWORD_LENGTH 30
#define EMAIL_LENGTH 70
#define PHONENUMBER_LENGTH 15
#define AUTH_DB "authDB.txt"
#define BANK_DB "bankDB.txt"


//set cursor position
COORD coord = {0, 0};
void gotoxy(int a, int b) {
    coord.X = a;
    coord.Y = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//user structure(obj)
typedef struct{
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} AuthUser;


//account structure(obj)
typedef struct {
    char name[USERNAME_LENGTH];
    char phone[PHONENUMBER_LENGTH];
    char email[EMAIL_LENGTH];
    char address[100];
    int accountNo;
    char citizen[50];
} Account;



// bank module defination
int bankModule(){

    int choiceCase;

    //selected by authorized user(maybe after login)
    gotoxy(48, 4);  printf("WELCOME TO MAIN MENU");
    gotoxy(44, 8);  printf("[1] . View Customer Accounts");
    gotoxy(44, 9);  printf("[2] . Customer Account Registration");
    gotoxy(44, 10); printf("[3] . Edit Customer Account");
    gotoxy(44, 11); printf("[4] . Delete Customer Account");
    gotoxy(44, 12); printf("[5] . Search Customer Account");
    gotoxy(44, 13); printf("[6] . Transaction");
    gotoxy(44, 14); printf("[7] . Log Out !!! ");
    gotoxy(44, 15); printf("[8] . About US ");
    gotoxy(43, 20); printf("Please Enter Your Choice [1-8] : ");

    gotoxy(43, 20); scanf("%d", &choiceCase);   //take choice input from user

    switch (choiceCase){
    case 1:
        printf("Under Development");
        break;
    case 2:
        printf("Under Development");
        break;

    case 3:
        printf("Under Development");
        break;

    case 4:
        printf("Under Development");
        break;

    case 5:
        printf("Under Development");
        break;

    case 6:
        printf("Under Development");
        break;

    case 7:
        printf("Under Development");
        break;

    case 8:
        printf("Under Development");
        break;

    default:
        break;
    }

    return;
}


// ==================CREATE USER OR REGISTER USER============================

// check is user name already exist to create new user
int isUsernameAlreadyExist(char username[USERNAME_LENGTH]){
    FILE *db = fopen(AUTH_DB, "r");

    if (db == NULL){
        printf("Failed to open Auth DB File.\n");
        exit(1);
    }

    char dbUsername[USERNAME_LENGTH];

    while (fscanf(db, "%s\n", dbUsername) == 1){

        if (strcmp(username, dbUsername) == 0){
            fclose(db);
            return 1;
        }
    }

    fclose(db);

    return 0;
}


// store new user data when create new user
void storeAuthData(authData){

    FILE *authDB = fopen(AUTH_DB, "a");

    if (authDB == NULL){
        printf("Failed to open Auth DB File.\n");
        exit(1);
    }

    fprintf(authDB, "%s %s\n", authData.username, authData.password);

    fclose(authDB);
}

// create or register new user
void createUser(){
    AuthUser user;

    printf("Enter username: ");
    scanf("%s", user.username);

    if (isUsernameAlreadyExist(user.username)){     //showing error if username already exist in db

        printf("Error: Username already exist.\n");
        createUser();
    }

    printf("Enter password: ");
    scanf("%s", user.password);

    storeAuthData(user);    //store new user information
    printf("User Created successfully.\n");
}
// ==================END CREATE USER OR REGISTER USER============================



// ==================START LOGIN FUNCTIONALITY============================

// check user data match in auth db in login
int authValidation(authenticateUser){
    FILE *file = fopen(AUTH_DB, "r");

    if (file == NULL){
        printf("Failed to open Auth DB File.\n");
        exit(1);
    }

    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    while (fscanf(file, "%s %s\n", username, password) == 2){

        if (strcmp(authenticateUser.username, username) == 0 && strcmp(authenticateUser.password, password) == 0){
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}

// login method defination
void login(){
    AuthUser authenticateUser;

    printf("Enter username: ");
    scanf("%s", authenticateUser.username);
    printf("Enter password: ");
    scanf("%s", authenticateUser.password);

    if (!authValidation(authenticateUser)){
        printf("Invalid username or password. \n");
        login();
    }

    printf("Authentication successful.\n");

}
// ================== END LOGIN FUNCTIONALITY============================



// home function defination
void home(){

    int choiceCase;

    //selected by annonymous user(before login)
    gotoxy(48, 4); printf("[1] . Login \n [2] . Create User \n [3] . Exit \n");
    gotoxy(48, 4); printf("Please Enter Your Choice [1-3] : ");

    gotoxy(48, 4); scanf("%d", &choiceCase);    //take choice input from user


    switch(choiceCase){
        case 1:{
            login();

            bankModule();
        }

        case 2:
            createUser();
            break;
        case 3:
            printf("Exit \n");
            return 0;
        default:
            printf("Invalid choice.\n");
            home();
    }
}


// main function
int main()
{

    printf(" \"Banking Solution\" \n");

    home();


    return 0;
}
