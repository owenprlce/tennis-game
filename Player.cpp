#include "Player.h"

Player::Player()
{
}

Player::Player(string name, vector<vector<double>> hitTypes, int score, int gameScore, int setScore)
{
    this->playerName = name;
    this->hitTypes = hitTypes;
    this->playerScore = score;
    this->gameScore = gameScore;
    this->setScore = setScore;
}

Player::~Player()
{
}