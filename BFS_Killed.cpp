#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <ctime>
using namespace std;


class State {
private:
    vector< vector< vector<string> > > visitedStates;
    vector<string> actionHistoryVector;
    int emptySpaceX;
    int emptySpaceY;

public:
    State(vector< vector< vector<string> > > newVisitedStates, vector<string> newActionVector) {
        visitedStates = newVisitedStates;
        actionHistoryVector = newActionVector;

        vector< vector<string> > lastState = visitedStates[visitedStates.size() - 1];

        // find out where the empty space is
        for (int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                if (lastState[i][j] == "0")
                {
                    emptySpaceX = j;
                    emptySpaceY = i;
                }
            }
        }
    }

    vector< vector<string> > getLastStateVector() {
        return visitedStates[visitedStates.size() - 1];
    }

    string getLastStateString() {
        vector< vector<string> > lastState = visitedStates[visitedStates.size() - 1];
        string result = "";
        for (int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                result += lastState[i][j] + " ";
            }
            if (i < 2) {
                result += "\n";
            }
        }
        return result;
    }

    string getAllStateAndActionString() {
        string result = "";
        for (int i = 0; i < actionHistoryVector.size(); i++) {
            result += actionHistoryVector[i] + "\n";
            /*for (int j = 0; j <= 2; j++) {
                for (int k = 0; k <= 2; k++) {
                    result += visitedStates[i][j][k] + " ";
                }
                result += "\n";
            }
            result += "\n";*/
        }
        stringstream ss;
        ss << (actionHistoryVector.size() - 1);
        string numberOfMoves = ss.str();
        
        result += "Number of moves is " + numberOfMoves + "\n";
        return result;
    }

    string getLastHistory() {
        return actionHistoryVector[actionHistoryVector.size() - 1];
    }

    vector<State> getNextPossibleStates() {
        vector<State> nextPossibleStates;

        vector< vector<string> > lastState = visitedStates[visitedStates.size() - 1];
        // space moves left
        if (emptySpaceX > 0) {
            string actionString = lastState[emptySpaceY][emptySpaceX - 1] + " moves right (Space moves left).";
            vector< vector<string> > nextStateVector = lastState;
            nextStateVector[emptySpaceY][emptySpaceX] = lastState[emptySpaceY][emptySpaceX - 1];
            nextStateVector[emptySpaceY][emptySpaceX - 1] = "0";
            
            bool flag = true;
            for (int i = 0; i < visitedStates.size(); i++) {
                if (nextStateVector == visitedStates[i]) {
                    flag = false;
                }
            }
            if (flag) {
                vector< vector< vector<string> > > newVisitedStates = visitedStates;
                newVisitedStates.push_back(nextStateVector);
                vector<string> newActionHistory = actionHistoryVector;
                newActionHistory.push_back(actionString);
                State nextState(newVisitedStates, newActionHistory);
                nextPossibleStates.push_back(nextState);
            }
        }

        // space moves right
        if (emptySpaceX < 2) {
            string actionString = lastState[emptySpaceY][emptySpaceX + 1] + " moves right (Space moves left).";
            vector< vector<string> > nextStateVector = lastState;
            nextStateVector[emptySpaceY][emptySpaceX] = lastState[emptySpaceY][emptySpaceX + 1];
            nextStateVector[emptySpaceY][emptySpaceX + 1] = "0";
            
            bool flag = true;
            for (int i = 0; i < visitedStates.size(); i++) {
                if (nextStateVector == visitedStates[i]) {
                    flag = false;
                }
            }
            if (flag) {
                vector< vector< vector<string> > > newVisitedStates = visitedStates;
                newVisitedStates.push_back(nextStateVector);
                vector<string> newActionHistory = actionHistoryVector;
                newActionHistory.push_back(actionString);
                State nextState(newVisitedStates, newActionHistory);
                nextPossibleStates.push_back(nextState);
            }
        }

        // space moves up
        if (emptySpaceY > 0) {
            string actionString = lastState[emptySpaceY - 1][emptySpaceX] + " moves down (Space moves up).";
            vector< vector<string> > nextStateVector = lastState;
            nextStateVector[emptySpaceY][emptySpaceX] = lastState[emptySpaceY - 1][emptySpaceX];
            nextStateVector[emptySpaceY - 1][emptySpaceX] = "0";
            
            bool flag = true;
            for (int i = 0; i < visitedStates.size(); i++) {
                if (nextStateVector == visitedStates[i]) {
                    flag = false;
                }
            }
            if (flag) {
                vector< vector< vector<string> > > newVisitedStates = visitedStates;
                newVisitedStates.push_back(nextStateVector);
                vector<string> newActionHistory = actionHistoryVector;
                newActionHistory.push_back(actionString);
                State nextState(newVisitedStates, newActionHistory);
                nextPossibleStates.push_back(nextState);
            }
        }

        // space moves down
        if (emptySpaceY < 2) {
            string actionString = lastState[emptySpaceY + 1][emptySpaceX] + " moves up (Space moves down).";
            vector< vector<string> > nextStateVector = lastState;
            nextStateVector[emptySpaceY][emptySpaceX] = lastState[emptySpaceY + 1][emptySpaceX];
            nextStateVector[emptySpaceY + 1][emptySpaceX] = "0";
            
            bool flag = true;
            for (int i = 0; i < visitedStates.size(); i++) {
                if (nextStateVector == visitedStates[i]) {
                    flag = false;
                }
            }
            if (flag) {
                vector< vector< vector<string> > > newVisitedStates = visitedStates;
                newVisitedStates.push_back(nextStateVector);
                vector<string> newActionHistory = actionHistoryVector;
                newActionHistory.push_back(actionString);
                State nextState(newVisitedStates, newActionHistory);
                nextPossibleStates.push_back(nextState);
            }
        }

        return nextPossibleStates;
    }
};




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

    // 6 steps
    // initial[0][0] = "1";
    // initial[0][1] = "2";
    // initial[0][2] = "5";
    // initial[1][0] = "3";
    // initial[1][1] = "4";
    // initial[1][2] = "8";
    // initial[2][0] = "0";
    // initial[2][1] = "6";
    // initial[2][2] = "7";

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
    // initial[0][0] = "4";
    // initial[0][1] = "1";
    // initial[0][2] = "0";
    // initial[1][0] = "3";
    // initial[1][1] = "7";
    // initial[1][2] = "6";
    // initial[2][0] = "8";
    // initial[2][1] = "5";
    // initial[2][2] = "2";

    vector< vector< vector<string> > > initialStateHistory;
    initialStateHistory.push_back(initial);
    vector<string> initialAction;
    initialAction.push_back("Initial State");
    State initialState(initialStateHistory, initialAction);

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
    stateQueue.push(initialState);
    while (!stateQueue.empty())
    {
        State currentState = stateQueue.front();
        if (currentState.getLastStateVector() == goalStateVector) {
            cout << currentState.getAllStateAndActionString() << endl;
            break;
        }
        stateQueue.pop();
        vector<State> nextPossibleStates = currentState.getNextPossibleStates();
        for (int i = 0; i < nextPossibleStates.size(); i++) {
            stateQueue.push(nextPossibleStates[i]);
            cout << stateQueue.size() << endl;
        }
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken: " << elapsed_secs << " seconds." << endl;
    return 0;
}