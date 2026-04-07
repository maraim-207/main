#include<iostream>
using namespace std;
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
moodEntry moods[100];
void addMood(moodEntry moods[])
{
	cout << "Enter the day\n";
	cin >> moods->day;
	cout << "Enter the month\n";
	cin >> moods->month;
	cout << "Enter the year\n";
	cin >> moods->year;
	cout << "Enter the mood type \n";
	cout << "Happy\tSad\tAngry\tStressed\tcalm\n";
	cin >> moods->moodtype;
	cout << "Enter the mood level\n";
	cin >> moods->moodLevel;
	do
	{
		cout << "wrong input please enter a number between 1 and 5\n";
	} while (moods->moodLevel > 5 || moods->moodLevel < 1) ;
	cout << "Enter the note\n";
	cin >> moods->note;
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


int main()
{
	return 0;
}
