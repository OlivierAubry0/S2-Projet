#pragma once
#include <mutex>

class GameBoard : public std::mutex
{
public:
	std::string content;
	int nbPowerUp;
	GameBoard();
};