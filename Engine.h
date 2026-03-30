#pragma once
#include <iostream>

class Engine {
private:
	std::string manufacturer; // Ford, Honda, MB, Ferrari
	std::string type; // V10, V6 etc.
	int horsepower;
public:
	Engine(std::string manufacturer, std::string type, int horsepower);
	void show_engine() const;
};