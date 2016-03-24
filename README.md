# Exceptional

C++ lightweight exception logger.

## Example Output

    ________________________________________

    LOG CREATED AT 2016-03-18T00:01:09

    Warning:
    Logged at: 2016-03-18T00:01:09
    Type of exception value: std::out_of_range
    Exception message: Exception message for std::out_of_range.

    Error:
    Logged at: 2016-03-18T00:01:09
    Type of exception value: std::out_of_range
    Exception message: Exception message for std::out_of_range.

    Warnings logged: 1
    Errors logged:   1

## Instructions for Use

1. #include _exceptional.hpp_ into the files which require logging
2. Edit the exception logger class(es) declared at the end of _exceptional.hpp_ to your preferred usage
3. Call exceptional::*logger\_name*.LogWarning(value) or exceptional::*logger\_name*.LogError(value) with a thrown exception value  
(from any file with _exceptional.hpp_ included)
