// coche.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>

#include "logger.h"
#include "uci.h"
#include "utility.h"

int main( int argc, char** argv )
{
    std::istream* stream = &std::cin;
    std::ifstream file;

    // Process the command line arguments
    if ( argc > 1 )
    {
#if _DEBUG
        logger::debug( "Launched with command line arguments:" );

        for ( int i = 1; i < argc; i++ )
        {
            logger::debug( "%s", argv[ i ] );
        }
#endif

        for ( int i = 1; i < argc; i++ )
        {
            std::string arg( argv[ i ] );
            if ( arg == "-i" || arg == "--input" )
            {
                if ( i + 1 < argc )
                {
                    file.open( argv[ i + 1 ] );

                    if ( !file.is_open() )
                    {
                        logger::error( "Could not open input file: %s", argv[ i + 1 ] );
                        return 1;
                    }

                    i++;
                    stream = &file;
                }
            }
        }
    }
#if _DEBUG
    else
    {
        logger::debug( "Launched with no command line arguments" );
    }
#endif

    // Create an instance of the uci engine class
    uci uci;

    std::cout << uci::name() << " v" << uci::version() << " by " << uci::author() << std::endl;

    std::string input;
    while ( true )
    {
        // Read a line of input, trim it and process it
        if ( std::getline( *stream, input ) )
        {
            input = utility::sanitize_string( input );

            // Skip empty lines and comments (comments are not part of the UCI spec, but silently ignoring unrecognised input is)
            if ( input.empty() || input.starts_with( "#" ) )
            {
                continue;
            }

            if ( !uci.process( input ) )
            {
                // Exit the application if instructed
                break;
            }
        }
        else
        {
#if _DEBUG
            logger::debug( "End of input stream detected" );
#endif

            break;
        }

    }

    if ( file.is_open() )
    {
        file.close();
    }

#if _DEBUG
    logger::debug( "Exiting" );
#endif

    return 0;
}
