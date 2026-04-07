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
