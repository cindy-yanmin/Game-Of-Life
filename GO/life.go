package main

import ( 
	"os"
	"fmt"
	"log"
	"bufio"
)

const SIDE = 10

// variables declared without an explicit initial value are set as
// bool - false, int - 0, string - "", etc
type Cell struct {  
    IsAlive bool
    NumOfNeighbor int
}

func (cell *Cell) display() {
    if (cell.IsAlive) {
		fmt.Print("*")
	} else {
		fmt.Print("-")
	}
}

func getInitialWorld() [][]Cell {
	file, err := os.Open("../input.txt")
	if err != nil {
		log.Fatal(err)
		os.Exit(1)
	}
	// defer will be executed at the end of this scope
	defer file.Close()

	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanLines)
	
	world := make([][]Cell, SIDE)
	for r := 0; r < SIDE; r++ {
		world[r] = make([]Cell, SIDE)

		read := scanner.Scan() // getline()
		line := scanner.Text()
		for c := 0; c < SIDE; c++ {
			if (read && c < len(line) && line[c]=='*') {
				world[r][c].IsAlive = true
			} 
		}
	}
	return world
}

func printWorld(generationNum int, world [][]Cell) {
	fmt.Printf("Generation %d:\n", generationNum)
	for _, row := range world {
		for _, cell := range row {
			cell.display()
		}
		fmt.Println("")
	}
	fmt.Println("========================")
}

func isValidCell (r int, c int) bool {
	return (r >= 0 && r < SIDE && c >=0 && c < SIDE)
}

func neighborNum(row int, col int, world *[][]Cell, done chan<- bool) {
	count := 0
	for r := -1; r <= 1; r++ {
		for c := -1; c <= 1; c++ {
			if (r == 0 && c == 0) {
				continue;
			}
			if (isValidCell(row + r, col + c) && (*world)[row + r][col + c].IsAlive) {
				count++;
			}
				
		}
	}
	(*world)[row][col].NumOfNeighbor = count
	done <- true
}

func nextGeneration(world *[][]Cell) {
	// Count alive neighbors using goroutines
	done := make(chan bool)

	for r := 0; r < SIDE; r++ {
		for c := 0; c < SIDE; c++ {
			go neighborNum(r, c, world, done)
		}
	}

	// Wait for all goroutines using channel
	for i := 0; i < SIDE*SIDE; i++ { <-done }

	// Done counting, update the alive status of each cell
	for r := 0; r < SIDE; r++ {
		for c := 0; c < SIDE; c++ {
			aliveCount := (*world)[r][c].NumOfNeighbor
			if (aliveCount < 2) {
				(*world)[r][c].IsAlive = false
			} else if (aliveCount > 3 && (*world)[r][c].IsAlive){
				(*world)[r][c].IsAlive = false
			} else if (aliveCount == 3 && !(*world)[r][c].IsAlive){
				(*world)[r][c].IsAlive = true
			} 
		}
	}
}

func main() {
	var generation int
	fmt.Println("Input generation number.")
	fmt.Scan(&generation)

	// Construct the world
	world := getInitialWorld()

	// Process generations
	for i := 0; i <= generation; i++ {
		printWorld(i, world)
		nextGeneration(&world)
	}
}