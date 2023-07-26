// header file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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


// //set cursor position
// COORD coord = {0, 0};
// void gotoxy(int a, int b) {
//     coord.X = a;
//     coord.Y = b;
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
// }

//user structure(obj)
typedef struct{
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} AuthUser;


//account structure(obj)
typedef struct {
    char name[30];
    char phone[PHONENUMBER_LENGTH];
    char email[EMAIL_LENGTH];
    char address[100];
    int accountNo;
} Account;



// store bank user account data when crate new bank account
int storeBankUserData(Account userAccount){
    if(userAccount.name && userAccount.email && userAccount.accountNo && userAccount.phone && userAccount.address){
        FILE *bankDb = fopen(BANK_DB, "a");

        if (bankDb == NULL){
            printf("Failed to open Bank DB File.\n");
            exit(1);
        }

        fprintf(bankDb, "%s %d %s %s %s \n",userAccount.name, userAccount.accountNo, userAccount.email, userAccount.phone, userAccount.address);

        fclose(bankDb);
        

        return 1;
    }

    return 0;

}

void createBankAccount(){
    Account bankAccount;

    printf("Enter Your Name: ");
    scanf("%s", &bankAccount.name);

    printf("Enter Your Email: ");
    scanf("%s", &bankAccount.email);

    printf("Enter Your Phone No: ");
    scanf("%s", &bankAccount.phone);

    printf("Enter Your Address: ");
    scanf("%s", &bankAccount.address);
    
    srend(time(0));
    bankAccount.accountNo = rand() % 9000 + 1000;

    if(!storeBankUserData(bankAccount)){
        printf("Some Went Wrong! Please Try Again.");
        createBankAccount();
    };

    printf("\n Bank Account Craeted Successfully.\n");
    printf("\n Your Account No: %d", bankAccount.accountNo);
    printf("\n Please Remember Your Account No For Future.\n");
    
};



// bank module defination
int bankModule(){

    int choiceCase;

    //selected by authorized user(maybe after login)
    // gotoxy(48, 4);  printf("WELCOME TO MAIN MENU");
    // gotoxy(44, 8);  printf("[1] . View Customer Accounts");
    // gotoxy(44, 9);  printf("[2] . Customer Account Registration");
    // gotoxy(44, 10); printf("[3] . Edit Customer Account");
    // gotoxy(44, 11); printf("[4] . Delete Customer Account");
    // gotoxy(44, 12); printf("[5] . Search Customer Account");
    // gotoxy(44, 13); printf("[6] . Transaction");
    // gotoxy(44, 14); printf("[7] . Log Out !!! ");
    // gotoxy(44, 15); printf("[8] . About US ");
    // gotoxy(43, 20); printf("Please Enter Your Choice [1-8] : ");

    // gotoxy(43, 20); scanf("%d", &choiceCase);   //take choice input from user


    printf("\nWELCOME TO MAIN MENU\n");
    printf("[1] . Customer Account Registration\n");
    printf("[2] . View Customer Accounts\n");
    printf("[3] . Edit Customer Account\n");
    printf("[4] . Delete Customer Account\n");
    printf("[5] . Search Customer Account\n");
    printf("[6] . Transaction\n");
    printf("[7] . About US \n");
    printf("[8] . Log Out !!! \n");
    printf("\n Please Enter Your Choice [1-8] : ");

    // gotoxy(43, 20); scanf("%d", &choiceCase);
    scanf("%d",&choiceCase);

    switch (choiceCase){
    case 1:
        createBankAccount();
        bankModule();
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

    return 0;
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
void storeAuthData(AuthUser authData){

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
    printf("\nUser Created And Logged In Successfully.\n");
    bankModule();
}
// ==================END CREATE USER OR REGISTER USER============================



// ==================START LOGIN FUNCTIONALITY============================

// check user data match in auth db in login
int authValidation(AuthUser authenticateUser){
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

    printf("\n*----***----***----***----* \n");
    printf("Authentication successful.\n");
    printf("*----***----***----***----* \n \n");

}
// ================== END LOGIN FUNCTIONALITY============================



// home function defination
int home(){

    int choiceCase;

    //selected by annonymous user(before login)
    printf(" [1] . Login \n [2] . Create User \n [3] . Exit \n");
    printf("Please Enter Your Choice [1-3] : ");

    scanf("%d", &choiceCase);    //take choice input from user


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

    printf(" \t \"Banking Solution\" \n");

    home();


    return 0;
}
