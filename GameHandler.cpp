#include "GameHandler.h"

int GameHandler::getRandom()
{
    srand(time(NULL));
    int _rand = rand() % 1;
    return _rand;
}

int GameHandler::getRacketFlip()
{
    srand(time(NULL));
    int _rand = rand() % 2;
    return racketFlip[_rand];
}

void GameHandler::setPlayer1(vector<double> &a, vector<double> &b, vector<double> &c)
{
    this->p1forehandOdds = a;
    this->p1backhandOdds = b;
    this->p1sliceOdds = c;
}

double GameHandler::getPlayer1(string &choice)
{
    //could create future initialization issues?
    int rand;

    if (choice == "1")
    {
        rand = getRandom();
        return p1forehandOdds[rand];
    }
    else if (choice == "2")
    {
        rand = getRandom();
        return p1backhandOdds[rand];
    }
    else if (choice == "3")
    {
        rand = getRandom();
        return p1sliceOdds[rand];
    }
    else if (choice == "SAVE")
    {

    }
    else if (choice == "QUIT")
    {

    }
    else
    {
        return 0.0;
    }

    return 0.0;
}
void GameHandler::setPlayer2(vector<double> &a, vector<double> &b, vector<double> &c)
{
    this->p2forehandOdds = a;
    this->p2backhandOdds = b;
    this->p2sliceOdds = c;
}


double GameHandler::getPlayer2(string &choice)
{
    //could create future initialization issues?
    int rand;
    GameHandler g;

    if (choice == "1")
    {
        rand = getRandom();
        //might look like this?
        return true;
    }
    else if (choice == "2")
    {
        rand = getRandom();
        return p2backhandOdds[rand];
    }
    else if (choice == "3")
    {
        rand = getRandom();
        return p2sliceOdds[rand];
    }
    else if (choice == "SAVE")
    {

    }
    else if (choice == "QUIT")
    {

    }
    else
    {
        return 0.0;
    }

    return 0.0;
}

template <typename T>
T GameHandler::option()
{
    string c;
    while (c != "1" || c != "2" || c != "3" || c != "SAVE" || c != "LOAD")
    {
        cout << "(1) Forehand" << endl
             << "(2) Backhand" << endl
             << "(3) Slice" << endl
             << "(SAVE) Save Game Status" << endl
             << "(LOAD) Load Game Status" << endl;
        cin >> c;

        if (cin.fail())
        {
            cout << "invalid input, try again" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }
    return c;
}

bool GameHandler::isValidShot(double &shotPercent, GameHandler &temp, string &shotType, int &player) {
    double counter = 0;
    
    if(player == 1) {
        if(shotType == "1") {
            for(int i = 0; i < p1forehandOdds.size(); ++i) {
                counter += i;
            }


        }
    }


    return false;
}

void GameHandler::setPlayer1AVGs(double &a, double &b, double &c) {
    this->p1forehandAVG = a;
    this->p1backhandAVG = b;
    this->p1sliceAVG = c;
}

void GameHandler::setPlayer2AVGs(double &d, double &e, double &f) {
    this->p2forehandAVG = d;
    this->p2backhandAVG = e;
    this->p2sliceAVG = f;
}