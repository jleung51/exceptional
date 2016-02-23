/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-02-22
 *
 * This C++ file contains the function implemenations for the
 * exception logger Exceptional.
 *
 */

#include <iostream>
#include <string>

#include "../include/exceptional.hpp"

namespace exceptional
{
  // Constructor
  Logger::Logger()
  {
    // Opens the file in append mode
    log_stream_.open( log_filename_, std::ios::app );

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
    log_stream_.close();
  }

  // This public method logs a thrown std::exception as a warning.
  void Logger::LogWarning( const std::exception& except )
  {
    LogSeverityLevel( SeverityLevel::kWarning );
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

  // This private method returns the current time as a string.
  std::string Logger::GetTime()
  {
    time_t raw_time;
    time( &raw_time );

    char buffer[ sizeof("1970-01-01T00:00:00") ];
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", localtime(&raw_time));
    return buffer;
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
