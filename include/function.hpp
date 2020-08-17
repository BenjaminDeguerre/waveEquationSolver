#ifndef FUNCTION_HEADER
#define FUNCTION_HEADER

#include <vector>
/**
  * @file function.hpp
  * @author Benjamin Deguerre
  * @version 0.1
  * @date 26 november 2016
  */

/**
  * @typedef functionPointer A pointer to a function that has a std::vector<double> as input and output
  */
typedef std::vector<double> (* functionPointer)(std::vector<double> entries);

/**
  * @class Function
  *
  * The class which describe a function.
  */
class Function {

public:

  /**
    * @brief Simple constructor of a function.
    *
    * An empty object is created
    */
  Function();

  /**
    * @brief Constructor for a Function
    *
    * @param myFunction THe function to be used when calculating a result
    * @see getExactSolution(std::vector<double> entries);
    */
  Function(functionPointer myFunction);

  /**
    * Setter for the minimun boudaries of the function
    * @param function The function which will be used to calculate the values of f.
    */
  void setFunction(functionPointer function);

  /**
    * Getter for the minimun boudaries of the function
    * @return the function used to calculate the values of y
    */
  functionPointer getFunction();

  /**
    * Allow the user to calculate the exact value of the function for a given set of entries
    * @param entries The std::vector<double> containing all the entry values.
    * @throw IncorrectSizeException If the entries std::vector<double> size is bigger than one of the boundaries std::vector<double> size.
    * @throw OutOfBoundException If one of the value of the entries std::vector<double> is outside of the boundaries
    */
  std::vector<double> getExactSolution(std::vector<double> entries);

private:
  functionPointer function;

};
#endif
