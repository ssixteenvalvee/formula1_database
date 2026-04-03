#pragma once
#include <iostream>
#include <Driver.h>
#include <Team.h>
#define MAXPART 34

class Round {
private:
	int id; // in order
	std::string place; // Russia_Sochi, Belgium_Spa-Francorchamps, etc
	std::string date; // dd-mm-yyyy;
	std::vector places_and_scores(34); // i == place, including 0. vector[i] == score.
};