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

}  // End of namespace exceptional
