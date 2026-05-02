#include "Driver.h"
#include "Engine.h"
#include "Racecar.h"
#include "utilities.h"
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
vector<string> commands = { "CalcDP: Calculate driver points", 
							"LeadDriver: Show leader of the season", 
							"DriverStats: Show driver stats.", 
							"WinEngine: Show the most effective engine" };

//prototypes
void CRUD(Season& season);
void UserInteraction(Season& season);
void Asktodo(Season& season);

void CRUD(Season& season) {
	cout << "Under Construction" << endl;
	return;
}

void UserInteraction(Season& season) {
	unordered_map<string, std::function<void()>> CommandList{
		{"CalcDP",[&season]() {
			clearScreen();
			int id, round_id;
			cout << "	Enter number of the driver and round: (number space number)" << endl;
			season.PrintDrivers(); // !!!
			cout << "\n\n";
			season.PrintRounds(); // !!!
			cout << ">> "; cin >> id >> round_id; 
			id--; round_id;
			season.CalcPoints(id, round_id, true);
			return;
		}},
		{"LeadDriver", [&season]() {
			string square(90, '-');
			Driver leadr = season.GiveLeaderDriver();
			cout << square << endl;
			cout << leadr.give_name() << " is a leader of the season" << " with " << season.CalcPoints(leadr.give_id(), season.give_rounds_size(), false) << " points." << endl;
			cout << "Do you want more about this driver?" << "\n\tY/N" << "\n>> ";
			string choice;
			cin >> choice;
			if (choice[0] == 'Y' || choice[0] == 'y') {
				season.ShowDriverStat(leadr.give_id(), season.give_rounds_size());
			}
			cout << square << endl;
			return;
		}},
		{"DriverStats", [&season] {
			string square(90, '-');
			clearScreen();
			int id, round;
			cout << "	Enter number of the driver and round: (number space number)" << endl;
			season.PrintDrivers();
			cout << "\n\n";
			season.PrintRounds();
			cout << ">> "; cin >> id >> round;
			id--;
			cout << square << endl;
			season.ShowDriverStat(id, round);
			cout << square << endl;
			return;
		}},
		{"WinEngine", [&season]() {
			Driver ldr = season.GiveLeaderDriver();
			vector<Team> teams = season.GiveTeamsVect();
			for (Team& team : teams) {
				vector<Driver> twodrivers = team.GiveTeamDrivers();
				if (twodrivers[0].give_id() == ldr.give_id() || twodrivers[1].give_id() == ldr.give_id()) {
					team.GiveCar().GiveCarEngine().show_engine();
				}
			}
			return;
		}}, 
		{"help", [&season]() {
			clearScreen();
			cout << "_________________________________________" << endl;
			for (string& cm : commands) {
				cout << "> " << cm << endl;
			}
			cout << "_________________________________________" << endl;
		}}
	};
	//
	string line;
	cout << "Type 'help' to get available commands. Type 'stop' to exit and 'return' to return.\n>> ";
	while (true) {
		if (!getline(cin, line)) break;
		if (line == "stop") break;
		if (line == "return") {
			clearScreen();
			return;
		}

		auto cmd = CommandList.find(line);
		if (cmd != CommandList.end()) {
			cmd->second();
			cout << "	Enter the command:\n>> ";
		}
		else if (!line.empty()) {
			cout << "Unknown command: \"" << line << "\". Type 'help' for list.\n>> ";
		}
	}
}

void Asktodo(Season& season) {
	int choice;
	clearScreen();
	cout << "Would you like to moderate the info or read it?" << endl;
	cout << "\t1. Read\t\t2. Moderate.\t\t3. New season (directory).\n>> ";
	cin >> choice;
	switch (choice) {
	case 1:
		clearScreen();
		cout << "Reading mode.\n";
		UserInteraction(season);
		break;
	case 2:
		clearScreen();
		cout << "Moderating Mode.\n";
		CRUD(season);
		break;
	case 3:
		clearScreen();
		cout << "Create new dir" << endl;
		// under construction.
		break;
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
	cout << "	Please, choose the number of the season:" << endl;
	int cnt = 1;
	for (auto& option : seasons_str) {
		cout << cnt << ". " << option << endl;
		cnt++;
	}
	int choice; 
	cout << ">> ";
	cin >> choice;
	while (choice > seasons_str.size() || choice < 0) {
		cout << "Wrong Format" << endl;
		cin >> choice;
	}
	
	fs::path Path = basePath/seasons_str[choice - 1]; // !!!
	Season season;
	season.ScanData(Path);
	while (true) {
		Asktodo(season);
		cout << "Would you like to continue? \n\tY/N\n>> ";
		char c; cin >> c;
		if (c == 'y' || c == 'Y') {
			continue;
		}
		else break;
	}
	return 0;
}