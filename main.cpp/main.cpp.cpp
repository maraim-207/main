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
UserAccount users[max_users];
moodEntry moods[maxModdStorage];
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

void addMood(moodEntry moods[] , int& moodCount)
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
void display(int& moodCount,moodEntry moods[])
{
		cout << "* Date:" << moods[moodCount].time.day << "/" << moods[moodCount].time.month << "/" << moods[moodCount].time.year << endl;
		cout << "* Mood type :) " << moods[moodCount].moodtype << endl;
		cout << "* Mood Level *_* :" << moods[moodCount].moodLevel << endl;
		cout << "* Notes ^_-: " << moods[moodCount].note << endl;
	
}
void dlete(int& moodCount, moodEntry moods[])
{

		cout << "Enter the date you want to delete";
		cin >> moods[moodCount].time.day; cout << "/";cin >> moods->time.month;cout << "/";cin >> moods->time.year;
		moods[moodCount].moodLevel = 0;
		moods[moodCount].moodtype = {};
		moods[moodCount].note = {};

	
}
float averagepermood(int entires, float& happyavg, float& sadavg, float& calmavg, float& stressavg, float& angryavg) {
	int happycount, happy_sum = 0,
		sadcount, sad_sum = 0,
		calmcount, calm_sum = 0,
		stresscount, stress_sum=0,
		angrycount, angry_sum = 0;
	for (int i = 0;i < entires;i++) {
		if (moods[i].moodtype == "happy") {
			happy_sum += moods[i].moodlevel;
			happycount++;
		}
		else if (moods[i].moodtype == "sad") {
			sad_sum += moods[i].moodllevel;
			sadcount++;
		}
		else if (moods[i].moodtype == "calm") {
			calm_sum += moods[i].moodlevel;
			calmcount++;
		}
		else if (moods[i].moodtype == "stress") {
			stress_sum += moods[i].moodlevel;
			stresscount++;
		}
		else if (moods[i].moodtype == "angry") {
			angry_sum += moods[i].moodlevel;
			angrycount++;
		}
	}
	if (happycount > 0)
		happyavg = (float)happy_sum / happycount;
	if (sadcount > 0)
		sadavg = (float)sad_sum / sadcount;
	if (calmcount > 0)
		calmavg = (float)calm_sum / calmcount;
	if (stresscount > 0)
		stressavg = (float)stress_sum / stresscount;
	if (angrycount > 0)
		angryavg = angry_sum / angrycount;
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
