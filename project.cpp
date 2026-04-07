#include<iostream>
using namespace std;
float averagepermood(int,float &, float &, float &, float &, float &);
int main() {
	
}
float averagepermood(int entires, float& happyavg, float& sadavg, float& calmavg, float& stressavg, float& angryavg) {
	int happycount, happy_sum = 0,
		sadcount, sad_sum = 0,
		calmcount, calm_sum = 0,
		stresscount, stress_sum=0,
		angrycount, angry_sum = 0;
	for (int i = 0;i < entires;i++) {
		if (mood[i].moodtype == "happy") {
			happy_sum += mood[i].moodlevel;
			happycount++;
		}
		else if (mood[i].moodtype == "sad") {
			sad_sum += mood[i].moodllevel;
			sadcount++;
		}
		else if (mood[i].moodtype == "calm") {
			calm_sum += mood[i].moodlevel;
			calmcount++;
		}
		else if (mood[i].moodtype == "stress") {
			stress_sum += mood[i].moodlevel;
			stresscount++;
		}
		else if (mood[i].moodtype == "angry") {
			angry_sum += mood[i].moodlevel;
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