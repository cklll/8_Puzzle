# [8_Puzzle](https://en.wikipedia.org/wiki/15_puzzle)

## BFS
```
cat input.txt goal.txt | python 8_puzzle.py BFS
```
## Iterative Deepening Search
```
cat input.txt goal.txt | python 8_puzzle.py IDS
```
## A* Search with number of misplaced tiles
```
cat input.txt goal.txt | python 8_puzzle.py AStar_Misplaced
```
## A* Search with Manhattan distance
```
cat input.txt goal.txt | python 8_puzzle.py AStar_Manhattan
```