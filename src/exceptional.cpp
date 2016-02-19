/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-02-18
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
    log_stream_.open( log_filename_ );
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
        output = "Warning";
        break;
      case SeverityLevel::kError:
        output = "Error";
        break;
    }

    log_stream_
      << output
      << " caught."
      << std::endl;
  }

  // This private method logs the message of an exception from std.
  void Logger::LogExceptionMessage( const std::exception& except )
  {
    log_stream_
      << "Exception message: "
      << except.what()
      << std::endl;
  }

}  // End of namespace exceptional
