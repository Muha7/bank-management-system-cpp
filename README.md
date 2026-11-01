# Bank Management System (C++)

A console-based Bank Management System developed using C++ and Object-Oriented Programming (OOP). This project simulates basic banking operations and administrative functions, providing a structured environment for managing client records, user accounts, access permissions, and financial transactions.

The application uses file handling to store and retrieve client and user information locally, allowing data to persist between program executions.

## Features

### 1. Client Management
- Display a complete list of registered clients.
- Add new client records.
- Delete existing clients.
- Update client information.
- Search for clients using their account numbers.
- Prevent duplicate account numbers.

### 2. Banking Transactions
- Deposit money into client accounts.
- Withdraw money from client accounts.
- Validate available balances before withdrawals.
- Display individual client balances.
- Calculate and display the total balance of all clients.
- Confirm transactions before applying balance changes.

### 3. User Management
- Add new system users.
- Display all registered users.
- Delete existing users.
- Update user information and permissions.
- Search for users by username.
- Prevent duplicate usernames.

### 4. Authentication & Access Control
- Username and password authentication.
- Role-based access control.
- Full-access and customized user permissions.
- Permission validation before accessing restricted client operations and transaction menus.
- Bitwise operations to manage individual permissions.

## Technologies Used

- **Programming Language:** C++
- **Programming Concepts:** Object-Oriented Programming (OOP), Structures, Enumerations, Functions, Vectors.
- **File Handling:** C++ File Streams (`fstream`, `ifstream`, `ofstream`).
- **Data Storage:** Local text files.
- **Access Control:** Bitwise Operators and Permission Flags.
- **Standard Libraries:** iostream, vector, string, fstream, iomanip, cctype, ctime.

## Project Structure

```text
bank-management-system-cpp/
│
├── Bank_Extention_user.cpp   # Main C++ source code
├── Client.txt                # Client records
├── users.txt                 # System user records
├── README.md                 # Project documentation
└── .gitignore                # Git ignored files
```

## Data Storage

The application uses local text files to maintain persistent records.

**Client.txt**

Stores client information, including:
- Account Number
- Client Name
- Phone Number
- PIN Code
- Account Balance

**users.txt**

Stores system user information, including:
- Username
- Password
- Permission Flags

Records are separated using a custom delimiter (`#//#`) and loaded into vectors when required.

## How to Run

### Prerequisites
- A C++ compiler (GCC or MinGW).
- A C++ development environment such as Visual Studio or Visual Studio Code.

### Steps

1. Clone the repository:

```bash
git clone https://github.com/Muha7/bank-management-system-cpp.git
```

2. Open the project directory.

3. Compile the source code using a C++ compiler:

```bash
g++ Bank_Extention_user.cpp -o BankSystem
```

4. Run the application on Windows:

```bash
BankSystem.exe
```

**Important:** Keep `Client.txt` and `users.txt` in the same working directory as the executable. The application uses these files to load and save records.

## Project Purpose

This project was developed to practice and demonstrate practical C++ programming skills, particularly:

- Applying OOP principles and structured programming.
- Managing records using vectors and structures.
- Implementing file-based data persistence.
- Building authentication and permission systems.
- Handling banking operations and validating user input.
- Organizing a multi-feature console application.

## Notes

This is an educational project intended to demonstrate programming concepts and basic banking system functionality. It is not designed for real-world financial use. User credentials are stored in plain text, and the application does not implement production-grade security.

## Author

**Muha7**

GitHub: [@Muha7](https://github.com/Muha7)
