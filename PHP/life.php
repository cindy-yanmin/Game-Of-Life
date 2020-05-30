<?php
define("SIDE", 10);

function getInitialWorld() {
    $world = array();
    $myfile = fopen("../input.txt", "r") or die("Unable to open file!");

    for ($r = 0; $r < SIDE; $r++) {
        $row = array();
        $char = fgetc($myfile);
        for ($c = 0; $c < SIDE; $c++) {
            if (!feof($myfile) && ($char == ' ' || $char == '*')) {
                array_push($row, $char);
                $char = fgetc($myfile);
            } else {
                array_push($row, ' ');
            }
        }
        array_push($world, $row);
    }
    fclose($myfile);

    return $world;
}

function printWorld($generationCount, $world) {
    echo "Generation $generationCount:<br>";
    foreach ( $world as $row ) {
        foreach ( $row as $col ) {
            if ($col == ' ') $col = ' -';
            echo $col; 
        }
        echo "<br>";
    }
    echo "========================<br>";
}

function isValidCell($row, $col) {
	return ($row >= 0 && $row < SIDE && $col >= 0 && $col < SIDE);
}

function neighborNum($row, $col, $world) {
	$count = 0;
	for ($r = -1; $r <= 1; $r++) {
		for ($c = -1; $c <= 1; $c++) {
			if ($r == 0 && $c == 0) continue;
			if (isValidCell($row + $r, $col + $c) && $world[$row + $r][$col + $c] == '*')
                $count++;
		}
	}
	return $count;
}

function nextGeneration($world) {
    $newWorld = array();
    
    for ($r = 0; $r < SIDE; $r++) {
        $row = array();
        for ($c = 0; $c < SIDE; $c++) {
            $aliveCount = neighborNum($r, $c, $world);
            if ($aliveCount < 2)
                array_push($row, ' ');
			else if ($aliveCount > 3 && $world[$r][$c] == '*')
                array_push($row, ' ');
			else if ($aliveCount == 3 && $world[$r][$c] == ' ')
                array_push($row, '*');
            else 
                array_push($row, $world[$r][$c]);
        }
        array_push($newWorld, $row);
    }

    return $newWorld;
}

$world = getInitialWorld(); 
for ($i = 0; $i <= $_POST['generation']; $i++) {
    printWorld($i, $world);
    $world = nextGeneration($world);
}

?>