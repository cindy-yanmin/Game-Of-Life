#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
using namespace std;

const size_t SIDE = 10;

void getInitialWorld(ifstream& ifs, vector<string>& world); 
void nextGeneration(vector<string>& world);
void printWorld(int generationCount, const vector<string>& world);

int main() {
	ifstream ifs("../input.txt");
	if (!ifs) {
		cout << "Could not open the file.\n";
		exit(1);
	}

	// Construct the world
	int generation;
	cout << "Input generation number." << endl;
	cin >> generation;

	vector<string> world;
	getInitialWorld(ifs, world);

	// Generations
	for (int i = 0; i <= generation; ++i) {
		printWorld(i, world);
		nextGeneration(world);
	}

	ifs.close();
}

void getInitialWorld(ifstream& ifs, vector<string>& world) {
	string line;
	while (getline(ifs, line)) {
		if (line.size() < SIDE) {
			for (size_t i = 0; i < SIDE-line.size(); )
				line += " ";
		}
		world.push_back(line.substr(0, SIDE));
	}

	if (world.size() < SIDE) {
		line = "";
		for (size_t i = 0; i < SIDE; i++)
			line += " ";
		for (size_t i = 0; i < SIDE-world.size(); )
			world.push_back(line);
	}
}

void printWorld(int generationCount, const vector<string>& world) {
	cout << "Generation: " << generationCount << endl;
	for (const string& row : world) {
		for (char c: row) 
			(c == ' ') ? cout << '-' : cout << c;
		cout << endl;
	} 
	cout << "========================" << endl;
}

bool isValidCell (int r, int c) {
	return (r >= 0 && r < int(SIDE) && c >=0 && c < int(SIDE));
}

int neighborNum(int row, int col, const vector<string>& world) {
	int count = 0;
	for (int r = -1; r <= 1; ++r) {
		for (int c = -1; c <= 1; ++c) {
			if (r == 0 && c == 0) continue;
			if (isValidCell(row + r, col + c) && world[row + r][col + c] == '*')
				count++;
		}
	}
	return count;
}

void nextGeneration(vector<string>& world) {
	vector <string> newWorld;

	for (size_t r = 0; r < world.size(); r++) {
		string line;
		for (size_t c = 0; c < world[r].length(); c++) {
			int aliveCount = neighborNum(r, c, world);
			
			if (aliveCount < 2)
				line += ' ';
			else if (aliveCount > 3 && world[r][c] == '*')
				line += ' ';
			else if (aliveCount == 3 && world[r][c] == ' ')
				line += '*';
			else 
				line += world[r][c];
		}
		newWorld.push_back(line);
	}
	world = newWorld;
}
