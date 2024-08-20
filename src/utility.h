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

    /**
     * Tokenizes a given string by splitting it into two substrings using the first occurrence of a space character.
     *
     * @param str The string to be tokenized.
     *
     * @return A pair of strings containing the first substring before the first space and the second substring after the first space. If the input string does not contain a space, the second string in the pair will be empty.
     *
     * @throws None
     */
    static std::pair<std::string,std::string> tokenize( const std::string& str );

    /**
     * Extracts the filename element from a given path, including extension if present.
     *
     * @param path The path.
     *
     * @return The filename extracted from the path.
     *
     * @throws None
     */
    static std::string filename( const std::string& path );
};