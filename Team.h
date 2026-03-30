#pragma once
#include "Racecar.h"
#include "Engine.h"
#include "Driver.h"

class Team {
private:
	string name;
	Racecar car;
	Driver pilot_1;
	Driver pilot_2;
	int titles;
	int gp_wins;
public:
	Team(string name, Racecar car, Driver pilot_1, Driver pilot_2, int titles, int gp_wins);
	void show_team();
};