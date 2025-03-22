#ifndef TENNISGAME_H
#define TENNISGAME_H

#include "Player.cpp"
#include "PlayerHandler.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

namespace fs = filesystem;

class TennisGame
{
public:
    TennisGame();
    ~TennisGame();

    // Game Initialization
    void menu(TennisGame t);
    void startGame();
        vector<Player *> loadPlayerArchetypes();
        vector<Player *> playerChoice(vector<Player *>);
    void loadGame();

    // Game Persistence
    string saveGame(vector<Player *>, int);

    // Game Modes
    void noAdPlayLogic(vector<Player *>, int);
    void adPlayLogic(vector<Player *>, int);
    void tieBreakerLogic(vector<Player *>, int);

    // File I/O
    vector<double> parseHitTypes(const string&);
    void createNewPlayer(string&);
    void resetGameSettings(); 
    void resetCache();
    
private:
    PlayerHandler PlayerOne, PlayerTwo;
    vector<Player *> loadedPlayers {};
};

#endif