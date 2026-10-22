# Virtual Ant Maze

A C program that walks a virtual ant through a text maze by following a script of instructions. The ant leaves pheromone marks, senses how much open space lies in each direction, jumps toward it, and collects the numbered "good deeds" it lands on.

Final project for ESE 124 at Stony Brook University, by Joseph Cabrera.

## The maze

`maze.txt` holds the maze. `*` is a wall, a space is open floor, and each digit is a good deed worth that many points.

```
**********
*2   * 9 *
** **** **
**    3 **
*  ***  **
* 5 ** * *
* * **   *
*  7 *** *
*    **1 *
*  *     *
******** *
```

The ant starts in the gap in the bottom wall, at x = 8, y = 10 (x counts columns from the left, y counts rows from the top). When it lands on a digit, it adds the digit to its total, prints the total and clears the cell.

## Instructions

`Ant_Instructions.txt` is the ant's script, one instruction per line, carried out in order. Forward and back move the ant right and left across the maze as printed; left and right move it up and down.

| Instruction | What the ant does |
|---|---|
| `MARK` | Marks its cell with a pheromone (`+`) and prints the maze |
| `MOVE_F`, `MOVE_B`, `MOVE_L`, `MOVE_R` | Steps one cell forward, back, left or right, unless a wall is in the way |
| `CWL`, `CWR`, `CWF`, `CWB` | Counts the open cells to its left, right, front or back, up to the next wall or mark, and prints the count as an "itch" |
| `BJPI` | Bold jump: jumps the full itch in the first direction that has one, checking left, right, front, then back |
| `CJPI` | Cautious jump: moves one cell in that direction and lowers that itch by one |

The program also has memory-stack instructions (`PUSH`, `POP`, `PEEK`, `CLEAR`, `BACKTRACK`) and a repeat instruction (`RP_n_t`) that asks for n and t at the keyboard. The included script doesn't use them.

Each run writes the instructions the ant carried out to `Ant_Movements_Out.txt`, leaving out any move a wall blocked.

## Building and running

```bash
gcc -std=c99 ant_maze.c -o ant_maze
./ant_maze
```

Run it from this folder so it finds `maze.txt` and `Ant_Instructions.txt`. The program needs C99 or later, which `-std=c99` guarantees on older compilers.

## Sample run

With the included maze and script, the ant starts at the bottom, reaches the 3 and then the 9, and finishes with 12 good deeds. The program prints the maze whenever the ant marks a cell, the itch counts, and the ant's position after each move:

```
Ant Starting position: x: 8 y 10

Marked Maze:
**********
*2   * 9 *
** **** **
**    3 **
*  ***  **
* 5 ** * *
* * **   *
*  7 *** *
*    **1 *
*  *     *
********+*
Itch 5 spot(s) left
Itch 0 spot(s) right
Itch 0 spot(s) front
Itch 0 spot(s) back
Ant Location: x: 8 y: 5
...
Ant Location: x: 7 y: 1

good deeds: 12
```
