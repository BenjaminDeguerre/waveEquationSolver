#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>

#include "weSolver.hpp"
#include "function.hpp"

#include "../gnuplot-iostream/gnuplot-iostream.h"

using namespace std;

vector<double> functionTest (vector<double> entries) {
  vector<double> output(1);
  double sign = entries[0] - 1.75*entries[1];
  output[0] = 0.5 * ( (( sign > 0) - (sign < 0)) + 1);
  return output;
}


int main () {

  Gnuplot gp;
  vector<boost::tuple<double, double> > initialPoints, estimatedValue, exactValue;

  int grid, functionNumber, scheme;
  double deltaX, deltaT, t, u;

  WESolver solver;
  Function function;
  vector<double> initial, sol, exact, boundMin(1), boundMax(1),temp(1);

  //Initializing boundaries
  boundMin[0] = -50;
  boundMax[0] = 50;

  function = Function(boundMin,boundMax,functionTest);

  cout << "Please enter the number of point in the grid : ";
  cin >> grid ;

  deltaX =  (boundMax[0] - boundMin[0]) / (grid - 1.0);

  cout << "Please enter the value of delta t :";
  cin >> deltaT;

  cout << "Please enter the value of u :";
  cin >> u;

  cout << "Please enter the value of t :";
  cin >> t;

  cout << "Please enter the number of the scheme 1/2/3/4 (upwind Explicit/Implicit/Lax-Wendroff/Richtmyer):";
  cin >> scheme;

  solver = WESolver(deltaX,deltaT,u);
  initial = vector<double>(grid);
  exact = vector<double>(grid);

  initial[0] = 0;
  exact[0] = 0;
  initialPoints.push_back(boost::make_tuple(-50, initial[0]));
  exactValue.push_back(boost::make_tuple(-50, exact[0]));
  for (int i = 1 ; i < grid ; i++){
    exact[i] = (function.getExactSolution(vector<double> {i*deltaX+boundMin[0], t}))[0];
    initial[i] = (function.getExactSolution(vector<double> {i*deltaX+boundMin[0], 0}))[0];
    initialPoints.push_back(boost::make_tuple(-50 +  i * deltaX, initial[i]));
    exactValue.push_back(boost::make_tuple(-50 +  i * deltaX, exact[i]));
  }
  initial[grid-1] = 1;
  exact[grid-1] = 1;
  initialPoints.push_back(boost::make_tuple(-50 +  (grid -1) * deltaX, initial[grid-1]));
  exactValue.push_back(boost::make_tuple(-50 +  (grid -1) * deltaX, exact[grid-1]));


  sol = solver.resolve(initial,t,scheme);

  for (int i = 0 ; i < grid  ; i++){
    estimatedValue.push_back(boost::make_tuple(-50 +  i * deltaX, sol[i]));
    //cout << sol[399-i] << " -- ";
    // cout << ((initial[398] * deltaX) - u * initial[399] * deltaX/2)/(deltaX - u * deltaX/2) << " -- ";
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
