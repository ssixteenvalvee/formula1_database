#include "utilities.h"
#include <iostream>

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}