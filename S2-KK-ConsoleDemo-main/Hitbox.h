#include <vector>
#include <coords.h>
#include <string>
#pragma once
class Hitbox 
{
	std::vector<Coords> coords;
	std::string content;
public:
	Hitbox();
	Hitbox(Coords start, std::string content);
	bool move(Coords c);
	bool touch(const Hitbox&);
	bool touch(const Coords&);
	void display(char c, int y, std::string&);
	Coords getPosition();
};