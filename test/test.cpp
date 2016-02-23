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

// This function throws an std::out_of_range error with a newline at the end.
void out_of_range_newline()
{
  throw std::out_of_range("Exception message for std::out_of_range.\n");
}

// This function throws an std::out_of_range error without a newline.
void out_of_range_no_newline()
{
  throw std::out_of_range("Exception message for std::out_of_range.");
}

}  // End of unnamed namespace (for local functions)

int main()
{
  int i = 948;
  log.LogWarning(i);
  log.LogError(i);

  std::string s = "Example string here.";
  log.LogWarning(s);
  log.LogError(i);

  try
  {
    out_of_range_newline();
  }
  catch( const std::exception& e )
  {
    log.LogWarning(e);
  }

  try
  {
    out_of_range_newline();
  }
  catch( const std::exception& e )
  {
    log.LogError(e);
  }

  try
  {
    out_of_range_no_newline();
  }
  catch( const std::exception& e )
  {
    log.LogWarning(e);
  }

  try
  {
    out_of_range_no_newline();
  }
  catch( const std::exception& e )
  {
    log.LogError(e);
  }

  std::cout << "Test output written to log.txt." << std::endl;
  return 0;
}
