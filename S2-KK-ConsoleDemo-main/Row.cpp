#include "Row.h"
#include "constants.h"
#include "Direction.h"

Row::Row()
{
	speed = 100;
	direction = Direction::RIGHT;
	currentCycle = 0;
	blocked = false;
}

Row::Row(double s, Direction d)
{
	speed = s;
	direction = d; 
	currentCycle = 0;
	blocked = false;
}

void Row::nextCycle()
{
	currentCycle++;
	if (currentCycle < speed || speed == 0) {
		return;
	}
	else {
		currentCycle = 0;
	}
	Coords delta;
	delta.y = 0;
	if (direction == Direction::LEFT) 
	{
		delta.x = -1;
	}
	else {
		delta.x = 1;
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].move(delta);
	}
}

void Row::display(int y, std::string& str)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].display(y, str);
	}
}

void Row::add(GameObject object)
{
	objects.push_back(object);
}

bool Row::collision(GameObject& g)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].touch(g)) 
		{
			if (!objects[i].obstacle() && !objects[i].PowerUp())
				return true;
		}
	}
	return false;
}
bool Row::collisionPowerUp(GameObject& g)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].touch(g) && !objects[i].hidden)
		{
			if (objects[i].PowerUp()) {
				objects[i].hidden = true;
				return true;
			}
				
		}
	}
	return false;
}
bool Row::collisionObstacle(const Coords& c) {

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].touch(c))
		{
			if (objects[i].obstacle())
				return true;
		}
	}
	return false;
}





