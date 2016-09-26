# Magic-square
Constraint Programming project

This is the first project of constraint programming.
It consists in modeling and resolving the magic square problem using constraint programming algorithm.

## Problem

You are given a number n. The problem consists in finding values for the cells of a n*n grid so that the sum of each line, each column and each diagonal is equal to the same number : the magic number. Moreover, two cells can't have the same value.

In this case the magic number is known. It is equal to (n * (n²+1)) / 2.

[a 3*3 solved grid](https://upload.wikimedia.org/wikipedia/commons/e/e4/Magicsquareexample.svg)

## Solvers

Two solvers are available.

The first one is a complete solver which tests implicitly all the combinations of values for variables and works on constraints to prevent from exploring all the tree.
This solver has been thought to be reusable. It should be easy to implment other contraints and solve mulitple problems.

The second one is an incomplete solver which uses heuristics to find a solution. It is designed to be very fast but it is unable to proove that the problem is impossible.
This solver is more specific and hasn't been designed to be reusable, asuming an incomplete solver requires less code.
