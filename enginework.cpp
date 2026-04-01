#include "Engine.h"
#include <iostream>

Engine::Engine(int engineid, std::string m, std::string t, int hp) : engine_id(engineid), manufacturer(m), type(t), horsepower(hp) {}
Engine::Engine() : engine_id(-1), manufacturer("NONE"), type("NONE"), horsepower(-1) {}

void Engine::show_engine() {
	std::cout << "engine: " << manufacturer << " " << type << " " << horsepower << std::endl;
}
int Engine::give_id() {
	return engine_id;
}