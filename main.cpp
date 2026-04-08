#include "Driver.h"
#include "Engine.h"
#include "Racecar.h"
#include "Team.h"
#include "Round.h"
#include "Season.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#define MAXPART 34 // In the whole history of Formula 1 no more than 34 cars participated in the race. (1953, Germany).

using std::cin, std::cout, std::endl, std::vector, std::string, std::getline;
namespace fs = std::filesystem;

int main()
{
	fs::path basePath = "alldata";
	if (!fs::exists(basePath) || !fs::is_directory(basePath)) {
		cout << "Directory is not found. Do something.\n";
		return 0;
	}
	vector<string> seasons_str;
	for (const auto& dir : fs::directory_iterator(basePath)) {
		if (dir.is_directory()) {
			seasons_str.push_back(dir.path().filename().string());
		}
	}
	if (seasons_str.empty()) {
		cout << "There is no data" << endl;
		return 0;
	}
	cout << "Please, choose the number of the season:" << endl;
	int cnt = 1;
	for (auto& option : seasons_str) {
		cout << cnt << ". " << option << endl;
		cnt++;
	}
	int choice;
	cin >> choice;
	while (choice > seasons_str.size() || choice < 0) {
		cout << "Wrong Format" << endl;
		cin >> choice;
	}
	fs::path Path = basePath/seasons_str[choice - 1];
	vector<Engine> engines;
	vector<Racecar> cars;
	vector<Driver> drivers;
	vector<Team> teams; // engine -> car -> team (+ driver) -> round info.
	vector<Round> rounds;
	engines.reserve(MAXPART);
	cars.reserve(MAXPART);
	drivers.reserve(MAXPART);
	teams.reserve(MAXPART);
	rounds.reserve(MAXPART);
	Season season(engines, drivers, cars, teams, rounds);
	season.ScanData(Path);
	return 0;
}