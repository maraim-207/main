#include<iostream>
using namespace std;
int count = 0;
struct moodEntry
{
	int day;
	int month;
	int year;
	int moodLevel;
	string moodtype;
	string note;
};
moodEntry moods[100];
void addMood(moodEntry moods[])
{
	cout << "Enter the day\n";
	cin >> moods->day;
	cout << "Enter the month\n";
	cin >> moods->month;
	cout << "Enter the year\n";
	cin >> moods->year;
	cout << "Enter the mood level\n";
	cin >> moods->moodLevel;
	do
	{
		cout << "wrong input please enter a number between 1 and 5\n";
	} while (moods->moodLevel > 5 || moods->moodLevel < 1) ;
	cout << "Enter the mood type \n";
	cin >> moods->moodtype;
	cout << "Enter the note\n";
	cin >> moods->note;
}
int main()
{

	int moodCount = 0;
	 
	return 0;
}
