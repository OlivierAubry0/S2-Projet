#pragma once
#include <string>
class Leaderboard 
{
private:
	int highestScore = 0;
	void verifyFile();
	void writeFile(int);
public:
	int getHighestScore();
	Leaderboard();
	void AddScore(int score);
};