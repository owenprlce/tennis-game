#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>

#include "TennisGame.cpp"

int main() {
    // Seed Randomness
    srand(time(NULL));
    // TennisGame object
    TennisGame t;
    // Program entrypoint
    t.menu(t);

    return 0;
}