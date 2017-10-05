#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <ctime>
#include <algorithm>
using namespace std;

void printStateVector(vector< vector<string> > &stateVector) {
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            cout << stateVector[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

class State {
private:
    vector< vector<string> > currentState;
    vector<string> actionHistoryVector;
    int emptySpaceX;
    int emptySpaceY;
public:
    State(vector< vector<string> > newState, vector<string> newActionVector);
    string getActionString();
    vector< vector<string> > getCurrentStateVector();
    void addNextPossibleStatesToQueue(queue<State> &stateQueue, vector< vector< vector<string> > > &visited);
};


State::State(vector< vector<string> > newState, vector<string> newActionVector) {
    currentState = newState;
    actionHistoryVector = newActionVector;
    

    // find out where the empty space is
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            if (currentState[i][j] == "0")
            {
                emptySpaceX = j;
                emptySpaceY = i;
            }
        }
    }
}

vector< vector<string> > State::getCurrentStateVector() {
    return currentState;
}

string State::getActionString() {
    string result = "";
    for (int i = 0; i < actionHistoryVector.size(); i++) {
        result += actionHistoryVector[i] + "\n";
    }
    stringstream ss;
    ss << (actionHistoryVector.size() - 1);
    string numberOfMoves = ss.str();
    
    result += "Number of moves is " + numberOfMoves + "\n";
    return result;
}

void State::addNextPossibleStatesToQueue(queue<State> &stateQueue, vector< vector< vector<string> > > &visited) {
    
    bool flag;
    string actionString;
    vector< vector<string> > nextStateVector;

    // cout << "size: " << visited.size() << endl; 

    // space moves right
    if (emptySpaceX < 2) {
        actionString = currentState[emptySpaceY][emptySpaceX + 1] + " moves left (Space moves right).";
        nextStateVector = currentState;
        nextStateVector[emptySpaceY][emptySpaceX] = currentState[emptySpaceY][emptySpaceX + 1];
        nextStateVector[emptySpaceY][emptySpaceX + 1] = "0";
        
        if (!(find(visited.begin(), visited.end(), nextStateVector) != visited.end())) {
            vector<string> newActionHistory = actionHistoryVector;
            newActionHistory.push_back(actionString);
            visited.push_back(nextStateVector);
            stateQueue.push(State(nextStateVector, newActionHistory));
            // cout << "added space move right" << endl;
            // cout << stateQueue.size() << endl;
        }
    }
    
    // space moves left
    if (emptySpaceX > 0) {
        actionString = currentState[emptySpaceY][emptySpaceX - 1] + " moves right (Space moves left).";
        nextStateVector = currentState;
        nextStateVector[emptySpaceY][emptySpaceX] = currentState[emptySpaceY][emptySpaceX - 1];
        nextStateVector[emptySpaceY][emptySpaceX - 1] = "0";
        
        if (!(find(visited.begin(), visited.end(), nextStateVector) != visited.end())) {
            vector<string> newActionHistory = actionHistoryVector;
            newActionHistory.push_back(actionString);
            visited.push_back(nextStateVector);
            stateQueue.push(State(nextStateVector, newActionHistory));
            //cout << "added space move left" << endl;
            //cout << stateQueue.size() << endl;
        }
    }

    // space moves up
    if (emptySpaceY > 0) {
        actionString = currentState[emptySpaceY - 1][emptySpaceX] + " moves down (Space moves up).";
        nextStateVector = currentState;
        nextStateVector[emptySpaceY][emptySpaceX] = currentState[emptySpaceY - 1][emptySpaceX];
        nextStateVector[emptySpaceY - 1][emptySpaceX] = "0";
        
        if (!(find(visited.begin(), visited.end(), nextStateVector) != visited.end())) {
            vector<string> newActionHistory = actionHistoryVector;
            newActionHistory.push_back(actionString);
            visited.push_back(nextStateVector);
            stateQueue.push(State(nextStateVector, newActionHistory));
            // cout << "added space move up" << endl;
            // cout << stateQueue.size() << endl;
        }
    }

    // space moves down
    if (emptySpaceY < 2) {
        actionString = currentState[emptySpaceY + 1][emptySpaceX] + " moves up (Space moves down).";
        nextStateVector = currentState;
        nextStateVector[emptySpaceY][emptySpaceX] = currentState[emptySpaceY + 1][emptySpaceX];
        nextStateVector[emptySpaceY + 1][emptySpaceX] = "0";
        
        if (!(find(visited.begin(), visited.end(), nextStateVector) != visited.end())) {
            vector<string> newActionHistory = actionHistoryVector;
            newActionHistory.push_back(actionString);
            visited.push_back(nextStateVector);
            stateQueue.push(State(nextStateVector, newActionHistory));
            // cout << "added space move down" << endl;
            // cout << stateQueue.size() << endl;
        }
    }
}


int main() {
    clock_t begin = clock();

    vector< vector<string> > initial;
    initial.resize(3, vector<string>(3, "0"));
    initial[0][0] = "7";
    initial[0][1] = "2";
    initial[0][2] = "4";
    initial[1][0] = "5";
    initial[1][1] = "0";
    initial[1][2] = "6";
    initial[2][0] = "8";
    initial[2][1] = "3";
    initial[2][2] = "1";

    // 2 steps
    initial[0][0] = "1";
    initial[0][1] = "2";
    initial[0][2] = "0";
    initial[1][0] = "3";
    initial[1][1] = "4";
    initial[1][2] = "5";
    initial[2][0] = "6";
    initial[2][1] = "7";
    initial[2][2] = "8";

    // 4 steps
    // initial[0][0] = "1";
    // initial[0][1] = "2";
    // initial[0][2] = "5";
    // initial[1][0] = "3";
    // initial[1][1] = "4";
    // initial[1][2] = "8";
    // initial[2][0] = "6";
    // initial[2][1] = "7";
    // initial[2][2] = "0";

    // 8 steps
    // initial[0][0] = "1";
    // initial[0][1] = "2";
    // initial[0][2] = "5";
    // initial[1][0] = "4";
    // initial[1][1] = "0";
    // initial[1][2] = "8";
    // initial[2][0] = "3";
    // initial[2][1] = "6";
    // initial[2][2] = "7";

    // 10 steps
    // initial[0][0] = "0";
    // initial[0][1] = "1";
    // initial[0][2] = "5";
    // initial[1][0] = "4";
    // initial[1][1] = "2";
    // initial[1][2] = "8";
    // initial[2][0] = "3";
    // initial[2][1] = "6";
    // initial[2][2] = "7";

    // 12 steps
    initial[0][0] = "4";
    initial[0][1] = "1";
    initial[0][2] = "5";
    initial[1][0] = "3";
    initial[1][1] = "2";
    initial[1][2] = "8";
    initial[2][0] = "0";
    initial[2][1] = "6";
    initial[2][2] = "7";

    // 18 steps
    initial[0][0] = "4";
    initial[0][1] = "1";
    initial[0][2] = "0";
    initial[1][0] = "3";
    initial[1][1] = "7";
    initial[1][2] = "6";
    initial[2][0] = "8";
    initial[2][1] = "5";
    initial[2][2] = "2";

    vector< vector< vector<string> > > initialStateHistory;
    initialStateHistory.push_back(initial);
    vector<string> initialAction;
    initialAction.push_back("Initial State");

    vector< vector<string> > goalStateVector;
    goalStateVector.resize(3, vector<string>(3, "0"));
    goalStateVector[0][0] = "0";
    goalStateVector[0][1] = "1";
    goalStateVector[0][2] = "2";
    goalStateVector[1][0] = "3";
    goalStateVector[1][1] = "4";
    goalStateVector[1][2] = "5";
    goalStateVector[2][0] = "6";
    goalStateVector[2][1] = "7";
    goalStateVector[2][2] = "8";

    queue<State> stateQueue;
    vector< vector< vector<string> > > visited;

    stateQueue.push(State(initial, initialAction));
    visited.push_back(initial);
    while (!stateQueue.empty())
    {
        State currentState = stateQueue.front();
        if (currentState.getCurrentStateVector() == goalStateVector) {
            cout << currentState.getActionString() << endl;
            break;
        }
        stateQueue.pop();
        currentState.addNextPossibleStatesToQueue(stateQueue, visited);
        
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken: " << elapsed_secs << " seconds." << endl;
    return 0;
}