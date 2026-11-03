#include "../game.h"
#include <iostream>
#include <string>
using namespace std;

// LEVEL 3: HASH MAP

void Game::setupHashTable() {
    for (int i = 0; i < 10; i++) {
        hashTable[i].occupied = false;
        hashTable[i].key = 0;
        hashTable[i].value = "";
    }

    insertHash(12, "Old Coin");
    insertHash(25, "Broken Glass");
    insertHash(17, "Cursed Ring");
    insertHash(27, "Royal Key");
    insertHash(48, "Empty Bottle");
}

int Game::hashFunction(int key) {
    return key % 10;
}

void Game::insertHash(int key, const char* value) {
    int index = hashFunction(key);

    // Linear probing handles collisions.
    while (hashTable[index].occupied) {
        index = (index + 1) % 10;
    }

    hashTable[index].key = key;
    hashTable[index].value = value;
    hashTable[index].occupied = true;
}

const char* Game::searchHash(int key) {
    int index = hashFunction(key);
    int attempts = 0;

    while (attempts < 10) {
        if (!hashTable[index].occupied) {
            return "NOT FOUND";
        }
        if (hashTable[index].key == key) {
            return hashTable[index].value;
        }

        // Check the next position after a collision.
        index = (index + 1) % 10;
        attempts++;
    }
    return "NOT FOUND";
}
// Level 3
bool Game::playHashMap() {
    cout << "\nLEVEL 3: THE LOCKED GATE\n";
    cout << "DATA STRUCTURE: HASH TABLE\n\n";

        cout << "The knight has reached another section of the castle.\n";
        cout << "A locked gate blocks the path to the princess.\n";
        cout << "You must find the Royal Key using the castle's hash table.\n";

        char castle[7][18] = {
            "#################",
            "#K....#.........#",
            "#.....#.........#",
            "#.....C.........#",
            "#.....#.........#",
            "#.............E.#",
            "#################"
        };

        int knightRow = 1;
        int knightColumn = 1;
        bool hasKey = false;
        bool consoleCompleted = false;
        bool escaped = false;

        setupHashTable();

        while (!gameOver && !escaped) {
            cout << "\nCASTLE MAP\n";

            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 17; j++) {
                    if (i == knightRow && j == knightColumn) {
                        cout << "K ";
                    } else {
                        cout << castle[i][j] << " ";
                    }
                }
                cout << "\n";
            }

            cout << "\nK = Knight\n";
            cout << "C = Security Console\n";
            cout << "E = Locked Exit\n";
            cout << "# = Wall\n";

            if (hasKey) {
                cout << "\nRoyal Key found! Reach the exit.\n";
            }

            cout << "\nMove with W, A, S, D. H = Hint. Q = Quit.\n";
            cout << "Your move: ";

            char move;
            cin >> move;

            if (move == 'Q' || move == 'q') {
                askForHelp(move);
                return false;
            }

            if (move == 'H' || move == 'h') {
                askForHelp(move);
                cout << "Find the security console marked C.\n";
                cout << "You must solve its hash table challenges.\n";
                continue;
            }

            int newRow = knightRow;
            int newColumn = knightColumn;

            if (move == 'W' || move == 'w') {
                newRow--;
            } else if (move == 'S' || move == 's') {
                newRow++;
            } else if (move == 'A' || move == 'a') {
                newColumn--;
            } else if (move == 'D' || move == 'd') {
                newColumn++;
            } else {
                cout << "Invalid movement.\n";
                continue;
            }

            if (castle[newRow][newColumn] == '#') {
                cout << "A wall blocks your path!\n";
                continue;
            }

            // Reach the security console
            if (castle[newRow][newColumn] == 'C') {
                if (consoleCompleted) {
                    knightRow = newRow;
                    knightColumn = newColumn;
                    continue;
                }

                cout << "\nYou reached the security console!\n";
                cout << "The hash table controls the locked gate.\n";
                cout << "Our hash function is: key % 10\n";

                // DISPLAY THE INITIAL HASH TABLE
                cout << "\nCURRENT HASH TABLE\n";

                for (int i = 0; i < 10; i++) {
                    cout << "[" << i << "] ";

                    if (hashTable[i].occupied) {
                        cout << hashTable[i].key << ": "
                             << hashTable[i].value;
                    } else {
                        cout << "EMPTY";
                    }

                    cout << "\n";
                }

    // CHALLENGE 1: CALCULATE THE HASH
    cout << "CHALLENGE 1: FIND THE STARTING SLOT\n";

                char answer = ' ';
    cout << "The Royal Key has key 37.\n";
    cout << "Calculate: 37 % 10\n";
    cout << "Which index should we check first?\n";

    while (!gameOver && answer != '7') {
        cout << "Enter the index (H for hint): ";
        cin >> answer;

        if (answer == 'H' || answer == 'h') {
            askForHelp(answer);
            cout << "37 % 10 = 7.\n";
        } else if (answer == 'Q' || answer == 'q') {
            askForHelp(answer);
            return false;
        } else if (answer != '7') {
            cout << "Incorrect. Find the remainder when 37 is divided by 10.\n";
        }
    }
                if (gameOver) {
                    return false;
                }

                cout << "Correct! The search begins at index 7.\n";
                score += 5;

    // CHALLENGE 2: RESOLVE COLLISIONS
    cout << "CHALLENGE 2: RESOLVE THE COLLISION\n";

    cout << "We want to insert key 37: Royal Key.\n";
    cout << "Its calculated index is 7.\n";
    cout << "But index 7 already contains key 17: Cursed Ring!\n";
    cout << "This is called a COLLISION.\n";
    cout << "Linear probing checks the next index until it finds an empty slot.\n";

    int current = hashFunction(37);

    while (!gameOver && hashTable[current].occupied) {
        cout << "\nThe current slot is [" << current << "].\n";
        cout << "It contains " << hashTable[current].key
             << ": " << hashTable[current].value << ".\n";

        int nextIndex = (current + 1) % 10;
        bool choseCorrectIndex = false;
        int collisionTries = 0;

        while (!gameOver && !choseCorrectIndex && collisionTries < 3) {
            cout << "Which index should we check next? ";
            cout << "(H for hint, Q to quit): ";
            cin >> answer;

            if (answer == 'H' || answer == 'h') {
                askForHelp(answer);
                cout << "Linear probing moves one slot to the right.\n";
                cout << "After index " << current
                     << ", check index " << nextIndex << ".\n";
                continue;
            }

            if (answer == 'Q' || answer == 'q') {
                askForHelp(answer);
                return false;
            }

            if (answer >= '0' && answer <= '9'
                && answer - '0' == nextIndex) {
                cout << "Correct! Check index " << nextIndex << ".\n";
                current = nextIndex;
                choseCorrectIndex = true;
            } else {
                cout << "Not quite. Linear probing checks the next slot.\n";
                collisionTries++;
            }
        }

        if (!choseCorrectIndex) {
            cout << "You ran out of tries. Review linear probing and try again.\n";
            return false;
        }

        if (hashTable[current].occupied) {
            cout << "Index " << current << " is also occupied!\n";
            cout << "You must keep probing.\n";
        } else {
            cout << "Index " << current << " is EMPTY!\n";
            cout << "We found a place for the Royal Key.\n";
        }
    }

    if (gameOver) {
        return false;
    }

    insertHash(37, "Royal Key");
    score += 10;

    cout << "\nThe Royal Key has been inserted into index "
         << current << ".\n";
    cout << "Notice that it was stored at index " << current
         << ", not its original hash index 7.\n";

    cout << "\nUPDATED HASH TABLE\n";

    for (int i = 0; i < 10; i++) {
        cout << "[" << i << "] ";

        if (hashTable[i].occupied) {
            cout << hashTable[i].key << ": "
                 << hashTable[i].value;
        } else {
            cout << "EMPTY";
        }

        cout << "\n";
    }

    // CHALLENGE 3: SEARCH THE TABLE
    cout << "CHALLENGE 3: FIND THE ROYAL KEY\n";

    cout << "Now imagine someone asks the hash table to find key 37.\n";
    cout << "The search calculates 37 % 10 = 7.\n";
    cout << "Where should the search begin?\n";
                answer = ' ';

                while (!gameOver && answer != '7') {
                    cout << "Where should the search begin? ";
                    cout << "(H for hint): ";
                    cin >> answer;

                    if (answer == 'H' || answer == 'h') {
                        askForHelp(answer);
                        cout << "The starting index is 7.\n";
                    } else if (answer == 'Q' || answer == 'q') {
                        askForHelp(answer);
                        return false;
                    } else if (answer != '7') {
                        cout << "Incorrect. Calculate 37 % 10.\n";
                    }
                }

                if (gameOver) {
                    return false;
                }

                cout << "Correct! The search begins at index 7.\n";
                score += 5;

                //Search
    cout << "\nSEARCH VISUALIZATION\n";

    int searchIndex = hashFunction(37);
    bool found = false;

    for (int i = 0; i < 10 && !found; i++) {
        cout << "Checking index [" << searchIndex << "]: ";

        if (!hashTable[searchIndex].occupied) {
            cout << "EMPTY. The search stops here.\n";
            break;
        }

        cout << hashTable[searchIndex].key
             << ": " << hashTable[searchIndex].value << "\n";

        if (hashTable[searchIndex].key == 37) {
            found = true;
            cout << "MATCH! The Royal Key has been found.\n";
        } else {
            cout << "Not the key. Checking the next index.\n";
            searchIndex = (searchIndex + 1) % 10;
        }
    }

                if (gameOver) {
                    return false;
                }

                if (found) {
                    cout << "\nThe security console accepts the Royal Key!\n";
                    cout << "The locked gate is now open.\n";
                    hasKey = true;
                    consoleCompleted = true;
                    castle[3][6] = '.';
                    score += 10;
                }
            }

            // REACH THE EXIT
            else if (castle[newRow][newColumn] == 'E') {
                if (!hasKey) {
                    cout << "The gate is still locked!\n";
                    cout << "You must find the Royal Key first.\n";
                    continue;
                }

                knightRow = newRow;
                knightColumn = newColumn;

                cout << "\nThe Royal Key unlocks the gate!\n";
                cout << "You escaped the castle. Level 3 complete!\n";
                cout << "You learned hashing, collisions, linear probing, and searching.\n";

                escaped = true;
            } else {
                knightRow = newRow;
                knightColumn = newColumn;
            }
        }

        if (gameOver) {
            return false;
        }

        return escaped;
    }