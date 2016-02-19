/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-02-18
 *
 * This C++ header file contains the function prototypes for the
 * exception logger Exceptional.
 *
 */

#pragma once

#include <fstream>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>

namespace exceptional
{

class Logger
{
  public:
    // Constructor
    Logger();

    // Destructor
    ~Logger();

    // This public method logs a thrown std::exception as a warning.
    void LogWarning( const std::exception& except );

    // This public method logs a thrown value as a warning.
    template <class T>
    void LogWarning( const T& except );
/*
    // This public method logs a thrown value as an error.
    template <class T>
    void LogError( const T& except );
*/
  private:
    const std::string log_filename_ = "log.txt";
    std::ofstream log_stream_;

    enum class SeverityLevel
    {
      kWarning,
      kError
    };

    // This private method logs the severity level of the exception.
    void LogSeverityLevel( SeverityLevel sl );

    // This private method logs the type of a thrown exception.
    template <class T>
    void LogExceptionType( const T& except );

    // This private method logs the value of a thrown exception.
    template <class T>
    void LogExceptionValue( const T& except );

    // This private method logs the message of an exception from std.
    void LogExceptionMessage( const std::exception& except );

};

}  // End of namespace exceptional
