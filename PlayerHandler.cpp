#include "PlayerHandler.h"

PlayerHandler::PlayerHandler() {}

PlayerHandler::~PlayerHandler() {}

int PlayerHandler::hitIndex() {
    // will need to eventually choiceange this to acomodate more values
    srand(time(NULL));
    int _rand = rand() % 11;
    return _rand;
}

int PlayerHandler::getTurn() {
    srand(time(NULL));
    int _rand = rand() % 2;
    return racketFlip[_rand];
}

void PlayerHandler::setPlayerOneHitValues(vector<double> &a, vector<double> &b, vector<double> &c) {
    this->p1fh = a;
    this->p1bh = b;
    this->p1sl = c;
}

bool PlayerHandler::getPlayerOneChoice(string &choice) {
    int rand;

    if (choice == "1") {
        rand = hitIndex();

        double test = p1fh[rand];
        if (test > p1fh_avg) {
            return true;

        } else {
            return false;
        }
    } else if (choice == "2") {
        rand = hitIndex();
        return p1bh[rand];
    } else if (choice == "3") {
        rand = hitIndex();
        return p1sl[rand];
    } else {
    }

    return 0.0;
}
void PlayerHandler::setPlayerTwoHitValues(vector<double> &a, vector<double> &b, vector<double> &c) {
    this->p2fh = a;
    this->p2bh = b;
    this->p2sl = c;
}

bool PlayerHandler::getPlayerTwoChoice(string &choice) {
    int rand;

    if (choice == "1") {
        rand = hitIndex();
        double fh = p2fh[rand];
        if (fh > p2fh_avg) {
            return true;
        } else {
            return false;
        }
    } else if (choice == "2") {
        rand = hitIndex();
        double bh = p2bh[rand];

        if (bh > p2bh_avg) {
            return true;
        } else {
            return false;
        }

    } else if (choice == "3") {
        rand = hitIndex();
        double sl = p2sl[rand];

        if (sl > p2sl_avg) {
            return true;
        } else {
            return false;
        }
    } else {
        return 0;
    }
    // does returning 0 naturally mean a missed shot
    return 0;
}

string PlayerHandler::playerMenu() {
    string choice;

    do {
        cout << "(1) Forehand\n"
             << "(2) Backhand\n"
             << "(3) Slice\n"
             << "(SAVE) Save Game\n";

        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

        if (choice == "1" || choice == "2" || choice == "3" || choice == "SAVE") {
            break;
        }

        cin.clear();

    } while (choice != "1" || choice != "2" || choice != "3" || choice != "SAVE");

    return choice;
}

void PlayerHandler::setPlayerOneAVGs() {
    p1fh_avg = accumulate(p1fh.begin(), p1fh.end(), 0.0) / p1fh.size();
    p1bh_avg = accumulate(p1bh.begin(), p1bh.end(), 0.0) / p1bh.size();
    p1sl_avg = accumulate(p1sl.begin(), p1sl.end(), 0.0) / p1sl.size();
}

void PlayerHandler::setPlayerTwoAVGs() {
    p2fh_avg = accumulate(p2fh.begin(), p2fh.end(), 0.0) / p2fh.size();
    p2bh_avg = accumulate(p2bh.begin(), p2bh.end(), 0.0) / p2bh.size();
    p2sl_avg = accumulate(p2sl.begin(), p2sl.end(), 0.0) / p2sl.size();
}
