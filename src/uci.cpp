#include "uci.h"

#include "logger.h"
#include "perft.h"
#include "utility.h"

#ifdef _DEBUG
#include <iostream>
#endif

#ifndef VERSION
#define VERSION "0.0.1"
#endif

uci::uci( bool debug ) : debugMode( debug )
{
    functionMap[ "debug" ] = std::bind( &uci::command_debug, this, std::placeholders::_1 );
    functionMap[ "quit" ] = std::bind( &uci::command_quit, this, std::placeholders::_1 );
    functionMap[ "uci" ] = std::bind( &uci::command_uci, this, std::placeholders::_1 );

    functionMap[ "perft" ] = std::bind( &uci::command_perft, this, std::placeholders::_1 );
}

uci::~uci()
{
    // Nothing to do
}

bool uci::process( const std::string& input )
{
    auto [command, arguments] = utility::tokenize( input );

    // Ignore command if it is not recognised
    if ( functionMap[ command ] )
    {
#ifdef _DEBUG
        if ( arguments.empty() )
        {
            logger::debug( "Command: %s", command.c_str() );
        }
        else
        {
            logger::debug( "Command: %s [%s]", command.c_str(), arguments.c_str() );
        }
#endif

        return functionMap[ command ]( arguments );
    }
#ifdef _DEBUG
    else
    {
        logger::error( "Unknown command: %s", command.c_str() );
    }
#endif

    return true;
}

// Commands

bool uci::command_debug( const std::string& arguments )
{
    debugMode = arguments == "on";

#ifdef _DEBUG
    logger::debug( "Debug mode: %s", ( debugMode ? "on" : "off" ) );
#endif

    return true;
}

bool uci::command_quit( const std::string& arguments )
{
    return false;
}

bool uci::command_uci( const std::string& arguments )
{
    return true;
}

// Custom commands

bool uci::command_perft( const std::string& arguments )
{
    // Support the following syntaxes:
    // - perft [depth]         - perform a search using a depth and the standard start position
    // - perft [depth] [fen]   - perform a search using a depth and FEN string
    // - perft fen [fen]       - perform a search using a FEN string containing expected results
    // - perft file [filename] - perform searches read from a file as FEN strings containing expected results
    //
    // Any of the above commands may begin with '-divide' to indicate that the search should be divided

    if ( arguments.empty() )
    {
        // TODO consider using this to run a standard test suite of perfts, like Shredder does?
        logger::error( "perft requires at least one argument" );
        return true;
    }

    if( debugMode )
    {
        send_info_string( "perft with arguments: %s", arguments.c_str() );
    }

    return true;
}

// Static methods

std::string uci::name()
{
    return "coche";
}

std::string uci::author()
{
    return "Motivesoft";
}

std::string uci::description()
{
    return "A UCI chess engine";
}

std::string uci::version()
{
    return VERSION;
}