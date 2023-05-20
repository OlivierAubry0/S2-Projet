#include <vector>
#include <string>
#include "constants.h"
#include "Direction.h"
#include "GameObject.h"
#include "Hitbox.h"
#include "coords.h"

#ifndef ROW_H
#define ROW_H
class Row
{
private:
	std::vector<GameObject> objects;
	int speed;
	Direction direction;
	int currentCycle;
	bool blocked;
public:
	Row();
	Row(double s, Direction d);
	void nextCycle();
	bool collision(GameObject&);
	void display(int y, std::string&);
	void add(GameObject object);
	bool collisionObstacle(const Coords&);
	bool collisionPowerUp(GameObject& g);
};
#endif