🏦 Bank Account Management System (C Project)
📖 Overview

A Bank Account Management System built in C using file handling and structured data storage. This program simulates real-world banking operations such as account creation, transactions, authentication, and statement generation using a random-access binary file (credit.dat).

📌 Features
🔐 Authentication
Role-based system:
Admin Login (username & password stored in admin.dat)
User Access (Account Number + PIN)
Admin credentials are initialized on first run
PIN verification required for sensitive operations
PIN is stored in binary file (credit.dat) as part of account record
👤 Account Management (Admin)
Create new accounts
Update account balance
Delete accounts
Search account by number
Display all accounts
Export all accounts to accounts.txt

Account includes:

Name (First & Last)
Gender
Date of Birth (DD/MM/YYYY)
Nationality
Account Type (savings, current, student, senior)
Balance
PIN
💰 Transactions (Admin + User)
Deposit money
Withdraw money
Transfer funds between accounts
Prevents negative balance
Requires PIN authentication
📜 Transaction Logging
All transactions stored in transaction.txt
Includes:
Timestamp
Transaction type (DEPOSIT / WITHDRAW / TRANSFER)
Account numbers
Amount and balance
📄 Statement Generation
Generates file: statement_<account_number>.txt
Includes:
Account details
Full transaction history
Requires PIN verification
📊 Additional Features
🔍 Search account with PIN verification
📋 View all transactions
📋 View transactions by specific account
🏆 Leaderboard (accounts sorted by balance)
🗂️ Project Structure
📁 Project Folder
│
├── credit.dat            # Binary file storing all accounts
├── admin.dat             # Admin credentials
├── accounts.txt          # Exported formatted accounts
├── transaction.txt       # Transaction history log
├── statement_*.txt       # Generated account statements
├── trans.c               # Main source code
⚙️ How It Works
🔄 File Initialization
If credit.dat does not exist:
Initializes 100 empty records
If admin.dat does not exist:
Prompts to create admin credentials
📍 Random Access Logic

Each account is stored at a fixed position:

Position = (account_number - 1) * sizeof(struct clientData)
Enables fast direct access to records
🧠 Data Structure
struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    char gender[10];
    char dob[12];
    char nationality[20];
    char accountType[20];
    double balance;
    int pin;
};

struct adminData
{
    char username[20];
    char password[20];
};
🖥️ Menu System
🔐 Login
1) ADMIN
2) USER
👨‍💼 Admin Menu
1 - store accounts to text file
2 - update account
3 - add new account
4 - delete account
5 - end program
6 - search account
7 - display all accounts
8 - deposit
9 - withdraw
10 - transfer
11 - view all transactions
12 - view transactions by account
13 - generate statement
14 - leaderboard
👤 User Menu
5 - end program
6 - search your account
8 - deposit
9 - withdraw
10 - transfer
11 - view transactions
12 - view your transactions
13 - generate statement
🔒 Security Features
Admin authentication using username & password
User authentication using account number + PIN
PIN verification required for:
Deposit
Withdraw
Transfer
Update
Delete
Search
Statement generation
Input validation:
Account number range (1–100)
DOB format validation
Account type validation
Non-negative balance enforcement
🧪 Sample Output
📄 accounts.txt
============================================================================================================
| Acct | Last Name     | First Name | Gender | DOB        | Nationality  | Type     | Balance    |
============================================================================================================
| 1    | Kumar         | Ravi       | Male   | 12/05/2000 | Indian       | savings  |   5000.00  |
============================================================================================================
📜 transaction.txt
[22/03/2026 14:32:10] DEPOSIT: Acc 1 | Amount: 1000.00 | Balance: 6000.00
[22/03/2026 15:10:45] TRANSFER: From Acc 1 -> To Acc 2 | Amount: 500.00
🚀 How to Compile & Run
🛠️ Compile
gcc trans.c -o trans
▶️ Run
./trans
💡 Highlights
⚡ Fast random-access file handling
🔐 Role-based access (Admin & User)
📊 Transaction tracking system
📄 Auto-generated statements
🏆 Leaderboard feature
🧾 Clean formatted outputs
⚠️ Limitations
PIN is stored directly in binary file (not encrypted)
Not suitable for real-world secure banking systems
CLI-based (no GUI)
Maximum 100 accounts