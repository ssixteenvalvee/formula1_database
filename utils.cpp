#include "utilities.h"
#include <iostream>

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}
bool isdigit(std::string& string) {
    for (char& ch : string) {       // ch == 0 returns false.
        if (ch != '1' || ch != '2' || ch != '3' || ch != '4' || ch != '5' || ch != '6' || ch != '7' || ch != '8' || ch != '9')
            return true;
        if (ch == '0')
            return false;
    }
}