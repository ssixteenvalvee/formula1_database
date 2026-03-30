#include "Engine.h"
#include "Racecar.h"
#include <iostream>

int main()
{
	Engine engine1("RBPTH003: Honda", "V6", 1040);
	engine1.show_engine();
	Racecar car1(engine1, "RB21");
	car1.show_car();
	return 0;
}