// Joseph Cabrera
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_NUMBER_OF_STEPS 1000
#define MAX_INSTRUCTION_LENGTH 30

typedef struct {
	int stack [MAX_SIZE][2];
	int top;
	int** maze; // pointer to maze array
} Stack; // stack for ant's memory

void initialize (Stack *s);
int isEmpty (Stack *s);
int isFull (Stack *s);
void push (Stack *s, int element1, int element2);
void pop (Stack *s, int *element1, int *element2);
int peek (Stack *s, int column);
void clear (Stack *s);
int checkLeft(Stack *s, int x, int y, int length);
int checkRight(Stack *s, int x, int y, int length);
int checkFront(Stack *s, int x, int y, int length);
int checkBack(Stack *s, int x, int y, int length);
int isOpen (char maze[][MAX_SIZE], int x, int y);
void backtrack (Stack *s, int x, int y, char *actions);
// function declarations

int main () {
	int i, j, k, l; // increments
	int x = 0, y = 0, xcount = 0; // coordinates
	int n = 0, t = 0; // for RP_n_t
	int repeatStart = 0, repeatEnd = 0, repeatsLeft = 0; // for RP_n_t
	int steps = 0; // count for MAX_NUMBER_OF_STEPS
	int mazeHeight, mazeDepth; //Size of maze from text
    int itchL = 0, itchR = 0, itchF = 0, itchB = 0; // itch and size
    int points = 0; // good deeds
	char maze [MAX_SIZE][MAX_SIZE], c; // local 2D array maze
	char actions [MAX_NUMBER_OF_STEPS][MAX_INSTRUCTION_LENGTH]; // stores instructions as strings
	FILE *fileInput, *fileInput1, *fileOutput;
	// maze.txt, Ant_Instructions.txt, Ant_Movements_Out.txt
	
	Stack antMemory;
	initialize (&antMemory); // stack (array)
	
	if ((fileInput = fopen ("maze.txt", "r")) == NULL)	{
		printf ("Error: maze.txt not found");
		exit (1);
	}
	if ((fileInput1 = fopen ("Ant_Instructions.txt", "r")) == NULL)	{
		printf ("Error: Ant_Instrutions.txt not found");
		exit (1);
	}
	if ((fileOutput = fopen ("Ant_Movements_Out.txt", "w")) == NULL)	{
		printf ("Error: Ant_Movements_Out.txt not found");
		exit (1);
	}	// check for files
	
	while ((fscanf (fileInput, "%c", &c)) == 1){
        if (c != '\n') {
			maze[x][y] = c;
			x++;
		}
		else {
			y++;
			x = 0;
			xcount++;
		}
    } // scan in maze.txt to maze array
    
    mazeHeight = y;
    mazeDepth = xcount - 1; // Set maze dimensions
    
    printf ("Starting Maze:\n");
	for (i = 0; i <= mazeDepth; i++) {
    	for (j = 0; j <= mazeHeight; j++) {
    	    printf ("%c", maze[j][i]);
    	}
  	printf("\n");
	}	// print starting maze
	
    printf ("\n"); // separate for clarity
        
	antMemory.maze = malloc(sizeof(int*) * mazeDepth);
	for (i = 0; i < mazeDepth; i++) {
    	antMemory.maze[i] = malloc(sizeof(int) * mazeHeight);
	}
	for (i = 0; i < mazeDepth; i++) {
    	for (j = 0; j < mazeHeight; j++) {
        	antMemory.maze[i][j] = maze[i][j];
    	}
	} // allocate memory for maze in the stack
    
    while (steps < MAX_NUMBER_OF_STEPS && fgets (actions[steps], MAX_INSTRUCTION_LENGTH, fileInput1) != NULL) {
    	if (actions[steps][0] != '\n')
    		steps++; // skip blank lines, like the ones at the end of the file
    }	// assign instructions to actions array
    
    x = 8;
    y = 10; // ant starting position
    
    printf ("Ant Starting position: x: %d y %d\n", x, y);
    
    printf ("\n"); // separate for clarity
    
    for (l = 0; l < steps; l++) { // translate actions
    
   		if ((strcmp (actions [l], "MARK\n")) == 0) { // 1
			maze[x][y] = '+'; // local
			antMemory.maze[x][y] = '+'; // stack

    		fprintf (fileOutput, "MARK\n");
    		// marking with "pheromone"

    		printf ("Marked Maze:\n");
			for (j = 0; j <= mazeDepth; j++) {
    			for (k = 0; k <= mazeHeight; k++) {
					printf ("%c", maze[k][j]);
    	  	}
				printf("\n");
		}	// reprint maze after mark
    } // marking with "pheromone"
    		
    	if ((strcmp (actions [l], "MOVE_F\n")) == 0) { // 2
    		if (isOpen (maze, x + 1, y)) {
				x += 1; // move ant forward
				fprintf (fileOutput, "MOVE_F\n"); 
				printf ("Ant Location: x: %d y: %d\n", x, y);
				}
		} 
			
		if ((strcmp (actions [l], "MOVE_B\n")) == 0) { // 3
			if (isOpen (maze, x - 1, y)) {
   				x -= 1; // Move ant backward
   				fprintf (fileOutput, "MOVE_B\n"); 
				printf ("Ant Location: x: %d y: %d\n", x, y);
				   }
		}
			
		if ((strcmp (actions [l], "MOVE_L\n")) == 0) { // 4
			if (isOpen (maze, x, y - 1)) {
   				y -= 1; // Move ant left
   				fprintf (fileOutput, "MOVE_L\n"); 
				printf ("Ant Location: x: %d y: %d\n", x, y);
				}
		}
			
		if ((strcmp (actions [l], "MOVE_R\n")) == 0) { // 5
			if (isOpen (maze, x, y + 1)) {
  				y += 1; //Move ant right
   				fprintf (fileOutput, "MOVE_R\n"); 
				printf ("Ant Location: x: %d y: %d\n", x, y);
				}
		}
			
		if ((strcmp (actions [l], "CWL\n")) == 0) { // 6
			itchL = checkLeft(&antMemory,x, y, mazeHeight);
			printf ("Itch %d spot(s) left\n", itchL);
			fprintf (fileOutput, "CWL\n");
		}	// detect left pheromone
		
		if ((strcmp (actions [l], "CWR\n")) == 0) { // 7
   			itchR = checkRight(&antMemory, x, y, mazeHeight);
			printf ("Itch %d spot(s) right\n", itchR);
   			fprintf (fileOutput, "CWR\n");
		}	// detect right pheromone
		
		if ((strcmp (actions [l], "CWF\n")) == 0) { // 8
   			itchF = checkFront(&antMemory, x, y, mazeDepth);
			printf ("Itch %d spot(s) front\n", itchF);
   			fprintf (fileOutput, "CWF\n");
		}	// detect front pheromone
		
		if ((strcmp (actions [l], "CWB\n")) == 0) { // 9
		   	itchB = checkBack(&antMemory, x, y, mazeDepth);
			printf ("Itch %d spot(s) back\n", itchB);
   			fprintf (fileOutput, "CWB\n");
		}	// detect back pheromone
		
		if ((strcmp (actions [l], "PUSH\n")) == 0) { // 10
   			push (&antMemory, x, y);
   			fprintf (fileOutput, "PUSH\n");
		}	// remember position
		
		if ((strcmp (actions [l], "POP\n")) == 0) { // 11
		   	pop (&antMemory, &x, &y);
   			pop (&antMemory, &x, &y);
   			fprintf (fileOutput, "POP\n");
		}	// remember position and forget later
		
		if ((strcmp (actions [l], "PEEK\n")) == 0) { // 12
		   	peek(&antMemory,0);
   			peek(&antMemory,1);
			fprintf (fileOutput, "PEEK\n"); 
		}	// remember position and do not forget
		
		if ((strcmp (actions [l], "CLEAR\n")) == 0) { // 13
			clear (&antMemory);
			fprintf (fileOutput, "CLEAR\n"); 
		}	// clear ants memory
		
		if ((strcmp (actions [l], "BJPI\n")) == 0) { // 14
			if (itchL != 0) {
				y -= itchL; // left amount of itch spots
				itchL -= itchL; // get rid of left itch
				printf ("Ant Location: x: %d y: %d\n", x, y);
			}
			else if (itchR != 0) {
				y += itchR; // right amount of itch spots
				itchR -= itchR; // get rid of right itch
				printf ("Ant Location: x: %d y: %d\n", x, y);
			}
			else if (itchF != 0) {
				x += itchF; // forward amount of itch spots
				itchF -= itchF; // get rid of forward itch
				printf ("Ant Location: x: %d y: %d\n", x, y);
			}
			else if (itchB != 0) {
				x -= itchB; // backward amount of itch spots
				itchB -= itchB; // get rid of backward itch
				printf ("Ant Location: x: %d y: %d\n", x, y);
			}	
			fprintf (fileOutput, "BJPI\n"); 
		}	// bold jump for itching
		
		if ((strcmp (actions [l], "CJPI\n")) == 0) { // 15
			if (itchL != 0) {
				y -= 1; // left one spot if itch
				itchL -= 1; // decrement left itch
				printf ("Ant Location: x: %d y: %d\n", x, y);
			}
			else if (itchR != 0) {
				y += 1; // right one spot if itch
				itchR -= 1; // decrement right itch
				printf ("Ant Location: x: %d y: %d\n", x, y);
			}
			else if (itchF != 0) {
				x += 1; // forward one spot if itch
				itchF -= 1; // decrement forward itch
				printf ("Ant Location: x: %d y: %d\n", x, y);
			}
			else if (itchB != 0) {
				x -= 1; // backward one spot if itch
				itchB -= 1; // decrement backward itch
				printf ("Ant Location: x: %d y: %d\n", x, y);
			}	
   			 fprintf (fileOutput, "CJPI\n"); 
		}	// cautious jump for itching
		
		if ((strcmp (actions [l], "BACKTRACK\n")) == 0) { // 16
			backtrack (&antMemory, x, y, actions[l]);
			
   			 fprintf (fileOutput, "BACKTRACK\n"); 
		}	// backtrack to a pop or push
		
		if ((strcmp (actions [l], "RP_n_t\n")) == 0) { // 17
			n = 0; // stays 0 if nothing is typed
			t = 0;
			printf ("n = ");
			scanf ("%d", &n);
			getchar ();
			printf ("t = ");
			scanf ("%d", &t);
			getchar ();	
   		 	 fprintf (fileOutput, "RP_n_t\n"); 
			if (n > 0 && t > 0 && l + 1 < steps) {
				repeatStart = l + 1; // first action to repeat
				repeatEnd = l + n; // last action to repeat
				if (repeatEnd > steps - 1)
					repeatEnd = steps - 1;
				repeatsLeft = t;
			}
		}	// repeat the next n actions t more times
		
		if (antMemory.maze[x][y] >= '1' && antMemory.maze[x][y] <= '9')  {
   		points += (antMemory.maze[x][y] - 48);
   		printf ("\ngood deeds: %d\n\n", points);
   		maze[x][y] = ' ';
   		antMemory.maze[x][y] = 32; //ascii for space
   		} // calculating and displaying 'good deeds'

		if (l == repeatEnd && repeatsLeft > 0) {
			repeatsLeft--;
			l = repeatStart - 1; // l++ takes the loop back to repeatStart
		}	// RP_n_t: go back to the first repeated action
   		
   		
	}  // for
	for (i = 0; i < mazeDepth; i++) {
    free(antMemory.maze[i]);
	}
	free(antMemory.maze);
// free previously allocated memory

	fclose (fileInput);
	fclose (fileInput1);
	fclose (fileOutput);
	// close files
} // main

void initialize (Stack *s) {
	s->top = -1;
}

int isEmpty (Stack *s) {
	return (s->top == -1);
}

int isFull (Stack *s) {
	return (s->top == MAX_SIZE - 1);
}

void push (Stack *s, int element1, int element2) {
	if (!isFull (s)) {
		s->top++;
   		s->stack[s->top][0] = element1;
   		s->stack[s->top][1] = element2;
	}
	else
		printf ("Error: Overflow\n");
}

void pop (Stack *s, int *element1, int *element2) {
	if (!isEmpty (s)) {
		*element1 = s->stack[s->top][0];
		*element2 = s->stack[s->top][1];
		s->top--;
	}
	else
		printf ("Error: Underflow\n");
}

int peek (Stack *s, int column) {
	if (!isEmpty (s)) 
		return s->stack[s->top][column];
	else {
		printf ("Error: Stack is empty\n");
		return -1;
	}
}

void clear (Stack *s) {
	s->top = -1;
}

int checkLeft(Stack *s, int x, int y, int length){
    int i;
    int open = 0;
    for(i = y - 1; i >= 0; i--) {
   		if(s->maze[x][i] != '*' && s->maze[x][i] != '+') 
   			open++;
   		else
   			return open;
   	}
   	return 0;
}

int checkRight(Stack *s, int x, int y, int length) {
    int i;
    int open = 0;
    for (i = y + 1; i < length; i++) {
   	 if (s->maze[x][i] != '*' && s->maze[x][i] != '+') 
   	 	open++;
   	 else 
	 	return open;
    }
    return 0;
}

int checkFront(Stack *s, int x, int y, int length){
    int i;
    int open = 0;
    for(i = x + 1; i < length; i++) {
   	 if(s->maze[i][y] != '*' && s->maze[i][y] != '+') 
   		 open++;
   	 else
   	 	return open;
    }
    return 0;
}

int checkBack(Stack *s, int x, int y, int length) {
    int i;
    int open = 0;
    for(i = x - 1; i >= 0; i--) {
   	 if(s->maze[i][y] != '*' && s->maze[i][y] != '+') 
   		 open++;
   	 else
   	 	return open;
	}
	return 0;
}

int isOpen (char maze[][MAX_SIZE], int x, int y) {
	return maze[x][y] != '*' && maze[x][y] != '+';
} // the ant can move into a cell that is not a wall and not marked

void backtrack (Stack *s, int x, int y, char *actions) {
	if (!isEmpty (s)) {
		int prevX, prevY;
		pop (s, &prevX, &prevY);
		if (prevX > x) 
			actions = "MOVE_B\n";
		else if (prevX < x) 
			actions = "MOVE_F\n";
		else if (prevY > y)
			actions = "MOVE_L\n";
		else if (prevY < y)
			actions = "MOVE_R\n";
		printf ("Ant Location: x: %d y: %d\n", x, y);
	}
	else {
		printf ("Memory is empty\n");
	}
}
