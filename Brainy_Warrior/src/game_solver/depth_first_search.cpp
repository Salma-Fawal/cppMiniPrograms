#include "algorithms.h"

#include <iostream>
#include <unordered_set>
#include <stack>
#include <list>
#include "node_state.h"
#include "board.h"
#include "helper_functions.h"
#include "main.h"

using namespace std;


void dfs(Board board){

    stack<Node_State> s;
    unordered_set<string> visitedStates;

    Node_State start(board, nullptr, 0, 0);
    s.push(start);
    visitedStates.insert(stringBoard(board));  

    while(!s.empty()){

        Node_State current(s.top());
        printBoard(current.getBoard());
        s.pop();

        if(current.getBoard().win()){
            cout<<"\033[38;5;226mYOU WIN!\033[0m\n";
            cout << "Number of opened states: " << visitedStates.size() << endl;
            printBoard(getPath(&current));
            exit(0);
        }

        list<Node_State> states = get_next_cost_states(&current);
        for(auto state:states){
            string stateHash = stringBoard(state.getBoard());
            if (visitedStates.find(stateHash) == visitedStates.end()) {
                visitedStates.insert(stateHash);
                s.push(state);
            }
        }
    }
}