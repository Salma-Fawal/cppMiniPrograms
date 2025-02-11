#include "algorithms.h"

#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <climits>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include "board.h"
#include "node_state.h"
#include "tile.h"
#include "helper_functions.h"
#include "main.h"


using namespace std;

int cost = 0;

void hill_climbing(Board board) {
    priority_queue<Node_State> pq;

    Node_State start(board, nullptr, 0, 0);
    unordered_set<string> visitedStates;

    pq.push(start);
    visitedStates.insert(stringBoard(board));

    while(!pq.empty()){
        Node_State current(pq.top());
        printBoard(current.getBoard());
        pq.pop();

        Tile player = current.getBoard().getPlayerTile();
        
        list<Tile> targets = current.getBoard().getTargetTiles();

        // Find the closest target tile
        Tile goal;
        int minDistance = INT_MAX;
        for (const Tile& target : targets) {
            int dist = distance(player, target);
            if (dist < minDistance) {
                minDistance = dist;
                goal = target;
            }
        }

        // Check for win condition
        if (current.getBoard().win()) {
            cout << "\033[38;5;226mYOU WIN!\033[0m\n";
            cout << "Number of opened states: " << visitedStates.size() << endl;
            cout<< "cost: " << cost<<endl;
            printBoard(getPath(&current));
            exit(0);
        }

        // Generate next states
        list<Node_State> states = get_next_cost_states(&current);
        for (auto& state : states) {
            string stateHash = stringBoard(state.getBoard());
            Tile nextPlayer = state.getBoard().getPlayerTile();
            if (visitedStates.find(stateHash) == visitedStates.end()) {
                visitedStates.insert(stateHash);
                int h = distance(nextPlayer, goal);
                cost += state.getG();
                Node_State newState(state.getBoard(), &current, 0, current.getH() + h);
                pq.push(newState);
            }
        }
    }
}