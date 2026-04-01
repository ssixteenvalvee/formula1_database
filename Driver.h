#pragma once
#include <iostream>

using std::string;
class Driver {
private:
	int driver_id;
	string name; //max_verstappen, ayrton_senna, niki_lauda
	int titles;
	int wins;
	int pole_pos;
public:
	Driver(int id, string name, int titles, int wins, int pole_pos);
	void show_info();
	int give_id();
	string print_name();
};
/* Fast markup: (chtobi ne zabyt`)
Stats from the .txt files should become a foundation for statistcs in "Round class"
1. We have an initial data from the .txt files.
2. We have an info about statistic from every round. (as well i write the class itself)
3. So we can answer on qeustion like "how many wins pilot/command has got in 6 round of the season"
by just summarizing the initial victories data with sum of wins from 1st to the n-th round of the season*/