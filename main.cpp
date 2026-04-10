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
vector<string> commands = { "CalcDP: calculate driver points" };

void UserInteraction(Season& season) {
	unordered_map<string, std::function<void()>> CommandList{
		{"CalcDP",[&season]() {
			int id, round_id;
			cout << "Enter number of the driver and round: (number space number)" << endl;
			season.Print_Drivers();
			cout << "\n\n";
			season.Print_Rounds();
			cin >> id >> round_id; cout << ">> ";
			id--; round_id--;
			season.CalcPoints(id, round_id, true);
		}}
	};
	//
	string line;
	cout << "Enter the command.\nCommands:" << endl;
	for (string& cm : commands) cout << cm;
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