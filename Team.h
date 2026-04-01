#pragma once
#include "Racecar.h"
#include "Engine.h"
#include "Driver.h"

class Team {
private:
	int team_id;
	string name;
	Racecar car;
	Driver pilot_1;
	Driver pilot_2;
	int titles;
	int gp_wins;
public:
	Team(int team_id, string name, Racecar car, Driver pilot_1, Driver pilot_2, int titles, int gp_wins);
	void show_team();
};