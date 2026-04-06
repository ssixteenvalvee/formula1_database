#pragma once
#include <iostream>
#include <vector>
#include "Engine.h"
#include "Racecar.h"
#include "Team.h"
#include "Round.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#define MAXPART 34

using std::vector, std::string;
namespace fs = std::filesystem;

class Season {
private:
	vector<Engine> engines(MAXPART);
	vector<Driver> drivers(MAXPART);
	vector<Racecar> cars(MAXPART;
	vector<Team> teams(MAXPART);
	vector<Round> rounds(MAXPART);
public:
	Season(vector<Engine> engs, vector<Driver> drvrs,vector<Racecar> cars, vector<Team> teams, vector<Round> rnds) : engines(engs), drivers(drvrs), cars(cars), teams(teams), rounds(rnds) {}
	void ScanData(fs::path Path);
};