#include <string>
#include <coords.h>
#include <controls.h>
#include "constants.h"
#include <GameObject.h>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <vector>
#include <Level.h>
#pragma once
class GameController
{
private:
	std::string content;
	GameObject player;
	Controls oldControlsValue;
	std::vector<Level> levels;
	bool dead;
	bool POWER;
	int powerUPCount = 0;
	int flashCounter = 0;
	bool playerHidden = false;
	
public:
	int nbPowerUp = 0;
	int currentLevel;
	float score;
	GameController(int x = 0, int y = 0);
	void movePlayer(Controls);
	void nextCycle();
	std::string display();
	bool isDead();
	void ActivatePowerup();
	void addLevel(Level& level);
	
	
};

