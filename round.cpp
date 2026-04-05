#include <iostream>
#include "Round.h"

using std::string, std::vector;

Round::Round(int id, string p, string d, vector<int> pl) : id(id), place(p), date(d), positions(pl) {}
int Round::give_id() {
	return id;
}
std::string Round::give_place(int show) {
	if (show == 1) std::cout << place << std::endl;
	return place;
}
std::string Round::give_date(int show) {
	if (show == 1) std::cout << date << std::endl;
	return date;
}
int Round::give_pos_points(int position) {
	if (position > 0 && position <= MAXPART)
		return points[position - 1];
	else {
		std::cout << "Wrong Format" << std::endl;
		return -1;
	}
}
/*
NamePosStruct Round::give_position(int driver_id, int show = 0) {
	if (driver_id > 34 || driver_id < 0) {
		std::cout << "Wrong Format!" << std::endl;
		std::cout << "There is no, such driver with id: " << driver_id << std::endl;
		NamePosStruct namepos("NONE", -1);
		return namepos;
	}
	for (int i = 0; i < MAXPART; i++) {

	}
}
*/