# waveEquationSolver

This project was done at Cranfield university. The aim of this assignment was to create a wave equation solver in C++/object oriented style. The pdf of the assignment is provided [here](assignment/assignment.pdf).

## Compiling the project

This project makes usage of gnuplot-iostream to display the results of the solver.

```bash
## Getting the gnuplot-iostream
git clone https://github.com/dstahlke/gnuplot-iostream.git
cd gnuplot-iostream
git checkout 95f95
cd ..

cmake CMakeLists.txt
make

# Solving the demo function
./build/bin/weSolver
```
