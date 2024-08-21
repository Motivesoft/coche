#include "utility.h"

#include <chrono>
#include <iomanip>
#include <sstream>

bool utility::is_number( const std::string& str )
{
    std::string::const_iterator it = str.begin();
    while ( it != str.end() && std::isdigit( *it ) )
    {
        ++it;
    }

    return !str.empty() && it == str.end();
}

std::string utility::sanitize_string( const std::string& str )
{
    const std::string doubleSpace = "  ";
    const std::string space = " ";

    // Find first non-space character
    size_t first = str.find_first_not_of( ' ' );
    if ( std::string::npos == first )
    {
        // Empty string
        return std::string();
    }

    // Find last non-space character
    size_t last = str.find_last_not_of( ' ' );

    // Extract the trimmed portion of the string
    std::string trimmed = str.substr( first, ( last - first + 1 ) );

    // Now replace multiple spaces with single spaces within the string
    size_t position = trimmed.find( doubleSpace );
    while ( position != std::string::npos )
    {
        trimmed.replace( position, doubleSpace.length(), space );
        position = trimmed.find( doubleSpace, position );
    }

    return trimmed;
}

std::pair<std::string, std::string> utility::tokenize( const std::string& str )
{
    size_t first = str.find_first_of( ' ' );
    if ( std::string::npos == first )
    {
        // No second token
        return std::make_pair( str, std::string() );
    }

    return std::make_pair( str.substr( 0, first ), str.substr( first + 1 ) );
}

std::pair<std::string, std::string> utility::split( const std::string& str, char separator )
{
    size_t pos = str.find( separator );

    if ( pos == std::string::npos )
    {
        return std::make_pair( str, std::string() );
    }

    // Trim the strings that we return
    return std::make_pair( utility::sanitize_string( str.substr( 0, pos ) ), 
                           utility::sanitize_string( str.substr( pos + 1 ) ) );
}

std::string utility::filename( const std::string& path )
{
    size_t first = path.find_last_of( '/' );
    if ( std::string::npos == first )
    {
        first = path.find_last_of( '\\' );
    }

    if ( std::string::npos != first )
    {
        return path.substr( first + 1 );
    }

    return path;
}
