#include "function.hpp"
#include "outOfBoundException.hpp"
#include "incorrectSizeException.hpp"

#include <vector>

using namespace std;

Function::Function(){}

Function::Function(vector<double> boundMin, vector<double> boundMax, functionPointer myFunction) {
  this->boundMin = boundMin;
  this->boundMax = boundMax;
  this->function = myFunction;
}

void Function::setBoundMin(vector<double> boundMin){
  this->boundMin = boundMin;
}

void Function::setBoundMax(vector<double> boundMax){
  this->boundMax = boundMax;
}

void Function::setFunction(functionPointer myFunction){
  this->function = myFunction;
}

vector<double> Function::getBoundMin(){
  return this->boundMin;
}

vector<double> Function::getBoundMax(){
  return this->boundMax;
}

functionPointer Function::getFunction(){
  return this->function;
}

vector<double> Function::getExactSolution(vector<double> entries){
  unsigned int entriesSize = entries.size();

  if (entriesSize > boundMax.size() || entriesSize > boundMax.size()) {
    throw IncorrectSizeException("Entries vector too big");
  }
  for (unsigned int i = 0; i < entriesSize; i++) {
    if (entries[i] < boundMin[i]) {
      throw OutOfBoundException("One of the entries is under min bound", 2);
    } else if (entries[i] > boundMax[i]) {
      throw OutOfBoundException("One of the entries is above max bound", 3);
    }
  }
  return this->function(entries);
}
