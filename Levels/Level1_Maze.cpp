#include "../game.h"
#include <iostream>
#include <string>
using namespace std;

// LEVEL 1- TWO-DIMENSIONAL ARRAY
bool Game::playMaze() {
    cout << "       LEVEL 1: THE BROKEN MAZE\n";

    cout << "The knight is trapped inside an ancient maze.\n";
    cout << "The map is stored inside a two-dimensional array.\n";
    cout << "Learn how the array works to find your way out!\n";

    cout << "QUICK LESS: UNDERSTAND THE ARRAY";
    cout << "A 2D array stores information in rows and columns.\n";
    cout << "Our maze is stored in maze[7][9].\n";
    cout << "That means 7 rows and 9 columns.\n\n";

    cout << "Each cell has two indexes:\n";
    cout << "maze[row][column]\n\n";

    cout << "Remember:\n";
    cout << "- The first index identifies the row.\n";
    cout << "- The second index identifies the column.\n";
    cout << "- Array indexes start at 0, not 1.\n\n";

    cout << "\nYOUR FIRST CODING CHALLENGE\n";
    cout << "The knight starts at row 3, column 1.\n";
    cout << "Complete this expression to access the knight's cell:\n\n";
    cout << "maze[________][________];\n\n";

    string rowAnswer;
    string columnAnswer;
    int attempts = 0;
    bool indexCorrect = false;

    while (!indexCorrect && attempts < 3 && !gameOver) {
        cout << "Enter the first index: ";
        cin >> rowAnswer;

        if (rowAnswer == "H" || rowAnswer == "h") {
            cout << "Hint: The first index represents the row.\n";
            continue;
        }

        cout << "Enter the second index: ";
        cin >> columnAnswer;

        if (columnAnswer == "H" || columnAnswer == "h") {
            cout << "Hint: The second index represents the column.\n";
            continue;
        }

        if (rowAnswer == "knightRow" &&
            columnAnswer == "knightColumn") {
            indexCorrect = true;
            cout << "\nCorrect! Your completed code is:\n";
            cout << "maze[knightRow][knightColumn];\n";
            cout << "This accesses the cell where the knight is standing.\n";
            score += 5;
            cout << "You earned 5 points!\n";
            } else {
                attempts++;
                cout << "\nNot quite. Remember:\n";
                cout << "First index = row.\n";
                cout << "Second index = column.\n";
            }
    }

    if (gameOver) {
        return false;
    }

    if (!indexCorrect) {
        cout << "\nThe correct expression is:\n";
        cout << "maze[knightRow][knightColumn];\n";
        cout << "Let's use this expression as we explore.\n";
    }
    cout << "\nHOW TO PLAY\n";
    cout << "W = Move up\n";
    cout << "A = Move left\n";
    cout << "S = Move down\n";
    cout << "D = Move right\n";
    cout << "H = Hint\n";
    cout << "Q = Quit\n";

    cout << "\nYour goal is to reach E.\n";
    cout << "Collect treasure ($) and avoid hazards (H).\n";

    bool wallChallengeDone = false;
    bool boundaryChallengeDone = false;
    bool treasureChallengeDone = false;

    while (!gameOver) {
        cout << "MAZE MAP\n";

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

        cout << "\nThe game needs to check maze["
             << newRow << "][" << newColumn << "].\n";

        //Here are some challenges that will teach about arrays
        //CHALLENGE: ARRAY BOUNDARIES
        if (newRow < 0 || newRow >= 7 ||
            newColumn < 0 || newColumn >= 9) {
            cout << "\nBOUNDARY CHALLENGE\n";
            cout << "The knight is trying to leave the array!\n";
            cout << "The maze has 7 rows and 9 columns.\n\n";

            if (!boundaryChallengeDone) {
                cout << "Complete the missing number:\n";
                cout << "if (knightRow < _____)\n";
                cout << "Enter the number: ";
                string answer;
                cin >> answer;

                if (answer == "7") {
                    cout << "\nCorrect! Valid row indexes are 0 through 6.\n";
                    cout << "The condition prevents access beyond the array.\n";
                    score += 5;
                } else {
                    cout << "\nThe correct condition is knightRow<7.\n";
                    cout << "Because the last valid row index is 6.\n";
                }
                boundaryChallengeDone = true;
            }

            cout << "\nThis position is outside the array.\n";
            loseLife();
            continue;
            }

        //Challenge: Those pesky walls! >:(
        if (maze[newRow][newColumn] == '#') {
            cout << "\nWALL DETECTED!\n";
            cout << "The array contains '#' at this position.\n";
            cout << "The knight cannot walk through walls.\n";

            if (!wallChallengeDone) {
                cout << "\nCODING CHALLENGE\n";
                cout << "Complete the condition that checks for a wall:\n\n";
                cout << "if (maze[newRow][newColumn] == _____)\n";
                cout << "Enter the missing character, including quotes: ";
                string answer;
                cin >> answer;
                if (answer == "'#'") {
                    cout << "\nCorrect!\n";
                    cout << "The expression checks whether the cell contains a wall.\n";
                    cout << "The == operator compares two values.\n";
                    score += 5;
                } else {
                    cout << "\nThe correct expression is:\n";
                    cout << "maze[newRow][newColumn] == '#'\n";
                    cout << "This checks whether the next cell is a wall.\n";
                }

                wallChallengeDone = true;
            }
            loseLife();
            continue;
        }
        //MOving the knight
        knightRow = newRow;
        knightColumn = newColumn;

        cout << "\nMove successful!\n";
        cout << "The knight is now at maze["
             << knightRow << "][" << knightColumn << "].\n";

        //getting the treasure
        // TREASURE CHALLENGE
        if (maze[knightRow][knightColumn] == '$') {
            cout << "\nTREASURE FOUND!\n";
            cout << "This cell contains '$'.\n";
            cout << "We can change the value stored in this array position.\n\n";
            if (!treasureChallengeDone) {
                cout << "CODING CHALLENGE\n";
                cout << "After collecting treasure, the cell should become empty.\n";
                cout << "Complete the assignment:\n\n";
                cout << "maze[knightRow][knightColumn] = _____;\n";
                cout << "Enter the replacement character, including quotes: ";

                string answer;
                cin >> answer;

                if (answer == "'.'") {
                    cout << "\nCorrect! You assigned '.' to the array cell.\n";
                    cout << "The treasure is no longer stored at that position.\n";
                    score += 5;
                } else {
                    cout << "\nThe correct assignment is:\n";
                    cout << "maze[knightRow][knightColumn] = '.';\n";
                    cout << "This changes the cell into an empty path.\n";
                }
                treasureChallengeDone = true;
            }
            maze[knightRow][knightColumn] = '.';
            score += 10;

            cout << "\nThe treasure disappeared from the maze!\n";
            cout << "The array now stores '.' at this position.\n";
            cout << "You earned 10 treasure points!\n";
        }

        //Boobytrap
        if (maze[knightRow][knightColumn] == 'H') {
            cout << "\nYou stepped into a boobytrap!\n";
            loseLife();
            knightRow = 3;
            knightColumn = 1;
            continue;
        }

        //the exit
        if (maze[knightRow][knightColumn] == 'E') {
            cout << "          MAZE ESCAPED!\n";
            cout << "You reached the exit!\n";
            return true;
        }
    }
    return false;
}
