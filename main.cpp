#include "Driver.h"
#include "Engine.h"
#include "Racecar.h"
#include "Team.h"
#include <iostream>

Driver d1("max_verstappen", 4, 22, 33);
Driver d2("kimi_antonelli", 0, 2, 2);

Team build_team() {
	Engine eng1("Honda", "V6", 1040);
	Racecar car1(eng1, "RB21");
	Team team1("red_bull", car1, d1, d2, 8, 88);
	return team1;
}

int main()
{
	Team red_bull = build_team();
	red_bull.show_team();
	return 0;
}