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

  private:
    const std::string log_filename_ = "log.txt";
    std::ofstream log_stream_;

    // This method logs a thrown value as a warning.
    template <class T>
    void LogWarning( const T& except );

    // This method logs a thrown value as an error.
    template <class T>
    void LogError( const T& except );

};

}  // End of namespace exceptional
