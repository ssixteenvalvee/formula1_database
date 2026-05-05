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
#include <nlohmann/json.hpp>
#define MAXPART 34 // In the whole history of Formula 1 no more than 34 cars participated in the race. (1953, Germany).

enum {stringlim = 2, seasonlim = 4, minyear = 1950};
using std::cin, std::cout, std::endl, std::vector, std::string, std::getline, std::unordered_map;
namespace fs = std::filesystem;
using json = nlohmann::json;
using CommandHandler = std::function<void(std::istringstream&)>;
vector<string> UI_commands = { "CalcDP: Calculate driver points", 
							"LeadDriver: Show leader of the season", 
							"DriverStats: Show driver stats.", 
							"WinEngine: Show the most effective engine" };
vector<string> CRUD_commands = { "help: if you're a new boy here." };

//prototypes
//
void CRUD(Season& season);
void UserInteraction(Season& season);
void Asktodo(Season& season);
void CreateNewDir(fs::path Path);

void CreateNewDir(fs::path BasePath) {
	cout << ">\tPlease, enter the year of the season.\n>> ";
	string choice;
	int choice_int;
	cin >> choice;
	if (isdigit(choice)) {
		choice_int = stoi(choice);
		if (choice_int >= minyear && choice_int <= 9999) {
			fs::path newPath = BasePath / choice;
			if (fs::create_directories(newPath)) {
				cout << "> Creating the " << choice << " folder ...\n";
				// engines.json;
				json Engines_array = json::array();
				json enginesWrap = { {"engines", Engines_array} };
				std::ofstream enginesFile(newPath / "engines.json");
				enginesFile << enginesWrap.dump(4);
				// cars.json;
				json Cars_array = json::array();
				json carsWrap = { {"cars", Cars_array} };
				std::ofstream carsFile(newPath / "cars.json");
				carsFile << carsWrap.dump(4);
				// drivers.json
				json Drivers_array = json::array();
				json driversWrap = { {"drivers", Drivers_array} };
				std::ofstream driversFile(newPath / "drivers.json");
				driversFile << driversWrap.dump(4);
				// teams.json
				json Teams_array = json::array();
				json teamsWrap = { {"teams", Teams_array} };
				std::ofstream teamsFile(newPath / "teams.json");
				teamsFile << teamsWrap.dump(4);
				// rounds.json
				json Rounds_array = json::array();
				json roundsWrap = { {"rounds", Rounds_array} };
				std::ofstream roundsFile(newPath / "rounds.json");
				roundsFile << roundsWrap.dump(4);
				cout << "> Good! " << choice << " directory is succesfully created.\n";
				cout << "> You can fill the information with Moderating mode now.\n";
			}
			else {
				cout << "> This folder already exists!\n";
				return;
			}
		}
		else {
			cout << "> Wrong format. Please enter the valid data:\n> 1. It is greater than 1949\n> 2. It is less than 10 thousand.\n";
			return;
		}
	}
	return;
}

void CRUD(Season& season) {
	unordered_map < string, std::function<void()>> CRUD_CommandList{
		{"help", [&season]() {
		string square(90, '-');
		clearScreen();
		cout << "> List of commands:\n";
		cout << square << endl;
		for (string& cmd : CRUD_commands) {
			cout << cmd << endl;
		}
		cout << square << endl;
		return;
		}}
	};
	//
	cout << "To get a list with commands type 'help'; To return type 'return'\n>> ";
	string line;
	while (true) {
		if (!getline(cin, line)) break;
		if (line == "stop") break;
		if (line == "return") {
			clearScreen();
			return;
		}
		auto cmd = CRUD_CommandList.find(line);
		if (cmd != CRUD_CommandList.end()) {
			cmd->second();
			cout << "	Enter the command:\n>> ";
		}
		else if (!line.empty()) {
			cout << "Unknown command: \"" << line << "\". Type 'help' for list.\n>> ";
		}
	}
}

void UserInteraction(Season& season) {
	unordered_map<string, std::function<void()>> UI_CommandList{
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
			for (string& cm : UI_commands) {
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

		auto cmd = UI_CommandList.find(line);
		if (cmd != UI_CommandList.end()) {
			cmd->second();
			cout << "	Enter the command:\n>> ";
		}
		else if (!line.empty()) {
			cout << "Unknown command: \"" << line << "\". Type 'help' for list.\n>> ";
		}
	}
}

void Asktodo(Season& season, fs::path BasePath) {
	int choice;
	clearScreen();
	cout << "Would you like to moderate the info or read it?" << endl;
	cout << "\t1. Read\t\t2. Moderate.\t\t3. New season (directory).\n>> ";
	cin >> choice;
	switch (choice) {
	case 1:
		clearScreen();
		cout << "Reading mode.\n";
		season.ScanData(BasePath);
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
		CreateNewDir(BasePath);
		break;
	}
}

//

int main()
{
	fs::path basePath = "alldata";
	Season season;
	while (true) {
		Asktodo(season, basePath);
		cout << "Would you like to continue? \n\tY/N\n>> ";
		char c; cin >> c;
		if (c == 'y' || c == 'Y') {
			continue;
		}
		else {
			cout << "> OK, Bye then.\n";
			break;
		}
	}
	return 0;
}