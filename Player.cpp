#include "Player.h"

Player::Player() {
}

Player::Player(string playerName, vector<vector<double>> hitTypes, int score, int gameScore, int setScore)
    : playerName(playerName), hitTypes(hitTypes), playerScore(score), gameScore(gameScore), setScore(setScore) {}

Player::~Player() {
}

string Player::createPlayer() {
    string newPlayer, playerName, fh_str, bh_str, sl_str, choice, fh, bh, sl;
    int playerScore, gameScore, setScore;


    regex validNumber("^[0-9]$");
    regex validName("^[A-Za-z]+$");

    while (true) {
        cin.clear();
        cout << "Enter player name" << endl;
        getline(cin, playerName);

        if (regex_match(playerName, validName)) {
            break;
        }

        cin.clear();
    }

    while (true) {
        cout << "Enter player forehand strength (0-9)\n";
        getline(cin, fh);

        if (regex_match(fh, validNumber)) {
            break;
        }

        cin.clear();
    }

    fh_str = hitConverter(fh);

    while (true) {
        cout << "Enter player backhand strength (0-9)\n";
        getline(cin, bh);

        if (regex_match(bh, validNumber)) {
            break;
        }

        cin.clear();
    }
    bh_str = hitConverter(bh);

    while (true) {
        cout << "Enter player slice strength (0-9)\n";
        getline(cin, sl);

        if (regex_match(sl, validNumber)) {
            break;
        }

        cin.clear();
    }
    sl_str = hitConverter(sl);

    cout << "Would you like to customize the playerScore? 'YES' or 'NO'\n";
    cin >> choice;

    if (choice == "YES") {
        cout << "Enter player score (0-3)\n";
        cin >> playerScore;
        cout << "Enter game score\n (0-2)\n";
        cin >> gameScore;
        cout << "Enter set score\n (0-1)\n";
        cin >> setScore;

        newPlayer = playerName + "," + fh_str + "|" + bh_str + "|" + sl_str + "|" + to_string(playerScore) + "|" + to_string(gameScore) + "|" + to_string(setScore);
        return newPlayer;
    }

    newPlayer = playerName + "," + fh_str + "|" + bh_str + "|" + sl_str + "|0|0|0";

    return newPlayer;
}

string Player::hitConverter(string& num) {
    string values = "";

    double d = stod(num) / 10;
    for (int i = 0; i <= 10; i++) {
        stringstream ss;
        ss << fixed << setprecision(2) << d;

        if (i == 10) {
            values.append(ss.str());
            break;
        }

        values.append(ss.str() + ",");
        d += .01;
    }

    return values;
}