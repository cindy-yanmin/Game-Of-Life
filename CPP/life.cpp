#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
using namespace std;

void printWorld(const vector<string>& world) {
	/*for (string row : world) {
	cout << row << endl;} */
	for (string row : world) {
		for (size_t i = 0; i < row.length(); i++) {
			if (row[i] == '-') {
				cout << " ";
			}
			else if (row[i] == '*') {
				cout << "*";
			}
		}
		cout << endl;
	}
	cout << "========================" << endl;
}

int neighborNum(const vector<string>& world, int row, int col) {
	int output = 0;
	for (int r = -1; r < 2; r++) {
		for (int c = -1; c < 2; c++) {
			if (world[row + r][col + c] == '*') {
				output++;
			}
		}
	}
	if (world[row][col] == '*') {
		output--;
	}
	return output;
}

void nextGeneration(vector<string>& world) {
	vector <string> newWorld = world;
	for (size_t r = 1; r < world.size() - 1; r++) {
		for (size_t c = 1; c < world[r].length() - 1; c++) {
			if (world[r][c] == '-' || world[r][c] == '*') {
				int neighbor = neighborNum(world, r, c);
				if (!(neighbor == 2 || neighbor == 3)) {
					newWorld[r][c] = '-';
				}
				if (world[r][c] == '-' && neighbor == 3) {
					newWorld[r][c] = '*';
				}
			}
		}
	}
	world = newWorld;
}

int main() {
	ifstream ifs("life.txt");
	vector<string> world;
	int generation;
	cout << "Input generation number." << endl;
	cin >> generation;

	if (!ifs) {
		cout << "Could not open the file.\n";
		exit(1);
	}
	else {

		string firstline;
		getline(ifs, firstline);
		int length = firstline.length() + 2;

		string edge;
		for (int i = 0; i < length; i++) {
			edge += "=";
		}

		//create the initial world
		world.push_back(edge);
		world.push_back("=" + firstline + "=");
		string line;
		while (getline(ifs, line)) {
			world.push_back("=" + line + "=");
		}
		world.push_back(edge);

		cout << "Initial World" << endl;
		printWorld(world);

		// generation
		for (int i = 1; i <= generation; i++) {
			nextGeneration(world);
			cout << "Generation: " << i << endl;
			printWorld(world);
		}

	}

	ifs.close();
}