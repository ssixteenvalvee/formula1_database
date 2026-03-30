#pragma once
#include "Engine.h"

using std::string, std::cout, std::endl;
class Racecar {
private:
	Engine engine;
	std::string chasis;
public:
	Racecar(Engine engine, string chasis);
	// Racecar(string manufacturer, string type, int hp, string chasis);
	void show_car();
	string print_chasis();
};