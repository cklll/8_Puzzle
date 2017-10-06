from copy import deepcopy

class Stack:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def size(self):
         return len(self.items)

def solve(initial_state, goal_state, max_depth):

    stateStack = Stack()
    stateStack.push({'state': initial_state, 'action': '', 'counter': 0})

    visited = []
    visited.append(deepcopy(initial_state))
    counter = 0
    while not stateStack.isEmpty():
        counter += 1
        print(counter)
        print(stateStack.size())
        current_state = stateStack.pop()


        if current_state.get('state') == goal_state:
            return 'Number of moves is {0}.\n{1}'.format(current_state.get('counter'), current_state.get('action'))
        
        if max_depth == current_state.get('counter'):
            continue

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
                stateStack.push({'state': nextState, 'action': newAction, 'counter': current_state.get('counter') + 1})

        #space moves right
        if space_X < 2:
            nextState = deepcopy(current_state.get('state'))
            newAction = current_state.get('action') + str(nextState[space_Y][space_X + 1]) + " moves left.\n"
            nextState[space_Y][space_X] = nextState[space_Y][space_X + 1]
            nextState[space_Y][space_X + 1] = 0
            
            if nextState not in visited:
                visited.append(nextState)                
                stateStack.push({'state': nextState, 'action': newAction, 'counter': current_state.get('counter') + 1})

        #space moves up
        if space_Y > 0:
            nextState = deepcopy(current_state.get('state'))
            newAction = current_state.get('action') + str(nextState[space_Y - 1][space_X]) + " moves down.\n"
            nextState[space_Y][space_X] = nextState[space_Y - 1][space_X]
            nextState[space_Y - 1][space_X] = 0
            
            if nextState not in visited:
                visited.append(nextState)                
                stateStack.push({'state': nextState, 'action': newAction, 'counter': current_state.get('counter') + 1})

        #space moves down
        if space_Y < 2:
            nextState = deepcopy(current_state.get('state'))
            newAction = current_state.get('action') + str(nextState[space_Y + 1][space_X]) + " moves up.\n"
            nextState[space_Y][space_X] = nextState[space_Y + 1][space_X]
            nextState[space_Y + 1][space_X] = 0
            
            if nextState not in visited:
                visited.append(nextState)
                stateStack.push({'state': nextState, 'action': newAction, 'counter': current_state.get('counter') + 1})

    return False

if __name__ == "__main__":
    
    state = []
    state.append(list(map(int,input().split(" "))))
    state.append(list(map(int,input().split(" "))))
    state.append(list(map(int,input().split(" "))))

    goal_state = []
    goal_state.append(list(map(int,input().split(" "))))
    goal_state.append(list(map(int,input().split(" "))))
    goal_state.append(list(map(int,input().split(" "))))

    current_depth = 0
    result = solve(state, goal_state, current_depth)
    while not result:
        current_depth += 1
        result = solve(state, goal_state, current_depth)

    print(result)