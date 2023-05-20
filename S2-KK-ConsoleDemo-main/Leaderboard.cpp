#include "Leaderboard.h"
#include <Windows.h>
#include <fstream>

std::string file = "C:\\ProgramData\\KrustyKrabCossyRoad\\highscore";
void Leaderboard::verifyFile()
{
	std::string folder = "C:\\ProgramData\\KrustyKrabCossyRoad";
	std::wstring stemp = std::wstring(folder.begin(), folder.end());
	LPCWSTR folderPath = stemp.c_str();
	CreateDirectory(folderPath,NULL);
	
	stemp = std::wstring(file.begin(), file.end());
	LPCWSTR sw = stemp.c_str();
	if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(sw) && GetLastError() == ERROR_FILE_NOT_FOUND)
	{
		std::ofstream stream(file);
		stream << "0";
		stream.close();
	}
	std::ifstream stream(file);

	if (stream.is_open()) {
		stream >> highestScore;
	}
}

void Leaderboard::writeFile(int newScore)
{
	std::ofstream stream(file);
	stream << newScore;
	stream.close();
}

int Leaderboard::getHighestScore()
{
	return highestScore;
}

Leaderboard::Leaderboard()
{
	verifyFile();
}

void Leaderboard::AddScore(int score)
{
	if (highestScore > score)
	{
		return;
	}
	highestScore = score;
	writeFile(score);
}
