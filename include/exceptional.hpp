/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-03-21
 *
 * This C++ header file contains the function prototypes for the
 * exception logger Exceptional, as well as definitions for all
 * templated methods.
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

namespace exceptional
{

class Logger
{
  public:
    // Default constructor
    Logger();

    // Parameterized constructor
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
    const std::string log_filename_ = "captains.log";
    std::ofstream log_stream_default_file_;
    std::ostream& log_stream_;

    size_t warning_count_ = 0;
    size_t error_count_ = 0;

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
};

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

// This private method logs the type of a thrown exception.
template <class T>
void Logger::LogExceptionValue( const T& except )
{
  log_stream_
    << "Exception value: "
    << except
    << std::endl;
}

}  // End of namespace exceptional
