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
        "#..$....#",
        "#.###...#",
        "#S..#.$.#",
        "###.#.###",
        "#...H...#",
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
