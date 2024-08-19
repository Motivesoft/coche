// coche.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "uci.h"
#include "utility.h"

int main( int argc, char** argv )
{
    // Create an instance of the uci engine class
    uci uci;

    std::cout << uci::name() << " v" << uci::version() << " by " << uci::author() << std::endl;

    std::string input;
    while ( true )
    {
        std::getline( std::cin, input );  // Read a line of input from stdin

        input = utility::sanitize_string( input );

        if ( !uci.process( input ) )
        {
            // Exit the application if instructed
            break;
        }
    }

    return 0;
}
