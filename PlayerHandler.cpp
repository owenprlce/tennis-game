#include "PlayerHandler.h"

PlayerHandler::PlayerHandler() {
}

PlayerHandler::~PlayerHandler() {}

int PlayerHandler::hitIndex() {
    int index = rand() % 11;
    return index;
}

int PlayerHandler::getTurn() {
    int index = rand() % 2;
    return racketFlip[index];
}

void PlayerHandler::setPlayerOneHitValues(vector<double> &fh, vector<double> &bh, vector<double> &sl) {
    this->p1fh = fh;
    this->p1bh = bh;
    this->p1sl = sl;
}

bool PlayerHandler::getPlayerOneChoice(string &choice) {
    int index = hitIndex();

    if (choice == "1") {
        cout << index << " is the index value for player one forehand" << endl;
        if (p1fh[index] > p1fh_avg) {
            return true;
        } else {
            return false;
        }
    } else if (choice == "2") {
        cout << index << " is the index value for player one backhand" << endl;
        if (p1bh[index] > p1bh_avg) {
            return true;
        } else {
            return false;
        }
    } else if (choice == "3") {
        cout << index << " is the index value for player one slice" << endl;
        if (p1sl[index] > p1sl_avg) {
            return true;
        } else {
            return false;
        }
    }

    return 0;
}
void PlayerHandler::setPlayerTwoHitValues(vector<double> &fh, vector<double> &bh, vector<double> &sl) {
    this->p2fh = fh;
    this->p2bh = bh;
    this->p2sl = sl;
}

// Optimized Code!
bool PlayerHandler::getPlayerTwoChoice(string &choice) {
    int index = hitIndex();
    
    // Create a map to store the choices and their respective data and averages
    
    // Map each choice to its corresponding data and average
    unordered_map<string, PlayerChoice> choices = {
        {"1", {"forehand", &p2fh, p2fh_avg}},
        {"2", {"backhand", &p2bh, p2bh_avg}},
        {"3", {"slice", &p2sl, p2sl_avg}}
    };

    // Check if the choice exists in the map
    auto it = choices.find(choice);
    if (it != choices.end()) {
        // Print the index value and choice name
        cout << index << " is the index value for player two " << it->second.name << endl;
        
        // Compare the value at index with the average and return the result
        return (*it->second.data)[index] > it->second.avg;
    }

    // If choice is invalid, return false (or handle error as needed)
    return false;
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
