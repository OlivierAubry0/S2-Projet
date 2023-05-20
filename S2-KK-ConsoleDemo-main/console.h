#pragma once
#include <string>
#include <Leaderboard.h>
class Console {
	int width;
	int height;
	void gotoxy(short x, short y);
	void drawHorizontalBar();
	void showCursor(bool show);
public:
	Leaderboard leaderboard;
	Console(int w = 10, int h = 10);
	~Console();
	void display(std::string content);
	int currentLevel = 0;
	int score = 0;
};