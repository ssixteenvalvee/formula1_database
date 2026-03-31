#pragma once
#include <iostream>

using std::string;
class Driver {
private:
	string name; //max_verstappen, ayrton_senna, niki_lauda
	int driver_id; // 0, 1, 2 ...
	int titles;
	int wins;
	int pole_pos;
public:
	Driver(string name,int driver_id,int titles, int wins, int pole_pos);
	void show_info();
	string print_name();
};