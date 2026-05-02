#include "utilities.h"
#include "Engine.h"
#include "Racecar.h"
#include "Team.h"
#include "Round.h"
#include "Driver.h"
#include "Season.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iomanip>
#define M1 -1

using json = nlohmann::json;
using std::cin, std::cout, std::endl, std::vector, std::string, std::getline;

//Season::Season() : engines(), drivers(), cars(), teams(), rounds() {}
// Season::Season(vector<Engine> engs, vector<Driver> drvrs, vector<Racecar> cars, vector<Team> teams, vector<Round> rnds) {}
void Season::ScanData(fs::path Path) {
	std::ifstream in;
	string line;
	in.open(Path / "engines.json");
	if (in.is_open()) { // engine: engine_id, manufacturer, type, hp // e.g.: 0, Honda, V6, 1040;
		json data;
		try {
			in >> data;
		} catch (const json::parse_error& e) {
			std::cerr << "Error parsing 'enignes.json': " << e.what() << std::endl;
			return;
		}
		for (auto& item : data["engines"]) {
			int id = item["id"];
			string manufacturer = item["manufacturer"];
			string type = item["type"];
			int hp = item["horsepower"];
			Engine engine(id, manufacturer, type, hp);
			engines.push_back(engine);
		}
	}
	else {
		std::cerr << "Can not open 'engines.json'." << std::endl;
		return;
	}
	in.close();
	in.open(Path / "cars.json");
	if (in.is_open()) { // car: car_id, engine_id/manufacturer, chasis (its name) // example: 0, 0/Honda, RB21; // At the moment, we only use IDs.
		json data;
		try {
			in >> data;
		}
		catch (const json::parse_error& e) {
			std::cerr << "Error cars.json: " << e.what() << endl;
			return;
		}
		for (auto& item : data["cars"]) {
			int id = item["id"];
			int engine_id = item["engine_id"];
			string chassis = item["chassis"];
			for (Engine& eng : engines) {
				if (eng.give_id() == engine_id) {
					Racecar car(id, eng, chassis);
					cars.push_back(car);
				}
			}
		}
	}
	else {
		cout << "Can not open cars.json." << endl;
		return;
	}
	in.close();
	in.open(Path / "drivers.json");
	if (in.is_open()) { // driver: id, name, titles, wins, pole positions.
		json data;
		try {
			in >> data;
		}
		catch (const json::parse_error& error) {
			std::cerr << "Error drivers.json: " << error.what() << endl;
			return;
		}
		for (auto& item : data["drivers"]) {
			int id = item["id"];
			string name = item["name"];
			int titles = item["titles"];
			int wins = item["wins"];
			int points = item["points"];
			Driver driver(id, name, titles, wins, points);
			drivers.push_back(driver);
		}
	}
	else {
		cout << "Can not open 'drivers.json'." << endl;
		return;
	}
	in.close();
	in.open(Path / "teams.json");
	if (in.is_open()) { // team: id, name, car_id, driver1_id, driver2_id, titles, wins;
		json data;
		try {
			in >> data;
		}
		catch (const json::parse_error& error) {
			std::cerr << "Error 'teams.json': " << error.what() << endl;
		}
		for (auto& item : data["teams"]) {
			int id = item["id"];
			string name = item["name"];
			int car_id = item["car_id"], driver1_id = item["driver1_id"], driver2_id = item["driver2_id"];
			int titles = item["titles"];
			int wins = item["wins"];
			for (Racecar& car : cars) {
				if (car.give_id() == car_id) {
					for (Driver& driver1 : drivers) {
						if (driver1.give_id() == driver1_id)
							for (Driver& driver2 : drivers) {
								if (driver2.give_id() == driver2_id) {
									Team team(id, name, car, driver1, driver2, titles, wins);
									teams.push_back(team);
								}
							}
					}
				}
			}
		}
	}
	else {
		cout << "Can not open 'teams.json'." << endl;
		return;
	}
	in.close();
	in.open(Path / "rounds.json");
	if (in.is_open()) { // id, geographical_place, date, vector with driver's positions at the finish of the race.
		json data;
		try {
			in >> data;
		}
		catch (const json::parse_error& error) {
			std::cerr << "Error 'rounds.json': " << error.what() << endl;
		}
		for (auto& item : data["rounds"]) {
			int id = item["id"];
			string place = item["place"];
			string date = item["date"];
			vector<int> positions_ids = item["positions"];
			Round round(id, place, date, positions_ids);
			rounds.push_back(round);
		}
	}
	else {
		cout << "Can not open 'rounds.json'." << endl;
		return;
	}
	in.close();
	clearScreen();
	cout << "> Scanning succesful <" << endl;
}
void Season::ModerateData(fs::path Path) {
	std::fstream out;
	string line;
}
size_t Season::give_rounds_size() {
	return rounds.size();
}
int Season::CalcPoints(int driver_id, int round_id, bool show) {
	if (round_id > rounds.size()) {
		cout << "Invalid number. Too big or to low." << endl;
		return -1;
	}
	string name;
	for (Driver& dr : drivers) {
		if (driver_id == dr.give_id()) {
			name = dr.give_name();
			format_name(name);
		}
	}
	if (round_id == -1) round_id = rounds.size();
	int driver_points = 0;
	string place;
	for (int i = 0; i < round_id; i++) {
		int position = rounds[i].give_driver_place(driver_id);
		driver_points += rounds[i].give_pos_points(position);
		if (i == round_id) place = rounds[i].give_place();
		else if (round_id == -1) place = rounds[rounds.size()].give_place();
	}
	if (show == true) std::cout << name << " has " << driver_points << " points after " << place << " race." << std::endl;
	return driver_points;
}
void Season::PrintDrivers() {
	int cnt = 1;
	string square(80, '=');
	cout << square << endl;
	for (Driver& dr : drivers) {
		string name = dr.give_name();
		cout << cnt << "." << format_name(name) << std::setw(4) <<" ";
		if (cnt % 3 == 0) cout << "\n";
		cnt++;
	}
	cout << "\n" << square << endl;
	return;
}
void Season::PrintRounds() {
	int cnt = 1;
	string square(80, '-');
	cout << square << endl;
	for (Round& r : rounds) {
		string place = r.give_place();
		cout << cnt << "." << format_name(place) << std::setw(4) << " ";
		if (cnt % 3 == 0) cout << "\n";
		cnt++;
	}
	cout << square << endl;
	return;
}
vector<int> Season::GiveSumPoints(int round_id) {
	vector<int> sum_driver_points(drivers.size(), 0);
	int maxRound = (round_id == -1) ? static_cast<int>(rounds.size()) : round_id;
	for (int r = 0; r < maxRound; ++r) {
		const vector<int>& positions = rounds[r].give_pos_vector();
		for (size_t pos = 0; pos < positions.size(); ++pos) {
			int driverId = positions[pos];
			if (driverId >= 0 && driverId < static_cast<int>(drivers.size())) {
				int points = rounds[r].give_pos_points(static_cast<int>(pos) + 1);
				sum_driver_points[driverId] += points;
			}
		}
	}
	return sum_driver_points;
}
Driver Season::GiveLeaderDriver() {
	vector<int> sum_dp = GiveSumPoints(-1);
	int leader_points = M1;
	int dr_id = M1;
	for (int i = 0; i < sum_dp.size(); i++) {
		if (leader_points < sum_dp[i]) {
			leader_points = sum_dp[i];
			dr_id = i;
		}
	}
	for (Driver& dr : drivers) {
		if (dr.give_id() == dr_id) return dr;
	}
	return Driver(1, "NONE", 0, 0, 0);
}
void Season::ShowDriverStat(int driver_id, int round_id) {
	if (driver_id < 0 && driver_id >= drivers.size()) {
		cout << "Incorrect Driver_id." << endl;
		return;
	}
	else if (round_id < 0 && round_id > rounds.size()) {
		cout << "Incorrect Round_id." << endl;
		return;
	}
	int w = 0, pts = 0;
	string place;
	string date;
	for (Driver& dr : drivers) {
		if (dr.give_id() == driver_id) {
			for (Round& r : rounds) {
				if (r.give_id() >= round_id) break;
				place = r.give_place();
				date = r.give_date();
				if (r.give_pos_vector()[0] == driver_id) w++;
				int pos = 1;
				for (int& id : r.give_pos_vector()) {
					if (id == driver_id) {
						pts += r.give_pos_points(pos);
						break;
					}
					pos += 1;

				}
			}
			cout << dr.give_name() << " has such achievements:" << endl;
			cout << dr.give_titles() << " titles, " << dr.give_points() + pts << " points, " << dr.give_wins() + w << " wins summary untill the " << place << ", " << date << endl;
			return;
		}
	}
	return;
}
Engine Season::GiveWinnerEngine() {
	return Engine();
}
vector<Team> Season::GiveTeamsVect() {
	return teams;
}