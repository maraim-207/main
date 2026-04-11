#include<iostream>
using namespace std;
#define maxModdStorage 100
int moodCount = 0;
struct moodEntry
{
	int day;
	int month;
	int year;
	int moodLevel;
	string moodtype;
	string note;
};
moodEntry moods[maxModdStorage];
void addMood(moodEntry moods[] , int& moodCount)
{
	cout << "Enter the day\n";
	cin >> moods[moodCount].day;
	cout << "Enter the month\n";
	cin >> moods[moodCount].month;
	cout << "Enter the year\n";
	cin >> moods[moodCount].year;
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
		cout << "* Notes ^_-: " << moods->note << endl;
	
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

int main()
{
	return 0;
}
