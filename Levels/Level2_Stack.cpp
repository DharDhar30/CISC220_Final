#include "../game.h"
#include <iostream>
#include <string>
using namespace std;

// LEVEL 2: STACK
bool Game::playStack(){
       cout << "\nLEVEL 2: The tower of trials!!! z\n";

        cout << "The tower is collapsing! Retrieve the key safely.\n";
        cout << "Find the Royal Key and escape before the tower falls.\n";
        cout << "Explore using WASD and collect items along the way.\n";

        cout << "GET READY FOR A QUICK LESSON :D";
        cout << "A stack follows LIFO: Last In, First Out.\n";
        cout << "You can only access the TOP item.\n";
        cout << "Your inventory is stored in an array of 5 spaces.\n";

        cout << "\nCONTROLS\n";
        cout << "W = Move up\n";
        cout << "A = Move left\n";
        cout << "S = Move down\n";
        cout << "D = Move right\n";
        cout << "P = Pop the top item\n";
        cout << "H = Hint\n";
        cout << "Q = Quit\n";

        cout << "\nMAP SYMBOLS\n";
        cout << "K = Knight\n";
        cout << "S = Shield\n";
        cout << "P = Potion\n";
        cout << "G = Guard\n";
        cout << "R = Royal Key\n";
        cout << "E = Exit\n";
        cout << "# = Wall\n";

        // TOWER MAP
        char tower[7][16] = {
            "###############",
            "#...S....#...E#",
            "#.......#.....#",
            "#.......G.....#",
            "#.......#.....#",
            "#...P...#..R..#",
            "###############"
        };

        int knightRow = 1;
        int knightColumn = 1;

    //Inventory
    int items[5];
    int top = -1;

        bool pushChallengeDone = false;
        bool guardChallengeDone = false;
        bool exitChallengeDone = false;

        bool guardDefeated = false;
        bool hasKey = false;
        bool escaped = false;

    while (!gameOver && !escaped) {
        cout << "          THE TOWER MAP\n";

        for (int r = 0; r < 7; r++) {
            for (int c = 0; c < 15; c++) {

                if (r == knightRow && c == knightColumn) {
                    cout << "K ";
                } else {
                    cout << tower[r][c] << " ";
                }
            }

            cout << "\n";
        }


        //Display the inventory
        cout << "             INVENTORY\n";

        if (top == -1) {
            cout << "[ EMPTY ]\n";
        } else {
            for (int i = top; i >= 0; i--) {
                cout << "| ";
                if (items[i] == 1) {
                    cout << "Shield";
                } else if (items[i] == 2) {
                    cout << "Royal Key";
                } else if (items[i] == 4) {
                    cout << "Potion";
                }
                cout << " | Index " << i << "\n";
            }

            cout << "       ---------";
            cout << "       BOTTOM\n";
        }

        cout << "\nTop index: " << top << "\n";
        cout << "Inventory spaces: " << top + 1 << "/5\n";
        cout << "\nMove (W/A/S/D), P to pop, H for hint, Q to quit: ";

        char choice;
        cin >> choice;

        if (choice == 'H' || choice == 'h') {
            askForHelp(choice);
            cout << "Hint: The last item pushed is the first item popped.\n";
            continue;
        }
        if (choice == 'Q' || choice == 'q') {
            askForHelp(choice);
            return false;
        }


        // MANUAL POP
        if (choice == 'P' || choice == 'p') {
            if (top == -1) {
                cout << "\nYour inventory is empty!\n";
                cout << "There is nothing to remove.\n";
                continue;
            }

            cout << "\nPOP CHALLENGE\n";
            cout << "Which expression removes the top item?\n\n";

            cout << "1. items[top--]\n";
            cout << "2. items[++top]\n";
            cout << "3. items[top]\n";

            int answer = 0;

            while (answer != 1) {
                cout << "Your answer: ";
                cin >> answer;

                if (answer != 1) {
                    cout << "Not quite! Try again.\n";
                    cout << "Hint: You need to retrieve the item and decrease top.\n";
                }

            } while (answer != 1);

            int item = items[top--];

            cout << "\nCorrect!\n";
            cout << "You used: items[top--];\n";
            cout << "The item was removed from the stack.\n";
            cout << "The new top index is " << top << ".\n";

            if (item == 1) {
                cout << "You removed the Shield.\n";
            } else if (item == 2) {
                cout << "You removed the Royal Key.\n";
                hasKey = true;
            } else if (item == 4) {
                cout << "You removed the Potion.\n";
            }

            continue;
        }

        // MOVEMENT
        int newRow = knightRow;
        int newColumn = knightColumn;

        if (choice == 'W' || choice == 'w') {
            newRow--;
        } else if (choice == 'S' || choice == 's') {
            newRow++;
        } else if (choice == 'A' || choice == 'a') {
            newColumn--;
        } else if (choice == 'D' || choice == 'd') {
            newColumn++;
        } else {
            cout << "Invalid movement!\n";
            continue;
        }

        //If a wall block you
        if (tower[newRow][newColumn] == '#') {
            cout << "\nA wall blocks your path!\n";
            continue;
        }
        char nextCell = tower[newRow][newColumn];

        //Collect items
        if (nextCell == 'S' || nextCell == 'P' || nextCell == 'R') {
            if (top == 4) {
                cout << "\nYour inventory is full!\n";
                cout << "Remove an item before collecting another.\n";
                continue;
            }

            int item;

            if (nextCell == 'S') {
                item = 1;
                cout << "\nYou found a SHIELD!\n";
            } else if (nextCell == 'P') {
                item = 4;
                cout << "\nYou found a POTION!\n";
            } else {
                item = 2;
                cout << "\nYOU FOUND THE ROYAL KEY!\n";
            }

            // Push challenge
            if (!pushChallengeDone) {
                cout << "       CODING CHALLENGE: PUSH\n";

                cout << "You need to add this item to your inventory.\n";
                cout << "Complete the missing expression:\n\n";

                cout << "items[________] = item;\n\n";

                cout << "1. ++top\n";
                cout << "2. top--\n";
                cout << "3. top + 1\n";

                int answer = 0;

                while (answer != 1) {
                    cout << "Your answer: ";
                    cin >> answer;

                    if (answer != 1) {
                        cout << "Incorrect! Try again.\n";
                        cout << "Hint: Increase top before storing the item.\n";
                    }

                } while (answer != 1);

                cout << "\nCorrect!\n";
                cout << "items[++top] = item;\n";
                cout << "You understand how PUSH works! YIPPEEE!\n";

                pushChallengeDone = true;
                score += 5;
                cout << "You earned 5 points!\n";
            }

            // Pushing
            items[++top] = item;

            cout << "\nPUSH SUCCESSFUL!\n";
            cout << "Item added at index " << top << ".\n";
            cout << "The top index is now " << top << ".\n";

            tower[newRow][newColumn] = '.';
        }

        // Guard
        if (nextCell == 'G' && !guardDefeated) {

            cout << "             GUARD!\n";

            cout << "A guard blocks the only passage!\n";
            cout << "You must use an item from your stack to get past.\n";

            //Guard challenge
            if (!guardChallengeDone) {

                cout << "\nCODING CHALLENGE: ACCESS THE TOP\n";
                cout << "Before removing an item, we need to check\n";
                cout << "that the stack is not empty.\n\n";

                cout << "Which condition checks for an empty stack?\n\n";

                cout << "1. top == -1\n";
                cout << "2. top == 5\n";
                cout << "3. top == 0\n";

                int answer = 0;
                while (answer != 1) {
                    cout << "Your answer: ";
                    cin >> answer;


                    if (answer != 1) {
                        cout << "Incorrect! Try again.\n";
                        cout << "Hint: An empty stack starts with top = -1.\n";
                    }

                } while (answer != 1);
                cout << "\nCorrect!\n";
                cout << "if (top == -1)\n";
                cout << "This prevents removing an item from an empty stack.\n";

                guardChallengeDone = true;
                score += 5;
                cout << "You earned 5 points!\n";
            }

            if (top == -1) {
                cout << "\nYour stack is empty!\n";
                cout << "Find an item before challenging the guard.\n";
                continue;
            }

            cout << "\nThe guard demands an item!\n";
            cout << "You must sacrifice the TOP item in your stack.\n";

            int sacrificedItem = items[top--];

            cout << "\nPOP: items[top--];\n";
            cout << "You sacrificed the top item.\n";
            cout << "The new top index is " << top << ".\n";

            if (sacrificedItem == 1) {
                cout << "The guard takes your Shield!\n";
            } else if (sacrificedItem == 4) {
                cout << "The guard takes your Potion!\n";
            }

            cout << "\nThe guard steps aside!\n";
            guardDefeated = true;
            tower[newRow][newColumn] = '.';
        }

        // Exit
        if (nextCell == 'E') {

            cout << "             LOCKED EXIT\n";

            cout << "The tower exit is locked!\n";
            cout << "You need the Royal Key at the TOP of your stack.\n";

            if (!exitChallengeDone) {

                cout << "\nFINAL CODING CHALLENGE\n";
                cout << "Which expression checks whether the top item\n";
                cout << "is the Royal Key?\n\n";

                cout << "1. items[top] == 2\n";
                cout << "2. items[0] == 2\n";
                cout << "3. top == 2\n";

                int answer = 0;
                while (answer != 1) {
                    cout << "Your answer: ";
                    cin >> answer;


                    if (answer != 1) {
                        cout << "Incorrect! Try again.\n";
                        cout << "Hint: Access the item using its top index.\n";
                    }

                } while (answer != 1);

                cout << "\nCorrect!\n";
                cout << "items[top] == 2\n";
                cout << "You can now check the item at the top of the stack.\n";

                exitChallengeDone = true;
                score += 5;
                cout << "You earned 5 points!\n";
            }

            if (top == -1 || items[top] != 2) {
                cout << "\nThe Royal Key is not at the top!\n";
                cout << "Find it before you can unlock the exit.\n";
                continue;
            }

            cout << "\nThe Royal Key is at the top of your stack!\n";
            cout << "Removing it now..\n";

            int key = items[top--];
            if (key == 2) {
                hasKey = true;
                cout << "You used the Royal Key!\n";
            }

            if (hasKey) {
                cout << "          TOWER ESCAPED!\n";

                cout << "You escaped the collapsing tower!\n";
                escaped = true;
            }

            continue;
        }

        // MOVE THE KNIGHT
        knightRow = newRow;
        knightColumn = newColumn;

        cout << "\nYou moved to row " << knightRow;
        cout << ", column " << knightColumn << ".\n";
    }

    if (gameOver) {
        return false;
    }
    return escaped;
}
