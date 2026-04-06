#include <iostream>
#include <vector>
#include "Engine.h"
#include "Racecar.h"
#include "Team.h"
#include "Round.h"
#include "Season.h"
#include <fstream>
#include <sstream>
#include <filesystem>

Season::Season(vector<Engine> engs, vector<Driver> drvrs, vector<Racecar> cars, vector<Team> teams, vector<Round> rnds) : : engines(engs), drivers(drvrs), cars(cars), teams(teams), rounds(rnds) {}
void Season::ScanData(fs::path Path) {
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
}