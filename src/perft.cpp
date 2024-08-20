#include "perft.h"

#include <fstream>
#include <iostream>

#include "fen.h"
#include "logger.h"
#include "utility.h"

void perft::run( const std::string& arguments )
{
    // Support the following syntaxes:
    // - perft [depth]         - perform a search using a depth and the standard start position
    // - perft [depth] [fen]   - perform a search using a depth and FEN string
    // - perft fen [fen]       - perform a search using a FEN string containing expected results
    // - perft file [filename] - perform searches read from a file as FEN strings containing expected results
    //
    // Any of the above commands may begin with '-divide' to indicate that the search should be divided

    // Work out the type of perft we're running

    std::string tokens( arguments );
    std::string type;
    std::tie( type, tokens ) = utility::tokenize( tokens );

    bool divide = false;
    if ( type == "-divide" )
    {
        divide = true;

        std::tie( type, tokens ) = utility::tokenize( tokens );
    }

    if ( utility::is_number( type ) )
    {
        // Depth, with or without FEN
        int depth = std::stoi( type );

        if ( tokens.empty() )
        {
            perft::runDepth( depth, divide );
        }
        else
        {
            perft::runDepth( depth, tokens, divide );
        }
    }
    else if ( type == "fen" )
    {
        if ( tokens.empty() )
        {
            logger::error( "Missing FEN" );
        }
        else
        {
            perft::runFen( tokens, divide );
        }
    }
    else if ( type == "file" )
    {
        if ( tokens.empty() )
        {
            logger::error( "Missing filename" );
        }
        else
        {
            perft::runFile( tokens, divide );
        }
    }
    else
    {
        logger::error( "Unknown perft command: %s", type.c_str() );
    }
}

void perft::runDepth( int depth, bool divide )
{
    runDepth( depth, fen::start_position, divide );
}

void perft::runDepth( int depth, const std::string& fen, bool divide )
{
    auto result = execute( depth, fen, divide );

    std::printf( "  Depth: %3d. Actual: %12d\n", depth, result );
}

void perft::runFen( const std::string& fen, bool divide )
{
    execute( fen, divide );
}

void perft::runFile( const std::string& filename, bool divide )
{
    std::ifstream file;

    file.open( filename );

    if ( !file.is_open() )
    {
        logger::error( "Could not open input file: %s", filename.c_str() );
        return;
    }

    std::string input;
    while ( std::getline( file, input ) )
    {
        input = utility::sanitize_string( input );

        // Allow blank lines and comments
        if ( input.empty() || input.starts_with( "#" ) )
        {
            continue;
        }

        // Run each line as a perft test
        execute( input, divide );
    }

    if ( file.is_open() )
    {
        file.close();
    }
}

unsigned int perft::execute( int depth, const std::string& fen, bool divide )
{
    // TODO
    logger::debug( "Not implemented: %d %s", depth, fen.c_str() );
    return 0;
}

void perft::execute( const std::string& fen, bool divide )
{
    // TODO
    logger::debug( "Not implemented: %s", fen.c_str() );
}
