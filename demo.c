#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define CREDENTIALS_FILE "credentials.txt"
#define STUDENT_FILE "students.txt"

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int age;
    float gpa;
} Student;

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} UserCredentials;

void saveCredentials(UserCredentials credentials)
{
    FILE *file = fopen(CREDENTIALS_FILE, "a");
    if (file == NULL)
    {
        printf("Error: Could not open credentials file.\n");
        exit(1);
    }

    fprintf(file, "%s %s\n", credentials.username, credentials.password);

    fclose(file);
}

int validateCredentials(UserCredentials credentials)
{
    FILE *file = fopen(CREDENTIALS_FILE, "r");
    if (file == NULL)
    {
        printf("Error: Could not open credentials file.\n");
        exit(1);
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    while (fscanf(file, "%s %s\n", username, password) == 2)
    {
        if (strcmp(credentials.username, username) == 0 && strcmp(credentials.password, password) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}

int isUsernameTaken(char username[MAX_USERNAME_LENGTH])
{
    FILE *file = fopen(CREDENTIALS_FILE, "r");
    if (file == NULL)
    {
        printf("Error: Could not open credentials file.\n");
        exit(1);
    }

    char storedUsername[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    while (fscanf(file, "%s %s\n", storedUsername, password) == 2)
    {
        if (strcmp(username, storedUsername) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}

void saveStudents(Student students[], int count)
{
    FILE *file = fopen(STUDENT_FILE, "w");
    if (file == NULL)
    {
        printf("Error: Could not open student file.\n");
        exit(1);
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s %d %.2f\n", students[i].name, students[i].age, students[i].gpa);
    }

    fclose(file);
}

int loadStudents(Student students[])
{
    FILE *file = fopen(STUDENT_FILE, "r");
    if (file == NULL)
    {
        printf("Error: Could not open student file.\n");
        exit(1);
    }

    int count = 0;
    while (fscanf(file, "%s %d %f", students[count].name, &students[count].age, &students[count].gpa) == 3)
    {
        count++;
    }

    fclose(file);

    return count;
}

void printStudent(Student student)
{
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
    printf("GPA: %.2f\n", student.gpa);
    printf("\n");
}

void registerUser()
{
    UserCredentials newUser;

    printf("Enter username: ");
    scanf("%s", newUser.username);

    if (isUsernameTaken(newUser.username))
    {
        printf("Username already taken.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", newUser.password);

    saveCredentials(newUser);
    printf("Registration successful.\n");
}

int main()
{
    int choice;
    printf("Student Management System\n");

    while (1)
    {
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            UserCredentials credentials;
            printf("Enter username: ");
            scanf("%s", credentials.username);
            printf("Enter password: ");
            scanf("%s", credentials.password);

            if (!validateCredentials(credentials))
            {
                printf("Invalid username or password.\n");
                break;
            }

            printf("Authentication successful.\n");

            Student students[MAX_STUDENTS];
            int studentCount = 0;

            studentCount = loadStudents(students);

            while (1)
            {
                printf("\nStudent Management System\n");
                printf("1. Add Student\n");
                printf("2. View All Students\n");
                printf("3. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    if (studentCount == MAX_STUDENTS)
                    {
                        printf("Maximum student limit reached.\n");
                    }
                    else
                    {
                        printf("Enter student name: ");
                        scanf(" %[^\n]s", students[studentCount].name);
                        printf("Enter student age: ");
                        scanf("%d", &students[studentCount].age);
                        printf("Enter student GPA: ");
                        scanf("%f", &students[studentCount].gpa);
                        studentCount++;
                        saveStudents(students, studentCount);
                        printf("Student added successfully.\n");
                    }
                    break;
                case 2:
                    if (studentCount == 0)
                    {
                        printf("No students found.\n");
                    }
                    else
                    {
                        printf("Student List\n");
                        for (int i = 0; i < studentCount; i++)
                        {
                            printf("Student %d:\n", i + 1);
                            printStudent(students[i]);
                        }
                    }
                    break;
                case 3:
                    saveStudents(students, studentCount);
                    printf("Logging out...\n");
                    break;
                default:
                    printf("Invalid choice.\n");
                }

                if (choice == 3)
                    break;
            }
            break;
        }
        case 2:
            registerUser();
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}