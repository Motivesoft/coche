#include "uci.h"

#include "utility.h"

#ifdef _DEBUG
#include <iostream>
#endif

#ifndef VERSION
#define VERSION "0.0.1"
#endif

uci::uci()
{
    functionMap[ "debug" ] = std::bind( &uci::command_debug, this, std::placeholders::_1 );
    functionMap[ "quit" ] = std::bind( &uci::command_quit, this, std::placeholders::_1 );
    functionMap[ "uci" ] = std::bind( &uci::command_uci, this, std::placeholders::_1 );

    debugMode = false;
}

uci::~uci()
{
    // Nothing to do
}

bool uci::process( const std::string& input )
{
    auto [command, arguments] = utility::tokenize( input );

#ifdef _DEBUG
    if ( arguments.empty() )
    {
        std::cerr << "Command: " << command << std::endl;
    }
    else
    {
        std::cerr << "Command: " << command << " - Arguments: " << arguments << std::endl;
    }
#endif

    // Ignore command if it is not recognised
    if ( functionMap[ command ] )
    {
        return functionMap[ command ]( arguments );
    }
#ifdef _DEBUG
    else
    {
        std::cerr << "Unknown command: " << command << std::endl;
    }
#endif

    return true;
}

// Commands

bool uci::command_debug( const std::string& arguments )
{
    debugMode = arguments == "on";

#ifdef _DEBUG
    std::cerr << "Debug mode: " << (debugMode ? "on" : "off") << std::endl;
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

// Broadcasts

void uci::send_info( const std::string& message )
{
    std::cout << "info string " << message << std::endl;
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