#ifndef TENNISGAME_H
#define TENNISGAME_H

#include "Player.cpp"
#include "GameHandler.h"
#include <fstream>
#include <sstream>

class TennisGame
{
public:
    vector<Player *> loadPlayerArchetypes();
    vector<Player *> playerChoice(vector<Player *>);
    void start();
    void noAdPlayLogic(vector<Player *>, int);
    void adPlayLogic(vector<Player *>, int);
    // change such that it is according to who goes first from actual game
    void tieBreakerLogic(vector<Player *>, int);

    // Need to implement
    string saveGame();
    void loadGame();

private:
    GameHandler gh, PlayerOne, PlayerTwo;
};

#endif