#include "Driver.h"
#include "Engine.h"
#include "Racecar.h"
#include "Team.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using std::cin, std::cout, std::endl, std::vector, std::string;
namespace fs = std::filesystem;

Team build_team() {
	Engine eng1("Honda", "V6", 1040);
	Racecar car1(eng1, "RB21");
	Team team1("red_bull", car1, d1, d2, 8, 88);
	return team1;
}

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
	vector<Driver> drivers;
	vector<Team> teams;
	std::ifstream in;
	in.open("drivers.txt");
	if (in.is_open()) {
		string n, int id, int t, int w, int pp;
		while (in >> n >> id >> t >> w >> pp) {
			Driver t_d(n, id, t, w, pp);
			drivers.push_back(t_d);
		}
	}
	in.close();
	in.open("teams.txt");
	if (in.is_open()) {
		// incorrect string n; Racecar c; Driver p1; Driver p2; int t, int w;

	}
	return 0;
}