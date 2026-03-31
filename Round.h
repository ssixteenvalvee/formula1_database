#pragma once
#include <vector>
#include <iostream>

class Round {
private:
	std::string place; // japan_suzuka_circuit
	std::string date; // 28-03-26
	std::vector<int> drivers_points;
	std::vector<int> drivers_status; // F, DNF, DSQ, DNS
};