#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>
#include <bits/stdc++.h>
using namespace std;

class GameHandler
{
public:
    template<typename T>
    T returnPlayerShot(T);
    int getRandom();
    int getRacketFlip();
    
    void setPlayer1(vector<double> &, vector<double> &, vector<double> &);
    void setPlayer1AVGs(double &, double &, double &);
    double getPlayer1(string &);


    void setPlayer2(vector<double> &, vector<double> &, vector<double> &);
    void setPlayer2AVGs(double &, double &, double &);
    double getPlayer2(string &);


    bool isValidShot(double &, GameHandler &, string &, int &);
    template <typename T>
    T option();

    vector<GameHandler> playerOdds;


private:
    vector<double> racketFlip = {1, 2};

    vector<double> p1forehandOdds = {};
    vector<double> p1backhandOdds = {};
    vector<double> p1sliceOdds = {};
    double p1forehandAVG = 0;
    double p1backhandAVG = 0;
    double p1sliceAVG = 0;

    vector<double> p2forehandOdds = {};
    vector<double> p2backhandOdds = {};
    vector<double> p2sliceOdds = {};
    double p2forehandAVG = 0;
    double p2backhandAVG = 0;
    double p2sliceAVG = 0;

    
};

#endif