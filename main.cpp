#include "Driver.h"
#include "Engine.h"
#include "Racecar.h"
#include "Team.h"
#include "Round.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#define MAXPART 34 // In the whole history of Formula 1 no more than 34 cars participated in the race. (1953, Germany).

using std::cin, std::cout, std::endl, std::vector, std::string, std::getline;
namespace fs = std::filesystem;

void print_engines(std::vector<Engine> &data) {
	for (Engine& d : data) {
		d.show_engine();
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
	std::ifstream in;
	string line;
	in.open(Path / "engines.txt");
	if (in.is_open()) { // engine: engine_id, manufacturer, type, hp // e.g.: 0, Honda, V6, 1040;
		int engine_id;
		string manufacturer, type;
		int horsepower;
		while (std::getline(in, line)) {
			std::istringstream ss(line);
			string token;
			getline(ss, token, ','); engine_id = std::stoi(token);
			getline(ss, token, ','); manufacturer = token;
			getline(ss, token, ','); type = token;
			getline(ss, token, ','); horsepower = std::stoi(token);
			Engine eng_temp(engine_id, manufacturer, type, horsepower);
			engines.push_back(eng_temp);
		}
	}
	in.close();
	in.open(Path / "cars.txt");
	if (in.is_open()) { // car: car_id, engine_id/manufacturer, chasis (its name) // example: 0, 0/Honda, RB21; // At the moment, we only use IDs.
		int car_id;
		int engine_id;
		string chasis;
		while (std::getline(in, line)) {
			std::istringstream ss(line);
			string token;
			getline(ss, token, ','); car_id = std::stoi(token);
			getline(ss, token, ','); engine_id = std::stoi(token);
			getline(ss, token, ','); chasis = token;
			for (Engine& eng : engines) {
				if (eng.give_id() == engine_id) { // we know the engine_id and we have an engine in vector. We need to give the car its engine.
					Racecar car(car_id, eng, chasis);
					cars.push_back(car);
				}
			}
		}
	}
	in.close();
	in.open(Path / "drivers.txt");
	if (in.is_open()) { // driver: id, name, titles, wins, pole positions.
		int id, t, w, pp;
		string name;
		while (getline(in, line)) {
			std::istringstream ss(line);
			string token;
			getline(ss, token, ','); id = std::stoi(token);
			getline(ss, token, ','); name = token;
			getline(ss, token, ','); t = std::stoi(token);
			getline(ss, token, ','); w = std::stoi(token);
			getline(ss, token, ','); pp = std::stoi(token);
			Driver driver(id, name, t, w, pp);
			drivers.push_back(driver);
		}
	}
	in.close();
	in.open(Path / "teams.txt");
	if (in.is_open()) { // team: id, name, car, driver1, driver2, titles, wins;
		int id; string name; int car_id, driver1_id, driver2_id, t, w;
		while (getline(in, line)) {
			std::istringstream ss(line);
			string token;
			getline(ss, token, ','); id = std::stoi(token);
			getline(ss, token, ','); name = token;
			getline(ss, token, ','); car_id = std::stoi(token);
			getline(ss, token, ','); driver1_id = std::stoi(token);
			getline(ss, token, ','); driver2_id = std::stoi(token); // REMINDER FOR THE FUTURE: DO BINARY SEARCH.
			getline(ss, token, ','); t = std::stoi(token);
			getline(ss, token, ','); w = std::stoi(token);
			for (Racecar& car : cars) {
				if (car.give_id() == car_id) {
					for (Driver& driver1 : drivers) {
						if (driver1.give_id() == driver1_id) {
							for (Driver& driver2 : drivers) {
								if (driver2.give_id() == driver2_id) {
									Team team(id, name, car, driver1, driver2, t, w);
									teams.push_back(team);
								}
							}
						}
					}
				}
			}
		} // Fix.
	}
	in.close();
	in.open(Path / "rounds.txt");
if (in.is_open()) {
    int id;
    string place, date;
    vector<int> positions;
    positions.reserve(MAXPART);
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        string token;
        getline(ss, token, ','); id = stoi(token);
		getline(ss, token, ','); place = token;
        getline(ss, token, ','); date = token;
        positions.clear();
        while (getline(ss, token, ',')) {
            positions.push_back(stoi(token));
        }
		Round round(id, place, date, positions);
		rounds.push_back(round);
    }
}
	in.close();
	rounds[0].give_date(1);
	int p = rounds[0].give_pos_points(1); cout << p;
	return 0;
}