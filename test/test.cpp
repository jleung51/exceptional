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
  {
    int i = 948;
    exceptional::logger_default_file.LogWarning(i);
    exceptional::logger_default_file.LogError(i);

    std::string s = "Example string here.";
    exceptional::logger_default_file.LogWarning(s);
    exceptional::logger_default_file.LogError(i);

    try
    {
      out_of_range_newline();
    }
    catch( const std::exception& e )
    {
      exceptional::logger_default_file.LogWarning(e);
    }

    try
    {
      out_of_range_newline();
    }
    catch( const std::exception& e )
    {
      exceptional::logger_default_file.LogError(e);
    }

    try
    {
      out_of_range_no_newline();
    }
    catch( const std::exception& e )
    {
      exceptional::logger_default_file.LogWarning(e);
    }

    try
    {
      out_of_range_no_newline();
    }
    catch( const std::exception& e )
    {
      exceptional::logger_default_file.LogError(e);
    }
  }
  std::cout << "Completed." << std::endl << std::endl;

  std::cout << std::endl;
  std::cout << "Testing output to example_file.log:" << std::endl;
  exceptional::logger_example_file.LogWarning(948);
  std::cout << "Completed." << std::endl << std::endl;

  std::cout << std::endl;
  std::cout << "Testing output to cout:" << std::endl;
  exceptional::logger_cout.LogWarning(948);
  std::cout << "Completed." << std::endl << std::endl;

  return 0;
}
