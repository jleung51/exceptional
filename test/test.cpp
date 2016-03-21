/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-03-21
 *
 * This C++ file tests the functions of the exception logger Exceptional.
 *
 */

#include <exception>
#include <iostream>
#include <stdexcept>

#include "../include/exceptional.hpp"

exceptional::Logger log_file;

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
  std::cout << "Testing output to captains.log:" << std::endl;

  int i = 948;
  log_file.LogWarning(i);
  log_file.LogError(i);

  std::string s = "Example string here.";
  log_file.LogWarning(s);
  log_file.LogError(i);

  try
  {
    out_of_range_newline();
  }
  catch( const std::exception& e )
  {
    log_file.LogWarning(e);
  }

  try
  {
    out_of_range_newline();
  }
  catch( const std::exception& e )
  {
    log_file.LogError(e);
  }

  try
  {
    out_of_range_no_newline();
  }
  catch( const std::exception& e )
  {
    log_file.LogWarning(e);
  }

  try
  {
    out_of_range_no_newline();
  }
  catch( const std::exception& e )
  {
    log_file.LogError(e);
  }

  std::cout << "Completed." << std::endl << std::endl;


  std::cout << std::endl;
  std::cout << "Testing output to example_file.log:" << std::endl;

  exceptional::Logger log_example_file("example_file.log");
  log_example_file.LogWarning(948);

  std::cout << "Completed." << std::endl << std::endl;


  std::cout << std::endl;

  std::cout << "Testing output to cout:" << std::endl;
  exceptional::Logger log_cout(std::cout);
  log_cout.LogWarning(948);

  return 0;
}
