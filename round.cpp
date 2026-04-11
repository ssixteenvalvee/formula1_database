#include <iostream>
#include "Round.h"
#include "Driver.h"

using std::string, std::vector;

Round::Round(int id, string p, string d, vector<int> pl) : id(id), place(p), date(d), positions(pl) {}
int Round::give_id() {
	return id;
}
std::vector<int> Round::give_pos_vector() {
	return positions;
}
std::string Round::give_place(int show) {
	if (show == 1) std::cout << place << std::endl;
	return format_name(place);
}
std::string Round::give_date(int show) {
	if (show == 1) std::cout << date << std::endl;
	return date;
}
int Round::give_pos_points(int position) {
	if (position > 10) return 0;
	if (position > 0 && position <= positions.size())
		return points[position - 1];
	else {
		std::cout << "Wrong Format" << std::endl;
		return -1;
	}
}
int Round::give_driver_place(int driver_id) {
	if (driver_id >= 0 && driver_id < positions.size()) {
		for (int id = 0; id < positions.size(); id++) {
			if (positions[id] == driver_id) return id + 1;
		}
		std::cout << "Driver Unfound" << std::endl;
		return -1;
	}
	else {
		std::cout << "Wrong Format" << std::endl;
		return -1;
	}
}