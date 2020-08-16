#include "function.hpp"

#include <vector>

#include "incorrectSizeException.hpp"
#include "outOfBoundException.hpp"

using namespace std;

Function::Function() {}

Function::Function(vector<double> boundMin, vector<double> boundMax,
                   functionPointer myFunction) {
  this->boundMin = boundMin;
  this->boundMax = boundMax;
  this->function = myFunction;
}

void Function::setBoundMin(vector<double> boundMin) {
  this->boundMin = boundMin;
}

void Function::setBoundMax(vector<double> boundMax) {
  this->boundMax = boundMax;
}

void Function::setFunction(functionPointer myFunction) {
  this->function = myFunction;
}

vector<double> Function::getBoundMin() { return this->boundMin; }

vector<double> Function::getBoundMax() { return this->boundMax; }

functionPointer Function::getFunction() { return this->function; }

vector<double> Function::getExactSolution(vector<double> entries) {
  return this->function(entries);
}
