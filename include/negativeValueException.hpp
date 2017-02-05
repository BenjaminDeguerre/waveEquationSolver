#ifndef NEGATIVE_VALUE
#define NEGATIVE_VALUE

/**
  * @file negativeValueException.hpp
  * @author Benjamin Deguerre
  * @version 0.1
  * @date 26 november 2016
  */

#include <exception>
#include <string>

/**
  * @class NegativeValueException
  *
  * Class for handling negative value in the weSolver
  * @see weSolver
  */
class NegativeValueException: public std::exception {

public:
  /**
    * @brief constructor
    * Constructor for the exception.
    *
    * @param msg The message to send through the error.
    * @param number An int to help define the type of the error
    */
  NegativeValueException(std::string const& msg="Error", int number = 1) throw(): msg(msg), number(number){}

  /**
    * @brief Accessor for the message send through the error.
    * @return char* the message.
    */
  virtual const char* what() const throw(){
    return msg.c_str();
  }

  /**
    * @brief Destructor of the class.
    */
  virtual ~NegativeValueException() throw(){}

  /**
    * Getter for the number
    * @return The number of the exception
    */
  int getNumber() const throw(){
    return number;
  }

  private:
    std::string msg;
    int number;
};

#endif
