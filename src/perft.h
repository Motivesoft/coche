#pragma once

#include <string>

class perft
{
public:
    static void runDepth( int depth, bool divide );

    static void runDepth( int depth, const std::string& fen, bool divide );

    static void runFen( const std::string& fen, bool divide );

    static void runFile( const std::string& filename, bool divide );
};
