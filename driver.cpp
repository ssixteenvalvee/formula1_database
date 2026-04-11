#include "Driver.h"
#include <iostream>

string format_name(string &name) {
	name[0] = toupper(name[0]);
	for (int i = 0; i < name.size(); i++) {
		char& ch = name[i];
		if (ch == 95) {
			ch = 32; // ASCII "_" = 95, " " = 32;
			name[i + 1] = toupper(name[i + 1]);
			break;
		}
	}
	return name;
}

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
string Driver::give_name() {
	return format_name(name);
}