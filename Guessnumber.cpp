#include <iostream>
#include <unordered_map>
using namespace std;

class Player {
public:
    string username;
    string password;
    int wins = 0;
    int attempts = 0;

    // Default constructor
    Player() {}

    // Parameterized constructor
    Player(string u, string p) : username(u), password(p) {}

    void incrementAttempts() { attempts++; }
    void incrementWins() { wins++; }
    void resetAttempts() { attempts = 0; }
};

class Game {
private:
    unordered_map<string, Player> players;
    Player* currentPlayer = nullptr;

public:
    Game() {}

    void signUp() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // Check if the username already exists
        if (players.find(username) != players.end()) {
            cout << "Username already exists. Try again with a different one." << endl;
            return;
        }

        players[username] = Player(username, password);
        cout << "Account created successfully!" << endl;
    }

    bool signIn() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (players.find(username) != players.end() && players[username].password == password) {
            currentPlayer = &players[username];
            cout << "Welcome back, " << username << "!" << endl;
            return true;
        }

        cout << "Invalid username or password." << endl;
        return false;
    }

    void startGame() {
        if (!currentPlayer) {
            cout << "Please sign in first!" << endl;
            return;
        }

        int secretNumber = rand() % 100 + 1;  // Generate random number between 1 and 100
        int guess;
        currentPlayer->resetAttempts();
        cout << "Guess the number between 1 and 100!" << endl;

        while (true) {
            cout << "Enter your guess: ";
            cin >> guess;
            currentPlayer->incrementAttempts();

            if (guess < secretNumber) {
                cout << "Too low!" << endl;
            }
            else if (guess > secretNumber) {
                cout << "Too high!" << endl;
            }
            else {
                cout << "Correct! You guessed the number in " << currentPlayer->attempts << " attempts." << endl;
                currentPlayer->incrementWins();
                break;
            }

            if (abs(secretNumber - guess) <= 10) {
                cout << "You're close!" << endl;
            }
        }
    }

    void showStats() {
        if (currentPlayer) {
            cout << "Player: " << currentPlayer->username << " - Wins: " << currentPlayer->wins << ", Attempts: " << currentPlayer->attempts << endl;
        }
        else {
            cout << "Please sign in first!" << endl;
        }
    }

    void showLeaderboard() {
        cout << "Leaderboard:" << endl;
        // Simply show the player with the lowest number of attempts (i.e., fastest win)
        for (const auto& player : players) {
            cout << player.second.username << " - Wins: " << player.second.wins << " - Attempts: " << player.second.attempts << endl;
        }
    }
};

int main() {
    Game game;
    int choice;

    while (true) {
        cout << "\n1. Sign Up\n2. Sign In\n3. Start Game\n4. Show Stats\n5. Show Leaderboard\n6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            game.signUp();
            break;
        case 2:
            if (game.signIn()) {
                int gameChoice;
                while (true) {
                    cout << "\n1. Start Game\n2. Show Stats\n3. Show Leaderboard\n4. Logout\n";
                    cout << "Choose an option: ";
                    cin >> gameChoice;

                    if (gameChoice == 1) {
                        game.startGame();
                    }
                    else if (gameChoice == 2) {
                        game.showStats();
                    }
                    else if (gameChoice == 3) {
                        game.showLeaderboard();
                    }
                    else {
                        cout << "Logging out..." << endl;
                        break;
                    }
                }
            }
            break;
        case 3:
            cout << "Please sign in first to play the game." << endl;
            break;
        case 4:
            game.showStats();
            break;
        case 5:
            game.showLeaderboard();
            break;
        case 6:
            cout << "Exiting game." << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
