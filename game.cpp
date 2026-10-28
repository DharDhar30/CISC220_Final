#include <iostream>
#include "game.h"

using namespace std;

Game::Game() {
    lives = 3;
    score = 0;
    level = 1;
    gameOver = false;
    knightRow = 1;
    knightColumn = 1;

    // "#" means wall "." means open path, E means exit.
    const char* rows[7] = {
        "#########",
        "#.......#",
        "#.###...#",
        "#...#...#",
        "###.#.###",
        "#.......#",
        "#########"
    };

    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 9; c++) {
            maze[r][c] = rows[r][c];
        }
    }

    maze[5][7] = 'E';
    setupHashTable();
}
void Game::showStatus() {
    cout << "\n-----------------------------\n";
    cout << "Level: " << level << " / 6\n";
    cout << "Lives: " << lives << "\n";
    cout << "Score: " << score << "\n";
    cout << "-----------------------------\n";
}

void Game::giveHint() {
    cout << "\nROYAL GUIDE: ";

    if (level == 1) {
        cout << "A 2D array uses rows and columns. ";
        cout << "Moving left or right changes the column.\n";
    } else if (level == 2) {
        cout << "A stack follows LIFO: Last In, First Out. ";
        cout << "Only the top item can be removed.\n";
    } else if (level == 3) {
        cout << "A hash function turns a key into an array index. ";
        cout << "Search for an item using its key.\n";
    } else if (level == 4) {
        cout << "Each linked-list node points to the next node. ";
        cout << "Follow the next pointer.\n";
    } else if (level == 5) {
        cout << "A graph has vertices and weighted edges. ";
        cout << "Add the costs of every edge in a route.\n";
    } else if (level == 6) {
        cout << "In a binary search tree, smaller values go left ";
        cout << "and larger values go right.\n";
    }

    if (score >= 2) {
        score -= 2;
        cout << "The hint costs 2 points.\n";
    } else {
        cout << "This hint is free because you have fewer than 2 points.\n";
    }
}

bool Game::askForHelp(char choice) {
    if (choice == 'H' || choice == 'h') {
        giveHint();
        return true;
    }

    if (choice == 'Q' || choice == 'q') {
        gameOver = true;
        cout << "\nYou chose to leave the quest.\n";
        return true;
    }

    return false;
}

bool Game::loseLife() {
    lives--;

    cout << "\nYou lost a life!\n";
    cout << "Lives remaining: " << lives << "\n";

    if (lives <= 0) {
        cout << "You ran out of lives. Try this level again!\n";
        lives = 3;

        knightRow = 1;
        knightColumn = 1;

        return true;
    }

    return false;
}

void Game::play() {
    while (level <= 6 && !gameOver) {
        showStatus();

        bool completed = false;

        if (level == 1) {
            completed = playMaze();
        } else if (level == 2) {
            completed = playStack();
        } else if (level == 3) {
            completed = playHashMap();
        } else if (level == 4) {
            completed = playLinkedList();
        } else if (level == 5) {
            completed = playGraph();
        } else if (level == 6) {
            completed = playTree();
        }

        if (gameOver) {
        }

        if (completed) {
            score += 10;

            cout << "\nLevel complete! You earned 10 points.\n";
            level++;
        }
    }

    if (level > 6 && !gameOver) {
        cout << "           QUEST COMPLETE!\n";
        cout << "You found the princess and saved the kingdom!\n";
        cout << "Final score: " << score << "\n";
    }
}
void Game::playTestLevel(int selectedLevel) {
    bool completed = false;
    gameOver = false;
    cout << "\nTEST MODE: Starting Level "
         << selectedLevel << "\n";
    if (selectedLevel == 1) {
        completed = playMaze();
    } else if (selectedLevel == 2) {
        completed = playStack();
    } else if (selectedLevel == 3) {
        completed = playHashMap();
    } else if (selectedLevel == 4) {
        completed = playLinkedList();
    } else if (selectedLevel == 5) {
        completed = playGraph();
    } else if (selectedLevel == 6) {
        completed = playTree();
    } else {
        cout << "Invalid level number.\n";
        return;
    }
    if (completed) {
        cout << "\nTEST RESULT: Level completed!\n";
    } else {
        cout << "\nTEST RESULT: Level ended without completion.\n";
    }
}

 // LEVEL 1- TWO-DIMENSIONAL ARRAY
bool Game::playMaze() {
    cout << "       LEVEL 1: THE BROKEN MAZE\n";

    cout << "LEARN: TWO-DIMENSIONAL ARRAYS\n\n";

    cout << "A 2D array stores information in rows and columns.\n";
    cout << "Our maze is stored in maze[7][9].\n";
    cout << "That means 7 rows and 9 columns.\n\n";

    cout << "Each cell has two indexes:\n";
    cout << "maze[row][column]\n\n";

    cout << "Remember:\n";
    cout << "- The first index identifies the row.\n";
    cout << "- The second index identifies the column.\n";
    cout << "- Array indexes start at 0, not 1.\n\n";

    cout << "For example, maze[1][2] means row 1, column 2.\n";
    cout << "The character stored there tells us what is in that cell.\n\n";

    cout << "KNOWLEDGE CHECK\n";
    cout << "What does maze[2][4] represent?\n";
    cout << "1. Row 4, column 2\n";
    cout << "2. Row 2, column 4\n";
    cout << "3. The fourth row and fifth column\n";
    cout << "Answer: ";

    int answer;
    cin >> answer;

    if (answer == 2) {
        cout << "\nCorrect! The first index is the row, ";
        cout << "and the second index is the column.\n";
        score += 5;
        cout << "You earned 5 points!\n";
    } else {
        cout << "\nNot quite. The correct answer is 2.\n";
        cout << "maze[2][4] means row 2, column 4.\n";
        cout << "Both indexes start counting at 0.\n";
    }

    cout << "\nYOUR MISSION\n";
    cout << "Guide K to the exit E without walking into walls.\n";
    cout << "Every move checks a specific position in the array.\n";
    cout << "W = up, A = left, S = down, D = right.\n";
    cout << "H = hint, Q = quit.\n";

    while (!gameOver) {
        cout << "\n";
        cout << "      COLUMNS\n";
        cout << "      0 1 2 3 4 5 6 7 8\n";
        for (int r = 0; r < 7; r++) {
            cout << "ROW " << r << "  ";

            for (int c = 0; c < 9; c++) {
                if (r == knightRow && c == knightColumn) {
                    cout << "K ";
                } else {
                    cout << maze[r][c] << " ";
                }
            }

            cout << "\n";
        }

        cout << "\nYour current position:\n";
        cout << "Row = " << knightRow << "\n";
        cout << "Column = " << knightColumn << "\n";
        cout << "Current cell: maze[" << knightRow;
        cout << "][" << knightColumn << "]\n";
        cout << "\nMove (W/A/S/D), H for hint, Q to quit: ";

        char move;
        cin >> move;

        if (askForHelp(move)) {
            if (gameOver) {
                return false;
            }

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
            cout << "Invalid input. Use W, A, S, D, H, or Q.\n";
            continue;
        }

        cout << "\nARRAY LESSON\n";
        cout << "Your move checks maze[" << newRow;
        cout << "][" << newColumn << "].\n";

        if (newRow < 0 || newRow >= 7 ||
            newColumn < 0 || newColumn >= 9) {
            cout << "This position is outside the array boundaries.\n";
            cout << "Valid row indexes are 0 through 6.\n";
            cout << "Valid column indexes are 0 through 8.\n";
            loseLife();
            continue;
        }

        cout << "The character at this position is: ";
        cout << maze[newRow][newColumn] << "\n";

        if (maze[newRow][newColumn] == '#') {
            cout << "This cell contains a wall (#).\n";
            cout << "The knight cannot move into this array position.\n";
            loseLife();
            continue;
        }

        cout << "This cell is accessible, so the move is allowed.\n";

        knightRow = newRow;
        knightColumn = newColumn;

        cout << "Your new position is maze[" << knightRow;
        cout << "][" << knightColumn << "].\n";

        if (maze[knightRow][knightColumn] == 'E') {
            cout << "\nYou escaped the maze!\n";
            cout << "You used row and column indexes to navigate ";
            cout << "a two-dimensional array.\n";
            return true;
        }
    }
    return false;
}

// LEVEL 2: STACK
bool Game::playStack() {
       cout << "\nLEVEL 2: The tower of trials!!! z\n";
    cout << "The tower is collapsing! Retrieve the key safely.\n";
    cout << "You can only access the TOP of the stack.\n";
    cout << "Commands: S = push an item, P = pop, H = hint, Q = quit.\n\n";

    int items[5];
    int top = -1;
    bool hasKey = false;
    bool escaped = false;
    while (!gameOver && !escaped) {
        cout << "\nSTACK (TOP FIRST)\n";

        if (top == -1) {
            cout << "[ EMPTY ]\n";
        } else {
            for (int i = top; i >= 0; i--) {
                cout << "| ";

                if (items[i] == 1) cout << "Shield";
                else if (items[i] == 2) cout << "Royal Key";
                else if (items[i] == 3) cout << "Cursed Stone";
                else cout << "Potion";

                cout << " |\n";
            }
            cout << "---------";
        }
        cout << "\nItems available to collect:\n";
        cout << "1 = Shield\n";
        cout << "2 = Royal Key\n";
        cout << "3 = Cursed Stone\n";
        cout << "4 = Potion\n";
        cout << "Choose S, P, H, or Q: ";

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
        if (choice == 'S' || choice == 's') {
            if (top == 4) {
                cout << "Your stack is full!\n";
                continue;
            }
            cout << "Which item do you want to push? Enter 1-4: ";
            int item;
            cin >> item;
            if (item < 1 || item > 4) {
                cout << "That item does not exist.\n";
                continue;
            }

            if (item == 3) {
                cout << "You cannot collect the cursed stone. It is too dangerous!\n";
                continue;
            }

            items[++top] = item;
            cout << "PUSH: item added at index " << top << ".\n";
        } else if (choice == 'P' || choice == 'p') {
            if (top == -1) {
                cout << "The stack is empty. Nothing to pop!\n";
                continue;
            }

            int item = items[top--];

            if (item == 2) {
                hasKey = true;
                cout << "You retrieved the Royal Key!\n";
            } else if (item == 1) {
                cout << "You removed the Shield.\n";
            } else {
                cout << "You removed the Potion.\n";
            }
            cout << "POP: top index decreased to " << top << ".\n";

            if (hasKey) {
                cout << "\nYou unlock the tower exit and escape!\n";
                escaped = true;
            }
        } else {
            cout << "Invalid command.\n";
        }
    }
    if (gameOver) return false;
    return escaped;
}
// LEVEL 3: HASH MAP
int Game::hashFunction(int key) {
    return key % 10;
}

void Game::setupHashTable() {
    for (int i = 0; i < 10; i++) {
        hashTable[i].occupied = false;
        hashTable[i].key = 0;
        hashTable[i].value = "";
    }

    insertHash(12, "Old Coin");
    insertHash(25, "Broken Glass");
    insertHash(37, "Royal Key");
    insertHash(48, "Empty Bottle");
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

        index = (index + 1) % 10;
        attempts++;
    }

    return "NOT FOUND";
}



bool Game::playHashMap() {
    cout << "\nLEVEL 3: THE LOCKED GATE\n";
    cout << "DATA STRUCTURE: HASH TABLE\n\n";

    cout << "The castle gate is protected by a magical security system.\n";
    cout << "You must retrieve the Royal Key to open the gate.\n\n";

    cout << "A hash table uses a key to calculate where an item belongs.\n";
    cout << "Our hash function is: key % 10\n";
    cout << "If a slot is occupied, linear probing checks the next slot.\n";

    setupHashTable();

    bool correct = false;
    int tries = 0;
    char answer;

    // CHALLENGE 1: CALCULATE THE HASH
    cout << "CHALLENGE 1: FIND THE STARTING SLOT\n";

    cout << "The Royal Key has key 37.\n";
    cout << "Calculate: 37 % 10\n";
    cout << "Which index should we check first?\n";

    while (!gameOver && !correct && tries < 3) {
        cout << "Enter an index from 0 to 9 (H for hint, Q to quit): ";
        cin >> answer;

        if (answer == 'H' || answer == 'h') {
            askForHelp(answer);
            cout << "37 % 10 = 7. The search begins at index 7.\n";
            continue;
        }

        if (answer == 'Q' || answer == 'q') {
            askForHelp(answer);
            return false;
        }

        if (answer == '7') {
            cout << "\nCorrect! 37 % 10 = 7.\n";
            cout << "The hash function gives us index 7.\n";
            score += 5;
            correct = true;
        } else {
            cout << "Not quite. Divide 37 by 10 and find the remainder.\n";
            tries++;
        }
    }

    if (gameOver) {
        return false;
    }

    if (!correct) {
        cout << "You ran out of tries for this challenge.\n";
        return false;
    }

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

    correct = false;
    tries = 0;

    while (!gameOver && !correct && tries < 3) {
        cout << "Enter the starting index (H for hint, Q to quit): ";
        cin >> answer;

        if (answer == 'H' || answer == 'h') {
            askForHelp(answer);
            cout << "The hash function gives index 7.\n";
            continue;
        }

        if (answer == 'Q' || answer == 'q') {
            askForHelp(answer);
            return false;
        }

        if (answer == '7') {
            cout << "Correct! The search begins at index 7.\n";
            correct = true;
            score += 5;
        } else {
            cout << "Try again. Calculate 37 % 10.\n";
            tries++;
        }
    }

    if (gameOver) {
        return false;
    }

    if (!correct) {
        cout << "You ran out of tries for this challenge.\n";
        return false;
    }

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
            cout << "Not the key we need. Probe the next index.\n";
            searchIndex = (searchIndex + 1) % 10;
        }
    }

    if (found && searchHash(37) != 0) {
        cout << "\nThe gate recognizes the Royal Key!\n";
        cout << "The locked gate swings open. Level 3 complete!\n";
        cout << "You learned hashing, collisions, linear probing, and searching.\n";
        score += 10;
        return true;
    }

    cout << "The Royal Key could not be found. Try the level again.\n";
    return false;
}


bool Game::playLinkedList() {
    cout << "\nLEVEL 4: THE BROKEN RIVER\n";
    cout << "DATA STRUCTURE: SINGLY LINKED LIST\n\n";
    cout << "A flood has damaged the path across the river.\n";
    cout << "Your goal is to reach node 5 by following next pointers.\n";
    cout << "You must investigate the list before you can repair it.\n";

    ListNode* head = createList();

    // Break the link after node 4.
    ListNode* node = head;
    while (node != nullptr && node->data != 4) {
        node = node->next;
    }

    ListNode* detached = nullptr;

    if (node != nullptr) {
        detached = node->next;
        node->next = nullptr;
    }

    bool inspected = false;
    bool understood = false;
    bool repaired = false;
    bool crossed = false;

    while (!gameOver && !crossed) {
        cout << "\n--- THE RIVER CROSSING ---\n";
        cout << "1. Inspect node data and next pointers\n";
        cout << "2. Answer the pointer question\n";
        cout << "3. Repair a pointer\n";
        cout << "4. Attempt to cross the river\n";
        cout << "H. Hint\n";
        cout << "Q. Quit\n";
        cout << "Choice: ";

        char choice;
        cin >> choice;

        if (choice == 'H' || choice == 'h') {
            askForHelp(choice);
            cout << "\nHint: Start at head and follow each node's next pointer.\n";
            cout << "Look for the node where traversal stops unexpectedly.\n";

        } else if (choice == 'Q' || choice == 'q') {
            askForHelp(choice);
            gameOver = true;

        } else if (choice == '1') {
            inspected = true;

            cout << "\nPOINTER INSPECTION\n";
            cout << "The head pointer starts at node "
                 << (head != nullptr ? head->data : -1) << ".\n";

            ListNode* current = head;

            while (current != nullptr) {
                cout << "Node " << current->data << ": next = ";

                if (current->next != nullptr) {
                    cout << current->next->data;
                } else {
                    cout << "NULL";
                }

                cout << "\n";
                current = current->next;
            }

            current = detached;

            while (current != nullptr) {
                cout << "Disconnected node " << current->data
                     << ": next = ";

                if (current->next != nullptr) {
                    cout << current->next->data;
                } else {
                    cout << "NULL";
                }

                cout << "\n";
                current = current->next;
            }

            cout << "\nRemember: a node can exist without being reachable from head.\n";

        } else if (choice == '2') {
            if (!inspected) {
                cout << "Inspect the pointers first so you have evidence to use.\n";
            } else {
                cout << "\nQUESTION: Why does traversal stop at node 4?\n";
                cout << "1. Node 4 contains the wrong data\n";
                cout << "2. Node 4's next pointer is NULL\n";
                cout << "3. The head pointer must point to node 5\n";
                cout << "Answer: ";

                char answer;
                cin >> answer;

                if (answer == '2') {
                    understood = true;
                    cout << "\nCorrect!\n";
                    cout << "Traversal follows next pointers. When next is NULL,\n";
                    cout << "there is no next node to visit. Nodes beyond that\n";
                    cout << "point are not reachable from head.\n";
                } else {
                    cout << "\nNot quite. Trace the list starting from head.\n";
                    cout << "Which pointer tells traversal where to go next?\n";
                }
            }

        } else if (choice == '3') {
            if (!inspected || !understood) {
                cout << "Inspect the list and answer the pointer question first.\n";
            } else if (repaired) {
                cout << "The list is already repaired. Try crossing the river.\n";
            } else {
                cout << "\nYou may change one node's next pointer.\n";
                cout << "Which node's next pointer do you want to change? ";
                char source;
                cin >> source;

                cout << "What should that pointer point to? ";
                char target;
                cin >> target;

                if (source == '4' && target == '1' &&
                    node != nullptr && detached != nullptr) {

                    node->next = detached;
                    detached = nullptr;
                    repaired = true;

                    cout << "\nCorrect repair!\n";
                    cout << "Node 4 now points to node 1, making node 1\n";
                    cout << "and the nodes after it reachable from head.\n";
                    cout << "Now test your repair by traversing the list.\n";

                } else {
                    cout << "\nThat repair does not reconnect the missing path.\n";
                    cout << "Changing a pointer changes which node is reached next.\n";
                    cout << "Inspect the list again and reconsider your choice.\n";
                }
            }

        } else if (choice == '4') {
            cout << "\nFollowing next pointers: ";

            ListNode* current = head;
            bool reachedFive = false;

            while (current != nullptr && !reachedFive) {
                cout << current->data << " ";

                if (current->data == 5) {
                    reachedFive = true;
                } else {
                    current = current->next;
                }
            }

            if (reachedFive && repaired) {
                crossed = true;
                cout << "\n\nYou reached node 5 and crossed the river!\n";
                cout << "You learned that traversal can only reach nodes\n";
                cout << "connected through the chain of next pointers.\n";
                score += 10;
                cout << "You earned 10 learning points!\n";
            } else if (!repaired) {
                cout << "\n\nYou have not repaired the broken path yet.\n";
                cout << "Traversal cannot reach node 5 from head.\n";
            } else {
                cout << "\n\nThe path is incomplete. Inspect the list again.\n";
            }

        } else {
            cout << "Invalid choice. Select an available option.\n";
        }
    }
    deleteList(head);
    deleteList(detached);
    if (gameOver) {
        return false;
    }
    return crossed;
}
// LEVEL 5: GRAPH AND DIJKSTRA'S ALGORITHM

bool Game::playGraph(){
    cout << "\nLEVEL 5: THE CURSED FOREST\n";
    cout << "DATA STRUCTURE: GRAPH\n\n";

    cout << "A graph contains vertices and edges.\n";
    cout << "Vertices are locations. Edges are roads.\n";
    cout << "Each road has a travel cost.\n";
    cout << "Dijkstra's algorithm finds a shortest path by cost.\n\n";

    cout << "The forest has four locations: A, B, C, D.\n";
    cout << "Road costs:\n";
    cout << "A to B: 2\n";
    cout << "A to C: 5\n";
    cout << "B to C: 1\n";
    cout << "B to D: 5\n";
    cout << "C to D: 2\n\n";

    cout << "Knowledge check:\n";
    cout << "Which route is cheaper from A to D?\n";
    cout << "1. A -> B -> D, cost 7\n";
    cout << "2. A -> B -> C -> D, cost 5\n";
    cout << "Answer: ";

    int answer;
    cin >> answer;

    if (answer == 2) {
        cout << "Correct! The total cost is 2 + 1 + 2 = 5.\n";
        score += 5;
    } else {
        cout << "The second route costs 5, which is less than 7.\n";
    }

    // Adjacency matrix: 0 means no direct road.
    int graph[4][4] = {
        {0, 2, 5, 0},
        {2, 0, 1, 5},
        {5, 1, 0, 2},
        {0, 5, 2, 0}
    };

    int distance[4];
    bool visited[4];

    for (int i = 0; i < 4; i++) {
        distance[i] = 9999;
        visited[i] = false;
    }

    distance[0] = 0;

    cout << "\nRunning Dijkstra's algorithm from A...\n";

    for (int step = 0; step < 4; step++) {
        int nearest = -1;

        for (int i = 0; i < 4; i++) {
            if (!visited[i] &&
                (nearest == -1 || distance[i] < distance[nearest])) {
                nearest = i;
            }
        }

        if (nearest == -1 || distance[nearest] == 9999) {
            break;
        }

        visited[nearest] = true;
        cout << "Visit location " << char('A' + nearest);
        cout << ", current cost: " << distance[nearest] << "\n";

        for (int next = 0; next < 4; next++) {
            if (graph[nearest][next] > 0 &&
                distance[nearest] + graph[nearest][next] < distance[next]) {
                distance[next] =distance[nearest]+graph[nearest][next];
                cout << "  Update cost to ";
                cout << char('A' + next) << ": ";
                cout << distance[next] << "\n";
            }
        }
    }

    cout << "\nShortest cost from A to D: " << distance[3] << "\n";

    cout << "Enter 2 to take the shortest route, ";
    cout << "H for a hint, or Q to quit: ";

    while (!gameOver) {
        char choice;
        cin >> choice;

        if (askForHelp(choice)) {
            if (gameOver) return false;
            continue;
        }

        if (choice == '2') {
            cout << "You reached the other side of the forest!\n";
            return true;
        }

        cout << "That route is not the shortest. Try again.\n";
        loseLife();
        cout << "Enter 2 to take the shortest route, H for a hint, ";
        cout << "or Q to quit: ";
    }

    return false;
}

// LEVEL 6: BINARY SEARCH TREE
Game::TreeNode* Game::insertTree(TreeNode* root, int value) {
    if (root == 0) {
        TreeNode* newNode = new TreeNode;
        newNode->data = value;
        newNode->left = 0;
        newNode->right = 0;
        return newNode;
    }

    if (value < root->data) {
        root->left = insertTree(root->left, value);
    } else if (value > root->data) {
        root->right = insertTree(root->right, value);
    }

    return root;
}

bool Game::searchTree(TreeNode* root, int target, int& comparisons){
    if (root == 0) {
        return false;
    }

    comparisons++;
    cout << "Compare target " << target;
    cout << " with node " << root->data << ".";

    if (root->data == target) {
        return true;
    }

    if (target < root->data) {
        cout << "Target is smaller. Go LEFT.";
        return searchTree(root->left, target, comparisons);
    }

    cout << "Target is larger. Go RIGHT.\n";
    return searchTree(root->right, target, comparisons);
}

void Game::deleteTree(TreeNode* root) {
    if (root == 0) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

bool Game::playTree() {
    cout << "Level 6: The Final Castle\n";
    cout << "The princess is locked in room 60!\n";
    cout << "The castle is organized as a binary search tree.\n";
    cout << "Smaller values are on the LEFT.\n";
    cout << "Larger values are on the RIGHT.\n";
    cout << "Use the tree to find the shortest search path!\n\n";

    TreeNode* root = 0;

    root = insertTree(root, 50);
    root = insertTree(root, 30);
    root = insertTree(root, 70);
    root = insertTree(root, 20);
    root = insertTree(root, 40);
    root = insertTree(root, 60);
    root = insertTree(root, 80);

    cout << "              [50]\n";
    cout << "             /    \\\n";
    cout << "          [30]    [70]\n";
    cout << "          /  \\    /  \\\n";
    cout << "       [20] [40][60] [80]\n\n";

    cout << "Your knight starts at room 50.\n";
    cout << "Your goal is room 60.\n";
    cout << "Each correct hallway earns 5 points.\n";
    cout << "Wrong hallways cost one life.\n\n";

    TreeNode* current = root;
    bool rescued = false;
    int comparisons = 0;

    while (!gameOver && !rescued) {
        cout << "CURRENT ROOM: " << current->data << "\n";
        cout << "TARGET ROOM: 60\n";

        comparisons++;

        if (current->data == 60) {
            rescued = true;
        } else {
            cout << "Compare 60 with " << current->data << ".\n";

            if (60 < current->data) {
                cout << "60 is smaller. The correct path is LEFT.\n";
            } else {
                cout << "60 is larger. The correct path is RIGHT.\n";
            }

            cout << "\nChoose your move:\n";
            cout << "1. Go LEFT\n";
            cout << "2. Go RIGHT\n";
            cout << "H. Get a hint\n";
            cout << "Q. Quit level\n";
            cout << "Choice: ";

            char choice;
            cin >> choice;

            if (choice == 'H' || choice == 'h') {
                askForHelp(choice);

                if (!gameOver) {
                    cout << "Hint: Compare the target, 60, with ";
                    cout << current->data << ".\n";

                    if (60 < current->data) {
                        cout << "Choose LEFT because 60 is smaller.\n";
                    } else {
                        cout << "Choose RIGHT because 60 is larger.\n";
                    }
                }
            } else if (choice == 'Q' || choice == 'q') {
                askForHelp(choice);
                deleteTree(root);
                return false;
            } else if (choice == '1') {
                if (60 < current->data && current->left != 0) {
                    current = current->left;
                    score += 5;
                    cout << "Correct! You entered the left room.\n";
                } else {
                    cout << "Wrong hallway! You lost one life.\n";
                    loseLife();
                }
            } else if (choice == '2') {
                if (60 > current->data && current->right != nullptr) {
                    current = current->right;
                    score += 5;
                    cout << "Correct! You entered the right room.\n";
                } else {
                    cout << "Wrong hallway! You lost one life.\n";
                    loseLife();
                }
            }

        }
    }
    if (gameOver) {
        deleteTree(root);
        return false;
    }
    if (rescued) {
        cout << "\nTHE PRINCESS IS FREE! YIPEEE!!!\n";
        cout << "You followed the path: 50 -> 70 -> 60\n";
        cout << "Nodes visited: " << comparisons << "\n";
        cout << "You earned 20 bonus points!\n";
        score += 20;
    }
    deleteTree(root);
    return rescued;
}
Game::ListNode* Game::createList() {
    ListNode* head = new ListNode;
    head->data = 2;

    head->next = new ListNode;
    head->next->data = 4;

    head->next->next = new ListNode;
    head->next->next->data = 1;

    head->next->next->next = new ListNode;
    head->next->next->next->data = 5;
    head->next->next->next->next = nullptr;

    return head;
}
void Game::deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}
