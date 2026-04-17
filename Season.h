#pragma once
#include <iostream>
#include <vector>
#include "Engine.h"
#include "Racecar.h"
#include "Team.h"
#include "Driver.h"
#include "Round.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#define MAXPART 34

using std::vector, std::string;
namespace fs = std::filesystem;

class Season {
private:
	vector<Engine> engines;
	vector<Driver> drivers;
	vector<Racecar> cars;
	vector<Team> teams;
	vector<Round> rounds;
	vector<int> points = { 25, 18, 15, 12, 10, 8, 6, 4, 2, 1 };
public:
	Season() = default;
	size_t give_rounds_size();
	void ScanData(fs::path Path);
	int CalcPoints(int driver_id, int round_id = -1, bool show = false);
	void PrintDrivers();
	void PrintRounds();
	vector<int> GiveSumPoints(int round_id = -1);
	Driver GiveLeaderDriver();
	void ShowDriverStat(int driver_id, int round_id);
	Engine GiveWinnerEngine();
	vector<Team> GiveTeamsVect();
};