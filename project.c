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

//-----GOBAL METHOS-----------
int getTerminalRows() {    // chatch curson position
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

void gotoxy(int x, int y) {     //set cusron position in x & y axis
    printf("\033[%d;%dH", y, x);
}

void gotox(int x) {      //set cusron position in x axis
    printf("\033[%dG", x);
}

void clearTerminal(){      ///clear terminal & show project name
    printf("\033[2J");
    gotoxy(50,1);printf(ANSI_COLOR_MAGENTA"-------------------------------\n");
    gotox(49); printf("|");
    printf(ANSI_COLOR_CYAN " \t Banking Solution \t");printf(ANSI_COLOR_MAGENTA"|\n");
    gotox(50);printf(ANSI_COLOR_MAGENTA"-------------------------------\n" ANSI_COLOR_RESET);
    gotoxy(0,8);
}

void loading(){
    gotoxy(30,12);printf(ANSI_COLOR_YELLOW "[LOADING....]" ANSI_COLOR_RESET);
    sleep(2);

    // printf("\033[2J");
    gotoxy(50,1);printf(ANSI_COLOR_MAGENTA"-------------------------------\n");
    gotox(49); printf("|");
    printf(ANSI_COLOR_CYAN " \t Banking Solution \t");printf(ANSI_COLOR_MAGENTA"|\n");
    gotox(50);printf(ANSI_COLOR_MAGENTA"-------------------------------\n");
    gotoxy(0,8);

}


void successMsg(char message[300]){     //success message showing.
    int line = strlen(message);
    // gotoxy(1,8);

    gotox(30);
    for(int i = 0; i < line + 10; i++){printf(ANSI_COLOR_GREEN"-");};printf("\n");
    gotox(28); printf("|");
    printf("\t %s \t",message);
    printf("| \n");
    gotox(30); 
    for(int i = 0; i < line + 10; i++){printf("-");};
    printf("\n\n");
    printf(""ANSI_COLOR_RESET);
}

void errorMsg(char message[300]){     //error message showing.
    int line = strlen(message);
    // gotoxy(1,8);

    gotox(30);
    for(int i = 0; i < line + 10; i++){printf(ANSI_COLOR_RED"-");};printf("\n");
    gotox(28); printf("|");
    printf("\t %s \t",message);
    printf("| \n");
    gotox(30); 
    for(int i = 0; i < line + 10; i++){printf("-");};
    printf("\n\n");
    printf(""ANSI_COLOR_RESET);
}


void infoMsg(char message[300]){     //info message showing.
    int line = strlen(message);
    // gotoxy(1,8);

    gotox(30);
    for(int i = 0; i < line + 10; i++){printf(ANSI_COLOR_CYAN"-");};printf("\n");
    gotox(28); printf("|");
    printf("\t %s \t",message);
    printf("| \n");
    gotox(30); 
    for(int i = 0; i < line + 10; i++){printf("-");};

    printf("\n\n");
    printf(""ANSI_COLOR_RESET);
}

void infoMsgWithPerameter(char message[300], int value){     //info message showing.
    int line = strlen(message);
    // gotoxy(1,8);

    gotox(30);
    for(int i = 0; i < line + 16; i++){printf(ANSI_COLOR_CYAN"-");};printf("\n");
    gotox(28); printf("|");
    printf("\t %s : %d\t", message, value);
    printf("| \n");
    gotox(30); 
    for(int i = 0; i < line + 16; i++){printf("-");};

    printf("\n\n");
    printf(""ANSI_COLOR_RESET);
}

void warningMsg(char message[300]){     //warning message showing.
    int line = strlen(message);
    // gotoxy(1,8);

    gotox(30);
    for(int i = 0; i < line + 10; i++){printf(ANSI_COLOR_YELLOW"-");};printf("\n");
    gotox(28); printf("|");
    printf("\t %s \t",message);
    printf("| \n");
    gotox(30); 
    for(int i = 0; i < line + 10; i++){printf("-");};

    printf("\n\n");
    printf(""ANSI_COLOR_RESET);
}

//-----GOBAL METHOS END-----------



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



// store bank user account data when create new bank account
int storeBankUserData(Account userAccount){
    if(userAccount.name && userAccount.email && userAccount.accountNo && userAccount.phone && userAccount.address){
        FILE *bankDb = fopen(BANK_DB, "a");

        if (bankDb == NULL){
            char msg[300] = "Failed To Open Bank DB";
            errorMsg(msg);
            exit(1);
        }

        fprintf(bankDb, "%s %d %s %s %s \n",userAccount.name, userAccount.accountNo, userAccount.email, userAccount.phone, userAccount.address);

        fclose(bankDb);
        

        return 1;
    }

    return 0;

}

//bank account create method
void createBankAccount(){

    clearTerminal();

    Account bankAccount;
    printf(ANSI_COLOR_MAGENTA "Enter Your Correct Information For Opening An Account ! \n\n " ANSI_COLOR_RESET);

    //input object value from user
    printf(ANSI_COLOR_MAGENTA "Enter Your Name: " ANSI_COLOR_RESET);
    scanf("%29s",bankAccount.name);

    printf(ANSI_COLOR_MAGENTA "\nEnter Your Email: "ANSI_COLOR_RESET);
    scanf("%29s",bankAccount.email);

    printf(ANSI_COLOR_MAGENTA "\nEnter Your Phone No: "ANSI_COLOR_RESET);
    scanf("%15s",bankAccount.phone);

    printf(ANSI_COLOR_MAGENTA "\nEnter Your Address: "ANSI_COLOR_RESET);
    scanf("%99s",bankAccount.address);
    
    //auto set account number
    srand(time(0));
    bankAccount.accountNo = rand() % 9000 + 1000;

    //store bank account data
    if(!storeBankUserData(bankAccount)){
        char message[300] = "Something Went Wrong! Please Try Again";
        errorMsg(message);
        createBankAccount();
    };

    //showing messages
    char mesg1[300] =  "Congratulations! Your Bank Account Created Successfully";
    char mesg2[300] = "Yor Account Number Is ";
    char mesg3[300] = "Please Remember Your Account Number For Future!";

    successMsg(mesg1);
    infoMsgWithPerameter(mesg2, bankAccount.accountNo);
    warningMsg(mesg3);
    
    
};


//Bank user list methods
int bankUserList(){

    printf("\033[2J");
    clearTerminal(); //clear terminal


    Account userList;
    
    FILE *bankDB = fopen(BANK_DB, "r");

    if (bankDB == NULL){

        char msg[300] = "Error: Could not open Bnak DB file";
        errorMsg(msg);
        
        return 0;
    }

    int listNo = 0;
    int getRowNum = 13;
    char name[USERNAME_LENGTH];
    int accountNo;
    char email[EMAIL_LENGTH];
    long long int phone;
    char address[100];

    //read bank data form bank DB file and store to these varriable
    while(fscanf(bankDB, "%s %d %s %lld %s\n", name, &accountNo, email, &phone, address) == 5){

        listNo++;

        if(listNo == 1){

            char msg[300] = "All Bank Account List";
            infoMsg(msg);
            
            //header for list table
            gotoxy(5, getRowNum);  printf(ANSI_COLOR_CYAN "Name");
            gotoxy(20, getRowNum);  printf("Account No");
            gotoxy(40, getRowNum); printf("Email");
            gotoxy(80, getRowNum); printf("Phone");
            gotoxy(105, getRowNum); printf("Address\n");

            for(int i=0; i < 130; i++){printf("-");};   // under line for header
            printf("\n");
            
        };
            //showing table row as each user account    
            getRowNum += 3;
            gotoxy(5, getRowNum);  printf(ANSI_COLOR_MAGENTA "%s",name);
            gotoxy(20, getRowNum);  printf("%d",accountNo);
            gotoxy(40, getRowNum); printf("%s",email);
            gotoxy(80, getRowNum); printf("%lld",phone);
            gotoxy(105, getRowNum); printf("%s \n",address);

            for(int i=0; i < 130; i++){printf("-"ANSI_COLOR_RESET);}; // under line for header
            printf("\n");
    };

    if(listNo > 0){
        printf("\n\n");
        gotox(120);

        char msg[300] = "Total Active Account " ;

        infoMsgWithPerameter(msg, listNo);
    
    }

    if(listNo == 0){
        printf("\n\n");
        gotox(120);
        char msg[300] = "Bank Account Not Found";
        errorMsg(msg);
        return 0;
    }

    fclose(bankDB);

    return bankUserList; //return total account
}




// bank module defination
int bankModule(){

    int choiceCase;

    printf(ANSI_COLOR_BLUE "\n<> MAIN MENU <>\n \n");

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
    // if(choiceCase){
    //     loading();
    // }

    switch (choiceCase){

        case 1:{    //crate bank account
            createBankAccount();
            bankModule();
        }
        case 2:{     //account List
            clearTerminal();
            sleep(1);
            bankUserList();
            printf("\n");
            sleep(1);
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

        case 8:{
            clearTerminal();
            successMsg("Log Out Successfull");
            home();
            break;
        }

        default:
            if(choiceCase > 0 && choiceCase <= 9){
                bankModule();
            }
            else{
                char msg[300] = "Alert: Enter Numeric Value Must!";
                errorMsg(msg);
                printf("\n \n");
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
        char msg[300] = "Failed to open Auth DB File";
        errorMsg(msg);
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

        char msg[300] = "Failed to open Auth DB File";
        errorMsg(msg);
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

        
        char msg[300] = "Alert: Username already exist ! Try again";
        errorMsg(msg);
        printf("\n\n");
        createUser();
    }

    printf(ANSI_COLOR_BLUE "Enter password: ");
    scanf("%29s", user.password);

    storeAuthData(user);    //store new user information

    char msg[300] = "User Created And Logged In Successfully";
    successMsg(msg);

    char msg1[300] = "Welcome To Banking Solution";
    infoMsg(msg1);


    bankModule();
}
// ==================END CREATE USER OR REGISTER USER============================



// ==================START LOGIN FUNCTIONALITY============================

// check user data match in auth db in login
int authValidation(AuthUser authenticateUser){
    FILE *file = fopen(AUTH_DB, "r");

    if (file == NULL){
        char msg[300] = "Failed to open Auth DB File !";
        errorMsg(msg);
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

    if (!authValidation(authenticateUser)) {
        printf("\n\n");
        char message[300] = "Invalid username or password! Try again ";
        errorMsg(message);
        printf("\n \n");

        login();
    }
    clearTerminal(); //clear terminal

    char message[300] = "Authentication successful";
    successMsg(message);
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
    // loading();
    

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
int main(){
    clearTerminal(); //showing project name & clean terminal
    home();

    return 0;
}
