#include "Driver.h"
#include <iostream>

Driver::Driver(int id ,string n, int t, int w, int pp) : driver_id(id), name(n), titles(t), wins(w), pole_pos(pp) {}
void Driver::show_info() {
	std::cout << name + " has such achievements:" << std::endl;
	std::cout << "\ttitles: " << titles << std::endl;
	std::cout << "\twins: " << wins << std::endl;
	std::cout << "\tpole positions: " << pole_pos << std::endl;
}
int Driver::give_id() {
	return driver_id;
}
string Driver::print_name() {
	return name;
}