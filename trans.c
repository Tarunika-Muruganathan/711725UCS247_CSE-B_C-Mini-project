// Bank-account program reads a random-access file sequentially, 
// updates data already written to the file, creates new data to 
// be placed in the file, and deletes data previously in the file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// structure
struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    char gender[10];
    char dob[12];
    char nationality[20];
    double balance;
};

// prototypes
unsigned int enterChoice(void);
void textFile(FILE *readPtr);
void updateRecord(FILE *fPtr);
void newRecord(FILE *fPtr);
void deleteRecord(FILE *fPtr);
void searchRecord(FILE *fPtr);
void displayAll(FILE *fPtr);
int isValidDOB(char *dob);
void clearBuffer();

// ------------------ HELPER FUNCTIONS ------------------

void clearBuffer()
{
    while (getchar() != '\n');
}

int isValidDOB(char *dob)
{
    if (strlen(dob) != 10) return 0;
    if (dob[2] != '/' || dob[5] != '/') return 0;

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5) continue;
        if (!isdigit(dob[i])) return 0;
    }
    return 1;
}

// ------------------ MAIN ------------------

int main()
{
    FILE *cfPtr;
    unsigned int choice;

    if ((cfPtr = fopen("credit.dat", "rb+")) == NULL)
    {
        printf("File could not be opened.\n");
        exit(1);
    }

    // enable user to specify action
    while ((choice = enterChoice()) != 5)
    {
        switch (choice)
        {
            case 1: textFile(cfPtr); break;
            case 2: updateRecord(cfPtr); break;
            case 3: newRecord(cfPtr); break;
            case 4: deleteRecord(cfPtr); break;
            case 6: searchRecord(cfPtr); break;
            case 7: displayAll(cfPtr); break;
            default: printf("Incorrect choice\n");
        }
    }

    fclose(cfPtr);
}

// ------------------ FUNCTIONS ------------------

unsigned int enterChoice(void)
{
    unsigned int choice;

    printf("\n1-Text File\n2-Update\n3-New\n4-Delete\n5-Exit\n6-Search\n7-Display\n? ");

    if (scanf("%u", &choice) != 1)
    {
        printf("Invalid input!\n");
        clearBuffer();
        return 0;
    }

    clearBuffer();
    return choice;
}

// ------------------

void newRecord(FILE *fPtr)
{
    struct clientData client = {0};
    unsigned int acc;

    printf("Enter account number (1-100): ");
    if (scanf("%u", &acc) != 1)
    {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    clearBuffer();

    if (acc < 1 || acc > 100)
    {
        printf("Invalid account number!\n");
        return;
    }

    fseek(fPtr, (acc - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&client, sizeof(client), 1, fPtr);

    if (client.acctNum != 0)
    {
        printf("Account already exists!\n");
        return;
    }

    printf("Enter lastname firstname gender DOB nationality balance:\n");

    if (scanf("%14s %9s %9s %11s %19s %lf",
              client.lastName,
              client.firstName,
              client.gender,
              client.dob,
              client.nationality,
              &client.balance) != 6)
    {
        printf("Invalid input format!\n");
        clearBuffer();
        return;
    }

    clearBuffer();

    if (!isValidDOB(client.dob))
    {
        printf("Invalid DOB format!\n");
        return;
    }

    if (client.balance < 0)
    {
        printf("Balance cannot be negative!\n");
        return;
    }

    client.acctNum = acc;

    fseek(fPtr, (acc - 1) * sizeof(client), SEEK_SET);
    fwrite(&client, sizeof(client), 1, fPtr);

    printf("Account created successfully!\n");
}

// ------------------

void updateRecord(FILE *fPtr)
{
    struct clientData client = {0};
    unsigned int acc;
    double amount;

    printf("Enter account number: ");
    if (scanf("%u", &acc) != 1)
    {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    clearBuffer();

    if (acc < 1 || acc > 100)
    {
        printf("Invalid account number!\n");
        return;
    }

    fseek(fPtr, (acc - 1) * sizeof(client), SEEK_SET);
    fread(&client, sizeof(client), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account not found!\n");
        return;
    }

    printf("Current Balance: %.2f\n", client.balance);
    printf("Enter amount (+/-): ");

    if (scanf("%lf", &amount) != 1)
    {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    clearBuffer();

    if (client.balance + amount < 0)
    {
        printf("Insufficient balance!\n");
        return;
    }

    client.balance += amount;

    fseek(fPtr, -(long)sizeof(client), SEEK_CUR);
    fwrite(&client, sizeof(client), 1, fPtr);

    printf("Updated Balance: %.2f\n", client.balance);
}

// ------------------

void deleteRecord(FILE *fPtr)
{
    struct clientData client, blank = {0};
    unsigned int acc;

    printf("Enter account number: ");
    if (scanf("%u", &acc) != 1)
    {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    clearBuffer();

    if (acc < 1 || acc > 100)
    {
        printf("Invalid account number!\n");
        return;
    }

    fseek(fPtr, (acc - 1) * sizeof(client), SEEK_SET);
    fread(&client, sizeof(client), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account does not exist!\n");
        return;
    }

    fseek(fPtr, (acc - 1) * sizeof(client), SEEK_SET);
    fwrite(&blank, sizeof(client), 1, fPtr);

    printf("Account deleted.\n");
}

// ------------------

void searchRecord(FILE *fPtr)
{
    struct clientData client;
    unsigned int acc;
    struct clientData client = {0, "", "", "", "", "", 0.0};

    printf("Enter account number: ");
    if (scanf("%u", &acc) != 1)
    {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    clearBuffer();

    if (acc < 1 || acc > 100)
    {
        printf("Invalid account number!\n");
        return;
    }

    fseek(fPtr, (acc - 1) * sizeof(client), SEEK_SET);
    fread(&client, sizeof(client), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account not found!\n");
    }
    else
    {
        printf("%d %s %s %s %s %s %.2f\n",
               client.acctNum,
               client.lastName,
               client.firstName,
               client.gender,
               client.dob,
               client.nationality,
               client.balance);
    }
}

// ------------------

void displayAll(FILE *fPtr)
{
    struct clientData client;
    rewind(fPtr);

    printf("\nAll Accounts:\n");

    while (fread(&client, sizeof(client), 1, fPtr))
    {
        if (client.acctNum != 0)
        {
            printf("%d %s %s %s %s %s %.2f\n",
                   client.acctNum,
                   client.lastName,
                   client.firstName,
                   client.gender,
                   client.dob,
                   client.nationality,
                   client.balance);
        }
    }
}

// ------------------

void textFile(FILE *readPtr)
{
    FILE *writePtr = fopen("accounts.txt", "w");
    struct clientData client;

    if (!writePtr)
    {
        printf("File error\n");
        return;
    }

    rewind(readPtr);

    while (fread(&client, sizeof(client), 1, readPtr))
    {
        if (client.acctNum != 0)
        {
            fprintf(writePtr, "%d %s %s %s %s %s %.2f\n",
                    client.acctNum,
                    client.lastName,
                    client.firstName,
                    client.gender,
                    client.dob,
                    client.nationality,
                    client.balance);
        }
    }

    fclose(writePtr);
}