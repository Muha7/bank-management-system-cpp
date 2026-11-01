#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>
#include <ctime>
using namespace std;

const string FileName = "Client.txt";
const string UserFile = "users.txt";

void ShowMainMenu();
void ShowTransactionMenuScreen();
void ShowManageUsersMenuScreen();
void Login();

struct Client
{
    string AC;
    string CName;
    string phoneNumber;
    string BinCode;
    double AB;
    bool MarkClient = false;
};

struct Users
{
    string userName;
    string Password;
    short permissions;
    bool MarkUser = false;
};

Users currentUser;

enum enMainMenuOptions
{
    eShowClientList = 1,
    eAddClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTransactios = 6,
    eManageUsers = 7,
    eLogOut = 8
};

enum enTransactionMenuOptions
{
    eDeposite = 1,
    eWithdraw = 2,
    eShowBalances = 3,
    eTransactionMainMenu = 4
};

enum enManageUsersMenuOptions
{
    eListUsers = 1,
    eAddnewuser = 2,
    eDeleteuser = 3,
    eUpdateuser = 4,
    eFinduser = 5,
    eManageUsersMainMenu = 6
};

enum enPermissions
{
    eAll = -1,
    eShowClientListPermission = 1,
    eAddClientPermission = 2,
    eDeleteClientPermission = 4,
    eUpdateClientPermission = 8,
    eFindClientPermission = 16,
    eTransactiosPermission = 32,
    eManageUsersPermission = 64
};

void showClientScreen(string Op)
{
    cout << "------------------------------------------------\n";
    cout << "\t\t " << Op << "\n";
    cout << "------------------------------------------------\n";
}

void showUserScreen(string Op)
{
    cout << "------------------------------------------------\n";
    cout << "\t\t " << Op << "\n";
    cout << "------------------------------------------------\n";
}

void Head()
{
    // cout << setw(10) << "Client List (" <<  << ") Clients"  << endl << endl;
    cout << "________________________________________________________________________________________________________\n\n";
    cout << "| Account Name   | Pin code   | Client Name                            | Phone                  | Balance";
    cout << "________________________________________________________________________________________________________\n\n";
}

vector<string> splitWords(string S, string D)
{
    short pos = 0;
    string sword;
    vector<string> vWord;

    while ((pos = S.find(D)) != std::string::npos)
    {
        sword = S.substr(0, pos);

        if (sword != "")
        {
            vWord.push_back(sword);
        }

        S.erase(0, pos + D.length());
    }

    if (sword != "")
    {
        vWord.push_back(S);
    }
    return vWord;
}

Client ConvertLineToRecord(string Line, string delim)
{
    Client sClient;
    vector<string> CDetails = splitWords(Line, delim);

    sClient.AC = CDetails[0];
    sClient.CName = CDetails[1];
    sClient.phoneNumber = CDetails[2];
    sClient.BinCode = CDetails[3];
    sClient.AB = stod(CDetails[4]);

    return sClient;
}

Users ConvertUserLineToRecord(string Line, string delim)
{
    Users sUser;
    vector<string> UDetails = splitWords(Line, delim);

    sUser.userName = UDetails[0];
    sUser.Password = UDetails[1];
    sUser.permissions = stoi(UDetails[2]);

    return sUser;
}

vector<Client> LoadClientsFromFile()
{
    vector<Client> vClient;
    fstream MyFile;
    MyFile.open("client.txt", ios::in);
    string line;

    Client sClient;
    while (getline(MyFile, line))
    {
        sClient = ConvertLineToRecord(line, "#//#");
        vClient.push_back(sClient);
    }

    return vClient;
}

vector<Users> LoadUsersFromFile()
{
    vector<Users> vUsers;
    fstream UserFile;
    UserFile.open("users.txt", ios::in);
    string line;

    Users sUsers;
    while (getline(UserFile, line))
    {
        sUsers = ConvertUserLineToRecord(line, "#//#");
        vUsers.push_back(sUsers);
    }

    return vUsers;
}

void printEachClient1(Client sClient)
{
    cout << "| " << left << setw(15) << sClient.AC;
    cout << "| " << left << setw(13) << sClient.BinCode;
    cout << "| " << left << setw(40) << sClient.CName;
    cout << "| " << left << setw(12) << sClient.phoneNumber;
    cout << "| " << left << setw(12) << sClient.AB << endl;
}

bool CheckAccessPermission(enPermissions permission)
{
    if (currentUser.permissions == enPermissions::eAll)
    {
        return true;
    }

    if ((permission & currentUser.permissions) == permission)
    {
        return true;
    }
    else
    {
        return false;
        // cout << "Permission denied, you are not allowed for this operation";
    }
}

void showAccessDenaiedMessage()
{
    cout << "Permission denied, you are not allowed for this operation";
}

void DisplayClients()
{
    if (!CheckAccessPermission(enPermissions::eShowClientListPermission))
    {
        showAccessDenaiedMessage();
        return;
    }

    vector<Client> vClient = LoadClientsFromFile();

    cout << "\n\t\t\t\t\t Client List " << vClient.size() << " Client(s)\n";
    cout << "\n________________________________________________________________________";
    cout << "____________________________\n\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(13) << "Pin code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n________________________________________________________________________";
    cout << "____________________________\n\n";

    if (vClient.size() == 0)
    {
        cout << "\n No Clients avaliable!\n";
    }
    else

        for (Client sClient : vClient)
        {
            printEachClient1(sClient);
        }

    cout << "\n________________________________________________________________________";
    cout << "____________________________\n\n";
}

bool FindClientByAC(Client &sClient, string AC, vector<Client> vClient)
{

    for (Client C : vClient)
    {
        if (AC == C.AC)
        {
            sClient = C;
            return true;
        }
    }
    return false;
}

bool ClientExisteByAC(string AC, string FileName)
{

    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string line;
        Client sClient;

        while (getline(MyFile, line))
        {
            sClient = ConvertLineToRecord(line, "#//#");

            if (sClient.AC == AC)
            {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

Client ReadClientDetails()
{
    Client sClient;

    cout << "Enter account number: ";
    getline(cin >> ws, sClient.AC);

    while (ClientExisteByAC(sClient.AC, "Client.txt"))
    {
        cout << "Client with [" << sClient.AC << "] already exists , Try another account number? ";
        getline(cin, sClient.AC);
    }

    cout << "Enter Cleint Name: ";
    getline(cin, sClient.CName);

    cout << "Enter Phone number: ";
    getline(cin, sClient.phoneNumber);

    cout << "Enter Bin code: ";
    getline(cin, sClient.BinCode);

    cout << "Enter account Balance: ";
    cin >> sClient.AB;

    return sClient;
}

string convertRecordToLine(Client sClient, string separator = "#//#")
{
    string S = "";

    S += sClient.AC + separator;
    S += sClient.CName + separator;
    S += sClient.phoneNumber + separator;
    S += sClient.BinCode + separator;
    S += to_string(sClient.AB);

    return S;
}

void AddClientDetailsToFile(string FileName, string Line)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << Line << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    Client sClient;

    sClient = ReadClientDetails();
    AddClientDetailsToFile(FileName, convertRecordToLine(sClient));
}

void AddClients()
{
    if (!CheckAccessPermission(enPermissions::eAddClientPermission))
    {
        showAccessDenaiedMessage();
        return;
    }

    char AddMore = 'Y';
    do
    {
        system("cls");

        showClientScreen("ADD Client Screen");

        AddNewClient();
        cout << "Client details added successufly, do you want to add more?\n";
        cin >> AddMore;
        cin.ignore();

    } while (toupper(AddMore) == 'Y');
}

string ReadString()
{
    string S;

    cout << "Enter Account Number: ";
    getline(cin >> ws, S);

    return S;
}

string ReadUserName()
{
    string S;

    cout << "Enter User Name : ";
    getline(cin >> ws, S);

    return S;
}

void printEachClient(Client sClient)
{
    cout << "\nClient details are: \n\n";
    cout << "Account number   :" << left << setw(15) << sClient.AC;
    cout << "\nBin code       :" << left << setw(13) << sClient.BinCode;
    cout << "\nName           :" << left << setw(40) << sClient.CName;
    cout << "\nPhone number   :" << left << setw(12) << sClient.phoneNumber;
    cout << "\nBalance        :" << left << setw(12) << sClient.AB << endl;
}

vector<Client> saveClientsTofile(string FileName, vector<Client> vClient)
{
    fstream Myfile;
    Myfile.open(FileName, ios::out);

    if (Myfile.is_open())
    {

        for (Client C : vClient)
        {
            if (C.MarkClient == false)
            {
                string line = convertRecordToLine(C);
                Myfile << line << endl;
            }
        }

        Myfile.close();
    }
    return vClient;
}

bool MarkClientForDeleteByAC(string AC, vector<Client> &vClient)
{
    for (Client &C : vClient)
    {
        if (C.AC == AC)
        {
            C.MarkClient = true;
            return true;
        }
    }
}

bool DeleteClientByAC()
{
    if (!CheckAccessPermission(enPermissions::eDeleteClientPermission))
    {
        showAccessDenaiedMessage();
        return true;
    }

    vector<Client> vClient = LoadClientsFromFile();
    string AC = ReadString();

    char D = 'n';
    Client sClient;

    if (FindClientByAC(sClient, AC, vClient))
    {
        printEachClient(sClient);

        cout << "are sure you want to delete Client: ";
        cin >> D;

        if (D == 'Y' || D == 'y')
        {
            MarkClientForDeleteByAC(AC, vClient);
            saveClientsTofile(FileName, vClient);

            // Refresh vector
            vClient = LoadClientsFromFile();

            cout << "\n\nClient Deleted succesfully\n\n";
            return true;
        }
    }
    else
    {
        cout << "\n\nCient with account number " << AC << " Not found\n\n";
        return false;
    }
}

Client UpdateClientDetails(string AC)
{
    Client sClient;

    sClient.AC = AC;

    cout << "Enter Phone number: ";
    getline(cin >> ws, sClient.phoneNumber);

    cout << "Enter Cleint Name: ";
    getline(cin, sClient.CName);

    cout << "Enter Bin code: ";
    getline(cin, sClient.BinCode);

    cout << "Enter account Balance: ";
    cin >> sClient.AB;

    return sClient;
}

bool UpdateClientByAC()
{
    if (!CheckAccessPermission(enPermissions::eUpdateClientPermission))
    {
        showAccessDenaiedMessage();
        return true;
    }

    vector<Client> vClient = LoadClientsFromFile();
    string AC = ReadString();

    char D = 'n';
    Client sClient;

    if (FindClientByAC(sClient, AC, vClient))
    {
        printEachClient(sClient);

        cout << "\nare sure you want to Udate Client? ";
        cin >> D;

        if (D == 'Y' || D == 'y')
        {
            for (Client &C : vClient)
            {
                if (AC == C.AC)
                {
                    C = UpdateClientDetails(AC);
                    break;
                }
            }

            saveClientsTofile(FileName, vClient);

            cout << "\n\nClient Udated succesfully\n\n";
            return true;
        }
    }
    else
    {
        cout << "Cient with account number " << AC << " Not found";
        return false;
    }
}

void FindPrintClient()
{
    if (!CheckAccessPermission(enPermissions::eFindClientPermission))
    {
        showAccessDenaiedMessage();
        return;
    }
    vector<Client> vClient = LoadClientsFromFile();
    string AC = ReadString();
    Client sClient;

    if (FindClientByAC(sClient, AC, vClient))
    {
        printEachClient(sClient);
    }
    else
    {
        cout << "Client with [" << AC << "] not found.\n";
    }
}

void performDeposite(int amount, vector<Client> vClient, string AC)
{
    char check;

    cout << "\nAre u sure to perform this transaction ?";
    cin >> check;

    if (check == 'y' || check == 'Y')
    {
        for (Client &C : vClient)
        {
            if (C.AC == AC)
            {
                C.AB = C.AB + amount;
                cout << "\nDone successfuly ! New balance is = " << C.AB << endl;
            }
        }

        saveClientsTofile(FileName, vClient);
    }
    else
    {
        cout << "Transaction failed\n";
    }
}

void DepositScreen()
{
    cout << "------------------------------------------------\n";
    cout << "\t\t Deposite Screen \n";
    cout << "------------------------------------------------\n";

    vector<Client> vClient = LoadClientsFromFile();
    string AC = ReadString();
    Client sClient;

    while (!FindClientByAC(sClient, AC, vClient))
    {
        cout << "Client with [" << AC << "] not found.\n";
        AC = ReadString();
    }

    printEachClient(sClient);

    int amount;
    cout << "\nPlease enter deposite amount: ";
    cin >> amount;

    performDeposite(amount, vClient, AC);
}

void WithdrawScreen()
{
    cout << "------------------------------------------------\n";
    cout << "\t\t Withdraw Screen \n";
    cout << "------------------------------------------------\n";

    vector<Client> vClient = LoadClientsFromFile();
    string AC = ReadString();
    Client sClient;

    while (!FindClientByAC(sClient, AC, vClient))
    {
        cout << "Client with [" << AC << "] not found.\n";
        AC = ReadString();
    }

    printEachClient(sClient);

    int amount;
    cout << "\nPlease enter Withdraw amount: ";
    cin >> amount;

    while (amount > sClient.AB)
    {
        cout << "Amount ecxeeds the balance, you can withdraw up to: " << sClient.AB << endl;
        cout << "Please enter another amount: ";
        cin >> amount;
    }

    performDeposite(amount * -1, vClient, AC);
}

void printEachClientBalance(Client sClient)
{
    cout << "| " << left << setw(15) << sClient.AC;
    cout << "| " << left << setw(40) << sClient.CName;
    cout << "| " << left << setw(12) << sClient.AB << endl;
}

void DisplayClientsBalances()
{
    vector<Client> vClient = LoadClientsFromFile();

    cout << "\n\t\t\t\t\t Client List " << vClient.size() << " Client(s)\n";
    cout << "\n________________________________________________________________________";
    cout << "____________________________\n\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n________________________________________________________________________";
    cout << "____________________________\n\n";

    int TotalBalances = 0;
    if (vClient.size() == 0)
    {
        cout << "\n No Clients avaliable!\n";
    }
    else
        for (Client sClient : vClient)
        {
            printEachClientBalance(sClient);
            TotalBalances += sClient.AB;
        }

    cout << "\n________________________________________________________________________";
    cout << "____________________________\n\n";

    cout << "\t\t\t Total balances = " << TotalBalances << endl;
}

short ReadMainMenuOptions()
{
    short choice;
    cout << "Choose what do you want to do? [1 To 6]? ";
    cin >> choice;

    return choice;
}

short ReadTransactionMenuOptions()
{
    short choice;
    cout << "Choose what do you want to do? [1 To 4]? ";
    cin >> choice;

    return choice;
}

short ReadManageUsersMenuOptions()
{
    short choice;
    cout << "Choose what do you want to do? [1 To 6]? ";
    cin >> choice;

    return choice;
}

void GoBackToTransactionMenu()
{
    cout << "Press any key to go back to Transaction menu. . .";
    system("pause>0");
    ShowTransactionMenuScreen();
}

void GoBackToManageUsersMenu()
{
    cout << "Press any key to go back to Manage users menu. . .";
    system("pause>0");
    ShowManageUsersMenuScreen();
}

void performTransactionMenuOperation(enTransactionMenuOptions TransactionMenuOption)
{

    switch (TransactionMenuOption)
    {
    case enTransactionMenuOptions::eDeposite:
        system("cls");
        DepositScreen();
        GoBackToTransactionMenu();
        break;

    case enTransactionMenuOptions::eWithdraw:
        system("cls");
        WithdrawScreen();
        GoBackToTransactionMenu();
        break;
    case enTransactionMenuOptions::eShowBalances:
        system("cls");
        DisplayClientsBalances();
        GoBackToTransactionMenu();
        break;
    case enTransactionMenuOptions::eTransactionMainMenu:
        system("cls");
        ShowMainMenu();
        break;
    }
}

void printEachUser(Users sUser)
{
    cout << "| " << left << setw(15) << sUser.userName;
    cout << "| " << left << setw(13) << sUser.Password;
    cout << "| " << left << setw(40) << sUser.permissions << endl;
}

void DisplayUsers()
{
    vector<Users> vUsers = LoadUsersFromFile();

    cout << "\n\t\t\t\t\t User List " << vUsers.size() << " User(s)\n";
    cout << "\n________________________________________________________________________";
    cout << "____________________________\n\n";

    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(13) << "Password";
    cout << "| " << left << setw(40) << "Permisstions";

    cout << "\n________________________________________________________________________";
    cout << "____________________________\n\n";

    if (vUsers.size() == 0)
    {
        cout << "\n No Clients avaliable!\n";
    }
    else

        for (Users sUsers : vUsers)
        {
            printEachUser(sUsers);
        }

    cout << "\n________________________________________________________________________";
    cout << "____________________________\n\n";
}

bool UserExisteByUserName(string UserName, string FileName)
{
    fstream UserFile;

    UserFile.open(FileName, ios::in);

    if (UserFile.is_open())
    {
        string line;
        Users sUser;

        while (getline(UserFile, line))
        {
            sUser = ConvertUserLineToRecord(line, "#//#");

            if (sUser.userName == UserName)
            {
                UserFile.close();
                return true;
            }
        }
        UserFile.close();
    }
    return false;
}

short ReadUserPermission()
{
    Users sUser;
    sUser.permissions = 0;
    char answer;

    cout << "\n\nDo u want to give full access? y/n";
    cin >> answer;

    if (answer == 'y' || answer == 'Y')
    {
        return -1;
    }
    else
    {
        cout << "Do u want to give access to:\n\n";

        cout << "Show Client List? y/n";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            sUser.permissions = sUser.permissions | enPermissions::eShowClientListPermission;
        }
        cout << "Add new client? y/n";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            sUser.permissions = sUser.permissions | enPermissions::eAddClientPermission;
        }
        cout << "Delete Client? y/n";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            sUser.permissions = sUser.permissions | enPermissions::eDeleteClientPermission;
        }
        cout << "Update Client? y/n";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            sUser.permissions = sUser.permissions | enPermissions::eUpdateClientPermission;
        }
        cout << "find Client? y/n";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            sUser.permissions = sUser.permissions | enPermissions::eFindClientPermission;
        }
        cout << "Transaction access? y/n";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            sUser.permissions = sUser.permissions | enPermissions::eTransactiosPermission;
        }
        cout << "Manage users? y/n";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            sUser.permissions = sUser.permissions | enPermissions::eManageUsersPermission;
        }
    }

    return sUser.permissions;
}

Users ReadUserDetails()
{
    Users sUser;

    cout << "Enter UserName: ";
    getline(cin >> ws, sUser.userName);

    while (UserExisteByUserName(sUser.userName, "users.txt"))
    {
        cout << "User with [" << sUser.userName << "] already exists , Try another user name? ";
        getline(cin, sUser.userName);
    }

    cout << "Enter Password: ";
    getline(cin, sUser.Password);

    sUser.permissions = ReadUserPermission();

    return sUser;
}

void AddUserDetailsToFile(string FileName, string Line)
{
    fstream UserFile;

    UserFile.open(FileName, ios::out | ios::app);

    if (UserFile.is_open())
    {
        UserFile << Line << endl;
        UserFile.close();
    }
}

string convertUserRecordToLine(Users sUser, string separator = "#//#")
{
    string S = "";

    S += sUser.userName + separator;
    S += sUser.Password + separator;
    S += to_string(sUser.permissions) + separator;

    return S;
}

vector<Users> saveUsersTofile(string FileName, vector<Users> &vUsers)
{
    fstream Myfile;
    Myfile.open(FileName, ios::out);

    if (Myfile.is_open())
    {

        for (Users U : vUsers)
        {
            if (U.MarkUser == false)
            {
                string line = convertUserRecordToLine(U);
                Myfile << line << endl;
            }
        }

        Myfile.close();
    }
    return vUsers;
}

void AddNewUser()
{
    Users sUser;

    sUser = ReadUserDetails();
    AddUserDetailsToFile(UserFile, convertUserRecordToLine(sUser));
}

void AddUsers()
{

    char AddMore = 'Y';
    do
    {
        system("cls");

        showUserScreen("ADD New User Screen");

        AddNewUser();
        cout << "USer details added successufly, do you want to add more?\n";
        cin >> AddMore;
        cin.ignore();

    } while (toupper(AddMore) == 'Y');
}

bool FindUserByUserName(Users &sUsers, string UserName, vector<Users> vUsers)
{
    for (Users U : vUsers)
    {
        if (UserName == U.userName)
        {
            sUsers = U;
            return true;
        }
    }
    return false;
}

bool MarkUserForDeleteByUserName(string UserName, vector<Users> &vUsers)
{
    for (Users &U : vUsers)
    {
        if (U.userName == UserName)
        {
            U.MarkUser = true;
            return true;
        }
    }
}

void printEachUser1(Users sUser)
{
    cout << "\nUser details are: \n\n";
    cout << "User Name      :" << left << setw(15) << sUser.userName;
    cout << "\nPassword     :" << left << setw(13) << sUser.Password;
    cout << "\nPermisiion   :" << left << setw(40) << sUser.permissions << endl;
}

bool DeleteUserByUserName()
{
    showUserScreen("Delete User Screen");
    vector<Users> vUsers = LoadUsersFromFile();
    string UserName = ReadUserName();

    char D = 'n';
    Users sUser;

    if (FindUserByUserName(sUser, UserName, vUsers))
    {
        printEachUser1(sUser);

        cout << "are sure you want to delete User: ";
        cin >> D;

        if (D == 'Y' || D == 'y')
        {
            MarkUserForDeleteByUserName(UserName, vUsers);
            saveUsersTofile(UserFile, vUsers);

            // Refresh vector
            vUsers = LoadUsersFromFile();

            cout << "\n\nUser Deleted succesfully\n\n";
            return true;
        }
    }
    else
    {
        cout << "\n\nUser with User Name" << UserName << " Not found\n\n";
        return false;
    }
}

Users UpdateUserDetails(string UserName)
{
    Users sUser;

    sUser.userName = UserName;

    cout << "\nEnter Password: ";
    cin >> sUser.Password;

    sUser.permissions = ReadUserPermission();

    return sUser;
}

bool UpdateUserByUserName()
{
    vector<Users> vUser = LoadUsersFromFile();
    string UserName = ReadUserName();

    char D = 'n';
    Users sUser;

    if (FindUserByUserName(sUser, UserName, vUser))
    {
        printEachUser1(sUser);

        cout << "\nare sure you want to Udate User? ";
        cin >> D;

        if (D == 'Y' || D == 'y')
        {
            for (Users &U : vUser)
            {
                if (UserName == U.userName)
                {
                    U = UpdateUserDetails(UserName);
                    break;
                }
            }

            saveUsersTofile(UserFile, vUser);

            cout << "\n\nUser Udated succesfully\n\n";
            return true;
        }
    }
    else
    {
        cout << "user with user name " << UserName << " Not found";
        return false;
    }
}

void FindUserAndPrint()
{
    vector<Users> vUsers = LoadUsersFromFile();
    string UserName = ReadUserName();

    Users sUser;

    if (FindUserByUserName(sUser, UserName, vUsers))
    {
        printEachUser1(sUser);
    }
    else
    {
        cout << "\n\nUser with User Name" << UserName << " Not found\n\n";
    }
}

void performManageUsersMenuOperation(enManageUsersMenuOptions ManageUsersMenuOption)
{

    switch (ManageUsersMenuOption)
    {
    case enManageUsersMenuOptions::eListUsers:
        system("cls");
        DisplayUsers();
        GoBackToManageUsersMenu();
        break;
    case enManageUsersMenuOptions::eAddnewuser:
        system("cls");
        AddUsers();
        GoBackToManageUsersMenu();
        break;

    case enManageUsersMenuOptions::eDeleteuser:
        system("cls");
        DeleteUserByUserName();
        GoBackToManageUsersMenu();
        break;

    case enManageUsersMenuOptions::eUpdateuser:
        system("cls");
        UpdateUserByUserName();
        GoBackToManageUsersMenu();
        break;
    case enManageUsersMenuOptions::eFinduser:
        system("cls");
        FindUserAndPrint();
        GoBackToManageUsersMenu();
        break;
    case enManageUsersMenuOptions::eManageUsersMainMenu:
        system("cls");
        ShowMainMenu();
        break;
    }
}

void ShowTransactionMenuScreen()
{
    system("cls");

    if (!CheckAccessPermission(enPermissions::eTransactiosPermission))
    {
        showAccessDenaiedMessage();
        return;
    }

    cout << "-------------------------------------------------------\n";
    cout << "\t\t\t Transaction Menu Screen\n";
    cout << "-------------------------------------------------------\n";

    cout << "\t\t [1] Deposite.\n";
    cout << "\t\t [2] Withdraw.\n";
    cout << "\t\t [3] Show balances.\n";
    cout << "\t\t [4] Main Menu.\n";

    cout << "-------------------------------------------------------\n";

    performTransactionMenuOperation((enTransactionMenuOptions)ReadTransactionMenuOptions());
}

void ShowManageUsersMenuScreen()
{
    system("cls");

    if (!CheckAccessPermission(enPermissions::eManageUsersPermission))
    {
        showAccessDenaiedMessage();
        return;
    }

    cout << "-------------------------------------------------------\n";
    cout << "\t\t\t Manage Users Menu Screen\n";
    cout << "-------------------------------------------------------\n";

    cout << "\t\t [1] List Users.\n";
    cout << "\t\t [2] Add new user.\n";
    cout << "\t\t [3] Delete user.\n";
    cout << "\t\t [4] Update user.\n";
    cout << "\t\t [5] Find user.\n";
    cout << "\t\t [6] Main Menu.\n";

    cout << "-------------------------------------------------------\n";

    performManageUsersMenuOperation((enum enManageUsersMenuOptions)ReadManageUsersMenuOptions());
}

void GoBackToMainMenu()
{
    cout << "Press any key to go back to main menu. . .";
    system("pause>0");
    ShowMainMenu();
}

void performMainMenuOperation(enMainMenuOptions MainMenuOption)
{

    switch (MainMenuOption)
    {
    case enMainMenuOptions::eShowClientList:
        system("cls");
        DisplayClients();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eAddClient:
        system("cls");
        AddClients();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eDeleteClient:
        system("cls");
        showClientScreen("Delete  Client Screen");
        DeleteClientByAC();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eUpdateClient:
        system("cls");
        showClientScreen("Update  Client Screen");
        UpdateClientByAC();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eFindClient:
        system("cls");
        showClientScreen("Find  Client Screen");
        FindPrintClient();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eTransactios:
        system("cls");
        ShowTransactionMenuScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eManageUsers:
        system("cls");
        ShowManageUsersMenuScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eLogOut:
        system("cls");
        Login();
        break;
    }
}

void ShowMainMenu()
{
    system("cls");

    cout << "-------------------------------------------------------\n";
    cout << "\t\t\t Main Menu Screen\n";
    cout << "-------------------------------------------------------\n";

    cout << "\t\t [1] Show Client List.\n";
    cout << "\t\t [2] Add new Client.\n";
    cout << "\t\t [3] Delete Client.\n";
    cout << "\t\t [4] Update Client Info.\n";
    cout << "\t\t [5] Find Client.\n";
    cout << "\t\t [6] Transactions.\n";
    cout << "\t\t [7] Manage users.\n";
    cout << "\t\t [8]Log out.\n";

    cout << "-------------------------------------------------------\n";

    performMainMenuOperation((enMainMenuOptions)ReadMainMenuOptions());
}

bool FindUserByUserNameAndPassword(string UserName, string Password)
{
    vector<Users> vUser = LoadUsersFromFile();

    for (Users U : vUser)
    {
        if (UserName == U.userName && Password == U.Password)
        {
            currentUser = U;
            return true;
        }
    }
    return false;
}

bool LaodUserInfo(string UserName, string Password)
{
    if (FindUserByUserNameAndPassword(UserName, Password))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Login()
{
    string UserName, Password;
    bool LoginFailed = false;

    do
    {
        system("cls");

        if (LoginFailed)
        {
            cout << "invalid userName or password, try again\n\n";
        }

        cout << "Enter userName:";
        cin >> UserName;

        cout << "Enter Password:";
        cin >> Password;

        LoginFailed = !LaodUserInfo(UserName, Password);

    } while (LoginFailed);

    ShowMainMenu();
}

int main()
{

    Login();
}