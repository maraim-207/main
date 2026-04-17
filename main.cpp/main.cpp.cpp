#include<iostream>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
int userscount = 0;
int logentry;
#define maxModdStorage 100
int moodCount = 0;
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

UserAccount users[max_users];
moodEntry moods[maxModdStorage];
MoodStatistics statistics[12];
moddstatistics avarage;
//function declarations
void logmenu();
void login();
void signup();
void mainmenu();
void closing();

//Loading data from file function
int loadfromfile()
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

//Saving data to file function
void savetofile()
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
void AnalyzeMoodFrequency(moodEntry moods[], int size, int month) {
    int mIdx = month - 1;
    statistics[mIdx].TotalEntries = 0;
    statistics[mIdx].HappyCount = 0;
    statistics[mIdx].SadCount = 0;
    statistics[mIdx].AngryCount = 0;
    statistics[mIdx].StressedCount = 0;
    statistics[mIdx].CalmCount = 0;

    for (int i = 0; i < size; i++) {
        if (moods[i].time.month == month) {
            statistics[mIdx].TotalEntries++;
            string type = moods[i].moodtype;
            if (type == "Happy" || type == "happy") statistics[mIdx].HappyCount++;
            else if (type == "Sad" || type == "sad") statistics[mIdx].SadCount++;
            else if (type == "Angry" || type == "angry") statistics[mIdx].AngryCount++;
            else if (type == "Stressed" || type == "stressed") statistics[mIdx].StressedCount++;
            else if (type == "Calm" || type == "calm") statistics[mIdx].CalmCount++;
        }
    }
}

void DisplayStatistics(int month) {
    int mIdx = month - 1;
    if (statistics[mIdx].TotalEntries == 0) {
        cout << "\nNo data for month " << month << endl;
        system("pause");
        return;
    }
    cout << "\n--- Statistics Report for Month " << month << " ---" << endl;
    cout << "Total Records: " << statistics[mIdx].TotalEntries << endl;
    cout << "Happy: " << statistics[mIdx].HappyCount << " | Sad: " << statistics[mIdx].SadCount << endl;
    cout << "Angry: " << statistics[mIdx].AngryCount << " | Stressed: " << statistics[mIdx].StressedCount << endl;
    cout << "Calm: " << statistics[mIdx].CalmCount << endl;
    cout << "Average Mood Level: " << AverageMoodlevel() << " / 5" << endl;
    system("pause");
}

void UpdateAllStatistics(moodEntry moods[], int size) {
    for (int m = 1; m <= 12; m++) {
        AnalyzeMoodFrequency(moods, size, m);
    }
}
void averageMoodlevel(int moodcount,int month) {
    int currentid=users[currentuser].id;
    int happy_sum = 0, sad_sum = 0,
      calm_sum = 0, stress_sum = 0,
       angry_sum = 0;
    float happyave,sadavg,calmave,sressavg,angryave;
    for (int i = 0; i < moodcount; i++) {
        if(moods[i].userid!=currentid){
            countinue;//neglect other users
        }
        if(moods[i].mounth!=mounth){
            countinue;//neglect other mounthes
        }
        if (moods[i].moodtype == "happy") {
            happy_sum += moods[i].moodlevel;
           statistcs[mIdx].happycount++;
        }
        else if (moods[i].moodtype == "sad") {
            sad_sum += moods[i].moodllevel;
             statistcs[mIdx].sadcount++;
        }
        else if (moods[i].moodtype == "calm") {
            calm_sum += moods[i].moodlevel;
              statistcs[mIdx].calmcount++;
        }
        else if (moods[i].moodtype == "stress") {
            stress_sum += moods[i].moodlevel;
             statistcs[mIdx]. stresscount++;
        }
        else if (moods[i].moodtype == "angry") {
            angry_sum += moods[i].moodlevel;
              statistcs[mIdx].angrycount++;
        }
    }
    if ( statistcs[mIdx].happycount > 0){
        happyavg = (float)happy_sum / statistcs[mIdx].happycount;
    cout<<"happy avarege= "<<happyave<<endl;
    }
    else {
        cout<<" No Happy Avgarage For This Month\n";
    }
    if ( statistcs[mIdx].sadcount > 0){
        sadavg = (float)sad_sum / statistcs[mIdx].sadcount;
       cout<<"sad avarege= "<<sadave<<endl;
    }
    else{
         cout<<" No Sad Avgarage For This Month\n";
    }
    if ( statistcs[mIdx].calmcount > 0){
        calmavg = (float)calm_sum / statistcs[mIdx].calmcount;
       cout<<"calm avarege= "<<calmave<<endl;
    }
    else{
         cout<<" No Calm Avgarage For This Month\n";
    }
    if (statistcs[mIdx].stresscount > 0){
        stressavg = (float)stress_sum / statistcs[mIdx].stresscount;
       cout<<"stress avarege= "<<stressave<<endl;
    }
    else{
         cout<<" No Stress Avgarage For This Month\n";
    }
    if (statistcs[mIdx].angrycount > 0){
        angryavg = angry_sum /  statistcs[mIdx]. angrycount;
       cout<<"angry avarege= "<<angryave<<endl;
    }
    else{
         cout<<" No Angry Avgarage For This Month\n";
    }
}

// Log menu loop function
void showLogMenu()
{
    userscount = loadfromfile(); // Reload users each time
    for (int i = 0; i < userscount; ++i)
        users[i].userid = i + 1;

    while (true) {
        logmenu();
        cin >> logentry;

        switch (logentry)
        {
        case 1:
            login();
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

void addMood(moodEntry moods[], int& moodCount)
{
    moods[moodcount].userid=users[currentuser].id;
    cout << "Enter the day\n";
    cin >> moods[moodCount].time.day;
    cout << "Enter the month\n";
    cin >> moods[moodCount].time.month;
    cout << "Enter the year\n";
    cin >> moods[moodCount].time.year;
    cout << "Enter the mood type \n";
    cout << "Happy\tSad\tAngry\tStressed\tcalm\n";
    cin >> moods[moodCount].moodtype;
    cout << "Enter the mood level\n";
    cin >> moods[moodCount].moodLevel;
    if (moods[moodCount].moodLevel > 5 || moods[moodCount].moodLevel < 1)
    {
        do
        {
            cout << "wrong input please enter a number between 1 and 5\n";
            cin >> moods[moodCount].moodLevel;
        } while (moods[moodCount].moodLevel > 5 || moods[moodCount].moodLevel < 1);
    }
    cout << "Enter the note\n";
    cin >> moods[moodCount].note;
    moodCount++;
}
void preStoredMoods()
{
    moods[0] = { 1, 4, 2026, 5, "Happy", "Finished my project" };
    moods[1] = { 2, 4, 2026, 3, "Calm", "Normal day" };
    moods[2] = { 3, 4, 2026, 2, "Stressed", "Exam coming up" };
    moods[3] = { 4, 4, 2026, 5, "sad", "did not pass the exam" };
    moods[4] = { 5, 4, 2026, 3, "Calm", "Normal day" };
    moods[5] = { 6, 4, 2026, 2, "Stressed", "Exam coming up" };
    moods[6] = { 7, 4, 2026, 5, "Happy", "passed the exam" };
    moods[7] = { 8, 4, 2026, 5, "Calm", "Normal day" };
    moods[8] = { 9, 4, 2026, 2, "happy", "a new semister comming up" };
}
void display(moodEntry moods[], int& moodCount)
{
    cout << "enter the date you want to delete :" << endl;
    if (moods[moodCount].time.day == moods[moodCount].time.day && moods[moodCount].time.month == moods[moodCount].time.month && moods[moodCount].time.year == moods[moodCount].time.year)
    {

        cout << "* Date: " << moods[moodCount].time.day << "/" << moods[moodCount].time.month << "/" << moods[moodCount].time.year << endl;
        cout << "* Mood type :) " << moods[moodCount].moodtype << endl;
        cout << "* Mood Level *_* : " << moods[moodCount].moodLevel << endl;
        cout << "* Notes ^_-: " << moods[moodCount].note << endl;
    }
    else
        cout << "invalid date!";

}
void updateFuncion(moodEntry moods[], int moodCount)
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
            if (moods[i].time.day == searchDay && moods[i].time.month == searchMonth && moods[i].time.year == searchYear)
            {
                indexDateUserUpdate = i;
                break;
            }

        }



        if (indexDateUserUpdate == -1)
            cout << "No entry found for the given date\n";
        else
        {
            display(moods , indexDateUserUpdate);
            cout << "Enter the new mood type \n";
            cin >> newMoodtype;
            cout << "Enter the new mood level\n";
            cin >> newMoodLevel;
            cout << "Enter the new note\n";
            cin >> newNote;
            moods[indexDateUserUpdate].moodtype = newMoodtype;
            moods[indexDateUserUpdate].moodLevel = newMoodLevel;
            moods[indexDateUserUpdate].note = newNote;
        }
    } while (indexDateUserUpdate == -1);

    display(moods, indexDateUserUpdate);

}

void delete(moodEntry moods[], int& moodCount)
{
    cout << "Enter the date you want to delete";
    cout << endl;
    cin >> moods[moodCount].time.day; cout << "/"; cin >> moods[moodCount].time.month; cout << "/"; cin >> moods[moodCount].time.year;


    if (moods[moodCount].time.day == moods[moodCount].time.day && moods[moodCount].time.month == moods[moodCount].time.month && moods[moodCount].time.year == moods[moodCount].time.year)
    {
        moods[moodCount].moodLevel = 0;
        moods[moodCount].moodtype = {};
        moods[moodCount].note = {};
    }
    else
        cout << "invalid date!";

}
//function declarations
void logmenu();
void login();
void signup();
void mainmenu();
void closing();

//Loading data from file function
int loadfromfile()
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

//Saving data to file function
void savetofile()
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

// Log menu loop function
void showLogMenu()
{
    userscount = loadfromfile(); // Reload users each time
    for (int i = 0; i < userscount; ++i)
        users[i].userid = i + 1;

    while (true) {
        logmenu();
        cin >> logentry;

        switch (logentry)
        {
        case 1:
            login();
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

    showLogMenu();
    return 0;
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
    cout << " Your entry: ";
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
    cout << " Your entry: ";
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
            mainmenu();
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
            cout << " Your entry: ";
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
        int entry3;
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
        cout << " Your entry: ";
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
            savetofile();
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
        cout << " Your entry: ";
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

void closing()
{
    system("cls");
    cout << "Thank you for using Digital Mood Tracker! Goodbye!👋\n";
    system("timeout /t 4 > nul");
    exit(0);
}

void mainmenu()
{
    int choice;
    system("cls");
    cout << "╔═════════════════════════════════════╗\n";
    cout << "║           Welcome to Main Menu!     ║\n";
    cout << "╠═════════════════════════════════════╣\n";
    cout << "║                                     ║\n";
    cout << "║         Main menu functionality     ║\n";
    cout << "║         goes here...                ║\n";
    cout << "║ [1] Some feature                    ║\n";
    cout << "║ [2] Another feature                 ║\n";
    cout << "║ [3] Logout                          ║\n";
    cout << "║                                     ║\n";
    cout << "╚═════════════════════════════════════╝\n";
    cout << " Your choice: ";
    cin >> choice;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input.\n";
        system("timeout /t 1 > nul");
        return;
    }
}
