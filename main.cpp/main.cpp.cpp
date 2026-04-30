#include<iostream>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>
#include<sstream>
#define maxMoodStorage 100
using namespace std;

//Global variables declarations
int userscount = 0;
int logentry;
int moodCount = 0;
int monthindex;

//Structs declarations
const int max_users = 10;
struct UserAccount
{
    int userid;
    string username;
    string password;
};
struct date
{
    int day;
    int month;
    int year;
};
struct moodEntry
{
    date time;
    int moodLevel;
    string moodtype;
    string note;
};
struct MoodStatistics {
    int TotalEntries;
    int HappyCount;
    int SadCount;
    int AngryCount;
    int StressedCount;
    int CalmCount;
};

//Array declarations
UserAccount users[max_users];
UserAccount currentuser;
moodEntry moods[maxMoodStorage];
MoodStatistics statistics[12];
date m[max_users];

//function declarations
void logmenu();
void login();
void signup();
void closing();
void showLogMenu();
int loadingusers();
void saveusers();
int loadingMoods(moodEntry moods[]);
void saveMoods();
void addMood(moodEntry moods[], int& moodCount);
void mood_output(moodEntry moods[], int i);
void display(moodEntry moods[], int);
void SearchMood(moodEntry moods[], int& moodCount);
void SearchByDate(moodEntry moods[], int& moodcount);
void SearchByType(moodEntry moods[], int& moodcount);
void updateFuncion(moodEntry moods[], int& moodCount);
void Delete(moodEntry moods[], int& moodCount);
void DisplayStatistics(int);
void UpdateAllStatistics(moodEntry moods[], int);
void AnalyzeMoodFrequency(moodEntry moods[], int, int);
void AverageMoodlevel(moodEntry moods[], int, int, float&, float&, float&, float&, float&);


//main function
int main()
{
    //لدعم الرموز والإطارات
    system("chcp 65001 > nul");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, false, &fontInfo);
    wcscpy_s(fontInfo.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(hConsole, false, &fontInfo);

    // Load users and assign user IDs
    userscount = loadingusers();
    for (int i = 0; i < userscount; ++i) {
        users[i].userid = i + 1;
    }

    // Initialize statistics
    for (int i = 0; i < 12; i++)
    {
        statistics[i] = { 0,0,0,0,0,0 };
    }

    // Show login menu until a user successfully logs in
    while (currentuser.userid == 0)
    {
        showLogMenu();
    }

    while (currentuser.userid != 0)
    {
        int choice;
        system("cls");
        cout << "╔═══════════════════════════════════════════════════════╗\n";
        cout << "║              🎉 Welcome " << currentuser.username << "! 🎉                 ║\n";
        cout << "╠═══════════════════════════════════════════════════════╣\n";
        cout << "║                                                       ║\n";
        cout << "║              📊 Digital Mood Tracker                  ║\n";
        cout << "║                                                       ║\n";
        cout << "╠═══════════════════════════════════════════════════════╣\n";
        cout << "║  [1] ➕ Add New Mood Entry                             ║\n";
        cout << "║  [2] 📅 Display Mood by Date                          ║\n";
        cout << "║  [3] 🔍 Search Mood                                   ║\n";
        cout << "║  [4] ✏️  Update Mood Entry                            ║\n";
        cout << "║  [5] 🗑️  Delete Mood Entry                            ║\n";
        cout << "║  [6] 📈 View Monthly Statistics                       ║\n";
        cout << "║  [7] 🚪 Logout                                        ║\n";
        cout << "║                                                       ║\n";
        cout << "╚═══════════════════════════════════════════════════════╝\n";
        cout << " Your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            system("timeout /t 1 > nul");
            continue;
        }

        // handle user choices
        switch (choice)
        {
        case 1:
            addMood(moods, moodCount);
            saveMoods();
            UpdateAllStatistics(moods, moodCount);
            cout << "Mood added successfully!\n";
            system("timeout /t 2 > nul");
            break;

        case 2:
            display(moods, moodCount);
            system("pause");
            break;

        case 3:
            SearchMood(moods, moodCount);
            system("pause");
            break;

        case 4:
            updateFuncion(moods, moodCount);
            saveMoods();
            UpdateAllStatistics(moods, moodCount);
            break;

        case 5:
            Delete(moods, moodCount);
            saveMoods();
            UpdateAllStatistics(moods, moodCount);
            break;

        case 6:
        {
            int month;
            cout << "Enter month (1-12): ";
            cin >> month;
            if (month >= 1 && month <= 12)
            {
                UpdateAllStatistics(moods, moodCount);
                DisplayStatistics(month);
            }
            else
            {
                cout << "Invalid month!\n";
                system("pause");
            }
        }
        break;

        case 7:
            cout << "Logging out...\n";
            system("timeout /t 1 > nul");
            currentuser = { 0, "", "" }; // إعادة تعيين المستخدم الحالي
            moodCount = 0; // إعادة تعيين عدد المودات
            // العودة لشاشة تسجيل الدخول
            showLogMenu();
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
            system("timeout /t 1 > nul");
            break;
        }
    }

    return 0;
}
//Ending main function

//Loading data from file functions
int loadingusers()
{
    ifstream infile("users.txt");
    int count = 0;
    if (infile.is_open())
    {
        while (count < max_users)
        {
            if (!(infile >> users[count].username >> users[count].password))
                break;
            users[count].userid = count + 1;
            count++;
        }
        infile.close();
    }
    return count;
}
int loadingMoods(moodEntry moods[])
{
    ifstream infile("inputData.txt");
    int count = 0;

    if (!infile.is_open() || currentuser.userid == 0) {
        moodCount = 0;
        return 0;
    }

    string line;
    while (getline(infile, line) && count < maxMoodStorage) {
        istringstream iss(line);
        int userid, day, month, year, moodLevel;
        string moodtype, note;

        if (iss >> userid >> day >> month >> year >> moodtype >> moodLevel) {
            if (userid == currentuser.userid) {
                moods[count].time.day = day;
                moods[count].time.month = month;
                moods[count].time.year = year;
                moods[count].moodtype = moodtype;
                moods[count].moodLevel = moodLevel;
                getline(iss, note);
                moods[count].note = note;
                count++;
            }
        }
    }
    infile.close();
    moodCount = count;
    return count;
}

//Saving data to file function
void saveusers()
{
    ofstream outfile("users.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < userscount; ++i)
        {
            outfile << users[i].username << " " << users[i].password << endl;
        }
        outfile.close();
    }
}
void saveMoods()
{
    ofstream out("inputData.txt");
    if (out.is_open()) {
        for (int i = 0; i < moodCount; i++) {
            out << currentuser.userid << " "
                << moods[i].time.day << " "
                << moods[i].time.month << " "
                << moods[i].time.year << " "
                << moods[i].moodtype << " "
                << moods[i].moodLevel << " "
                << moods[i].note << endl;
        }
        out.close();
    }
}
void logmenu()
{
    system("cls");
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║        ♥️ Welcome to Digital Mood Tracker ♥️       ║   \n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║                                                    ║\n";
    cout << "║ Are you new user?👋                                ║\n";
    cout << "║ [1] Log in🔑                                       ║\n";
    cout << "║ [2] Sign up📝                                      ║ \n";
    cout << "║ [3] Exit❎                                         ║\n";
    cout << "║                                                    ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║ 📊 Total Registered Users: " << userscount << "/" << max_users << "                    ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
    cout << " Your entry (1-3): ";
}

void login()
{
    system("cls");
    int entry1;
    int entry2;
    string namecheck;
    string passcheck;
    bool loginSuccess = false;

    cout << "╔════════════════════════════════════════╗\n";
    cout << "║                Log in🔑                ║\n";
    cout << "╠════════════════════════════════════════╣\n";
    cout << "║ ┌──────────────────────────────┐       ║\n";
    cout << "║ │👤User name:_                 │       ║\n";
    cout << "║ └──────────────────────────────┘       ║\n";
    cout << "║ ┌──────────────────────────────┐       ║\n";
    cout << "║ │🔒Password:_                  │       ║\n";
    cout << "║ └──────────────────────────────┘       ║\n";
    cout << "╠════════════════════════════════════════╣\n";
    cout << "║                                        ║\n";
    cout << "║ [1] Log in✔️                           ║\n";
    cout << "║ [2] Don't have an account? Sign up📝   ║\n";
    cout << "║ [3] Return to home screen...           ║\n";
    cout << "║                                        ║\n";
    cout << "╚════════════════════════════════════════╝\n";
    cout << " Your entry (1-3): ";
    cin >> entry1;

    if (entry1 == 1)
    {
        cout << "Enter your user name: ";
        cin >> namecheck;
        cout << "Enter your password: ";
        cin >> passcheck;

        for (int i = 0; i < userscount; ++i)
        {
            if (users[i].username == namecheck && users[i].password == passcheck)
            {
                loginSuccess = true;
                break;
            }
        }

        if (loginSuccess)
        {
            for (int i = 0; i < userscount; i++)
            {
                if (users[i].username == namecheck && users[i].password == passcheck)
                {
                    currentuser = users[i];
                    moodCount = loadingMoods(moods);
                    return;
                }
            }
        }
        else
        {
            system("cls");
            cout << "╔══════════════════════════════════╗\n";
            cout << "║             ❌Wrong              ║\n";
            cout << "╠══════════════════════════════════╣\n";
            cout << "║                                  ║\n";
            cout << "║   Invalid username or password!  ║\n";
            cout << "║                                  ║\n";
            cout << "║ [1] 🔁Try again                  ║\n";
            cout << "║ [2] 🔙Return to home screen      ║\n";
            cout << "║                                  ║\n";
            cout << "╚══════════════════════════════════╝\n";
            cout << " Your entry (1-2): ";
            cin >> entry2;
            if (entry2 == 1)
            {
                login(); // Recursive call for try again
            }
            else if (entry2 == 2)
            {
                return; // Return to main menu loop
            }
            else
            {
                system("cls");
                cout << "╔════════════════════════════════════╗\n";
                cout << "║           Invalid Entry!           ║\n";
                cout << "╠════════════════════════════════════╣\n";
                cout << "║                                    ║\n";
                cout << "║      Returning to home screen...   ║\n";
                cout << "║                                    ║\n";
                cout << "╚════════════════════════════════════╝\n";
                cin.clear();
                cin.ignore(10000, '\n');
                system("timeout /t 4 > nul");
                return;
            }
        }
    }
    else if (entry1 == 2)
    {
        signup();
    }
    else if (entry1 == 3)
    {
        return; // Return to main menu loop
    }
    else
    {
        system("cls");
        cout << "╔════════════════════════════════════╗\n";
        cout << "║           Invalid Entry!           ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║                                    ║\n";
        cout << "║      Returning to home screen...   ║\n";
        cout << "║                                    ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cin.clear();
        cin.ignore(10000, '\n');
        system("timeout /t 4 > nul");
        return;
    }

    currentuser = { 0, "", "" };
    return;
}

void signup()
{
    system("cls");
    int entry3;
    string newname;
    string newpass;
    string confpass;

    if (userscount < max_users)
    {
        cout << "╔═════════════════════════════════════════╗\n";
        cout << "║                Sign up📝                ║\n";
        cout << "╠═════════════════════════════════════════╣\n";
        cout << "║ ┌──────────────────────────────┐        ║\n";
        cout << "║ │ 🪪User name:_                │        ║\n";
        cout << "║ └──────────────────────────────┘        ║\n";
        cout << "║ ┌──────────────────────────────┐        ║\n";
        cout << "║ │🔒Password:_                  │        ║\n";
        cout << "║ └──────────────────────────────┘        ║\n";
        cout << "║ ┌──────────────────────────────┐        ║\n";
        cout << "║ │🔒Confirm password:_          │        ║\n";
        cout << "║ └──────────────────────────────┘        ║\n";
        cout << "║                                         ║\n";
        cout << "║ 📝Notes:                                ║\n";
        cout << "║ - User name must be unique.             ║\n";
        cout << "║ - Passwords must match.                 ║\n";
        cout << "╠═════════════════════════════════════════╣\n";
        cout << "║                                         ║\n";
        cout << "║ [1] Create account📝                    ║\n";
        cout << "║ [2] Already have an account? Log in✔️   ║\n";
        cout << "║ [3] Return to home screen...            ║\n";
        cout << "║                                         ║\n";
        cout << "╚═════════════════════════════════════════╝\n";
        cout << " Your entry (1-3): ";
        cin >> entry3;
        if (entry3 == 3)
        {
            return; // Return to main menu loop
        }
        else if (entry3 == 2)
        {
            login();
            return;
        }
        else if (entry3 != 1)
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║      Returning to home screen...   ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("timeout /t 4 > nul");
            return;
        }
        cout << "Enter your user name: ";
        cin >> newname;
        cout << "Enter your password: ";
        cin >> newpass;
        cout << "Confirm your password: ";
        cin >> confpass;

        if (newpass == confpass)
        {
            bool usernameExists = false;
            for (int i = 0; i < userscount; ++i)
            {
                if (users[i].username == newname)
                {
                    usernameExists = true;
                    break;
                }
            }

            if (usernameExists)
            {
                system("cls");
                cout << "╔══════════════════════════════════╗\n";
                cout << "║        ❌Username exists         ║\n";
                cout << "╠══════════════════════════════════╣\n";
                cout << "║ Username already taken!          ║\n";
                cout << "╚══════════════════════════════════╝\n";
                system("timeout /t 4 > nul");
                signup();
                return;
            }

            users[userscount].username = newname;
            users[userscount].password = newpass;
            users[userscount].userid = userscount + 1;
            userscount++;
            saveusers();
            system("cls");
            cout << "╔═════════════════════════════════╗\n";
            cout << "║             Success✅           ║\n";
            cout << "╠═════════════════════════════════╣\n";
            cout << "║                                 ║\n";
            cout << "║   Account created successfully! ║\n";
            cout << "║                                 ║\n";
            cout << "╚═════════════════════════════════╝\n";
            cout << "\nYou are being redirected to the homepage to log in...";
            system("timeout /t 5 > nul");
            return; // Return to main menu loop
        }
        else
        {
            system("cls");
            cout << "╔══════════════════════════════════╗\n";
            cout << "║            ❌Mismatch            ║\n";
            cout << "╠══════════════════════════════════╣\n";
            cout << "║ Passwords do not match!          ║\n";
            cout << "║ Please try again...              ║\n";
            cout << "╚══════════════════════════════════╝\n";
            system("timeout /t 4 > nul");
            signup(); // Recursive call
        }
    }
    else
    {
        system("cls");
        cout << "╔═══════════════════════════════════════════╗\n";
        cout << "║    ❌Sorry! Maximum user limit reached    ║\n";
        cout << "╠═══════════════════════════════════════════╣\n";
        cout << "║                                           ║\n";
        cout << "║ Cannot create more accounts..             ║\n";
        cout << "║                                           ║\n";
        cout << "║ [1] 🗝️Log in                              ║\n";
        cout << "║ [2] ❌Exit                                ║\n";
        cout << "║                                           ║\n";
        cout << "╚═══════════════════════════════════════════╝\n";
        cout << " Your entry (1-2): ";
        cin >> entry3;
        if (entry3 == 1)
        {
            login();
        }
        else if (entry3 == 2)
        {
            closing();
        }
        else
        {
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
    }
}

//Exit function
void closing()
{
    system("cls");
    cout << "Thank you for using Digital Mood Tracker! Goodbye!👋\n";
    system("timeout /t 4 > nul");
    exit(0);
}

// Log menu loop function
void showLogMenu()
{
    userscount = loadingusers();
    for (int i = 0; i < userscount; ++i) 
    {
        users[i].userid = i + 1;
    }

    while (true) {
        logmenu();
        if (!(cin >> logentry))
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║         Please try again...        ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("timeout /t 4 > nul");
            continue;
        }

        switch (logentry)
        {
        case 1:
            login();
            if (currentuser.userid != 0)
                return;
            break;
        case 2:
            signup();
            break;
        case 3:
            closing();
            break;
        default:
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║         Please try again...        ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("timeout /t 4 > nul");
            continue;
        }
    }
}


//Add new mood entry function
void addMood(moodEntry moods[], int& moodCount)
{
    cout << "Enter the day\n";
    cin >> moods[moodCount].time.day;
    cout << "Enter the month\n";
    cin >> moods[moodCount].time.month;
    cout << "Enter the year\n";
    cin >> moods[moodCount].time.year;
    cout << "Enter the mood type \n";
    cout << "Happy\tSad\tAngry\tStressed\tcalm\n";
    cin >> moods[moodCount].moodtype;
    cout << "Enter the mood level from (1 - 5)\n";
    cin >> moods[moodCount].moodLevel;
    if (moods[moodCount].moodLevel > 5 || moods[moodCount].moodLevel < 1)
    {
        do
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║      Enter Digits from 1 to 5      ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("timeout /t 4 > nul");
            cin >> moods[moodCount].moodLevel;
        } while (moods[moodCount].moodLevel > 5 || moods[moodCount].moodLevel < 1);
    }
    cout << "Enter the note\n";
    cin >> moods[moodCount].note;
    moodCount++;
}

//Display mood entry function
void mood_output(moodEntry moods[], int i)
{

    cout << "_________________________________________________________________";
    cout << "Date:" << moods[i].time.day << "/" << moods[i].time.month << "/" << moods[i].time.year << endl << "      ________________"
        << endl
        << "Mood type:" << moods[i].moodtype << endl << "      ________________"
        << endl
        << "Mood level:" << moods[i].moodLevel << endl << "      ________________"
        << endl
        << "Notes:" << moods[i].note << endl;
    cout << "_________________________________________________________________";
}
void display(moodEntry moods[], int moodCount)
{
    int day, month, year;
    bool found = false;

    cout << "Enter date to display (day month year): ";
    cin >> day >> month >> year;

    for (int i = 0; i < moodCount; i++)
    {
        if (moods[i].time.day == day &&
            moods[i].time.month == month &&
            moods[i].time.year == year)
        {
            mood_output(moods, i);

            found = true;
        }
    }

    if (!found)
        cout << "No data found for this date\n";
}

//Search moods function

void SearchByDate(moodEntry moods[], int& moodCount) {
    system("cls");
    int day, month, year;
    bool found = false;
    cout << "_________________________________________________________________";
    cout << "Enter the day:";
    cin >> day;
    cout << endl << "      ________________";
    cout << endl << "Enter the month:";
    cin >> month;
    cout << endl << "      ________________";
    cout << endl << "Enter the year:";
    cin >> year;
    cout << endl << "      ________________";
    for (int i = 0; i < moodCount; i++)
        if (moods[i].time.day == day && moods[i].time.month == month && moods[i].time.year == year) {
            mood_output(moods, i);
            found = true;
        }
    if (!found) {

        cout << "╔════════════════════════════════════╗\n";
        cout << "║                                    ║\n";
        cout << "║    No mood found on this date...   ║\n";
        cout << "║                                    ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }

}

void SearchByType(moodEntry moods[], int& moodCount) {
    system("cls");
    string type;
    bool found = false;
    cout << "_________________________________________________________________";
    cout << "Enter the type of mood:";
    cin >> type;
    cout << endl << "      ________________";
    for (int i = 0; i < moodCount; i++)
        if (moods[i].moodtype == type) {
            mood_output(moods, i);
            found = true;
        }
    if (!found) {
        cout << "╔════════════════════════════════════╗\n";
        cout << "║                                    ║\n";
        cout << "║ No mood found on with this type... ║\n";
        cout << "║                                    ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }

}

void SearchMood(moodEntry moods[], int& moodCount)
{
    system("cls");
    int choise;
    cout << "_________________________________________________________________";
    cout << "ENTER 1 to search by date." << endl << "ENTER 2 to search by mood type";
    cin >> choise;
    if (choise == 1)
        SearchByDate(moods, moodCount);
    else if (choise == 2)
        SearchByType(moods, moodCount);
    else {

        cout << "╔════════════════════════════════════╗\n";
        cout << "║           Invalid choise!          ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }
}

//Update moods function
void updateFuncion(moodEntry moods[], int& moodCount)
{
    int indexDateUserUpdate = -1;
    int searchDay;
    int searchMonth;
    int searchYear;
    string newMoodtype;
    int newMoodLevel;
    string newNote;

    do {
        cout << "Enter day / month / year to update mood entry\n";
        cin >> searchDay >> searchMonth >> searchYear;



        for (int i = 0; i < moodCount; i++)
        {
            if (moods[i].time.day == searchDay
                && moods[i].time.month == searchMonth &&
                moods[i].time.year == searchYear)
            {
                indexDateUserUpdate = i;
                break;
            }
        }



        if (indexDateUserUpdate == -1)
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║           Invalid Entry!           ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║                                    ║\n";
            cout << "║         Please try again...        ║\n";
            cout << "║                                    ║\n";
            cout << "╚════════════════════════════════════╝\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("timeout 4 > nul");
        }


        else
        {
            system("cls");
            cout << "╔════════════════════════════════════╗\n";
            cout << "║         Current Mood Entry         ║\n";
            cout << "╠════════════════════════════════════╣\n";
            cout << "║ Date: " << moods[indexDateUserUpdate].time.day << "/"
                << moods[indexDateUserUpdate].time.month << "/"
                << moods[indexDateUserUpdate].time.year << "\n";
            cout << "║ Mood Type:  " << moods[indexDateUserUpdate].moodtype << "\n";
            cout << "║ Mood Level: " << moods[indexDateUserUpdate].moodLevel << "\n";
            cout << "║ Note:       " << moods[indexDateUserUpdate].note << "\n";
            cout << "╚════════════════════════════════════╝\n";

            cout << "\nEnter the new mood type\n";
            cin >> newMoodtype;
            cout << "Enter the new mood level\n";
            cin >> newMoodLevel;
            cout << "Enter the new note\n";
            cin.ignore();
            getline(cin, newNote);



            moods[indexDateUserUpdate].moodtype = newMoodtype;
            moods[indexDateUserUpdate].moodLevel = newMoodLevel;
            moods[indexDateUserUpdate].note = newNote;
        }
    } while (indexDateUserUpdate == -1);

    system("cls");
    cout << "╔════════════════════════════════════╗\n";
    cout << "║       Updated Successfully!        ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cout << "║ Date: " << moods[indexDateUserUpdate].time.day << "/"
        << moods[indexDateUserUpdate].time.month << "/"
        << moods[indexDateUserUpdate].time.year << "\n";
    cout << "║ Mood Type:  " << moods[indexDateUserUpdate].moodtype << "\n";
    cout << "║ Mood Level: " << moods[indexDateUserUpdate].moodLevel << "\n";
    cout << "║ Note:       " << moods[indexDateUserUpdate].note << "\n";
    cout << "╚════════════════════════════════════╝\n";
    system("timeout 4 > nul");
}

//Delete moods function
void Delete(moodEntry moods[], int& moodCount)
{
    system("cls");
    cout << "╔════════════════════════════════════╗\n";
    cout << "║         🗑️ Delete Mood Entry       ║\n";
    cout << "╠════════════════════════════════════╣\n";
    cout << "║  Enter date to delete (DD MM YYYY):║\n";
    cout << "╚════════════════════════════════════╝\n\n";

    int day, month, year;
    cout << "📅 Date: ";
    cin >> day >> month >> year;

    bool found = false;
    int deleteIndex = -1;

    // البحث عن المدخل في المصفوفة
    for (int i = 0; i < moodCount; i++)
    {
        if (moods[i].time.day == day &&
            moods[i].time.month == month &&
            moods[i].time.year == year)
        {
            deleteIndex = i;
            found = true;
            break;
        }
    }

    if (found)
    {
        // عرض المدخل قبل الحذف للتأكيد
        cout << "\n╔════════════════════════════════════╗\n";
        cout << "║     Entry to be deleted:           ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║ Date: " << moods[deleteIndex].time.day << "/"
            << moods[deleteIndex].time.month << "/"
            << moods[deleteIndex].time.year << "\n";
        cout << "║ Mood Type:  " << moods[deleteIndex].moodtype << "\n";
        cout << "║ Mood Level: " << moods[deleteIndex].moodLevel << "\n";
        cout << "║ Note:       " << moods[deleteIndex].note << "\n";
        cout << "╚════════════════════════════════════╝\n";

        cout << "\nAre you sure you want to delete this entry? (1 for Yes / 2 for No): ";
        int confirm;
        cin >> confirm;

        if (confirm == 1)
        {
            // حذف من المصفوفة عن طريق إزاحة العناصر
            for (int i = deleteIndex; i < moodCount - 1; i++)
            {
                moods[i] = moods[i + 1];
            }
            moodCount--;  // تقليل العدد الكلي

            cout << "\n╔════════════════════════════════════╗\n";
            cout << "║      ✅ Deleted successfully!       ║\n";
            cout << "╚════════════════════════════════════╝\n";
        }
        else
        {
            cout << "\n╔════════════════════════════════════╗\n";
            cout << "║      ❌ Deletion cancelled.         ║\n";
            cout << "╚════════════════════════════════════╝\n";
        }
    }
    else
    {
        cout << "\n╔════════════════════════════════════╗\n";
        cout << "║           ❌ Not Found!             ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║      No mood entry found on        ║\n";
        cout << "║      this date...                  ║\n";
        cout << "╚════════════════════════════════════╝\n";
    }

    system("pause");
}

//Statistics functions
void DisplayStatistics(int month) {
    float happyavg = 0, sadavg = 0, calmavg = 0, stressavg = 0, angryavg = 0;
    monthindex = month - 1;
    if (statistics[monthindex].TotalEntries == 0) {
        cout << "\nNo data for month " << month << endl;
        system("pause");
        return;
    }
    cout << "\n--- Statistics Report for Month " << month << " ---" << endl;
    cout << "Total Records: " << statistics[monthindex].TotalEntries << endl;
    cout << "Average Mood Level: ";
    AverageMoodlevel(moods, moodCount, month, happyavg, sadavg, calmavg, stressavg, angryavg);
    if (statistics[monthindex].HappyCount > 0) {
        cout << "happy avarege= " << happyavg << endl;
    }
    else {
        cout << " No Happy Avgarage For This Month\n";
    }
    if (statistics[monthindex].SadCount > 0) {
        cout << "sad avarege= " << sadavg << endl;
    }
    else {
        cout << " No Sad Avgarage For This Month\n";
    }
    if (statistics[monthindex].CalmCount > 0) {
        cout << "calm avarege= " << calmavg << endl;
    }
    else {
        cout << " No Calm Avgarage For This Month\n";
    }
    if (statistics[monthindex].StressedCount > 0) {
        cout << "stress avarege= " << stressavg << endl;
    }
    else {
        cout << " No Stress Avgarage For This Month\n";
    }
    if (statistics[monthindex].AngryCount > 0) {
        cout << "angry avarege= " << angryavg << endl;
    }
    else {
        cout << " No Angry Avgarage For This Month\n";
    }
    cout << " / 5" << endl;
    system("pause");
}
void UpdateAllStatistics(moodEntry moods[], int size)
{
    for (int m = 1; m <= 12; m++) {
        AnalyzeMoodFrequency(moods, size, m);
    }
}

void AnalyzeMoodFrequency(moodEntry moods[], int size, int month) {
    monthindex = month - 1;
    statistics[monthindex] = { 0,0,0,0,0,0 }; // reset all

    for (int i = 0; i < size; i++) {
        if (moods[i].time.month == month) {
            statistics[monthindex].TotalEntries++;

            string type = moods[i].moodtype;
            if (type == "happy") statistics[monthindex].HappyCount++;
            else if (type == "sad") statistics[monthindex].SadCount++;
            else if (type == "angry") statistics[monthindex].AngryCount++;
            else if (type == "stressed") statistics[monthindex].StressedCount++;
            else if (type == "calm") statistics[monthindex].CalmCount++;
        }
    }
}

//Calculate average mood level for a given month
void AverageMoodlevel(moodEntry moods[], int moodCount, int month, float& happyavg, float
    & sadavg, float& calmavg, float& stressavg, float& angryavg)
{
    int happy_sum = 0, sad_sum = 0,
        calm_sum = 0, stress_sum = 0,
        angry_sum = 0;
    for (int i = 0; i < moodCount; i++) {
        if (moods[i].time.month != month) {
            continue;//neglect other mounthes
        }
        if (moods[i].moodtype == "happy") {
            happy_sum += moods[i].moodLevel;
            statistics[monthindex].HappyCount++;
        }
        else if (moods[i].moodtype == "sad") {
            sad_sum += moods[i].moodLevel;
            statistics[monthindex].SadCount++;
        }
        else if (moods[i].moodtype == "calm") {
            calm_sum += moods[i].moodLevel;
            statistics[monthindex].CalmCount++;
        }
        else if (moods[i].moodtype == "stress") {
            stress_sum += moods[i].moodLevel;
            statistics[monthindex].StressedCount++;
        }
        else if (moods[i].moodtype == "angry") {
            angry_sum += moods[i].moodLevel;
            statistics[monthindex].AngryCount++;
        }
    }
    if (statistics[monthindex].HappyCount > 0) {
        happyavg = (float)happy_sum / statistics[monthindex].HappyCount;
    }
    if (statistics[monthindex].SadCount > 0) {
        sadavg = (float)sad_sum / statistics[monthindex].SadCount;
    }
    if (statistics[monthindex].CalmCount > 0) {
        calmavg = (float)calm_sum / statistics[monthindex].CalmCount;
    }
    if (statistics[monthindex].StressedCount > 0) {
        stressavg = (float)stress_sum / statistics[monthindex].StressedCount;
    }
    if (statistics[monthindex].AngryCount > 0) {
        angryavg = (float)angry_sum / statistics[monthindex].AngryCount;
    }
}
