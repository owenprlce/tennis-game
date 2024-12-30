#include "Player.h"

Player::Player() {
}

Player::Player(string playerName, vector<vector<double>> hitTypes, int score, int gameScore, int setScore)
: playerName(playerName), hitTypes(hitTypes), playerScore(score), gameScore(gameScore), setScore(setScore) {}

Player::~Player() {
}