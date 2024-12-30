#ifndef TENNISGAME_H
#define TENNISGAME_H

#include "Player.cpp"
#include "PlayerHandler.h"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = filesystem;

class TennisGame
{
public:
    TennisGame();
    ~TennisGame();

    // Game Initialization
    void play(TennisGame t);
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

    // File Parsing
    vector<double> parseHitTypes(const string& line);
    string trimLeadingSpaces(string&);
    
private:
    PlayerHandler PlayerOne, PlayerTwo;
    vector<Player *> loadedPlayers {};
};

#endif