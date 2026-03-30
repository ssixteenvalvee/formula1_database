#include "Team.h"

Team::Team(string n, Racecar c, Driver p1, Driver p2, int t, int w)
	: name(n), car(c), pilot_1(p1), pilot_2(p2), titles(t), gp_wins(w) {
}
void Team::show_team() {
	cout << "About " << name << ": " << endl;
	cout << "Car: " << car.print_chasis() << endl;
	cout << "First pilot: " << pilot_1.print_name() << endl;
	cout << "Second pilot: " << pilot_2.print_name() << endl;
	cout << "Titles: " << titles << ", Wins: " << gp_wins << endl;
}