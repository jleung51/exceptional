/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-03-04
 *
 * This C++ file contains the function implemenations for the
 * exception logger Exceptional.
 *
 */

#include <iostream>
#include <string>

#include "../include/exceptional.hpp"

namespace
{

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

}  // End of unnamed namespace (for local functions)

namespace exceptional
{

// Default constructor
Logger::Logger() :
  log_stream_default_file_{},
  log_stream_{log_stream_default_file_}
{
  // Opens the file in append mode
  // Executed on the ofstream object, not the ostream object
  log_stream_default_file_.open( log_filename_, std::ios::app );

  log_stream_
    << "________________________________________"
    << std::endl
    << std::endl
    << "LOG CREATED AT "
    << GetTime()
    << std::endl
    << std::endl;
}

// Parameterized constructor
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

}  // End of namespace exceptional
