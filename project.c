// header file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
// #include <conio.h>
// #include <windows.h>

// pre define fixed property
#define USERNAME_LENGTH 30
#define PASSWORD_LENGTH 30
#define EMAIL_LENGTH 70
#define PHONENUMBER_LENGTH 15
#define AUTH_DB "authDB.txt"
#define BANK_DB "bankDB.txt"

// ANSI escape codes for text color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"




// void gotoxy(int x, int y) {
//     COORD coord;
//     coord.X = x;
//     coord.Y = y;
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
// }

int getTerminalRows() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}


void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
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
} Account;



// store bank user account data when crate new bank account
int storeBankUserData(Account userAccount){
    if(userAccount.name && userAccount.email && userAccount.accountNo && userAccount.phone && userAccount.address){
        FILE *bankDb = fopen(BANK_DB, "a");

        if (bankDb == NULL){
            printf(ANSI_COLOR_RED "Failed to open Bank DB File.\n" ANSI_COLOR_RESET);
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

    int c;
    int i = 0;

    printf(ANSI_COLOR_MAGENTA "Enter Your Name: " ANSI_COLOR_RESET);
    scanf("%29s",&bankAccount.name);


    printf(ANSI_COLOR_MAGENTA "\nEnter Your Email: "ANSI_COLOR_RESET);
    scanf("%29s",&bankAccount.email);

    printf(ANSI_COLOR_MAGENTA "\nEnter Your Phone No: "ANSI_COLOR_RESET);
    scanf("%15s",&bankAccount.phone);

    printf(ANSI_COLOR_MAGENTA "\nEnter Your Address: "ANSI_COLOR_RESET);
    scanf("%99s",&bankAccount.address);
    
    srand(time(0));
    bankAccount.accountNo = rand() % 9000 + 1000;

    if(!storeBankUserData(bankAccount)){
        printf(ANSI_COLOR_RED "Some Went Wrong! Please Try Again." ANSI_COLOR_RESET);
        createBankAccount();
    };

    printf(ANSI_COLOR_GREEN "\n \"%s\" , Your Bank Account Successfully Craeted. \n\n"ANSI_COLOR_RESET, bankAccount.name);
    printf(ANSI_COLOR_BLUE "\n Your Account No: %d" ANSI_COLOR_RESET, bankAccount.accountNo);
    printf(ANSI_COLOR_YELLOW"\n -|- Please Remember Your Account No For Future -|-\n"ANSI_COLOR_RESET);
    
};

int bankUserList(){
    printf("\033[2J");
    Account userList;
    
    FILE *bankDB = fopen(BANK_DB, "r");

    if (bankDB == NULL){
        printf(ANSI_COLOR_RED "Error: Could not open Bnak DB file.\n"ANSI_COLOR_RESET);
        // exit(1);
        return 0;
    }

    int listNo = 0;
    int getRowNum = getTerminalRows();
    char name[USERNAME_LENGTH];
    int accountNo;
    char email[EMAIL_LENGTH];
    long long int phone;
    char address[100];

    while(fscanf(bankDB, "%s %d %s %lld %s\n", name, &accountNo, email, &phone, address) == 5){

        listNo++;

        if(listNo == 1){
            printf(ANSI_COLOR_BLUE "\n \t <> All Bank Account List -- \n \n\n" ANSI_COLOR_RESET);
            
            gotoxy(5, getRowNum);  printf(ANSI_COLOR_CYAN "Name");
            gotoxy(20, getRowNum);  printf("Account No");
            gotoxy(40, getRowNum); printf("Email");
            gotoxy(80, getRowNum); printf("Phone");
            gotoxy(105, getRowNum); printf("Address");


            printf("\n------------------------------------------------------------------------------------------------------\n\n");
        };

            getRowNum = getTerminalRows();
            gotoxy(5, getRowNum);  printf(ANSI_COLOR_MAGENTA "%s",name);
            gotoxy(20, getRowNum);  printf("%d",accountNo);
            gotoxy(40, getRowNum); printf("%s",email);
            gotoxy(80, getRowNum); printf("%lld",phone);
            gotoxy(105, getRowNum); printf("%s",address);
        printf("\n------------------------------------------------------------------------------------------------------\n \n"ANSI_COLOR_RESET);
    };

    if(listNo > 0){
        printf(ANSI_COLOR_YELLOW"\n <|> Total Active Account : %d <|>\n \n "ANSI_COLOR_RESET, listNo);
    }

    if(listNo == 0){
        printf(ANSI_COLOR_RED"\n Bank Account Not Found !\n\n" ANSI_COLOR_RESET);
        return 0;
    }

    fclose(bankDB);

    

    return bankUserList;
}




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


    printf(ANSI_COLOR_GREEN "\n<> MAIN MENU <>\n \n");

    printf(ANSI_COLOR_YELLOW "[1] . Bank Account Registration\n");
    printf("[2] . View ALL Customers Account\n");
    printf("[3] . Edit Customer Account\n");
    printf("[4] . Delete Customer Account\n");
    printf("[5] . Search Customer Account\n");
    printf("[6] . Transaction\n");
    printf("[7] . About US \n");
    printf("[8] . Log Out !!! \n");

    printf(ANSI_COLOR_CYAN "\n Please Enter Your Choice [1-8] : "ANSI_COLOR_RESET);

    // gotoxy(43, 20); scanf("%d", &choiceCase);
    scanf("%d",&choiceCase);

    switch (choiceCase){
    case 1:{
        createBankAccount();
        bankModule();
    }
    case 2:{
        int totalAccount = bankUserList();
        printf("\n");
        bankModule();
        break;
    }

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
        if(choiceCase > 0 && choiceCase <= 9){
            bankModule();
        }else{
            printf("\n Alert: Enter Numeric Value Must! \n \n");
        }
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

    printf(ANSI_COLOR_MAGENTA "Enter username: ");
    scanf("%49s", user.username);

    

    if (isUsernameAlreadyExist(user.username)){     //showing error if username already exist in db

        printf(ANSI_COLOR_RED "\nAlert: Username already exist ! Try again -\n\n");
        createUser();
    }

    printf(ANSI_COLOR_BLUE "Enter password: ");
    scanf("%29s", user.password);

    storeAuthData(user);    //store new user information
    printf(ANSI_COLOR_GREEN "\n  -- User Created And Logged In Successfully -- \n\n");
    printf(ANSI_COLOR_MAGENTA "\n  -|- Welcome \"%s\" , To Banking Solution -|- \n\n"ANSI_COLOR_RESET, user.username);
    bankModule();
}
// ==================END CREATE USER OR REGISTER USER============================



// ==================START LOGIN FUNCTIONALITY============================

// check user data match in auth db in login
int authValidation(AuthUser authenticateUser){
    FILE *file = fopen(AUTH_DB, "r");

    if (file == NULL){
        printf(ANSI_COLOR_RED "Failed to open Auth DB File.\n" ANSI_COLOR_RESET);
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
void login() {
    AuthUser authenticateUser;
    char blankChar;

    printf(ANSI_COLOR_MAGENTA "Enter username: ");
    scanf("%49s", authenticateUser.username);

    printf(ANSI_COLOR_CYAN "\nEnter password: ");
    scanf("%29s", authenticateUser.password);

    // Consume the newline character left in the input buffer
    // while ((blankChar = getchar()) != '\n' && blankChar != EOF);

    if (!authValidation(authenticateUser)) {
        printf("\nInvalid username or password! Try again.\n");
        login();
    }
    printf("\033[2J"); 
    // fflush(stdout);

    printf(ANSI_COLOR_BLUE "\n*----***----***----***----*\n");
    printf(ANSI_COLOR_MAGENTA "Authentication successful.\n");
    printf(ANSI_COLOR_BLUE "*----***----***----***----*\n\n"ANSI_COLOR_RESET);
}

// ================== END LOGIN FUNCTIONALITY============================



// home function defination
int home(){

    int choiceCase;

    //selected by annonymous user(before login)
    printf(ANSI_COLOR_BLUE " [1] . Login \n [2] . Create User \n [3] . Exit \n");
    printf(ANSI_COLOR_YELLOW "\nPlease Enter Your Choice [1-3] : " ANSI_COLOR_RESET);

    scanf("%d", &choiceCase);    //take choice input from user
    printf("\n");

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
            printf("Invalid choice.\n \n");
            if(choiceCase > 0 && choiceCase <=9){
                home();
            }
            else{
                printf(ANSI_COLOR_RED "Enter a numeric value must.\n"ANSI_COLOR_RESET);
                return 0;
            }
    }
}


// main function
int main()
{
    // printf(ANSI_COLOR_RED "This is red text.\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_CYAN " \t \"Banking Solution\" \n \n" ANSI_COLOR_RESET);

    home();


    return 0;
}
