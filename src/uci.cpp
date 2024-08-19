#include "uci.h"

#ifdef _DEBUG
#include <iostream>
#endif

bool uci::process( const std::string& command )
{
    // Ignore command if it is not recognised
    if ( functionMap[ command ] )
    {
        return functionMap[ command ]( "arguments" );
    }
#ifdef _DEBUG
    else
    {
        std::cerr << "Unknown command: " << command << std::endl;
    }
#endif

    return true;
}

bool uci::command_quit( const std::string& arguments )
{
    return false;
}