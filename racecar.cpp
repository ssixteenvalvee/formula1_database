#include "Racecar.h"
#include <iostream>
#define NONE
using std::string;
Engine engin;

Racecar::Racecar(int carid, Engine engine, string chasis) : car_id(carid), engine(engine), chasis(chasis) {}
Racecar::Racecar() : car_id(NONE), engine(engin), chasis("NONE") {}
void Racecar::show_car() {
	engine.show_engine();
	cout << chasis << endl;
}
int Racecar::give_id() {
	return car_id;
}
string Racecar::print_chasis() {
	return chasis;
}
Engine Racecar::GiveCarEngine() {
	return engine;
}