#include "TennisGame.h"

TennisGame::TennisGame() {}

TennisGame::~TennisGame() {}

void TennisGame::menu(TennisGame t) {
    string option;
    cout << "Welcome to text-based tennis\n\n";

    do {
        cout << "To start a new game: 'NEW'\nTo load an old game 'OLD'\n"
             << "To create a new player: 'CREATE'\nTo reset player settings 'RESET'\n"
             << "To clear game cache: 'RESET-CACHE'\n";
        cin >> option;
        transform(option.begin(), option.end(), option.begin(), ::toupper);

        if (option == "OLD") {
            t.loadGame();
            break;
        }
        if (option == "NEW") {
            t.startGame();
            break;
        }
        if (option == "CREATE") {
            Player player;
            string newPlayer = player.createPlayer();
            createNewPlayer(newPlayer);
            break;
        }

        if (option == "RESET") {
            resetGameSettings();
            break;
        }

        if (option == "RESET-CACHE") {
            resetCache();
            break;
        }

        cin.clear();

    } while (option != "NEW" || option != "OLD" || option != "CREATE" || option != "RESET" || option != "RESET-CACHE");
}

void TennisGame::startGame() {
    vector<Player *> players = loadPlayerArchetypes();

    if (players.size() >= 2) {
        cout << "\nPlayers choose your character! " << endl;

        vector<Player *> matchPlayers = playerChoice(players);
        int racketFlipResult = PlayerOne.getTurn();

        noAdPlayLogic(matchPlayers, racketFlipResult);
    }

    cout << "\nYou must have two player archetypes created" << endl;
}

vector<Player *> TennisGame::loadPlayerArchetypes() {
    vector<Player *> players;
    ifstream filestream("settings/players.txt");

    string junk;
    getline(filestream, junk);

    string name, line, score, gameScore, setScore;
    double forehand, backhand, slice;
    int _score, _gameScore, _setScore;

    while (getline(filestream, line)) {
        vector<vector<double>> hit_values;
        vector<double> _forehand, _backhand, _slice;
        stringstream ss(line);
        getline(ss, name, ',');
        while (ss >> forehand) {
            _forehand.push_back(forehand);
            if (ss.peek() == ',') {
                ss.ignore();
            } else if (ss.peek() == '|') {
                ss.ignore();
                break;
            }
        }

        while (ss >> backhand) {
            _backhand.push_back(backhand);
            if (ss.peek() == ',') {
                ss.ignore();
            } else if (ss.peek() == '|') {
                ss.ignore();
                break;
            }
        }

        while (ss >> slice) {
            _slice.push_back(slice);
            if (ss.peek() == ',') {
                ss.ignore();
            } else if (ss.peek() == '|') {
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

vector<Player *> TennisGame::playerChoice(vector<Player *> playerList) {
    vector<Player *> remainingPlayers, matchPlayers;
    int p1choice, p2choice;

    int j = 1;
    for (int i = 0; i < playerList.size(); ++i) {
        cout << j << ")" << playerList.at(i)->playerName << endl;
        j++;
    }

    cout << "Player 1 Choose: " << endl;
    cin >> p1choice;

    Player *playerOne = playerList.at(p1choice - 1);
    PlayerOne.setPlayerOneHitValues(playerOne->hitTypes[0], playerOne->hitTypes[1], playerOne->hitTypes[2]);
    PlayerOne.setPlayerOneAVGs();
    matchPlayers.push_back(playerOne);

    for (int i = 0; i < playerList.size(); ++i) {
        if (i != p1choice - 1) {
            remainingPlayers.push_back(playerList.at(i));
        }
    }

    j = 1;
    for (int i = 0; i < remainingPlayers.size(); ++i) {
        cout << j << ")" << remainingPlayers.at(i)->playerName << endl;
        j++;
    }

    cout << "Player 2 Choose: " << endl;
    cin >> p2choice;

    Player *playerTwo = remainingPlayers.at(p2choice - 1);
    PlayerTwo.setPlayerTwoHitValues(playerTwo->hitTypes[0], playerTwo->hitTypes[1], playerTwo->hitTypes[2]);
    PlayerTwo.setPlayerTwoAVGs();
    matchPlayers.push_back(playerTwo);

    return matchPlayers;
}

void TennisGame::loadGame() {
    string path = "savedGames";
    string gamePath;
    vector<string> filePathVec = {};
    int inc = 1;
    int gameToResume;

    if (!fs::is_directory("savedGames") || !fs::exists("savedGames")) {
        fs::create_directory("savedGames");
    }

    for (const auto &file : fs::directory_iterator(path)) {
        if (file.is_regular_file()) {
            cout << inc << ") " << file.path().filename().string() << endl;
            filePathVec.push_back(file.path().filename().string());
            inc++;
        }
    }

    if (!filePathVec.empty()) {
        cout << "Enter number corresponding to the filename you'd like to resume\n";
        cin >> gameToResume;
        gamePath = filePathVec.at(gameToResume - 1);
        gamePath = "savedGames/" + gamePath;
        cout << gamePath << endl;

        ifstream file(gamePath);

        if (!file.is_open()) {
            cerr << "Error opening file " << gamePath << endl;
            return;
        }

        string line;
        int turn;
        int playerScore, gameScore, setScore;

        vector<Player *> loadedPlayers;

        while (getline(file, line)) {
            // Parse the turn
            if (line.find("Turn:") != string::npos) {
                // Get the turn number
                turn = stoi(line.substr(line.find(":") + 1));
                cout << "Turn: " << turn << endl;
            }

            // Player 1 data
            if (line.find("Player 1:") != string::npos) {
                string playerName;
                vector<vector<double>> hitTypes;
                vector<double> forehand, backhand, slice;

                // Get Player 1's name
                getline(file, line);
                playerName = line.substr(line.find("Name:") + 5);
                playerName = playerName.substr(playerName.find_first_not_of(" "));  // Trim leading spaces

                // Parse the hit types for Player 1
                getline(file, line);
                forehand = parseHitTypes(line.substr(line.find("Hit-Types(FH):") + 14));

                getline(file, line);
                backhand = parseHitTypes(line.substr(line.find("Hit-Types(BH):") + 14));

                getline(file, line);
                slice = parseHitTypes(line.substr(line.find("Hit-Types(SL):") + 14));

                hitTypes.push_back(forehand);
                hitTypes.push_back(backhand);
                hitTypes.push_back(slice);

                // Parse Player 1's scores
                getline(file, line);
                playerScore = stoi(line.substr(line.find("Player-Score:") + 13));
                cout << "did not fail" << endl;

                getline(file, line);
                gameScore = stoi(line.substr(line.find("Game-Score:") + 11));

                getline(file, line);
                setScore = stoi(line.substr(line.find("Set-Score:") + 10));

                // Create Player 1 object and add it to the vector
                Player *player1 = new Player(playerName, hitTypes, playerScore, gameScore, setScore);
                loadedPlayers.push_back(player1);
            }

            // Player 2 data
            if (line.find("Player 2:") != string::npos) {
                string playerName;
                vector<vector<double>> hitTypes;
                vector<double> forehand, backhand, slice;
                int playerScore = 0, gameScore = 0, setScore = 0;

                // Get Player 2's name
                getline(file, line);
                playerName = line.substr(line.find("Name:") + 5);
                playerName = playerName.substr(playerName.find_first_not_of(" "));  // Trim leading spaces

                // Parse the hit types for Player 2
                getline(file, line);
                forehand = parseHitTypes(line.substr(line.find("Hit-Types(FH):") + 14));

                getline(file, line);
                backhand = parseHitTypes(line.substr(line.find("Hit-Types(BH):") + 14));

                getline(file, line);
                slice = parseHitTypes(line.substr(line.find("Hit-Types(SL):") + 14));

                hitTypes.push_back(forehand);
                hitTypes.push_back(backhand);
                hitTypes.push_back(slice);

                // Parse Player 2's scores
                getline(file, line);
                playerScore = stoi(line.substr(line.find("Player-Score:") + 13));

                getline(file, line);
                gameScore = stoi(line.substr(line.find("Game-Score:") + 11));

                getline(file, line);
                setScore = stoi(line.substr(line.find("Set-Score:") + 10));

                // Create Player 2 object and add it to the vector
                Player *player2 = new Player(playerName, hitTypes, playerScore, gameScore, setScore);
                loadedPlayers.push_back(player2);
            }
        }

        PlayerOne.setPlayerOneHitValues(loadedPlayers.at(0)->hitTypes[0], loadedPlayers.at(0)->hitTypes[1], loadedPlayers.at(0)->hitTypes[2]);
        PlayerOne.setPlayerOneAVGs();
        PlayerTwo.setPlayerTwoHitValues(loadedPlayers.at(1)->hitTypes[0], loadedPlayers.at(1)->hitTypes[1], loadedPlayers.at(1)->hitTypes[2]);
        PlayerTwo.setPlayerTwoAVGs();

        noAdPlayLogic(loadedPlayers, turn);
    }

    cout << "\nNo saved games" << endl;
}

string TennisGame::saveGame(vector<Player *> playersToSave, int playerTurn) {
    string fileName, path;
    Player *p1, *p2;

    p1 = playersToSave.at(0);
    p2 = playersToSave.at(1);

    if (!fs::is_directory("savedGames") || !fs::exists("savedGames")) {
        fs::create_directory("savedGames");
    }

    cout << "Please name the file" << endl;
    cin >> fileName;
    path = "savedGames/" + fileName;
    ofstream outputFile((path).append(".txt"));

    outputFile << "Turn:" << playerTurn << endl;
    outputFile << "Player 1:" << endl;
    outputFile << "Name:" << p1->playerName << endl;
    outputFile << "Hit-Types(FH):";
    for (size_t i = 0; i < p1->hitTypes[0].size(); ++i) {
        outputFile << p1->hitTypes[0][i];
        if (i < p1->hitTypes[0].size() - 1) {
            outputFile << " ";
        }
    }
    outputFile << endl;

    outputFile << "Hit-Types(BH):";
    for (size_t i = 0; i < p1->hitTypes[1].size(); ++i) {
        outputFile << p1->hitTypes[1][i];
        if (i < p1->hitTypes[1].size() - 1) {
            outputFile << " ";
        }
    }
    outputFile << endl;

    outputFile << "Hit-Types(SL):";
    for (size_t i = 0; i < p1->hitTypes[2].size(); ++i) {
        outputFile << p1->hitTypes[2][i];
        if (i < p1->hitTypes[2].size() - 1) {
            outputFile << " ";
        }
    }
    outputFile << endl;

    outputFile << "Player-Score:" << p1->playerScore << endl;
    outputFile << "Game-Score:" << p1->gameScore << endl;
    outputFile << "Set-Score:" << p1->setScore << endl;
    outputFile << "Player 2:" << endl;
    outputFile << "Name:" << p2->playerName << endl;
    outputFile << "Hit-Types(FH):";
    for (size_t i = 0; i < p2->hitTypes[0].size(); ++i) {
        outputFile << p2->hitTypes[0][i];
        if (i < p2->hitTypes[0].size() - 1) {
            outputFile << " ";
        }
    }
    outputFile << endl;

    outputFile << "Hit-Types(BH):";
    for (size_t i = 0; i < p2->hitTypes[1].size(); ++i) {
        outputFile << p2->hitTypes[1][i];
        if (i < p2->hitTypes[1].size() - 1) {
            outputFile << " ";
        }
    }
    outputFile << endl;

    outputFile << "Hit-Types(SL):";
    for (size_t i = 0; i < p2->hitTypes[2].size(); ++i) {
        outputFile << p2->hitTypes[2][i];
        if (i < p2->hitTypes[2].size() - 1) {
            outputFile << " ";
        }
    }
    outputFile << endl;
    outputFile << "Player-Score:" << p2->playerScore << endl;
    outputFile << "Game-Score:" << p2->gameScore << endl;
    outputFile << "Set-Score:" << p2->setScore << endl;

    return "Successfully saved game";
}

void TennisGame::noAdPlayLogic(vector<Player *> players, int turn) {
    string option;
    bool result;
    int numRounds = 1;
    int originalTurn = turn;

    cout << "This is round number: " << numRounds << endl;

    while (players.at(0)->setScore <= 1 && players.at(1)->setScore <= 1) {
        if (turn % 2 != 0) {
            cout << "It is player 1 turn" << endl;
            option = PlayerOne.playerMenu();

            if (option == "SAVE") {
                saveGame(players, 1);
                break;
            }

            result = PlayerOne.getPlayerOneChoice(option);
            if (result == 1) {
                turn++;
                continue;
            } else if (result == 0) {
                cout << "Player 1 Missed" << endl;
                players.at(1)->playerScore++;
                cout << "Player 2 Score: " << players.at(1)->playerScore << endl;
                cout << "Player 2 Gamescore: " << players.at(1)->gameScore << endl;

                if (players.at(1)->playerScore > 3) {
                    originalTurn++;
                    players.at(1)->gameScore++;
                    cout << "Player 2 GameScore: " << players.at(1)->gameScore << endl;
                    players.at(1)->playerScore = 0;
                    players.at(0)->playerScore = 0;
                }
            }
        } else if (turn % 2 == 0) {
            cout << "It is player 2 turn" << endl;
            option = PlayerTwo.playerMenu();

            if (option == "SAVE") {
                saveGame(players, 0);
                break;
            }

            result = PlayerTwo.getPlayerTwoChoice(option);
            if (result) {
                turn++;
                continue;
            } else if (result == 0) {
                cout << "Player 2 Missed" << endl;
                players.at(0)->playerScore++;
                cout << "Player 1 Score: " << players.at(0)->playerScore << endl;
                cout << "Player 1 GameScore: " << players.at(0)->gameScore << endl;

                // can I add into this if statement the condition necesarry to make the game ad capable?
                if (players.at(0)->playerScore > 3) {
                    originalTurn++;
                    players.at(0)->gameScore++;
                    cout << "Player 1 GameScore: " << players.at(0)->gameScore << endl;
                    players.at(0)->playerScore = 0;
                    players.at(1)->playerScore = 0;
                }
            }
        } else {
        }

        if (players.at(0)->playerScore == 3 && players.at(1)->playerScore == 3) {
            cout << "DEUCE!" << endl;
        }

        if (players.at(1)->gameScore >= 2) {
            players.at(1)->setScore++;
            players.at(0)->gameScore = 0;
            players.at(1)->gameScore = 0;
            cout << "Player 2 SetScore: " << players.at(1)->setScore << endl;
        }

        if (players.at(0)->gameScore >= 2) {
            players.at(0)->setScore++;
            players.at(0)->gameScore = 0;
            players.at(1)->gameScore = 0;
            cout << "Player 2 SetScore: " << players.at(0)->setScore << endl;
        }
        turn = originalTurn;
        numRounds++;
    }

    cout << "Thank you for playing!" << endl;
}

void TennisGame::adPlayLogic(vector<Player *> players, int turn) {
}
// need to fix
void TennisGame::tieBreakerLogic(vector<Player *> players, int turn) {
    // int numRounds = 1;
    // int switchTurns = turn;

    // while (players.at(0)->playerScore < 10 && players.at(1)->playerScore < 10)
    // {
    //     cout << "This is round number: " << numRounds << endl;
    //     // condition to check if player game score exceeds 4 points
    //     if (turn % 2 != 0)
    //     {
    //         turn++;
    //         cout << "It is player 1 turn" << endl;
    //         int n = players.at(0)->option<int>();
    //         if (n == 1)
    //         {
    //             continue;
    //         }
    //         else
    //         {
    //             cout << "Player 1 Missed" << endl;
    //             players.at(1)->playerScore++;
    //             cout << "Player 2 Score: " << players.at(1)->playerScore << endl;
    //             // up player game score
    //         }
    //     }
    //     else if (turn % 2 == 0)
    //     {
    //         turn++;
    //         cout << "It is player 2 turn" << endl;
    //         int n = players.at(1)->option<int>();
    //         if (n == 1)
    //         {
    //             continue;
    //         }
    //         else
    //         {
    //             cout << "Player 2 Missed" << endl;
    //             players.at(0)->playerScore++;
    //             cout << "Player 1 Score: " << players.at(0)->playerScore << endl;
    //             // up player game score
    //         }
    //     }
    //     else
    //     {
    //     }

    //     numRounds++;
    //     switchTurns++;
    //     turn = switchTurns;
    // }

    // cout << "Player 1 Score: " << players.at(0)->playerScore++ << endl;
    // cout << "Player 2 Score: " << players.at(1)->playerScore++ << endl;
}
// need to change this
vector<double> TennisGame::parseHitTypes(const string &line) {
    vector<double> hitTypes;
    stringstream ss(line);
    double hitType;
    while (ss >> hitType) {
        hitTypes.push_back(hitType);
    }
    return hitTypes;
}

void TennisGame::createNewPlayer(string &newPlayer) {
    if (!fs::is_directory("settings") || !fs::exists("settings")) {
        fs::create_directory("settings");
        ofstream output("settings/players.txt");
        output << "Player Information:\n";
        output << newPlayer << "\n";
    } else {
        ofstream output("settings/players.txt", ios::app);
        output << newPlayer << "\n";
    }
}

void TennisGame::resetGameSettings() {
    fs::remove_all("settings");
    cout << "\nPlayer settings cleared" << endl;
}

void TennisGame::resetCache() {
    fs::remove_all("savedGames");
    cout << "\nSaved games cleared" << endl;
    fs::remove_all("settings");
    cout << "\nPlayer settings cleared" << endl;
}