#include "Row.h"
#include "GameObject.h"
#include <vector>
#include <coords.h>
#include <string>
#ifndef LEVEL_H
#define LEVEL_H
class Level
{
private:
	std::vector<Row> rows;
public:
	Level();
	void nextCycle();
	bool collision(GameObject& gameobject);
	bool collisionPowerUp(GameObject& gameobject);
	bool collisionObstacle(const Coords&);
	void display(std::string& str);
	void addRow(Row r);
};
#endif