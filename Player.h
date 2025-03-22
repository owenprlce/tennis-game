#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerHandler.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <regex>

using namespace std;

class Player
{
public:
    int playerScore = 0;
    int gameScore = 0;
    int setScore = 0;
    string playerName;
    vector<vector<double>> hitTypes;

    Player();
    Player(string, vector<vector<double>>, int, int, int);
    ~Player();

    string createPlayer();
    string hitConverter(string&);

private:

};

#endif