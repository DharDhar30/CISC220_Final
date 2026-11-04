#include <iostream>
#include "../game.h"
using namespace std;

// LEVEL 5: GRAPH AND DIJKSTRA'S ALGORITHM
bool Game::playGraph(){
    cout << "\nLEVEL 5: THE CURSED FOREST\n";
    cout << "DATA STRUCTURE: GRAPH\n\n";

    cout << "A graph contains vertices and edges.\n";
    cout << "Vertices are locations. Edges are roads.\n";
    cout << "Each road has a travel cost.\n";
    cout << "Dijkstra's algorithm finds a shortest path by cost.\n\n";

    cout << "The forest has four locations: A, B, C, D.\n";

    cout << "       2        1        2\n";
    cout << "   A ------ B ------ C ------ D\n";
    cout << "    \\                         /\n";
    cout << "     ----------- 5 ----------\n";
    cout << "          B to D: 5\n\n";
    cout << "Road costs:\n";
    cout << "A to B: 2\n";
    cout << "A to C: 5\n";
    cout << "B to C: 1\n";
    cout << "B to D: 5\n";
    cout << "C to D: 2\n\n";

    cout << "HOW DIJKSTRA'S ALGORITHM WORKS:\n";
    cout << "1. Start at A with distance 0.\n";
    cout << "2. Give every other vertex distance infinity.\n";
    cout << "3. Visit the unvisited vertex with the smallest distance.\n";
    cout << "4. Check its neighbors and update their distances if a\n";
    cout << "   shorter route has been found.\n";
    cout << "5. Repeat until every vertex is visited.\n\n";

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

    cout << "INITIAL DISTANCES:\n";
    cout << "A = 0, B = infinity, C = infinity, D = infinity\n\n";

    for (int step = 0; step < 4 && !gameOver; step++) {

        int nearest = -1;

        for (int i = 0; i < 4; i++) {
            if (!visited[i] &&
                (nearest == -1 || distance[i] < distance[nearest])) {
                nearest = i;
            }
        }

        cout << "CURRENT DISTANCE TABLE:\n";

        for (int i = 0; i < 4; i++) {
            cout << char('A' + i) << ": ";

            if (distance[i] == 9999) {
                cout << "infinity";
            } else {
                cout << distance[i];
            }
            if (visited[i]) {
                cout << " (visited)";
            } else {
                cout << " (unvisited)";
            }

            cout << "\n";
        }

        cout << "\nWhich unvisited vertex has the smallest distance?\n";
        cout << "Enter A, B, C, or D: ";

        char choice;
        cin >> choice;

        if (askForHelp(choice)) {
            if (gameOver) return false;
            step= step-1;
            continue;
        }

        if (choice >= 'a' && choice <= 'z') {
            choice = choice - 32;
        }

        while (!gameOver &&
               (choice < 'A' || choice > 'D' ||
                visited[choice - 'A'] ||
                choice - 'A' != nearest)) {

            cout << "\nIncorrect choice.\n";
            cout << "Remember: choose the unvisited vertex with the smallest current distance.\n";

            loseLife();
            if (gameOver) return false;
            cout << "Try again: ";
            cin >> choice;

            if (choice >= 'a' && choice <= 'z') {
                choice = choice - 32;
            }
            if (askForHelp(choice)) {
                if (gameOver) return false;
                cout << "Try again: ";
                cin >> choice;
                if (choice >= 'a' && choice <= 'z') {
                    choice = choice - 32;
                }
            }
        }

        if (gameOver) return false;

        cout << "\nCorrect! " << choice;
        cout << " has the smallest unvisited distance.\n";

        visited[nearest] = true;
        score += 2;

        cout << "Location " << choice << " is now visited.\n";

        // check neighbor and update distances
        for (int next = 0; next < 4 && !gameOver; next++) {
            if (graph[nearest][next] > 0 && !visited[next]) {
                int newDistance = distance[nearest] + graph[nearest][next];
                cout << "\nChecking edge ";
                cout << choice << " to " << char('A' + next) << ".\n";

                cout << "Current distance to ";
                cout << char('A' + next) << ": ";
                if (distance[next] == 9999) {
                    cout << "infinity\n";} else {
                    cout << distance[next] << "\n";
                }
                cout << "Distance through " << choice << ": ";
                cout << distance[nearest] << " + ";
                cout << graph[nearest][next] << " = ";
                cout << newDistance << "\n";

                if (newDistance < distance[next]) {

                    cout << "A shorter route exists!\n";
                    cout << "Enter 1 to update the distance or 2 to keep it: ";

                    int update;
                    cin >> update;

                    while (!gameOver && update != 1) {
                        cout << "You should update it because ";
                        cout << newDistance;
                        cout << " is smaller than the current distance.\n";

                        loseLife();

                        if (gameOver) return false;

                        cout << "Try again. Enter 1 to update: ";
                        cin >> update;
                    }

                    if (gameOver) return false;
                    distance[next] = newDistance;

                    cout << "Distance to " << char('A' + next);
                    cout << " updated to " << newDistance << ".\n";

                    score += 1;
                } else {
                    cout << "The current distance is already shorter.\n";
                    cout << "No update is needed.\n";
                }
            }
        }
    }

    if (gameOver) return false;

    cout << "ALL LOCATIONS VISITED!\n";
    cout << "Final distances:\n";

    for (int i = 0; i < 4; i++) {
        cout << char('A' + i) << ": " << distance[i] << "\n";
    }

    cout << "\nShortest cost from A to D: ";
    cout << distance[3] << "\n";

    cout << "The shortest route is A -> B -> C -> D.\n";
    cout << "You escaped the Cursed Forest!\n";

    score += 10;
    return true;
}