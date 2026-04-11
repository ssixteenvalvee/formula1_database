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
#include <functional>
#define MAXPART 34 // In the whole history of Formula 1 no more than 34 cars participated in the race. (1953, Germany).

using std::cin, std::cout, std::endl, std::vector, std::string, std::getline, std::unordered_map;
namespace fs = std::filesystem;
using CommandHandler = std::function<void(std::istringstream&)>;
vector<string> commands = { "CalcDP: Calculate driver points", "LeadDriver: Show leader of the season", "DriverStats: Show driver stats.)", "WinEngine: Show the most effective engine"};

void UserInteraction(Season& season) {
	unordered_map<string, std::function<void()>> CommandList{
		{"CalcDP",[&season]() {
			int id, round_id;
			cout << "Enter number of the driver and round: (number space number)" << endl;
			season.PrintDrivers(); // !!!
			cout << "\n\n";
			season.PrintRounds(); // !!!
			cout << ">> "; cin >> id >> round_id; 
			id--; round_id;
			season.CalcPoints(id, round_id, true);
			return;
		}},
		{"LeadDriver", [&season]() {
			Driver leadr = season.GiveLeaderDriver();
			cout << leadr.give_name() << " is a leader of the season" << " with " << season.CalcPoints(leadr.give_id(), season.give_rounds_size(), false) << " points." << endl;
			cout << "Do you want more about this driver?" << "\n\tY/N" << "\n>> ";
			string choice;
			cin >> choice;
			if (choice[0] == 'Y' || choice[0] == 'y') {
				season.ShowDriverStat(leadr.give_id(), season.give_rounds_size());
			}
			return;
		}},
		{"DriverStats", [&season] {
			int id, round;
			cout << "Enter number of the driver and round: (number space number)" << endl;
			season.PrintDrivers();
			cout << "\n\n";
			season.PrintRounds();
			cout << ">> "; cin >> id >> round;
			id--;
			season.ShowDriverStat(id, round);
			return;
		}},
		{"WinEngine", [&season]() {
		
		}}
	};
	//
	string line;
	cout << "Enter the command:" << endl;
	for (string& cm : commands) cout << "> " << cm << endl;
	cout << "\n";
	while (getline(cin, line)) {
		if (line == "stop") return;
		cout << ">> ";
		auto cmd = CommandList.find(line);
		if (cmd != CommandList.end()) {
			cmd->second();
		}
		else {
			//cout << "Unknown command. Please try again." << endl;
		}
	}
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
	cout << ">> Please, choose the number of the season:" << endl;
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
	Season season;
	season.ScanData(Path);
	UserInteraction(season);
	return 0;
}