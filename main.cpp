#include "Driver.h"
#include "Engine.h"
#include "Racecar.h"
#include "Team.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using std::cin, std::cout, std::endl, std::vector, std::string;
namespace fs = std::filesystem;
Driver d1("max_verstappen", 4, 22, 33);
Driver d2("kimi_antonelli", 0, 2, 2);

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
	
	Team red_bull = build_team();
	red_bull.show_team();
	d1.print_name();
	d2.show_info();
	return 0;
}