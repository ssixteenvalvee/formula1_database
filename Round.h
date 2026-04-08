#pragma once
#include <iostream>
#include <vector>
#include <string>
#define MAXPART 34

struct NamePosStruct {
	std::string name;
	int pos;
};

class Round {
private:
	int id; // in order
	std::string place; // Russia_Sochi, Belgium_Spa-Francorchamps, etc
	std::string date; // dd-mm-yyyy;
	std::vector<int> positions;
	std::vector<int> points = { 25, 18, 15, 12, 10, 8, 6, 4, 2, 1 };
public:
	Round(int id, std::string place, std::string date, std::vector<int> places);
	int give_id();
	std::string give_place(int show = 0);
	std::string give_date(int show = 0);
	int give_pos_points(int position);
	int give_driver_place(int driver_id);
};