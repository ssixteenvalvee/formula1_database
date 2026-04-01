#pragma once
#include <iostream>

class Engine {
private:
	int engine_id;
	std::string manufacturer; // Ford, Honda, MB, Ferrari
	std::string type; // V10, V6 etc.
	int horsepower;
public:
	Engine(int engine_id, std::string manufacturer, std::string type, int horsepower);
	Engine();
	void show_engine();
	int give_id();
};