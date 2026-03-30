#include "Racecar.h"
#include <iostream>
using std::string;

Racecar::Racecar(Engine engine, string chasis) : engine(engine), chasis(chasis) {}
void Racecar::show_car() {
	engine.show_engine();
	cout << chasis << endl;
}