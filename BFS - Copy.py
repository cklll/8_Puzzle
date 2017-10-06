import queue
from copy import deepcopy

def solve():
    state = []
    state.append(list(map(int,input().split(" "))))
    state.append(list(map(int,input().split(" "))))
    state.append(list(map(int,input().split(" "))))

    goal_state = []
    goal_state.append(list(map(int,input().split(" "))))
    goal_state.append(list(map(int,input().split(" "))))
    goal_state.append(list(map(int,input().split(" "))))

    stateQueue = queue.Queue()
    stateQueue.put({'state': state, 'action': '', 'counter': 0})

    visited = []
    visited.append(deepcopy(state))
    counter = 0
    while not stateQueue.empty():
        counter += 1
        print(counter)
        print(stateQueue.qsize())
        current_state = stateQueue.get()

        if current_state.get('state') == goal_state:
            print('Number of moves is {0}.\n{1}'.format(current_state.get('counter'), current_state.get('action')))
            break

        space_X, space_Y = None, None
        for i in range(3):
            for j in range(3):
                if current_state.get('state')[i][j] == 0:
                    space_X = j
                    space_Y = i

        #space moves left
        if space_X > 0:
            nextState = deepcopy(current_state.get('state'))
            newAction = current_state.get('action') + str(nextState[space_Y][space_X - 1]) + " moves right.\n"
            nextState[space_Y][space_X] = nextState[space_Y][space_X - 1]
            nextState[space_Y][space_X - 1] = 0
            
            if nextState not in visited:
                visited.append(nextState)                
                stateQueue.put({'state': nextState, 'action': newAction, 'counter': current_state.get('counter') + 1})

        #space moves right
        if space_X < 2:
            nextState = deepcopy(current_state.get('state'))
            newAction = current_state.get('action') + str(nextState[space_Y][space_X + 1]) + " moves left.\n"
            nextState[space_Y][space_X] = nextState[space_Y][space_X + 1]
            nextState[space_Y][space_X + 1] = 0
            
            if nextState not in visited:
                visited.append(nextState)                
                stateQueue.put({'state': nextState, 'action': newAction, 'counter': current_state.get('counter') + 1})

        #space moves up
        if space_Y > 0:
            nextState = deepcopy(current_state.get('state'))
            newAction = current_state.get('action') + str(nextState[space_Y - 1][space_X]) + " moves down.\n"
            nextState[space_Y][space_X] = nextState[space_Y - 1][space_X]
            nextState[space_Y - 1][space_X] = 0
            
            if nextState not in visited:
                visited.append(nextState)                
                stateQueue.put({'state': nextState, 'action': newAction, 'counter': current_state.get('counter') + 1})

        #space moves down
        if space_Y < 2:
            nextState = deepcopy(current_state.get('state'))
            newAction = current_state.get('action') + str(nextState[space_Y + 1][space_X]) + " moves up.\n"
            nextState[space_Y][space_X] = nextState[space_Y + 1][space_X]
            nextState[space_Y + 1][space_X] = 0
            
            if nextState not in visited:
                visited.append(nextState)                
                stateQueue.put({'state': nextState, 'action': newAction, 'counter': current_state.get('counter') + 1})


if __name__ == "__main__":
    solve()