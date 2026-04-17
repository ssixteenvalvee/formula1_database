#pragma once
#include "Engine.h"

using std::string, std::cout, std::endl;
class Racecar {
private:
	int car_id;
	Engine engine;
	std::string chasis;
public:
	Racecar(int car_id ,Engine engine, string chasis);
	Racecar();
	// Racecar(string manufacturer, string type, int hp, string chasis);
	void show_car();
	int give_id();
	string print_chasis();
	Engine GiveCarEngine();
};