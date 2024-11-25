#include "TennisGame.h"

vector<Player *> TennisGame::loadPlayerArchetypes()
{
    vector<Player *> players;
    ifstream filestream("players.txt");

    if (!filestream.is_open())
    {
        cerr << "Error opening file " << endl;
    }

    string junk;
    getline(filestream, junk);

    string name, line, score, gameScore, setScore;
    double forehand, backhand, slice;
    int _score, _gameScore, _setScore;

    while (getline(filestream, line))
    {
        vector<vector<double>> hit_values;
        vector<double> _forehand, _backhand, _slice;
        stringstream ss(line);
        getline(ss, name, ',');
        while (ss >> forehand)
        {
            _forehand.push_back(forehand);
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            else if (ss.peek() == '|')
            {
                ss.ignore();
                break;
            }
        }

        while (ss >> backhand)
        {
            _backhand.push_back(backhand);
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            else if (ss.peek() == '|')
            {
                ss.ignore();
                break;
            }
        }

        while (ss >> slice)
        {
            _slice.push_back(slice);
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
            else if (ss.peek() == '|')
            {
                ss.ignore();
                break;
            }
        }
        getline(ss, score, '|');
        _score = stoi(score);
        getline(ss, gameScore, '|');
        _gameScore = stoi(gameScore);
        getline(ss, setScore, '\n');
        _setScore = stoi(setScore);

        hit_values.push_back(_forehand);
        hit_values.push_back(_backhand);
        hit_values.push_back(_slice);

        Player *tempPlayerObject = new Player(name, hit_values, _score, _gameScore, _setScore);
        players.push_back(tempPlayerObject);
        ss.clear();
    }

    filestream.close();
    return players;
}

vector<Player *> TennisGame::playerChoice(vector<Player *> playerList)
{
    vector<Player *> matchPlayers;
    int p1choice, p2choice;
    for (int i = 0; i < playerList.size(); ++i)
    {
        cout << i << ")" << playerList.at(i)->playerName << endl;
    }

    cout << "Player 1 Choose: " << endl;
    cin >> p1choice;
    Player *playerOne = playerList.at(p1choice);
    PlayerOne.setPlayer1(playerOne->hitTypes[0], playerOne->hitTypes[1], playerOne->hitTypes[2]);
    gh.playerOdds.push_back(PlayerOne);
    // vector<double> p1forehand = player1->getForehand();
    // vector<double> p1backhand = player1->getBackhand();
    // vector<double> p1slice = player1->getSlice();
    // for (int i = 0; i < p1forehand.size(); ++i)
    // {
    //     if (p1forehand.empty())
    //     {
    //         cout << "Empty" << endl;
    //     }
    //     else
    //     {
    //         cout << p1forehand.at(i) << " ";
    //     }
    // }
    // for (int i = 0; i < p1backhand.size(); ++i)
    // {
    //     if (p1backhand.empty())
    //     {
    //         cout << "Empty" << endl;
    //     }
    //     else
    //     {
    //         cout << p1backhand.at(i) << " ";
    //     }
    // }
    // for (int i = 0; i < p1slice.size(); ++i)
    // {
    //     if (p1slice.empty())
    //     {
    //         cout << "Empty" << endl;
    //     }
    //     else
    //     {
    //         cout << p1slice.at(i) << " ";
    //     }
    // }
    matchPlayers.push_back(playerOne);

    cout << "Player 2 Choose: " << endl;
    cin >> p2choice;

    Player *playerTwo = playerList.at(p2choice);
    PlayerTwo.setPlayer2(playerTwo->hitTypes[0], playerTwo->hitTypes[1], playerTwo->hitTypes[2]);
    matchPlayers.push_back(playerTwo);
    gh.playerOdds.push_back(PlayerTwo);
    // vector<double> p2forehand = player2->getForehand();
    // vector<double> p2backhand = player2->getBackhand();
    // vector<double> p2slice = player2->getSlice();
    // for (int i = 0; i < p2forehand.size(); ++i)
    // {
    //     if (p2forehand.empty())
    //     {
    //         cout << "Empty" << endl;
    //     }
    //     else
    //     {
    //         cout << p2forehand.at(i) << " ";
    //     }
    // }
    // for (int i = 0; i < p2backhand.size(); ++i)
    // {
    //     if (p2backhand.empty())
    //     {
    //         cout << "Empty" << endl;
    //     }
    //     else
    //     {
    //         cout << p2backhand.at(i) << " ";
    //     }
    // }
    // for (int i = 0; i < p2slice.size(); ++i)
    // {
    //     if (p2slice.empty())
    //     {
    //         cout << "Empty" << endl;
    //     }
    //     else
    //     {
    //         cout << p2slice.at(i) << " ";
    //     }
    // }
    return matchPlayers;
}

void TennisGame::start()
{
    vector<Player *> players = loadPlayerArchetypes();

    cout << "Welcome to the world series of tennis! " << endl;
    cout << "Players choose your character! " << endl;

    vector<Player *> matchPlayers = playerChoice(players);
    int racketFlipResult = gh.getRacketFlip();

    noAdPlayLogic(matchPlayers, racketFlipResult);
}

void TennisGame::noAdPlayLogic(vector<Player *> players, int turn)
{
    string choice;
    double shot_percent;
    int numRounds = 1;
    int originalTurn = turn;

    cout << "This is round number: " << numRounds << endl;

    while (players.at(0)->setScore <= 1 && players.at(1)->setScore <= 1)
    {
        if (turn % 2 != 0)
        {
            cout << "It is player 1 turn" << endl;
            choice = gh.option<string>();
            shot_percent = PlayerOne.getPlayer1(choice);
            if (shot_percent > 0)
            {
                turn++;
                continue;
            }
            else
            {
                cout << "Player 1 Missed" << endl;
                players.at(1)->playerScore++;
                cout << "Player 2 Score: " << players.at(1)->playerScore << endl;
                cout << "Player 2 Gamescore: " << players.at(1)->gameScore << endl;

                // can I add into this if statement the condition necesarry to make the game ad capbale?
                if (players.at(1)->playerScore > 3)
                {
                    originalTurn++;
                    players.at(1)->gameScore++;
                    cout << "Player 2 GameScore: " << players.at(1)->gameScore << endl;
                    players.at(1)->playerScore = 0;
                    players.at(0)->playerScore = 0;
                }
            }
        }
        else if (turn % 2 == 0)
        {
            cout << "It is player 2 turn" << endl;
            choice = gh.option<string>();
            shot_percent = PlayerTwo.getPlayer2(choice);
            if (shot_percent > 0)
            {
                turn++;
                continue;
            }
            else
            {

                cout << "Player 2 Missed" << endl;
                players.at(0)->playerScore++;
                cout << "Player 1 Score: " << players.at(0)->playerScore << endl;
                cout << "Player 1 GameScore: " << players.at(0)->gameScore << endl;

                // can I add into this if statement the condition necesarry to make the game ad capbale?
                if (players.at(0)->playerScore > 3)
                {
                    originalTurn++;
                    players.at(0)->gameScore++;
                    cout << "Player 1 GameScore: " << players.at(0)->gameScore << endl;
                    players.at(0)->playerScore = 0;
                    players.at(1)->playerScore = 0;
                }
            }
        }
        else
        {
        }

        if (players.at(0)->playerScore == 3 && players.at(1)->playerScore == 3)
        {
            cout << "DEUCE!" << endl;
        }

        if (players.at(1)->gameScore >= 2)
        {
            players.at(1)->setScore++;
            players.at(0)->gameScore = 0;
            players.at(1)->gameScore = 0;
            cout << "Player 2 SetScore: " << players.at(1)->setScore << endl;
        }

        if (players.at(0)->gameScore >= 2)
        {
            players.at(0)->setScore++;
            players.at(0)->gameScore = 0;
            players.at(1)->gameScore = 0;
            cout << "Player 2 SetScore: " << players.at(0)->setScore << endl;
        }

        turn = originalTurn;
        numRounds++;
    }
}

void TennisGame::adPlayLogic(vector<Player *> players, int turn) {

}

// void TennisGame::tieBreakerLogic(vector<Player *> players, int turn)
// {

//     int numRounds = 1;
//     int switchTurns = turn;

//     while (players.at(0)->playerScore < 10 && players.at(1)->playerScore < 10)
//     {
//         cout << "This is round number: " << numRounds << endl;
//         // condition to check if player game score exceeds 4 points
//         if (turn % 2 != 0)
//         {
//             turn++;
//             cout << "It is player 1 turn" << endl;
//             int n = players.at(0)->option<int>();
//             if (n == 1)
//             {
//                 continue;
//             }
//             else
//             {
//                 cout << "Player 1 Missed" << endl;
//                 players.at(1)->playerScore++;
//                 cout << "Player 2 Score: " << players.at(1)->playerScore << endl;
//                 // up player game score
//             }
//         }
//         else if (turn % 2 == 0)
//         {
//             turn++;
//             cout << "It is player 2 turn" << endl;
//             int n = players.at(1)->option<int>();
//             if (n == 1)
//             {
//                 continue;
//             }
//             else
//             {
//                 cout << "Player 2 Missed" << endl;
//                 players.at(0)->playerScore++;
//                 cout << "Player 1 Score: " << players.at(0)->playerScore << endl;
//                 // up player game score
//             }
//         }
//         else
//         {
//         }

//         numRounds++;
//         switchTurns++;
//         turn = switchTurns;
//     }

//     cout << "Player 1 Score: " << players.at(0)->playerScore++ << endl;
//     cout << "Player 2 Score: " << players.at(1)->playerScore++ << endl;
// }

void TennisGame::loadGame()
{

}

string TennisGame::saveGame()
{

    return "Succesfully saved game to file system";
}