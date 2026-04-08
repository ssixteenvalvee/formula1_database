#include "Team.h"

Team::Team(int teamid, string n, Racecar c, Driver p1, Driver p2, int t, int w)
	: team_id(teamid), name(n), car(c), pilot_1(p1), pilot_2(p2), titles(t), gp_wins(w) {
}
void Team::show_team() {
	cout << "About " << name << ": " << endl;
	cout << "\tCar: " << car.print_chasis() << endl;
	cout << "\tFirst pilot: " << pilot_1.give_name() << endl;
	cout << "\tSecond pilot: " << pilot_2.give_name() << endl;
	cout << "\tTitles: " << titles << ", Wins: " << gp_wins << endl;
}