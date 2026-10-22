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

`Ant_Instructions.txt` is the ant's script, one instruction per line, carried out in order. Blank lines are skipped, and the program reads up to 1,000 instructions (`MAX_NUMBER_OF_STEPS` in `ant_maze.c`). Forward and back move the ant right and left across the maze as printed; left and right move it up and down.

| Instruction | What the ant does |
|---|---|
| `MARK` | Marks its cell with a pheromone (`+`) and prints the maze |
| `MOVE_F`, `MOVE_B`, `MOVE_L`, `MOVE_R` | Steps one cell forward, back, left or right, unless that cell is a wall or a mark |
| `CWL`, `CWR`, `CWF`, `CWB` | Counts the open cells to its left, right, front or back, up to the next wall or mark, and prints the count as an "itch" |
| `BJPI` | Bold jump: jumps the full itch in the first direction that has one, checking left, right, front, then back |
| `CJPI` | Cautious jump: moves one cell in that direction and lowers that itch by one |
| `PUSH` | Saves its position in memory (a stack) |
| `POP` | Returns to the last saved position and removes it from memory |
| `PEEK` | Returns to the last saved position but keeps it in memory |
| `CLEAR` | Erases its memory |
| `BACKTRACK` | Same as `POP`, and prints the new position |
| `RP_n_t` | Asks for n and t at the keyboard, then runs the next n instructions t more times |

The included script doesn't use the memory or repeat instructions.

Each run writes the instructions the ant carried out to `Ant_Movements_Out.txt`, leaving out any move that was blocked.

## Building and running

```bash
gcc -std=c99 ant_maze.c -o ant_maze
./ant_maze
```

Run it from this folder so it finds `maze.txt` and `Ant_Instructions.txt`.

## Sample run

With the included maze and script, the ant starts at the bottom, collects the 3 and then the 9 for 12 good deeds, and ends at x = 7, y = 4. The program prints the maze whenever the ant marks a cell, the itch counts, and the ant's position after each move. A run starts like this:

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
```

It ends with the maze as the ant left it. The 3 and the 9 are gone, and each `+` is one of the ant's four marks:

```
**********
*2   * + *
** **** **
**      **
*  *** +**
* 5 ** *+*
* * **   *
*  7 *** *
*    **1 *
*  *     *
********+*
```
