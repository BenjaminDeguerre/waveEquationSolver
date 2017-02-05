#ifndef INCORRECT_SIZE
#define INCORRECT_SIZE

/**
  * @file incorrectSizeException.hpp
  * @author Benjamin Deguerre
  * @version 0.1
  * @date 26 november 2016
  */

#include <exception>
#include <iostream>

/**
  * @class UncorrectSizeException
  *
  * Class for handling incorrect size exception.
  */
class IncorrectSizeException: public std::exception
{

public:
  /**
    * @brief constructor
    * Constructor for the exception.
    *
    * @param msg The message to send through the error.
    */
  IncorrectSizeException(std::string const& msg="Error") throw(): msg(msg){}

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
  virtual ~IncorrectSizeException() throw(){}

  private:
    std::string msg;
};

#endif
