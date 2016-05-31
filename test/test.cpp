/*
 *
 * This C++ file tests the functions of the exception logger Exceptional.
 *
 */

#include <exception>
#include <iostream>
#include <stdexcept>

#include "../include/exceptional.hpp"

// These functions, if placed into the unnamed namespace, do not appear
// in the stack backtrace.
namespace Private
{

// This function throws an std::out_of_range error without a newline.
void out_of_range_no_newline();

// This function throws an std::out_of_range error with a newline at the end.
void out_of_range_newline();

// This function throws an std::out_of_range error with a newline at the end.
void out_of_range_newline();

// This function throws an std::out_of_range error without a newline.
void out_of_range_no_newline();

// This local function calls func2(), and is for testing the stack backtrace.
void func1(int i);

// This local function calls func3(), and is for testing the stack backtrace.
void func2(char c);

// This local function logs an std::string error to std::cout, and is
// for testing the stack backtrace.
int func3(std::string s);

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

// This local function calls func2(), and is for testing the stack backtrace.
void func1(int i)
{
  if(i){}
  func2('a');
}

// This local function calls func3(), and is for testing the stack backtrace.
void func2(char c)
{
  if(c){}
  func3("word");
}

// This local function logs an std::string error to std::cout, and is
// for testing the stack backtrace.
int func3(std::string s)
{
  if(s[0]){}
  exceptional::logger_cout.LogError("Logging error from nested function call");
  return 0;
}

}  // End of namespace Private

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
      Private::out_of_range_newline();
    }
    catch( const std::exception& e )
    {
      exceptional::logger_default_file.LogWarning(e);
    }

    try
    {
      Private::out_of_range_newline();
    }
    catch( const std::exception& e )
    {
      exceptional::logger_default_file.LogError(e);
    }

    try
    {
      Private::out_of_range_no_newline();
    }
    catch( const std::exception& e )
    {
      exceptional::logger_default_file.LogWarning(e);
    }

    try
    {
      Private::out_of_range_no_newline();
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

  std::cout << std::endl;
  std::cout << "Testing a stack backtrace from within nested function calls "
    << "to cout:" << std::endl;
  Private::func1(5);
  std::cout << "Completed." << std::endl << std::endl;

  return 0;
}
