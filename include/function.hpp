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
    * @param boundMin The std::vector<double> containing the minimum boundaries of the function.
    * @param boundMax The std::vector<double> containing the maximum boundaries of the function.
    * @param myFunction THe function to be used when calculating a result
    * @see getExactSolution(std::vector<double> entries);
    */
  Function(std::vector<double> boundMin, std::vector<double> boundMax, functionPointer myFunction);

  /**
    * Setter for the minimun boudaries of the function
    * @param boundMin A std::vector<double> containing all the minimum boudaries of the function
    */
  void setBoundMin(std::vector<double> boundMin);

  /**
    * Setter for the minimun boudaries of the function
    * @param boundMin A std::vector<double> containing all the maximum boudaries of the function
    */
  void setBoundMax(std::vector<double> boundMax);

  /**
    * Setter for the minimun boudaries of the function
    * @param function The function which will be used to calculate the values of f.
    */
  void setFunction(functionPointer function);


  /**
    * Getter for the minimun boudaries of the function
    * @return all the minimun boudaries of the function.
    */
  std::vector<double> getBoundMin();

  /**
    * Getter for the minimun boudaries of the function
    * @return all the maximum boudaries of the function.
    */
  std::vector<double> getBoundMax();

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
  std::vector<double> boundMin;
  std::vector<double> boundMax;
  functionPointer function;

};
#endif
