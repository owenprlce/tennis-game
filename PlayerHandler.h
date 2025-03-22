#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include <ctime>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// Testing
#include <unordered_map>

using namespace std;

struct PlayerChoice {
    string name;
    vector<double>* data;
    double avg;

    // Constructor for easy initialization
    PlayerChoice(const string& name, vector<double>* data, double avg)
        : name(name), data(data), avg(avg) {}
};

class PlayerHandler {
   public:

    PlayerHandler();
   ~PlayerHandler();

    int hitIndex();
    int getTurn();
    string playerMenu();

    // Player 1 
    void setPlayerOneHitValues(vector<double> &, vector<double> &, vector<double> &);
    void setPlayerOneAVGs();
    bool getPlayerOneChoice(string &);

    // Player 2
    void setPlayerTwoHitValues(vector<double> &, vector<double> &, vector<double> &);
    void setPlayerTwoAVGs();
    bool getPlayerTwoChoice(string &);

   private:
    vector<double> racketFlip = {1, 2};

    // Player 1 Attributes
    vector<double> p1fh = {};
    vector<double> p1bh = {};
    vector<double> p1sl = {};
    double p1fh_avg = 0;
    double p1bh_avg = 0;
    double p1sl_avg = 0;

    // Player 2 Attributes
    vector<double> p2fh = {};
    vector<double> p2bh = {};
    vector<double> p2sl = {};
    double p2fh_avg = 0;
    double p2bh_avg = 0;
    double p2sl_avg = 0;
};

#endif