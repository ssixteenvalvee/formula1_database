#include "Engine.h"
#include <iostream>

Engine::Engine(std::string m, std::string t, int hp) : manufacturer(m), type(t), horsepower(hp) {}

void Engine::show_engine() const {
	std::cout << manufacturer + " " << type + " " << horsepower << std::endl;
}