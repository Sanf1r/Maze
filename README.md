# Maze

Tested on MacOS Big Sur 11.6.6.

Made on November 8 2023 as part of my education in School 21 :)

## Introduction

This project is about mazes, including the basic algorithms of their handling, such as: generation, rendering, solving.

## Information

A maze with "thin walls" is a table of _n_ rows by _m_ columns size. There may be "walls" between the cells of a table. The table as a whole is also surrounded by "walls".

The solution to a maze is the shortest path from a given starting point (table cell) to the ending one.

When traversing a maze, you can move to neighboring cells that are not separated by a "wall" from the current cell and that are on the top, bottom, right or left.
A route is considered the shortest if it passes through the smallest number of cells.

## Maze description

The maze can be stored in a file as a number of rows and columns, as well as two matrices containing the positions of vertical and horizontal walls respectively.

The first matrix shows the wall to the right of each cell, and the second - the wall at the bottom.

An example of such a file:
```
4 4
0 0 0 1
1 0 1 1
0 1 0 1
0 0 0 1

1 0 1 0
0 0 1 0
1 1 0 1
1 1 1 1
```

## Usage

- Load button - load the maze from a file.
- Save button - save the maze in the file.
- Generate - generate a perfect maze according to Eller's algorithm.
- To solve the maze use LMB to sets the starting and ending points.
- RMB removes path from the maze.

