#include "../game.h"
#include <iostream>
#include <string>
using namespace std;

  //LEVEL 4
bool Game::playLinkedList() {
    cout << "\nLEVEL 4: THE BROKEN RIVER\n";
    cout << "A flood has damaged the path across the river.\n";
    cout << "Eight stepping stones remain, but their connections are broken.\n";
    cout << "You must reconstruct the linked list to reach the other bank.\n";

    cout << "\nYOUR MISSION:\n";
    cout << "1. Investigate all disconnected chains.\n";
    cout << "2. Determine which pointers are missing.\n";
    cout << "3. Repair all three broken connections.\n";
    cout << "4. Cross all eight stones without falling.\n";

    // 8 nodes
    ListNode* n3 = new ListNode;
    ListNode* n7 = new ListNode;
    ListNode* n2 = new ListNode;
    ListNode* n9 = new ListNode;
    ListNode* n1 = new ListNode;
    ListNode* n8 = new ListNode;
    ListNode* n4 = new ListNode;
    ListNode* n6 = new ListNode;

    n3->data = 3;
    n7->data = 7;
    n2->data = 2;
    n9->data = 9;
    n1->data = 1;
    n8->data = 8;
    n4->data = 4;
    n6->data = 6;

    // build OG list
    n3->next = n7;
    n7->next = n2;
    n2->next = n9;
    n9->next = n1;
    n1->next = n8;
    n8->next = n4;
    n4->next = n6;
    n6->next = nullptr;

    ListNode* head = n3;

    // break three connections
    n7->next = nullptr;
    n9->next = nullptr;
    n8->next = nullptr;

    // 4 seperate chains exist now
    ListNode* fragment2 = n2;
    ListNode* fragment3 = n1;
    ListNode* fragment4 = n4;

    bool inspected = false;
    bool analyzed = false;
    bool crossed = false;

    int repairs = 0;
    int stonesCrossed = 1;

    ListNode* current = head;

    while (!gameOver && !crossed) {

        cout << "              THE BROKEN RIVER\n";
        cout << "\n              THE EIGHT STONES\n\n";

        int stoneValues[8] = {3, 7, 2, 9, 1, 8, 4, 6};

        for (int i = 0; i < 8; i++) {
            cout << "   [" << stoneValues[i] << "]  ";
        }

        cout << "\n";

        for (int i = 0; i < 8; i++) {
            if (current != nullptr && current->data == stoneValues[i]) {
                cout << "    K   ";
            } else {
                cout << "        ";
            }
        }

        cout << "\n\n";

        cout << "                DEEP WATER\n";
        cout << "\nRepairs completed: " << repairs << "/3\n";
        cout << "Stones crossed: " << stonesCrossed << "/8\n";

        if (current != nullptr) {
            cout << "Current stone: " << current->data << "\n";
        }

        cout << "\nRIVER COMMAND CENTER\n";
        cout << "1. Inspect all linked-list chains\n";
        cout << "2. Analyze the missing connections\n";
        cout << "3. Repair a broken pointer\n";
        cout << "4. Jump to the next stone\n";
        cout << "5. View the river map\n";
        cout << "H. Hint\n";
        cout << "Q. Quit\n";

        cout << "\nChoice: ";

        char choice;
        cin >> choice;

        // HINT
        if (choice == 'H' || choice == 'h') {
            askForHelp(choice);

            cout << "\nHINT:\n";
            cout << "A linked list does not use neighboring positions.\n";
            cout << "Each node stores data and a pointer to another node.\n";
            cout << "Look for nodes whose next pointer is NULL.\n";
        }

        // quit
        else if (choice == 'Q' || choice == 'q') {
            askForHelp(choice);
            gameOver = true;
        }

        // Inspect chains
        else if (choice == '1') {

            inspected = true;
            cout << "\n========== LINKED LIST INSPECTION ==========\n";

            ListNode* temp = head;

            cout << "\nCHAIN 1: Starting from HEAD\n";

            while (temp != nullptr) {
                cout << "[" << temp->data << "] -> ";
                temp = temp->next;
            }

            cout << "NULL\n";

            temp = fragment2;

            cout << "\nCHAIN 2:\n";

            while (temp != nullptr) {
                cout << "[" << temp->data << "] -> ";
                temp = temp->next;
            }

            cout << "NULL\n";

            temp = fragment3;

            cout << "\nCHAIN 3:\n";

            while (temp != nullptr) {
                cout << "[" << temp->data << "] -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
            temp = fragment4;
            cout << "\nCHAIN 4:\n";

            while (temp != nullptr) {
                cout << "[" << temp->data << "] -> ";
                temp = temp->next;
            }

            cout << "NULL\n";

            cout << "\nIMPORTANT OBSERVATION:\n";
            cout << "A NULL pointer means that the chain stops there.\n";
            cout << "The other nodes still exist, but HEAD cannot reach them.\n";
        }

        // Analyze teh broken connections
        else if (choice == '2') {

            if (!inspected) {
                cout << "\nInspect the chains before analyzing them.\n";
            } else {

                cout << "\n========== POINTER ANALYSIS ==========\n";

                cout << "There are eight nodes but only four separate chains.\n";
                cout << "Three connections must be restored.\n";

                cout << "\nCHALLENGE 1:\n";
                cout << "Which pointer is responsible for moving from one node to another?\n";
                cout << "1. data\n";
                cout << "2. next\n";
                cout << "3. head->data\n";

                char answer1;
                cout << "Answer: ";
                cin >> answer1;

                if (answer1 == '2') {

                    cout << "\nCorrect! The next pointer stores the address of the next node.\n";

                    cout << "\nCHALLENGE 2:\n";
                    cout << "If node 7 has next = NULL, what happens during traversal?\n";
                    cout << "1. Traversal stops at node 7\n";
                    cout << "2. Traversal automatically jumps to node 2\n";
                    cout << "3. The entire list is deleted\n";

                    char answer2;
                    cout << "Answer: ";
                    cin >> answer2;

                    if (answer2 == '1') {

                        cout << "\nCorrect! Traversal stops when the pointer is NULL.\n";

                        cout << "\nCHALLENGE 3:\n";
                        cout << "Which expression moves a pointer to the next node?\n";
                        cout << "1. current = current->data;\n";
                        cout << "2. current = current->next;\n";
                        cout << "3. current->next = current;\n";

                        char answer3;
                        cout << "Answer: ";
                        cin >> answer3;

                        if (answer3 == '2') {
                            analyzed = true;

                            cout << "\nALL THREE CHALLENGES COMPLETED!\n";
                            cout << "You understand linked-list traversal.\n";

                            score += 10;
                            cout << "You earned 10 points!\n";

                        } else {
                            cout << "\nIncorrect. Think about how traversal moves between nodes.\n";
                        }
                    } else {
                        cout << "\nIncorrect. NULL means there is no next node.\n";
                    }
                } else {
                    cout << "\nIncorrect. Each node uses its next pointer to connect to another node.\n";
                }
            }
        }

        // REPAIR A POINTER
        else if (choice == '3') {

            if (!inspected || !analyzed) {
                cout << "\nYou must inspect and analyze the list first.\n";
            } else if (repairs == 3) {
                cout << "\nAll three connections have already been repaired!\n";
            } else {

                cout << "\n========== POINTER REPAIR! ==========\n";

                cout << "Choose the node whose next pointer you want to repair.\n";
                cout << "Available broken nodes: 7, 9, 8\n";

                cout << "\nSource node: ";
                int source;
                cin >> source;

                cout << "Which node should it point to? ";
                int target;
                cin >> target;

                bool correct = false;

                if (source == 7 && target == 2 && n7->next == nullptr) {
                    n7->next = fragment2;
                    fragment2 = nullptr;
                    correct = true;
                }

                else if (source == 9 && target == 1 && n9->next == nullptr) {
                    n9->next = fragment3;
                    fragment3 = nullptr;
                    correct = true;
                }

                else if (source == 8 && target == 4 && n8->next == nullptr) {
                    n8->next = fragment4;
                    fragment4 = nullptr;
                    correct = true;
                }

                if (correct) {

                    repairs++;

                    cout << "\nPOINTER SUCCESSFULLY REPAIRED!\n";
                    cout << "Node " << source << " now points to node " << target << ".\n";

                    cout << "\nThe linked list is becoming connected!\n";

                    score += 5;
                    cout << "You earned 5 points!\n";

                } else {

                    cout << "\nINCORRECT CONNECTION!\n";
                    cout << "That is not the correct connection in the original path.\n";

                    cout << "Think about the order of the disconnected chains.\n";

                    loseLife();
                }
            }
        }

        // CROSS TO THE NEXT STONE
        else if (choice == '4') {

            if (current == nullptr) {
                cout << "\nYou are not standing on a connected stone.\n";
            }

            else if (current->next == nullptr) {

                cout << "\nTHE PATH ENDS HERE!\n";
                cout << "There is no next pointer to follow.\n";

                if (repairs < 3) {
                    cout << "Repair the remaining connections before continuing.\n";
                } else {
                    cout << "Something is wrong with the linked list.\n";
                }
            }

            else {

                cout << "\nThe next pointer leads to node "
                     << current->next->data << ".\n";

                cout << "Enter the number of the stone you want to jump to: ";

                int jump;
                cin >> jump;

                if (jump == current->next->data) {

                    current = current->next;
                    stonesCrossed++;

                    cout << "\nPERFECT JUMP!\n";
                    cout << "You followed the next pointer correctly.\n";

                    if (current->data == 6) {
                        crossed = true;
                    }
                } else {
                    cout << "\nYOU MISSED THE STONE!\n";
                    cout << "You cannot jump to a node that is not connected.\n";

                    loseLife();

                    cout << "You are swept back to the starting bank.\n";

                    current = head;
                    stonesCrossed = 0;
                }
            }
        }

        // VIEW THE MAP
        else if (choice == '5') {

            cout << "\n========== RIVER MAP ==========\n";

            cout << "Original path:\n";
            cout << "3 -> 7 -> 2 -> 9 -> 1 -> 8 -> 4 -> 6 -> NULL\n";

            cout << "\nBroken connections still remaining:\n";

            if (n7->next == nullptr) {
                cout << "7 -> NULL\n";
            }

            if (n9->next == nullptr) {
                cout << "9 -> NULL\n";
            }
            if (n8->next == nullptr) {
                cout << "8 -> NULL\n";
            }
            if (repairs == 3) {
                cout << "All connections restored!\n";
            }
        }

        else {
            cout << "\nInvalid choice. Try again.\n";
        }
    }

    // Reconnect all nodes after delteing memory
    // This ensures every allocated node is deleted, even if the player quits.
    n3->next = n7;
    n7->next = n2;
    n2->next = n9;
    n9->next = n1;
    n1->next = n8;
    n8->next = n4;
    n4->next = n6;
    n6->next = nullptr;

    deleteList(head);

    if (gameOver) {
        return false;
    }
    if (crossed) {
        cout << "             RIVER CONQUERED!\n";

        cout << "You successfully crossed all eight stones!\n";
        cout << "You repaired three pointers and reconstructed the list.\n";
        cout << "You earned 20 crossing points!\n";

        score += 20;
    }

    return crossed;
}