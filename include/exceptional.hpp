/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-03-24
 *
 * This C++ header file contains the definition of the exception logger
 * class Exceptional and its methods, as well as functions which can be
 * used to log exceptions with.
 *
 */

#pragma once

#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

// For type demangling when using g++
#ifdef __GNUG__
#include <cxxabi.h>
#endif

namespace  // Unnamed namespace for local functions/classes
{

// Local functions:

// This local function returns the current time as a string, formatted in
// the ISO 8601 standard.
std::string GetTime();

// This local function returns the current time as a string, formatted in
// the ISO 8601 standard.
std::string GetTime()
{
  time_t raw_time;
  time( &raw_time );

  char buffer[ sizeof("1970-01-01T00:00:00") ];
  strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", localtime(&raw_time));
  return buffer;
}

// Local classes:

class Logger
{
  public:
    // Default constructor
    Logger();

    // Parameterized constructor (string filename)
    Logger( const std::string filename );

    // Parameterized constructor (output stream)
    Logger( std::ostream& os );

    // Destructor
    ~Logger();

    // This public method logs a thrown std::exception as a warning.
    void LogWarning( const std::exception& except );

    // This public method logs a thrown value as a warning.
    template <class T>
    void LogWarning( const T& except );

    // This public method logs a thrown std::exception as an error.
    void LogError( const std::exception& except );

    // This public method logs a thrown value as an error.
    template <class T>
    void LogError( const T& except );

  private:
    const std::string log_filename_default_  = "captains.log";
    std::ofstream log_stream_default_file_;
    std::ostream& log_stream_;

    size_t warning_count_ = 0;
    size_t error_count_ = 0;

    static constexpr size_t kStackBacktraceLevel = 10;

    enum class SeverityLevel
    {
      kWarning,
      kError
    };

    // This private method logs the severity level of the exception.
    void LogSeverityLevel( SeverityLevel sl );

    // This private method logs the time of a thrown exception.
    void LogTime();

    // This private method logs the type of a thrown exception.
    template <class T>
    void LogExceptionType( const T& except );

    // This private method demangles the type of a thrown exception
    // if g++ is used.
    // An exception is thrown if:
    //   type_name is null (invalid_argument)
    std::string DemangleType( const char* type_name );

    // This private method logs the value of a thrown exception.
    template <class T>
    void LogExceptionValue( const T& except );

    // This private method logs the message of an exception from std.
    void LogExceptionMessage( const std::exception& except );

    // This private method backtraces and logs the call stack.
    // An exception is thrown if:
    //   backtrace_symbols returns an invalid set of function names (runtime_error)
    std::vector<std::string> GetStackBacktrace();
};

// Default constructor
Logger::Logger() :
  log_stream_default_file_{},
  log_stream_{log_stream_default_file_}
{
  // Opens the file in append mode
  // Executed on the ofstream object, not the ostream object
  log_stream_default_file_.open( log_filename_default_, std::ios::app );

  log_stream_
    << "________________________________________"
    << std::endl
    << std::endl
    << "LOG CREATED AT "
    << GetTime()
    << std::endl
    << std::endl;
}

// Parameterized constructor (string filename)
Logger::Logger( const std::string filename ) :
  log_stream_default_file_{},
  log_stream_{log_stream_default_file_}
{
  // Opens the file in append mode
  // Executed on the ofstream object, not the ostream object
  log_stream_default_file_.open( filename, std::ios::app );

  log_stream_
    << "________________________________________"
    << std::endl
    << std::endl
    << "LOG CREATED AT "
    << GetTime()
    << std::endl
    << std::endl;
}

// Parameterized constructor (output stream)
Logger::Logger( std::ostream& os ) :
  log_stream_{os}
{
  log_stream_
    << "________________________________________"
    << std::endl
    << std::endl
    << "LOG CREATED AT "
    << GetTime()
    << std::endl
    << std::endl;
}

// Destructor
Logger::~Logger()
{
  log_stream_
    << "Warnings logged: "
    << warning_count_
    << std::endl
    << "Errors logged:   "
    << error_count_
    << std::endl
    << std::endl;

  // Executed on the ofstream object, not the ostream object
  log_stream_default_file_.close();
}

// This public method logs a thrown std::exception as a warning.
void Logger::LogWarning( const std::exception& except )
{
  ++warning_count_;
  LogSeverityLevel( SeverityLevel::kWarning );
  LogTime();
  LogExceptionType( except );
  LogExceptionMessage( except );
  log_stream_ << std::endl;
}

// This public method logs a thrown value as a warning.
template <class T>
void Logger::LogWarning( const T& except )
{
  ++warning_count_;
  LogSeverityLevel( SeverityLevel::kWarning );
  LogTime();
  LogExceptionType( except );
  LogExceptionValue( except );
  log_stream_ << std::endl;
}

// This public method logs a thrown std::exception as an error.
void Logger::LogError( const std::exception& except )
{
  ++error_count_;
  LogSeverityLevel( SeverityLevel::kError );
  LogTime();
  LogExceptionType( except );
  LogExceptionMessage( except );
  log_stream_ << std::endl;
}

// This public method logs a thrown value as an error.
template <class T>
void Logger::LogError( const T& except )
{
  ++error_count_;
  LogSeverityLevel( SeverityLevel::kError );
  LogTime();
  LogExceptionType( except );
  LogExceptionValue( except );
  log_stream_ << std::endl;
}


// This private method logs the severity level of the exception.
void Logger::LogSeverityLevel( SeverityLevel sl )
{
  std::string output;
  switch( sl )
  {
    case SeverityLevel::kWarning:
      output = "Warning:";
      break;
    case SeverityLevel::kError:
      output = "Error:";
      break;
  }

  log_stream_
    << output
    << std::endl;
}

// This private method logs the time of a thrown exception.
void Logger::LogTime()
{
  log_stream_
    << "Logged at: "
    << GetTime()
    << std::endl;
}

// This private method logs the type of a thrown exception.
template <class T>
void Logger::LogExceptionType( const T& except )
{
  const char* type_name = typeid(except).name();
  if(type_name == nullptr)
  {
    log_stream_
      << "Type of exception value could not be detected."
      << std::endl;
  }
  else
  {
    try
    {
      log_stream_
        << "Type of exception value: "
        << DemangleType(type_name)
        << std::endl;
    }
    catch(...)
    {
    }
  }
}

#ifdef __GNUG__  // Using g++

// This private method demangles the type of a thrown exception
// if g++ is used.
// An exception is thrown if:
//   type_name is null (invalid_argument)
std::string Logger::DemangleType( const char* type_name )
{
  if( type_name == nullptr )
  {
    throw std::invalid_argument("Error: DemangleType() was given an invalid "\
      "(null) pointer.\n");
  }

  int status = -1;
  char* type_name_demangled =
    abi::__cxa_demangle( type_name, NULL, NULL, &status );

  if( status == 0 )
  {
    std::string demangled_string( type_name_demangled );
    free( type_name_demangled );
    return demangled_string;
  }
  else
  {
    return type_name;
  }
}

#else

// This private method demangles the type of a thrown exception
// if g++ is used.
std::string Logger::DemangleType( const char* type_name )
{
  return type_name;
}

#endif

// This private method logs the type of a thrown exception.
template <class T>
void Logger::LogExceptionValue( const T& except )
{
  log_stream_
    << "Exception value: "
    << except
    << std::endl;
}

// This private method logs the message of an exception from std.
void Logger::LogExceptionMessage( const std::exception& except )
{
  log_stream_
    << "Exception message: "
    << except.what();

  std::string s = except.what();
  if( s[s.length()-1] != '\n' )
  {
    log_stream_
      << std::endl;
  }
}

// This private method backtraces and logs the call stack.
// An exception is thrown if:
//   backtrace_symbols returns an invalid set of function names (runtime_error)
std::vector<std::string> Logger::GetStackBacktrace()
{
  throw std::logic_error("Error: GetStackBacktrace() has not yet "\
    "been implemented!\n");
}

}  // End of unnamed namespace (local to the file)

// Place loggers in here
namespace exceptional
{
  Logger logger_default_file;
  Logger logger_example_file("example_file.log");
  Logger logger_cout(std::cout);
}
