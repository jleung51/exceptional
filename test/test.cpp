/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-02-18
 *
 * This C++ file tests the functions of the exception logger Exceptional.
 *
 */

#include <exception>
#include <iostream>
#include <stdexcept>

#include "../include/exceptional.hpp"

exceptional::Logger log;

namespace
{

// This function throws an std::out_of_range error.
void out_of_range()
{
  throw std::out_of_range("Exception message for std::out_of_range.");
}

}  // End of unnamed namespace (for local functions)

int main()
{
  int i = 948;
  log.LogWarning(i);

  std::string s = "Example string here.";
  log.LogWarning(s);

  try
  {
    out_of_range();
  }
  catch( const std::exception& e )
  {
    log.LogWarning(e);
  }

  std::cout << "Test output written to log.txt." << std::endl;
  return 0;
}
