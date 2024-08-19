// coche.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "utility.h"

int main( int argc, char** argv )
{
    std::cout << "Hello World!\n";

    std::string input;
    while ( true )
    {
        std::getline( std::cin, input );  // Read a line of input from stdin

        input = utility::sanitize_string( input );

        if ( input == "quit" )
        {
            break;  // Exit the loop if the input is "quit"
        }

        // Process the input (here we just print it)
        std::cout << "You entered: [" << input << "]" << std::endl;
    }

    std::cout << "Program terminated." << std::endl;
    return 0;

}
