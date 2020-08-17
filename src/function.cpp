#include "function.hpp"

#include <vector>

Function::Function() {}

Function::Function(functionPointer myFunction) { this->function = myFunction; }

void Function::setFunction(functionPointer myFunction) {
  this->function = myFunction;
}

functionPointer Function::getFunction() { return this->function; }

std::vector<double> Function::getExactSolution(std::vector<double> entries) {
  return this->function(entries);
}
