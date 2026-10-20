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
            break;
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


 // LEVEL 1: TWO-DIMENSIONAL ARRAY
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
    cout << "\nLEVEL 2: THE TOWER OF TRIALS\n";
    cout << "DATA STRUCTURE: STACK\n\n";

    cout << "A stack follows LIFO: Last In, First Out.\n";
    cout << "New items are pushed onto the top.\n";
    cout << "Only the top item can be popped off.\n\n";

    int items[4];
    int top = -1;

    // Push items onto the stack.
    items[++top] = 1; // Treasure
    items[++top] = 2; // Shield
    items[++top] = 3; // Potion
    items[++top] = 4; // Cursed Stone

    cout << "The items were pushed in this order:\n";
    cout << "Treasure, Shield, Potion, Cursed Stone.\n";
    cout << "The last item pushed is now on top.\n\n";

    cout << "Which item will be removed first?\n";
    cout << "1. Treasure\n";
    cout << "2. Shield\n";
    cout << "3. Potion\n";
    cout << "4. Cursed Stone\n";
    cout << "Answer: ";

    int answer;
    cin >> answer;

    if (answer == 4) {
        cout << "Correct! The Cursed Stone is on top.\n";
        score += 5;
    } else {
        cout << "Incorrect. The Cursed Stone was pushed last, ";
        cout << "so it is removed first.\n";
    }

    cout << "\nRemove items from the top to reach the treasure.\n";

    while (top >= 0 && !gameOver) {
        cout << "\nTop item: ";

        if (items[top] == 4) {
            cout << "Cursed Stone";
        } else if (items[top] == 3) {
            cout << "Potion";
        } else if (items[top] == 2) {
            cout << "Shield";
        } else {
            cout << "Treasure";
        }

        cout << "\nEnter 1 to pop the top item, H for hint, Q to quit: ";

        char choice;
        cin >> choice;
        if (askForHelp(choice)) {
            if (gameOver) return false;
            continue;
        }

        if (choice != '1') {
            cout << "Enter 1 to pop the top item.\n";
            continue;
        }

        int removed = items[top];
        top--;

        cout << "You popped item number " << removed << ".\n";

        if (removed == 4) {
            cout << "The Cursed Stone! It costs you a life.\n";
            loseLife();
        } else if (removed == 1) {
            cout << "You reached the treasure!\n";
            return true;
        }

        cout << "Stack size remaining: " << top + 1 << "\n";
    }

    return false;
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
    cout << "DATA STRUCTURE: HASH MAP\n\n";

    cout << "A hash map stores key-value pairs.\n";
    cout << "A hash function converts a key into an array index.\n";
    cout << "If two keys collide, this table uses linear probing.\n\n";

    cout << "Knowledge check:\n";
    cout << "What does a hash map use to find a stored value?\n";
    cout << "1. A key\n";
    cout << "2. The last item inserted\n";
    cout << "3. The smallest number\n";
    cout << "Answer: ";

    int answer;
    cin >> answer;

    if (answer == 1) {
        cout << "Correct! A key is used to look up its value.\n";
        score += 5;
    } else {
        cout << "A hash map uses a key to look up its value.\n";
    }

    cout << "\nFind the Royal Key to open the gate.\n";
    cout << "Available keys: 12, 25, 37, 48\n";

    while (!gameOver) {
        cout << "Enter a key, H for hint, or Q to quit: ";

        char choice;
        cin >> choice;

        if (askForHelp(choice)) {
            if (gameOver) return false;
            continue;
        }

        if (choice < '0' || choice > '9') {
            cout << "Please enter a numeric key.\n";
            continue;
        }

        int key = choice - '0';

        // Allow two-digit keys.
        if (key == 1 || key == 2 || key == 3 || key == 4) {
            cout << "Enter the second digit: ";
            char second;
            cin >> second;

            if (second < '0' || second > '9') {
                cout << "Invalid second digit.\n";
                continue;
            }

            key = key * 10 + (second - '0');
        }

        int index = hashFunction(key);

        cout << "Hash function: " << key << " % 10 = ";
        cout << index << "\n";

        const char* result = searchHash(key);
        cout << "Lookup result: " << result << "\n";

        if (key == 37) {
            cout << "The Royal Key opens the gate!\n";
            return true;
        }

        cout << "That is not the Royal Key. Try again.\n";
    }

    return false;
}

// LEVEL 4: LINKED LIST

Game::ListNode* Game::createList() {
    ListNode* first = new ListNode;
    ListNode* second = new ListNode;
    ListNode* third = new ListNode;
    ListNode* fourth = new ListNode;

    first->data = 2;
    first->next = second;

    second->data = 4;
    second->next = third;

    third->data = 1;
    third->next = fourth;

    fourth->data = 5;
    fourth->next = 0;

    return first;
}

void Game::deleteList(ListNode* head) {
    while (head != 0) {
        ListNode* nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

bool Game::playLinkedList() {
    cout << "\nLEVEL 4: THE BROKEN RIVER\n";
    cout << "DATA STRUCTURE: LINKED LIST\n\n";

    cout << "Each linked-list node stores data and a next pointer.\n";
    cout << "The pointer tells you which node comes next.\n";
    cout << "The last node points to 0, meaning no next node.\n\n";

    cout << "Knowledge check:\n";
    cout << "What does a node's next pointer identify?\n";
    cout << "1. The previous node\n";
    cout << "2. The next node\n";
    cout << "Answer: ";

    int answer;
    cin >> answer;

    if (answer == 2) {
        cout << "Correct! The next pointer connects the nodes.\n";
        score += 5;
    } else {
        cout << "The next pointer identifies the next node.\n";
    }

    ListNode* head = createList();
    ListNode* current = head;

    cout << "\nCross the river by following the linked nodes.\n";

    while (current != 0 && !gameOver) {
        cout << "\nCurrent node: " << current->data << "\n";
        cout << "Enter the next stone number, H for hint, Q to quit: ";

        char choice;
        cin >> choice;

        if (askForHelp(choice)) {
            if (gameOver) {
                deleteList(head);
                return false;
            }
            continue;
        }

        if (choice < '0' || choice > '9') {
            cout << "Enter the stone number.\n";
            continue;
        }

        int chosen = choice - '0';

        if (chosen != current->data) {
            cout << "Wrong stone! Follow the current node.\n";
            loseLife();
            current = head;
            cout << "Start again from the first node.\n";
        } else {
            cout << "Correct node!\n";
            current = current->next;
        }
    }

    deleteList(head);

    if (!gameOver) {
        cout << "You followed the linked list across the river!\n";
        return true;
    }

    return false;
}

// LEVEL 5: GRAPH AND DIJKSTRA'S ALGORITHM

bool Game::playGraph() {
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
                distance[next] =
                    distance[nearest] + graph[nearest][next];

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

bool Game::searchTree(TreeNode* root, int target, int& comparisons) {
    if (root == 0) {
        return false;
    }

    comparisons++;
    cout << "Compare target " << target;
    cout << " with node " << root->data << ".\n";

    if (root->data == target) {
        return true;
    }

    if (target < root->data) {
        cout << "Target is smaller. Go LEFT.\n";
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
    cout << "\nLEVEL 6: THE PRINCESS'S CASTLE\n";
    cout << "DATA STRUCTURE: BINARY SEARCH TREE\n\n";

    cout << "Smaller values go left; larger values go right.\n";
    cout << "Each comparison tells you which direction to search.\n";
    cout << "Find node 60 to rescue the princess!\n\n";

    cout << "Knowledge check:\n";
    cout << "You are at node 50. Your target is 60.\n";
    cout << "Which direction should you go?\n";
    cout << "1. Left\n";
    cout << "2. Right\n";
    cout << "Answer: ";

    int answer;
    cin >> answer;

    if (answer == 2) {
        cout << "Correct! 60 is greater than 50, so go right.\n";
        score += 5;
    } else {
        cout << "60 is greater than 50, so you must go right.\n";
    }

    TreeNode* root = 0;

    root = insertTree(root, 50);
    root = insertTree(root, 30);
    root = insertTree(root, 70);
    root = insertTree(root, 20);
    root = insertTree(root, 40);
    root = insertTree(root, 60);
    root = insertTree(root, 80);

    cout << "\nTree layout:\n";
    cout << "          50\n";
    cout << "        /    \\\n";
    cout << "      30      70\n";
    cout << "     /  \\    /  \\\n";
    cout << "   20   40  60   80\n\n";

    while (!gameOver) {
        cout << "Enter the value to search for, ";
        cout << "H for a hint, or Q to quit: ";

        char choice;
        cin >> choice;

        if (askForHelp(choice)) {
            if (gameOver) {
                deleteTree(root);
                return false;
            }
            continue;
        }

        if (choice < '0' || choice > '9') {
            cout << "Enter a number such as 60.\n";
            continue;
        }

        int target = choice - '0';

        if (target == 2 || target == 3 || target == 4 ||
            target == 5 || target == 6 || target == 7 || target == 8) {
            cout << "Enter the remaining digit: ";
            char second;
            cin >> second;

            if (second < '0' || second > '9') {
                cout << "Invalid digit.\n";
                continue;
            }

            target = target * 10 + (second - '0');
        }

        int comparisons = 0;
        bool found = searchTree(root, target, comparisons);

        cout << "Nodes visited: " << comparisons << "\n";

        if (found && target == 60) {
            cout << "\nYou found the princess!\n";
            cout << "You used the binary search tree to find her.\n";
            deleteTree(root);
            return true;
        }
        if (found) {
            cout << "That node exists, but the princess is at 60.\n";
        } else {
            cout << "That value is not in the tree.\n";
        }

        loseLife();
    }

    deleteTree(root);
    return false;
}
