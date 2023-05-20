	#include "Hitbox.h"
	#include "Level.h"
	#include "Row.h"
	#include "constants.h"

	Level::Level()
	{

	}

	void Level::nextCycle()
	{
		for (int i = 0; i < rows.size(); i++)
		{
			rows[i].nextCycle();
		}
	}
	bool Level::collision(GameObject& gameobject)
	{
		int y = gameobject.getPosition().y;
		
		if (y >= rows.size())
		{
			return false;
		}
		return rows[y].collision(gameobject);
	}
	bool Level::collisionPowerUp(GameObject& gameobject)
	{
		int y = gameobject.getPosition().y;
		
		if (y >= rows.size()) 
		{
			return false;
		}
		return rows[y].collisionPowerUp(gameobject);
	}
	bool Level::collisionObstacle(const Coords& c)
	{
		int y = c.y;
		if (y >= rows.size())
		{
			return false;
		}
		
		return rows[y].collisionObstacle(c);
	}

	void Level::display(std::string& str)
	{
		for (int i = 0; i < rows.size(); i++)
		{
			rows[i].display(i, str);
		}
	}

	void Level::addRow(Row row)
	{
		rows.push_back(row);
	}
