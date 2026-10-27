
#ifndef GAME_H
#define GAME_H

class Game {
private:
    int lives;
    int score;
    int level;
    bool gameOver;
    bool codeChallenge(
    const char* title,
    const char* code,
    const char* option1,
    const char* option2,
    const char* option3,
    int correctAnswer,
    const char* explanation
);

    // Level 1: Two-dimensional array.
    char maze[7][9];
    int knightRow;
    int knightColumn;

    // Level 3: Simple hash table.
    struct HashEntry {
        int key;
        const char* value;
        bool occupied;
    };

    HashEntry hashTable[10];

    // Level 4: Linked-list node.
    struct ListNode {
        int data;
        ListNode* next;
    };

    // Level 6: Binary search tree node.
    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
    };

    void showStatus();
    bool askForHelp(char choice);
    bool loseLife();
    void giveHint();

    bool playMaze();
    bool playStack();
    bool playHashMap();
    bool playLinkedList();
    bool playGraph();
    bool playTree();

    int hashFunction(int key);
    void setupHashTable();
    void insertHash(int key, const char* value);
    const char* searchHash(int key);

    ListNode* createList();
    void deleteList(ListNode* head);

    TreeNode* insertTree(TreeNode* root, int value);
    bool searchTree(TreeNode* root, int target, int& comparisons);
    void deleteTree(TreeNode* root);

public:
    Game();
    void play();
    void playTestLevel(int selectedLevel);
};

#endif
