import queue
import timeit

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


def swap_char(s, i, j):
    l = list(s)
    l[i], l[j] = l[j], l[i]
    return ''.join(l)

def print_result(initial_state, space_action):
    result = ''
    action = ''
    current_matrix = initial_state
    result = 'Initial State:\n' + to_matrix_from_string(current_matrix) + '\n\n'
    for char in space_action:
        empty_index = current_matrix.index('0')
        if char == 'L':
            action = current_matrix[empty_index - 1] + ' moves right.\n'
            current_matrix = swap_char(current_matrix, empty_index, empty_index - 1)

        if char == 'R':
            action = current_matrix[empty_index + 1] + ' moves left.\n'
            current_matrix = swap_char(current_matrix, empty_index, empty_index + 1)

        if char == 'U':
            action = current_matrix[empty_index - 3] + ' moves down.\n'
            current_matrix = swap_char(current_matrix, empty_index, empty_index - 3)

        if char == 'D':
            action = current_matrix[empty_index + 3] + ' moves up.\n'
            current_matrix = swap_char(current_matrix, empty_index, empty_index + 3)

        result += action + to_matrix_from_string(current_matrix) + '\n\n'

    result += 'Total moves: {0}'.format(len(space_action))
    print(result)

def to_matrix_from_string(s):
    return "{0} {1} {2}\n{3} {4} {5}\n{6} {7} {8}".format(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8])


def solve_IDS(initial_state, goal_state):

    current_depth = -1
    while True:
        current_depth += 1
        print(current_depth)
        visited = {initial_state: 0}
        stateStack = Stack()
        stateStack.push({'state': initial_state, 'space_action': ''})

        while not stateStack.isEmpty():
            current_state = stateStack.pop()
            if current_state.get('state') == goal_state:
                print_result(initial_state, current_state.get('space_action'))
                return

            if len(current_state.get('space_action')) >= current_depth:
                continue

            empty_index = current_state.get('state').index('0')


            # space moves up
            if not (empty_index == 0 or empty_index == 1 or empty_index == 2):
                next_state = swap_char(current_state.get('state'), empty_index, empty_index - 3)
                if (next_state not in visited) or (visited[next_state] > len(current_state.get('space_action')) + 1):
                    visited[next_state] = len(current_state.get('space_action')) + 1
                    stateStack.push({'state': next_state, 'space_action': current_state.get('space_action') + 'U'})

            # space moves left
            if not (empty_index == 0 or empty_index == 3 or empty_index == 6):
                next_state = swap_char(current_state.get('state'), empty_index, empty_index - 1)
                if (next_state not in visited) or (visited[next_state] > len(current_state.get('space_action')) + 1):
                    visited[next_state] = len(current_state.get('space_action')) + 1
                    stateStack.push({'state': next_state, 'space_action': current_state.get('space_action') + 'L'})
            
            # space moves down
            if not (empty_index == 6 or empty_index == 7 or empty_index == 8):
                next_state = swap_char(current_state.get('state'), empty_index, empty_index + 3)
                if (next_state not in visited) or (visited[next_state] > len(current_state.get('space_action')) + 1):
                    visited[next_state] = len(current_state.get('space_action')) + 1
                    stateStack.push({'state': next_state, 'space_action': current_state.get('space_action') + 'D'})

            # space moves right
            if not (empty_index == 2 or empty_index == 5 or empty_index == 8):
                next_state = swap_char(current_state.get('state'), empty_index, empty_index + 1)
                if (next_state not in visited) or (visited[next_state] > len(current_state.get('space_action')) + 1):
                    visited[next_state] = len(current_state.get('space_action')) + 1
                    stateStack.push({'state': next_state, 'space_action': current_state.get('space_action') + 'R'})



if __name__ == "__main__":
    start = timeit.default_timer()

    initial_state = ""
    initial_state += input().replace(" ", "")
    initial_state += input().replace(" ", "")
    initial_state += input().replace(" ", "")

    goal_state = ""
    goal_state += input().replace(" ", "")
    goal_state += input().replace(" ", "")
    goal_state += input().replace(" ", "")
    
    solve_IDS(initial_state, goal_state)

    stop = timeit.default_timer()

    print('Time used: {0}'.format(stop - start))