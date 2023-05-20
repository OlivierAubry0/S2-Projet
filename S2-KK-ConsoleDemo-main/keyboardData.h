#include <mutex>
#include <controls.h>
#pragma once
class KeyboardData : public std::mutex
{
public:
	Controls controls;
	KeyboardData();
};

