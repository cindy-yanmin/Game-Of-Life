import React from 'react';

function Life({input, setContent}) {
    const SIDE = 10;

    var content = "";
    var world = getInitialWorld(input);

    for (var i = 0; i <= 10; ++i) {
        printWorld(i, world);
        world = nextGeneration(world);
    }

    function getInitialWorld(input) {
        var charIndex = 0;
        var world = [];

        for (var r = 0; r < SIDE; ++r) {
            world.push([]);
            for (var c = 0; c < SIDE; ++c) {
                if (input[charIndex] && input[charIndex]!=="\n") {
                    if (input[charIndex]==="*") world[r].push("*");
                    else world[r].push("-");
                    charIndex++;
                } else {
                    world[r].push("-");
                }
            }
            ++charIndex;
        }

        return world;
    }

    function printWorld(generationCount, world) {
        content += "Generation " + generationCount + ":\n";
        for (var r = 0; r < SIDE; ++r) {
            for (var c = 0; c < SIDE; ++c) {
                content += world[r][c];
            }
            content += "\n";
        }
        content += "====================\n";
        setContent(content);
    }

    function nextGeneration(world) {
        var newWorld = [];
        for (var r = 0; r < SIDE; ++r) {
            newWorld.push([]);
            for (var c = 0; c < SIDE; ++c) {
                const aliveCount = getAliveNeighbours(r, c, world);
                if (aliveCount < 2)
                    newWorld[r].push("-");
                else if (aliveCount > 3 && world[r][c] === "*")
                    newWorld[r].push("-");
                else if (aliveCount === 3 && world[r][c] === "-")
                    newWorld[r].push("*");
                else 
                    newWorld[r].push(world[r][c]);
            }
        }
        return newWorld;
    }

    function isValidCell (r, c) {
        return (r >= 0 && r < SIDE && c >=0 && c < SIDE);
    }

    function getAliveNeighbours (row, col, world) {
        var count = 0;
        for (var r = -1; r <= 1; ++r) {
            for (var c = -1; c <= 1; ++c) {
                if (r === 0  && c === 0) continue;
                if (isValidCell(row+r, col+c) && world[row+r][col+c] === "*")
                    ++count;
            }
        }
        return count;
    }

  return <></>;
}

export default Life;
