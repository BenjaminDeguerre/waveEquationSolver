#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#include <iomanip>
#include <iostream>

#include "../gnuplot-iostream/gnuplot-iostream.h"
#include "function.hpp"
#include "weSolver.hpp"

using namespace std;

vector<double> functionTest(vector<double> entries) {
  vector<double> output(1);
  double sign = entries[0] - 1.75 * entries[1];
  output[0] = 0.5 * (((sign > 0) - (sign < 0)) + 1);
  return output;
}

int main() {
  Gnuplot gp;
  vector<boost::tuple<double, double> > initialPoints, estimatedValue,
      exactValue;

  int grid, functionNumber, scheme;
  double deltaX, deltaT, t, u, exact, boundMinVal, boundMaxVal;

  WESolver solver;
  Function function;
  vector<double> initial, sol, boundMin(1), boundMax(1);

  // Initializing boundaries
  boundMin[0] = -50;
  boundMax[0] = 50;

  function = Function(boundMin, boundMax, functionTest);

  // Initializing the different solver parameters.
  grid = 100;
  deltaX = (boundMax[0] - boundMin[0]) / (grid - 1.0);
  deltaT = 0.1;
  u = 1.75;
  t = 10;
  boundMinVal = 0;
  boundMaxVal = 1;

  // Enter the values manually
  // cout << "Please enter the number of point in the grid : ";
  // cin >> grid;
  // cout << "Please enter the value of delta t :";
  // cin >> deltaT;
  // cout << "Please enter the value of u :";
  // cin >> u;
  // cout << "Please enter the value of t :";
  // cin >> t;

  // Selection of the solving scheme
  cout << "Please enter the number of the scheme 1/2/3/4 (upwind "
          "Explicit/Implicit/Lax-Wendroff/Richtmyer):";
  cin >> scheme;

  // Setting the solver
  solver = WESolver(deltaX, deltaT, u);

  // Vector holding the initial values of the function we wish to estimate
  initial = vector<double>(grid);

  // The first and last values are preset and fixed
  initial[0] = boundMinVal;
  initial[grid - 1] = boundMaxVal;

  // These are used for display
  initialPoints.push_back(boost::make_tuple(-50, boundMinVal));
  exactValue.push_back(boost::make_tuple(-50, boundMinVal));

  for (int i = 1; i < grid; i++) {
    exact = (function.getExactSolution(
        vector<double>{i * deltaX + boundMin[0], t}))[0];
    initial[i] = (function.getExactSolution(
        vector<double>{i * deltaX + boundMin[0], 0}))[0];

    initialPoints.push_back(boost::make_tuple(-50 + i * deltaX, initial[i]));
    exactValue.push_back(boost::make_tuple(-50 + i * deltaX, exact));
  }

  // Pushing the last values
  initialPoints.push_back(
      boost::make_tuple(-50 + (grid - 1) * deltaX, boundMaxVal));
  exactValue.push_back(
      boost::make_tuple(-50 + (grid - 1) * deltaX, boundMaxVal));

  sol = solver.resolve(initial, t, scheme);

  for (int i = 0; i < grid; i++) {
    estimatedValue.push_back(boost::make_tuple(-50 + i * deltaX, sol[i]));
  }

  gp << "set xlabel 't'\n";
  gp << "set ylabel 'y'\n";
  gp << "set xrange [-50:50]\nset yrange [-1:2]\n";
  gp << "plot '-' with line title 't = 0s', ";
  gp << "'-' with line title 't = 5s' lt -1, ";
  gp << "'-' with line title 't = exact'\n ";

  gp.send1d(initialPoints);
  gp.send1d(estimatedValue);
  gp.send1d(exactValue);

  return 0;
}
