#include <stdio.h>
#include <stdlib.h>

#define DEFAULT 10

char** getInitialWorld(char* filename, int row, int column); 
void nextGeneration(char*** world, char*** newWorld, int row, int column);
void printWorld(int generationCount, char** map, int row, int column);
char** allocateWorld(int row, int column);
void freeWorld(char** world, int row);

int main(int argc, char *argv[]) {
	// Default values
	char* filename = "../input.txt";
	int row = DEFAULT;
	int column = DEFAULT;
	int generation = DEFAULT;

	// Check if input is vaild, cant take 6+ arguments
	if (argc > 1) {
		if (argc > 4) generation = atoi(argv[4]);
		if (argc > 3) filename = (char*)argv[3];
		if (argc > 2) column = atoi(argv[2]);
		row = atoi(argv[1]);
	}
	if (row == 0 || column == 0 || generation == 0 || argc > 5) {
		printf ("Error! invalid arguments\n");
		exit(1);
	}

	char** world = getInitialWorld(filename, row, column); 
	char** newWorld = allocateWorld(row, column);

	// Process the world
	for (int i = 0; i <= generation; ++i) {
		printWorld(i, world, row, column);
		nextGeneration(&world, &newWorld, row, column);
	}

	freeWorld(world, row);
	freeWorld(newWorld, row);
	return 0;
}

char** getInitialWorld(char* filename, int row, int column) {
	// Open the file and read
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error! opening file\n");
		exit(1);
	}

	char **world = allocateWorld(row, column);

	// Read from file
	for (int i = 0; i < row; ++i) {
		char chr = getc(file);
		for (int j = 0; j < column; ++j) {
			if (chr != EOF && chr != '\n'){
				world[i][j] = chr;
				chr = getc(file);
			} else
				// When the line is too short, fill the row with dead cells
				world[i][j] = ' ';
		}
		// When a line is too long, overlook the extra ones
		while (chr != EOF && chr != '\n') chr = getc(file);
	}
	fclose(file);

	return world;
}

void printWorld(int generationCount, char** map, int row, int column) {
	printf("Generation %i:\n", generationCount);

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) 
			(map[i][j] == ' ') ? printf("%c", '-') : printf("%c", map[i][j]);
		printf("\n");
	}

	printf("========================\n");
};

// Check if a cell is valid
int isValid(int r, int c, int row, int column) {
	return (r >= 0 && r < row && c >= 0 && c < column);
}

// Count neighbors
int countNeighbors(char** world, int i, int j, int row, int column) {
	int count = 0;
	count += (isValid(i - 1, j - 1, row, column) && world[i - 1][j - 1] == '*');
	count += (isValid(i - 1, j, row, column) && world[i - 1][j] == '*');
	count += (isValid(i - 1, j + 1, row, column) && world[i - 1][j + 1] == '*');
	count += (isValid(i, j - 1, row, column) && world[i][j - 1] == '*');
	count += (isValid(i, j + 1, row, column) && world[i][j + 1] == '*');
	count += (isValid(i + 1, j - 1, row, column) && world[i + 1][j - 1] == '*');
	count += (isValid(i + 1, j, row, column) && world[i + 1][j] == '*');
	count += (isValid(i + 1, j + 1, row, column) && world[i + 1][j + 1] == '*');
	return count;
}

void nextGeneration(char*** world, char*** newWorld, int row, int column) {
	// Decide alive or dead
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			int aliveCount = countNeighbors(*world, i, j, row, column);
			
			if (aliveCount < 2) 
				(*newWorld)[i][j] = ' ';
			else if (aliveCount > 3 && (*world)[i][j] == '*')
				(*newWorld)[i][j] = ' '; 
			else if (aliveCount == 3 && (*world)[i][j] == ' ') 
				(*newWorld)[i][j] = '*'; 
			else 
				(*newWorld)[i][j] = (*world)[i][j]; 
		}
	}
	
	// Copy over from newWorld
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j)
			(*world)[i][j] = (*newWorld)[i][j]; 
	}
}

char** allocateWorld(int row, int column) {
	char** world = (char **)malloc(row * sizeof(char*));

	for (int i = 0; i < row; i++) {
		world[i] = (char *)malloc(column * sizeof(char));
		if (!world[i]) {
			printf ("Error! allocate heap space\n");
			exit(1);
		}
	}
		
	if (!world) {
		printf ("Error! allocate heap space\n");
		exit(1);
	}

	return world;
}

void freeWorld(char** world, int row){
	for (int i = 0; i < row; i++)
		free(world[i]);
	free(world);
}