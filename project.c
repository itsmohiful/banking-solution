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
#define USERNAME_LENGTH 50
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


int adminFlag = 0;

//user structure(obj)
typedef struct{
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} AuthUser;


//account structure(obj)
typedef struct {
    char name[USERNAME_LENGTH];
    long long int phone;
    char email[EMAIL_LENGTH];
    char address[100];
    int accountNo;
    double balance; 
} Account;

//function declaration of avoid implicite declaration
int home();


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


void successMsg(char *message){     //success message showing.

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

void errorMsg(char *message){     //error message showing.

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


void infoMsg(char *message){     //info message showing.

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

void infoMsgWithPerameter(char *message, int value){     //info message showing.

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

void warningMsg(char *message){     //warning message showing.
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


// store bank user account data when create new bank account
int storeBankUserData(Account userAccount){
    if(userAccount.name && userAccount.email && userAccount.accountNo && userAccount.phone && userAccount.address && userAccount.balance){
        FILE *bankDb = fopen(BANK_DB, "a");

        if (bankDb == NULL){
            errorMsg("Failed To Open Bank DB");
            exit(1);
        }

        fprintf(bankDb, "%s %d %s %lld %s %.2lf\n",userAccount.name, userAccount.accountNo, userAccount.email, userAccount.phone, userAccount.address, userAccount.balance);

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
    printf(ANSI_COLOR_MAGENTA "Enter Your Name [In Letter]: " ANSI_COLOR_RESET);
    scanf(" %[^\n]s",bankAccount.name);
    // fgets(bankAccount.name, sizeof(30), stdin);
    // bankAccount.name[strcspn(bankAccount.name, "\n")] = '\0';
    // getchar();

    printf(ANSI_COLOR_MAGENTA "\nEnter Your Email [Must Include \'@\']: "ANSI_COLOR_RESET);
    scanf("%29s",bankAccount.email);

    printf(ANSI_COLOR_MAGENTA "\nEnter Your Phone No [Numeric]: "ANSI_COLOR_RESET);
    scanf("%lld",&bankAccount.phone);

    printf(ANSI_COLOR_MAGENTA "\nEnter Your Address [In Letter]: "ANSI_COLOR_RESET);
    scanf(" %[^\n]s",bankAccount.address);
    
    //auto set account number
    srand(time(0));
    bankAccount.accountNo = rand() % 9000 + 1000;
    bankAccount.balance = 1000;

    //store bank account data
    if(!storeBankUserData(bankAccount)){
        errorMsg("Something Went Wrong! Please Try Again");
        createBankAccount();
    };

    //showing messages
    successMsg("Congratulations! Your Bank Account Created Successfully");
    infoMsgWithPerameter("Yor Account Number Is ", bankAccount.accountNo);
    warningMsg("Please Remember Your Account Number For Future!");
    
    
};


//Bank user list methods
int bankUserList(){
    printf("\033[2J");
    clearTerminal(); //clear terminal
    Account userList;
    
    FILE *bankDB = fopen(BANK_DB, "r");

    if (bankDB == NULL){
        errorMsg("Error: Could not open Bnak DB file");
        return 0;
    }

    int listNo = 0;
    int getRowNum = 13;
    char name[USERNAME_LENGTH];
    int accountNo;
    char email[EMAIL_LENGTH];
    long long int phone;
    char address[100];
    double balance;

    //read bank data form bank DB file and store to these varriable
    while(fscanf(bankDB, "%s %d %s %lld %s %lf\n", name, &accountNo, email, &phone, address, &balance) == 6){

        listNo++;

        if(listNo == 1){

            infoMsg("All Bank Account List");
            
            //header for list table
            gotoxy(5, getRowNum);  printf(ANSI_COLOR_CYAN "Name");
            gotoxy(20, getRowNum);  printf("Account No");
            gotoxy(37, getRowNum); printf("Email");
            gotoxy(65, getRowNum); printf("Phone");
            gotoxy(88, getRowNum); printf("Balance");
            gotoxy(105, getRowNum); printf("Address\n");

            for(int i=0; i < 120; i++){printf("-");};   // under line for header
            printf("\n");
            
        };
            //showing table row as each user account    
            getRowNum += 3;
            gotoxy(5, getRowNum);  printf(ANSI_COLOR_MAGENTA "%s",name);
            gotoxy(20, getRowNum);  printf("%d",accountNo);
            gotoxy(37, getRowNum); printf("%s",email);
            gotoxy(65, getRowNum); printf("%lld",phone);
            gotoxy(88, getRowNum); printf("%.2lf",balance);
            gotoxy(105, getRowNum); printf("%s \n",address);

            for(int i=0; i < 120; i++){printf("-"ANSI_COLOR_RESET);}; // under line for header
            printf("\n");
    };

    if(listNo > 0){
        printf("\n\n");
        gotox(120);

        infoMsgWithPerameter("Total Active Account ", listNo);
    
    }

    if(listNo == 0){
        printf("\n\n");
        gotox(30);

        errorMsg("Bank Account Not Found");
        return 0;
    }

    fclose(bankDB);

    return 1; //return total account
}


//View Single Bank User Or searching bank user
int searchingBankUser(char targetName[30]){

    Account userList;
    FILE *bankDB = fopen(BANK_DB, "r");

    if (bankDB == NULL){
        errorMsg("Error: Could not open Bnak DB file");
        return 0;
    }

    int listNo = 0;
    int getRowNum = 13;
    char name[USERNAME_LENGTH];
    int accountNo;
    char email[EMAIL_LENGTH];
    long long int phone;
    char address[100];
    double balance;

    //read bank data form bank DB file and store to these varriable
    while(fscanf(bankDB, "%s %d %s %lld %s %lf\n", name, &accountNo, email, &phone, address, &balance) == 6){

        if(strcmp(targetName,name)==0){
            
            infoMsg("Account Details For Bank User: ");
            
            //header for list table
            gotoxy(5, getRowNum);  printf(ANSI_COLOR_CYAN "Name");
            gotoxy(20, getRowNum);  printf("Account No");
            gotoxy(37, getRowNum); printf("Email");
            gotoxy(65, getRowNum); printf("Phone");
            gotoxy(88, getRowNum); printf("Balance");
            gotoxy(105, getRowNum); printf("Address\n");

            for(int i=0; i < 120; i++){printf("-");};   // under line for header
            printf("\n");

            //showing table row as each user account    
            getRowNum += 3;
            gotoxy(5, getRowNum);  printf(ANSI_COLOR_MAGENTA "%s",name);
            gotoxy(20, getRowNum);  printf("%d",accountNo);
            gotoxy(37, getRowNum); printf("%s",email);
            gotoxy(65, getRowNum); printf("%lld",phone);
            gotoxy(88, getRowNum); printf("%lf",balance);
            gotoxy(105, getRowNum); printf("%s \n",address);

            for(int i=0; i < 120; i++){printf("-"ANSI_COLOR_RESET);}; // under line for header
            printf("\n");

            fclose(bankDB);
            return 1;
        }

    };

    gotox(30);
    errorMsg("Bank Account Not Found");
    fclose(bankDB);
    return 0; 
}



//Update Bank Accounts Info
int updateAccountsInfo(){

    FILE *bankDB = fopen("bankDB.txt", "r");
    if (bankDB == NULL) {
        perror("Error opening bankDB.txt");
        return 1;
    }

    Account records[200];
    int numRecords = 0;

    while (fscanf(bankDB, "%s %d %s %lld %s %lf\n",
            records[numRecords].name, &records[numRecords].accountNo,
            records[numRecords].email, &records[numRecords].phone,
            records[numRecords].address,&records[numRecords].balance) == 6) {
            
            numRecords++;
    }

    fclose(bankDB);
    clearTerminal();

    int accountToEdit;
    printf(ANSI_COLOR_CYAN "Enter the account number you want to edit: ");
    scanf("%d", &accountToEdit);
    printf("\n\n");

    int recordIndex = -1;

    for (int i = 0; i < numRecords; i++) {
        if (records[i].accountNo == accountToEdit) {
            recordIndex = i;
            break;
        }
    }

    if (recordIndex == -1) {
        errorMsg("Account number not found. Enter valid number");
        updateAccountsInfo();
    }


    //--------showing current information by table------
    infoMsg("Current Infomation");
    printf("\n");

    //header for list table
    gotoxy(5, 15);  printf(ANSI_COLOR_CYAN "Name");
    gotoxy(20, 15);  printf("Account No");
    gotoxy(37, 15); printf("Email");
    gotoxy(65, 15); printf("Phone");
    gotoxy(88, 15); printf("Balance");
    gotoxy(105, 15); printf("Address\n");

    for(int i=0; i < 120; i++){printf("-");};   // under line for header
    printf("\n");

    //value
    gotoxy(5, 17);  printf(ANSI_COLOR_MAGENTA "%s",records[recordIndex].name);
    gotoxy(20, 17);  printf("%d",records[recordIndex].accountNo);
    gotoxy(37, 17); printf("%s",records[recordIndex].email);
    gotoxy(65, 17); printf("%lld",records[recordIndex].phone);
    gotoxy(88, 17); printf("%.2lf",records[recordIndex].balance);
    gotoxy(105, 17); printf("%s \n",records[recordIndex].address);

    for(int i=0; i < 120; i++){printf("-"ANSI_COLOR_RESET);}; // under line for header
    printf("\n \n \n");


    warningMsg("Enter new information");
    printf(ANSI_COLOR_YELLOW "Name: ");
    scanf("%s", records[recordIndex].name);
    
    printf("Email: ");
    scanf("%s", records[recordIndex].email);

    printf("Phone: ");
    scanf("%lld", &records[recordIndex].phone);

    printf("Address: " ANSI_COLOR_RESET);
    scanf("%s", records[recordIndex].address);


    //--------showing updated information by table------
    infoMsg("Updated Infomation");
    printf("\n");
    //header for list table
    gotoxy(5, 15);  printf(ANSI_COLOR_CYAN "Name");
    gotoxy(20, 15);  printf("Account No");
    gotoxy(37, 15); printf("Email");
    gotoxy(65, 15); printf("Phone");
    gotoxy(88, 15); printf("Balance");
    gotoxy(105, 15); printf("Address\n");

    for(int i=0; i < 120; i++){printf("-");};   // under line for header
    printf("\n");

    //value
    gotoxy(5, 17);  printf(ANSI_COLOR_MAGENTA "%s",records[recordIndex].name);
    gotoxy(20, 17);  printf("%d",records[recordIndex].accountNo);
    gotoxy(37, 17); printf("%s",records[recordIndex].email);
    gotoxy(65, 17); printf("%lld",records[recordIndex].phone);
    gotoxy(88, 17); printf("%lf",records[recordIndex].balance);
    gotoxy(105, 17); printf("%s \n",records[recordIndex].address);

    for(int i=0; i < 120; i++){printf("-"ANSI_COLOR_RESET);}; // under line for header
    printf("\n \n \n");



    bankDB = fopen("bankDB.txt", "w");
    if (bankDB == NULL) {
        perror("Error opening bankDB.txt");
        return 1;
    }

    for (int i = 0; i < numRecords; i++) {
        fprintf(bankDB, "%s %d %s %lld %s %.2lf\n",
                records[i].name, records[i].accountNo,
                records[i].email, records[i].phone,
                records[i].address,records[i].balance);
    }

    fclose(bankDB);
    successMsg("Information Updated Successfully");
    return 0;
}




//Update Bank Accounts Info
int deleteBankAccount(){
    FILE *bankDB = fopen("bankDB.txt", "r");
    if (bankDB == NULL) {
        errorMsg("Error opening bankDB");
        return 1;
    }

    Account records[200];
    int numRecords = 0;

    while (fscanf(bankDB, "%s %d %s %lld %s %lf\n",
            records[numRecords].name, &records[numRecords].accountNo,
            records[numRecords].email, &records[numRecords].phone,
            records[numRecords].address,&records[numRecords].balance) == 6) {
            
            numRecords++;
    }

    fclose(bankDB);

    int accountToDelete;
    printf(ANSI_COLOR_CYAN "Enter the account number you want to delete: ");
    scanf("%d", &accountToDelete);
    printf("\n\n");

    int recordIndex = -1;

    for (int i = 0; i < numRecords; i++) {
        if (records[i].accountNo == accountToDelete) {
            recordIndex = i;
            break;
        }
    }

    if (recordIndex == -1) {
        errorMsg("Account number not found. Enter valid number");
        deleteBankAccount();
        
    }


    
    bankDB = fopen("bankDB.txt", "w");
    if (bankDB == NULL) {
        errorMsg("Error opening bankDB");
        return 1;
    }

    for (int i = 0; i < numRecords; i++) {

        if( i == recordIndex){
            continue;
        }
        else{
            fprintf(bankDB, "%s %d %s %lld %s %.2lf\n",
                records[i].name, records[i].accountNo,
                records[i].email, records[i].phone,
                records[i].address,records[i].balance);
        }

        
    }

    fclose(bankDB);
    successMsg("Bank Account Deleted Successfully");
    return 0;
}



int transaction(){
    clearTerminal();

    FILE *bankDB = fopen("bankDB.txt", "r+");
    if (bankDB == NULL) {
        errorMsg("Error opening bankDB");
        return 0;
    }

    Account records[200];
    int numRecords = 0;

    while (fscanf(bankDB, "%s %d %s %lld %s %lf\n",
            records[numRecords].name, &records[numRecords].accountNo,
            records[numRecords].email, &records[numRecords].phone,
            records[numRecords].address, &records[numRecords].balance) == 6) {

            numRecords++;
    }

        fclose(bankDB);

    // Perform transactions
    int senderAccountNo;
    int receiverAccountNo;
    double amount;

//----------find sender index------------
    printf("Enter your account number : ");
    scanf("%d", &senderAccountNo);
    printf("\n");
    int senderIndex = -1;

    for (int i = 0; i < numRecords; i++) {
        if (records[i].accountNo == senderAccountNo) {
            senderIndex = i;
            break;
        }
    }

    if (senderIndex == -1) {
        errorMsg("Invalid account number");
        return 0;
    }

    if(records[senderIndex].balance < 1){
        errorMsg("Failed! You Have No Balance To Perform Transaction");
        return 0;
    }


//----------find receiver index------------
    printf("Enter the receiver account number : ");
    scanf("%d", &receiverAccountNo);
    int receiverIndex = -1;

    for (int i = 0; i < numRecords; i++) {
        if (records[i].accountNo == receiverAccountNo) {
            receiverIndex = i;
            break;
        }
    }

    if (receiverIndex == -1) {
        errorMsg("Receiver account number not found!");
        return 0;
    }

    //input amount
    printf("Enter the amount for the transaction: ");
    scanf("%lf", &amount);

    if(records[senderIndex].balance < amount){
        errorMsg("Failed For Insufficient Banalce!");
        return 0;
    }


    FILE *bankDBW = fopen("bankDB.txt", "w");
    if (bankDB == NULL) {
        errorMsg("Error opening bankDB");
        return 0;
    }

    //update balance
    records[senderIndex].balance -= amount;  
    records[receiverIndex].balance += amount;  
    
    // updated data write in db file
    for (int i = 0; i < numRecords; i++) {
        fprintf(bankDBW, "%s %d %s %lld %s %.2lf\n",
                records[i].name, records[i].accountNo,
                records[i].email, records[i].phone,
                records[i].address, records[i].balance);
    }

    fclose(bankDBW);

    successMsg("Transaction completed successfully");

    return 1;

}



// bank module defination
int bankModule(){

    int choiceCase;

    printf(ANSI_COLOR_BLUE "\n<> MAIN MENU <>\n \n");

    printf(ANSI_COLOR_YELLOW "[1] . Bank Account Registration\n");
    printf("[2] . View ALL Bank Accounts\n");
    printf("[3] . Edit Bank Account\n");
    printf("[4] . Delete Bank Account\n");
    printf("[5] . Search Bank Account\n");
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

            // if(adminFlag == 1){
            //     bankUserList();
            // }
            // else{
            //     errorMsg("You are not eligible for this module!");
            // }

            bankUserList();
            printf("\n");
            bankModule();
            break;
        }

        case 3:{
            updateAccountsInfo();
            bankModule();
            break;

        }
            

        case 4:{
            if(adminFlag == 1){
                deleteBankAccount();
            }
            else{
                errorMsg("You are not eligible for this module!");
            }
            
            bankModule();
            break;
        }

        case 5:{
            clearTerminal();
            char targetedName[30];

            printf("Enter The Targeted User Name: ");
            scanf(" %[^\n]s",targetedName);
        
            searchingBankUser(targetedName);

            bankModule();
            break;
        }
        case 6:{
            transaction();
            bankModule();
            break;
        }

        case 7:
            printf("Under Development");
            break;

        case 8:{
            clearTerminal();
            successMsg("Log Out Successfull");
            adminFlag = 0;
            home();
            break;
        }

        default:
            if(choiceCase > 0 && choiceCase <= 9){
                bankModule();
            }
            else{
                
                errorMsg("Alert: Enter Numeric Value Must!");
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
        
        errorMsg("Failed to open Auth DB File");
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

        errorMsg("Failed to open Auth DB File");
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

    

    if (isUsernameAlreadyExist(user.username)){
             //showing error if username already exist in db
        errorMsg("Alert: Username already exist ! Try again");
        printf("\n\n");
        createUser();
    }

    printf(ANSI_COLOR_BLUE "Enter password: ");
    scanf("%29s", user.password);

    storeAuthData(user);    //store new user information

    successMsg("User Created And Logged In Successfully");

    infoMsg("Welcome To Banking Solution");


    bankModule();
}
// ==================END CREATE USER OR REGISTER USER============================



// ==================START LOGIN FUNCTIONALITY============================

// check user data match in auth db in login
int authValidation(AuthUser authenticateUser){
    FILE *file = fopen(AUTH_DB, "r");

    if (file == NULL){
        
        errorMsg("Failed to open Auth DB File !");
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
        errorMsg("Invalid username or password! Try again ");
        printf("\n \n");

        login();
    }

    if(strcmp(authenticateUser.username,"admin") == 0 || strcmp(authenticateUser.username,"itsmohiful") == 0 || strcmp(authenticateUser.username,"superadmin") == 0){
        adminFlag = 1;
    }

    clearTerminal(); //clear terminal

    successMsg( "Authentication successful");
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

        case 3:{
            printf("Exit \n");
            exit(1);
        }
        default:{
            errorMsg("Invalid Choice !");
            printf("\n \n");
            if(choiceCase > 0 && choiceCase <=9){
                home();
            }
            else{
                errorMsg("Enter a numeric value must !");
                printf("\n \n");

                return 0;
            }
        }
    }
}


// main function
int main(){
    clearTerminal(); //showing project name & clean terminal
    home();

    return 0;
}
