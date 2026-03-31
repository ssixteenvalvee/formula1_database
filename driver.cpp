#include "Driver.h"
#include <iostream>

Driver::Driver(string n, int id, int t, int w, int pp) : name(n), driver_id(id), titles(t), wins(w), pole_pos(pp) {}
void Driver::show_info() {
	std::cout << name + " has such achievements:" << std::endl;
	std::cout << "titles: " << titles << std::endl;
	std::cout << "wins: " << wins << std::endl;
	std::cout << "pole positions: " << pole_pos << std::endl;
}
string Driver::print_name() {
	return name;
}