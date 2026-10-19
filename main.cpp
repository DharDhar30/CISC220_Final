
#include <iostream>
#include "game.h"

using namespace std;

int main() {
    Game game;

    cout << "========================================\n";
    cout << "           THE KNIGHT'S QUEST\n";
    cout << "========================================\n\n";

    cout << "The princess has been trapped in a castle!\n";
    cout << "To rescue her, you must complete six challenges.\n\n";

    cout << "Along the way, you will learn how data structures work.\n";
    cout << "Pay attention to the lessons because each level\n";
    cout << "will test what you have learned.\n\n";

    cout << "YOUR SIX CHALLENGES\n";
    cout << "1. Broken Maze: 2D grids and coordinates\n";
    cout << "2. Tower of Trials: stacks and LIFO\n";
    cout << "3. Locked Gate: hash maps and key-value pairs\n";
    cout << "4. Broken River: linked lists and pointers\n";
    cout << "5. Cursed Forest: graphs and shortest paths\n";
    cout << "6. Princess's Castle: binary search trees\n\n";

    cout << "GAME CONTROLS\n";
    cout << "H = Ask the Royal Guide for a hint\n";
    cout << "Q = Quit the game\n\n";

    cout << "You begin with 3 lives.\n";
    cout << "Correct answers earn points.\n";
    cout << "Each level teaches a data structure before testing you.\n\n";

    cout << "Good luck, knight!\n\n";

    game.play();

    cout << "\nThanks for playing The Knight's Quest!\n";

    return 0;
}
