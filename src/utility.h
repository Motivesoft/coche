#pragma once

#include <string>

class utility
{
public:
    /**
     * Checks if a given string is a number.
     *
     * @param str The string to be checked.
     *
     * @return True if the string is a number, false otherwise.
     */
    static bool is_number( const std::string& str );

    /**
     * Removes leading and trailing spaces from a given string and replaces
     * multiple consecutive spaces with a single space.
     *
     * @param str The input string to be sanitized.
     *
     * @return The sanitized string.
     */
    static std::string sanitize_string( const std::string& str );
};