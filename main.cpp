
#include <iostream>
#include "game.h"

using namespace std;

int main() {
    cout << "         THE KNIGHT'S QUEST\n";

    cout << "1. Play the full game\n";
    cout << "2. Test an individual level\n";
    cout << "3. Quit\n";

    int choice;
    cin >> choice;

    if (choice == 1) {
        Game game;
        game.play();
    } else if (choice == 2) {
        int levelChoice;

        while (true) {
            cout << "1. The Broken Maze\n";
            cout << "2. The Tower of Trials\n";
            cout << "3. The Locked Gate\n";
            cout << "4. The Broken River\n";
            cout << "5. The Cursed Forest\n";
            cout << "6. The Princess's Castle\n";
            cout << "0. Return to quit\n";
            cout << "\nChoose a level: ";

            cin >> levelChoice;

            if (levelChoice == 0) {
                break;
            }

            if (levelChoice < 1 || levelChoice > 6) {
                cout << "Choose a number from 1 to 6, or 0 to quit.\n";
                continue;
            }

            Game game;
            game.playTestLevel(levelChoice);
        }
    } else if (choice == 3) {
        cout << "Goodbye!\n";
    } else {
        cout << "Invalid option.\n";
    }

    return 0;
}
