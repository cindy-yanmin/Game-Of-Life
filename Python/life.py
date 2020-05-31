import sys

SIDE = 10

def getInitialWorld():
    try:
        file = open("../input.txt", "r")
        lines = file.readlines()
        file.close()
    except Exception:
        sys.exit("Failed to open file!!!")  

    world = []
    for r in range (SIDE):
        line = []
        for c in range (SIDE):
            if (r < len(lines) and c < len(lines[r]) and lines[r][c] == '*'):
                line.append(True)
            else:
                line.append(False)
        world.append(line)
    
    return world

def printWorld(world, generationNum = 0):
    print("Generation", generationNum, ":")
    for r in range (len(world)):
        for c in range (len(world[r])):
            if (world[r][c]):
                print('*', end='')
            else:
                print('-', end='')
        print('')
    print("========================")

def isValidCell(row, col):
    return (row >= 0 and row < SIDE and col >= 0 and col < SIDE)

def neighborNum(row, col, world):
    count = 0
    for r in range (-1, 2 ,1 ):
        for c in range (-1, 2 ,1 ):
            if (r == 0 and c == 0):
                continue
            if (isValidCell(row + r, col + c) and world[row + r][col + c]):
                count += 1
            
    return count

def nextGeneration(world):
    newWorld = []

    for r in range (SIDE):
        line = []
        for c in range (SIDE):
            aliveCount = neighborNum(r, c, world)
            if (aliveCount < 2):
                line.append(False)
            elif (aliveCount > 3 and world[r][c]):
                line.append(False)
            elif (aliveCount == 3 and not world[r][c]):
                line.append(True)
            else:
                line.append(world[r][c])
        newWorld.append(line)

    return newWorld
        
if __name__ == "__main__":

    while True:
        try:
            generation = int(input("Input generation number.\n"))
            break
        except Exception:
            print("Invalid input!!!")
    
    world = getInitialWorld()
    for i in range (generation+1):
        printWorld(world, i)
        world = nextGeneration(world)