#pragma once

int getCurrentMission(int x)
{
	int mission = 0;

	if ((x > 0) && (x < 600))
		mission = 0;
	else if (x > 400)
		mission = 1;
	else if (x > 700)
		mission = 2;
	else if (x > 2200)
		mission = 3;

	return mission;
}

std::string getTextMission(int currentMission)
{
	setlocale(LC_ALL, "ru");

	std::string missionText = "";

	switch (currentMission)
	{
	case 0:
		missionText = "\nНачальный этап и \nинструкция к игре";
		break;
	case 1:
		missionText = "\nMission 1\n\nВот твоя первая\n миссия";
	case 2:
		missionText = "\nMission 1\n\nВот твоя вторая\n миссия";
	case 3:
		missionText = "\nMission 1\n\nВот твоя третья\n миссия";
	default:
		break;
	}

	return missionText;
}