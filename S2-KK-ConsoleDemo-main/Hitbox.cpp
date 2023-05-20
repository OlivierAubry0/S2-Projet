#include "Hitbox.h"
#include <constants.h>

Hitbox::Hitbox()
{
}

Hitbox::Hitbox(Coords start, std::string content)
{
	this->content = content;
	for (int i = 0; i < content.length(); i++)
	{
		Coords coord;
		coord.x = start.x + i;
		coord.y = start.y;
		coords.push_back(coord);
	}
}

bool Hitbox::move(Coords c)
{
	for (int i = 0; i < coords.size(); i++)
	{
		coords[i].x += c.x;
		coords[i].y += c.y;

		if (coords[i].y >= HEIGHT)
		{
			coords[i].y = HEIGHT - 1;
			return false;
		}
		if (coords[i].y < 0)
		{
			coords[i].y = HEIGHT - 1;
		}
		if (coords[i].x >= WIDTH)
		{
			coords[i].x = 0;
		}
		if (coords[i].x < 0)
		{
			coords[i].x = WIDTH - 1;
		}
	}
	return true;
}

bool Hitbox::touch(const Hitbox& h)
{
	for (int i = 0; i < h.coords.size(); i++)
	{
		for (int j = 0; j < coords.size(); j++)
		{
			if (h.coords[i].x == coords[j].x /* && h.coords[i].y == coords[j].y*/)
			{
				return true;
			}
		}
	}
	return false;
}

bool Hitbox::touch(const Coords& c)
{
	for (int j = 0; j < coords.size(); j++)
	{
		if (c.x == coords[j].x)
		{
			return true;
		}
	}
	return false;
}

void Hitbox::display(char c, int y, std::string& s)
{
	for (int i = 0; i < coords.size(); i++)
	{
		int index = y * WIDTH + coords[i].x;
		s[index] = content[i];
	}
}

Coords Hitbox::getPosition()
{
	if (coords.empty()) return { -1,-1 };
	return coords[0];
}
