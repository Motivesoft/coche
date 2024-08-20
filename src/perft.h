#pragma once

#include <string>

class perft
{
public:
    /**
     * Run a perft test based on the provided arguments string
     * 
     * Support the following:
     * - perft [depth]         - perform a search using a depth and the standard start position
     * - perft [depth] [fen]   - perform a search using a depth and FEN string
     * - perft fen [fen]       - perform a search using a FEN string containing expected results
     * - perft file [filename] - perform searches read from a file as FEN strings containing expected results
     * 
     * Any of the above commands may begin with '-divide' to indicate that the search should be divided
     */
    static void run( const std::string& arguments );

private:
    static void runDepth( int depth, bool divide );

    static void runDepth( int depth, const std::string& fen, bool divide );

    static void runFen( const std::string& fen, bool divide );

    static void runFile( const std::string& filename, bool divide );

    static unsigned int execute( int depth, const std::string& fen, bool divide );

    static void execute( const std::string& fen, bool divide );
};
