import React from 'react';

function Life({input, setContent}) {
    var content = "";
    var world = getInitialWorld(input);

    for (var i = 0; i <= 10; ++i) {
        printWorld(i, world);
        world = oneGeneration(world);
    }

    function getInitialWorld(input) {
        var charIndex = 0;
        var world = [];

        for (var r = 0; r < 10; ++r) {
            world.push([]);
            for (var c = 0; c < 10; ++c) {
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
        for (var r = 0; r < 10; ++r) {
            for (var c = 0; c < 10; ++c) {
                content += world[r][c];
            }
            content += "\n";
        }
        content += "====================\n";
        setContent(content);
    }

    function oneGeneration(world) {
        var newWorld = [];
        for (var r = 0; r < 10; ++r) {
            newWorld.push([]);
            for (var c = 0; c < 10; ++c) {
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
        return (r >= 0 && r < 10 && c >=0 && c < 10);
    }

    function getAliveNeighbours (row, col, world) {
        var count = 0;
        for (var r = -1; r <= 1; ++r) {
            for (var c = -1; c <= 1; ++c) {
                if (r === 0  && c === 0) continue;
                if (isValidCell(row+r, col+c) &&
                    world[row+r][col+c] === "*"
                )
                    ++count;
            }
        }
        return count;
    }

  return <></>;
}

export default Life;
