#include <stdio.h>
#include <stdlib.h>

//Print a world
void printWorld(char** map, int row, int column) {
	int i, j;
	for (i = 0; i < row; ++i) {
		for (j = 0; j < column; ++j) {
			if (map[i][j] == '*' ||  map[i][j] == '=')
				printf("%c", map[i][j]);
			else	printf("%c", '-');
		}
		printf("\n");
	}
};

//Check if a cell is valid
int isValid(int r, int c, int row, int column) {
	return ((r >= 0 && r + 1 < row) && (c >= 0 && c < column));
}

//Count neighbors
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

//Generate new world
char** newGeneration(char** world, int row, int column) {
	int i, j;
	//Allocate 2D array on heap
	char **newWorld = (char **)malloc((row) * sizeof(char *));
	for (i = 0; i < row; i++)
		newWorld[i] = (char *)malloc(column * sizeof(char));
	if (!world) {
		printf ("Error! allocate heap space\n");
		exit(1);
	}

	//Decide alive or dead
	for (i = 0; i < row; ++i) {
		for (j = 0; j < column; ++j) {
			int neighborCount = countNeighbors(world, i, j, row, column);
			char cell = '-';
			if (world[i][j] == '*' && (neighborCount == 2 || neighborCount == 3)) cell = '*';
			if (world[i][j] == '-' && (neighborCount == 3)) cell = '*';
			if (world[i][j] == '=') cell = '=';
			newWorld[i][j] = cell;
		}
	}
	return newWorld;
}

int main(int argc, char *argv[]) {
	//Default values
	char* filename = "life.txt";
	int row = 10;
	int column = 10;
	int generation = 10;

	//Check if input is vaild, cant take 6+ arguments
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

	//Allocate 2D array on heap
	int i, j;
	char **world = (char **)malloc((++row) * sizeof(char *));
	for (i = 0; i < row; i++)
		world[i] = (char *)malloc(column * sizeof(char));
	if (!world) {
		printf ("Error! allocate heap space\n");
		exit(1);
	}

	//Open the file and read
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error! opening file\n");
		exit(1);
	}

	//Store the info on heap
	for (i = 0; i < row; ++i) {
		for (j = 0; j < column; ++j) {
			char chr = getc(file);
			//Make a line that divides worlds
			if (i == row - 1)	world[i][j] = '=';
			//Fill in according to the input file
			else if (chr == '*' || chr == '-')	world[i][j] = chr;
		}
		//When a line is too long, overlook the extra ones
		char chr = getc(file);
		while (chr == '*' || chr == '-') chr = getc(file);
	}
	fclose(file);

	//Print initial world
	printf("Initial World\n");
	printWorld(world, row, column);

	//Print generations
	int f;
	for (i = 1; i < generation + 1; ++i) {
		printf("Generation: %i\n", i);
		char** oldWorld = world;
		world = newGeneration(world, row, column);
		//Free heap space
		for (f = 0; f < row; f++)
			free(oldWorld[f]);
		free(oldWorld);
		printWorld(world, row, column);
	}

	//Free heap space
	for (f = 0; f < row; f++)
		free(world[f]);
	free(world);
	return 0;
}
