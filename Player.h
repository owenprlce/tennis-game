#ifndef PLAYER_H
#define PLAYER_H

#include "GameHandler.cpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TennisGame;

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
    //need to figure out function parameters
    Player createPlayer();




    //to check values read in
    vector<double> getForehand() {
        return playerForehand;
    }
    vector<double> getBackhand() {
        return playerBackhand;
    }
    vector<double> getSlice() {
        return playerSlice;
    }

    template <typename T>
    T option();
private:
    vector<double> playerForehand;
    vector<double> playerBackhand;
    vector<double> playerSlice;

};

#endif