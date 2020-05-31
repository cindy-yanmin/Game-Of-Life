import java.io.File;
import java.util.Scanner;
import java.lang.Exception;

// Creating 3 classes here is for practicing polymorphism
abstract class Cell {
    public Cell() {
        numOfNeighbor = 0;
    }
    public boolean isAlive;
    public int numOfNeighbor;
    public abstract void display();
} 
class AliveCell extends Cell {
    public AliveCell() {
        super();
        isAlive = true;
    }
    @Override
    public void display() {
        System.out.print("*");
    }
}
class DeadCell extends Cell {
    public DeadCell() {
        super();
        isAlive = false;
    }
    @Override
    public void display() {
        System.out.print("-");
    }
}
  
class life { 
    public static final int SIDE = 10;

    public static Cell[][] getInitialWorld() {
        Cell[][] world = new Cell[SIDE][SIDE];

        try {
            Scanner scanner = new Scanner(new File("../input.txt"));
            
            for (int r = 0; r < world.length; r++) {
                String line = "";
                if (scanner.hasNextLine()) line = scanner.nextLine();
                
                for (int c = 0; c < world[r].length; c++) {
                    if (c < line.length() && line.charAt(c)=='*') 
                        world[r][c] = new AliveCell();
                    else 
                        world[r][c] = new DeadCell();
                }
            }
			scanner.close();
		} catch (Exception e) {
            System.out.println("Failed to open the file");
			System.exit(0);
        }

        return world;
    }

    public static void printWorld(int generationNum, Cell[][] world) {
        System.out.println("Generation "+generationNum+":");
        for (int r = 0; r < world.length; r++) {
            for (int c = 0; c < world[r].length; c++) {
                world[r][c].display();
            }
            System.out.println("");
        }
        System.out.println("========================");
    }

    public static boolean isValidCell(int r, int c) {
        return (r >= 0 && r < SIDE && c >=0 && c < SIDE);
    }

    public static void neighborNum(int row, int col, Cell[][] world) {
        int count = 0;
        for (int r = -1; r <= 1; r++) {
            for (int c = -1; c <= 1; c++) {
                if (r == 0 && c == 0) continue;
                if (isValidCell(row + r, col + c) && world[row + r][col + c].isAlive)
                    count++;
            }
        }
        world[row][col].numOfNeighbor = count;
    }

    public static void nextGeneration(Cell[][] world) {
        for (int r = 0; r < world.length; r++) {
            for (int c = 0; c < world[r].length; c++) {
                neighborNum(r, c, world);
            }
        }

        for (int r = 0; r < world.length; r++) {
            for (int c = 0; c < world[r].length; c++) {
                int aliveCount = world[r][c].numOfNeighbor;
                if (aliveCount < 2) {
                    world[r][c] = new DeadCell();
                } else if (aliveCount > 3 && world[r][c].isAlive){
                    world[r][c] = new DeadCell();
                } else if (aliveCount == 3 && !world[r][c].isAlive){
                    world[r][c] = new AliveCell();
                } 
            }
        }
    }

    public static void main(String args[]) { 
        Scanner scanner = new Scanner(System.in);  
        System.out.println("Input generation number.");
        int generation = scanner.nextInt(); 

        // Construct the world
        Cell[][] world = getInitialWorld();

        // Process generations
        for (int i = 0; i <= generation; i++) {
            printWorld(i, world);
            nextGeneration(world);
        }
    } 
} 